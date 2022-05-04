/****************************************************************************
**
** Copyright (C) 2008-2012 NVIDIA Corporation.
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick 3D.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSSG_RENDER_NODE_H
#define QSSG_RENDER_NODE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtQuick3DRuntimeRender/private/qssgrendergraphobject_p.h>

#include <QtQuick3DUtils/private/qssgbounds3_p.h>
#include <QtQuick3DUtils/private/qssginvasivelinkedlist_p.h>

#include <QtGui/QMatrix4x4>
#include <QtGui/QVector3D>

QT_BEGIN_NAMESPACE

struct QSSGRenderModel;
struct QSSGRenderLight;
struct QSSGRenderCamera;
struct QSSGRenderText;
struct QSSGRenderNode;
class QSSGBufferManager;

struct Q_QUICK3DRUNTIMERENDER_EXPORT QSSGRenderNode : public QSSGRenderGraphObject
{
    enum class LocalState : quint8
    {
        Active = 1 << 0,
        Pickable = 1 << 1
    };

    enum class GlobalState : quint8
    {
        Active = 1 << 2,
        Pickable = 1 << 3
    };

    enum class DirtyFlag : quint32
    {
        TransformDirty = 1 << 4,
        OpacityDirty = 1 << 5,
        ActiveDirty = 1 << 6,
        PickableDirty = 1 << 7,
        SubNodeDirty = 1 << 8, // Sub-nodes should set/unest this if they "extend" the dirty flags provided by the node

        GlobalValuesDirty = TransformDirty | OpacityDirty | ActiveDirty | PickableDirty,
        DirtyMask = GlobalValuesDirty | SubNodeDirty
    };
    using FlagT = std::underlying_type_t<DirtyFlag>;

    static constexpr QVector3D initScale { 1.0f, 1.0f, 1.0f };

    // changing any one of these means you have to
    // set this object dirty
    QVector3D pivot;
    int staticFlags = 0;

    // This only sets dirty, not transform dirty
    // Opacity of 1 means opaque, opacity of zero means transparent.
    float localOpacity = 1.0f;

    // Nodes are initially dirty, but not active!
    FlagT flags { FlagT(DirtyFlag::GlobalValuesDirty) };
    // These end up right handed
    QMatrix4x4 localTransform;
    QMatrix4x4 globalTransform;
    QMatrix4x4 localInstanceTransform;
    QMatrix4x4 globalInstanceTransform;
    float globalOpacity = 1.0f;

    // node graph members.
    QSSGRenderNode *parent = nullptr;
    QSSGRenderNode *nextSibling = nullptr;
    QSSGRenderNode *previousSibling = nullptr;
    QSSGRenderNode *instanceRoot = nullptr;
    // Property maintained solely by the render system.
    // Depth-first-search index assigned and maintained by render system.
    quint32 dfsIndex = 0;

    using ChildList = QSSGInvasiveLinkedList<QSSGRenderNode, &QSSGRenderNode::previousSibling, &QSSGRenderNode::nextSibling>;
    ChildList children;

    QSSGRenderNode();
    explicit QSSGRenderNode(Type type);
    ~QSSGRenderNode() override;

    // Sets this object dirty and walks down the graph setting all
    // children who are not dirty to be dirty.
    void markDirty(DirtyFlag dirtyFlag);
    void clearDirty(DirtyFlag dirtyFlag);
    [[nodiscard]] inline constexpr bool isDirty(DirtyFlag dirtyFlag = DirtyFlag::DirtyMask) const { return ((flags & FlagT(dirtyFlag)) != 0); }
    void setState(LocalState state, bool on = true);
    [[nodiscard]] inline constexpr bool getLocalState(LocalState stateFlag) const { return ((flags & FlagT(stateFlag)) != 0); }
    [[nodiscard]] inline constexpr bool getGlobalState(GlobalState stateFlag) const { return ((flags & FlagT(stateFlag)) != 0); }

    void addChild(QSSGRenderNode &inChild);
    void removeChild(QSSGRenderNode &inChild);

    // Remove this node from the graph.
    // It is no longer the the parent's child lists
    // and all of its children no longer have a parent
    // finally they are no longer siblings of each other.
    void removeFromGraph();

    // Calculate global transform and opacity
    // Walks up the graph ensure all parents are not dirty so they have
    // valid global transforms.
    bool calculateGlobalVariables();

    // Calculates a tranform matrix based on the position, scale, pivot and rotation arguments.
    // NOTE!!!: This function does not update or mark any nodes as dirty, if the returned matrix is set on a node then
    // markDirty, calculateGlobalVariables etc. needs to be called as needed!
    [[nodiscard]] static QMatrix4x4 calculateTransformMatrix(QVector3D position, QVector3D scale, QVector3D pivot, QQuaternion rotation);

    // Get the bounds of us and our children in our local space.
    QSSGBounds3 getBounds(const QSSGRef<QSSGBufferManager> &inManager,
                            bool inIncludeChildren = true) const;
    QSSGBounds3 getChildBounds(const QSSGRef<QSSGBufferManager> &inManager) const;
    // Assumes CalculateGlobalVariables has already been called.
    QVector3D getGlobalPos() const;
    QVector3D getGlobalPivot() const;
    // Pulls the 3rd column out of the global transform.
    QVector3D getDirection() const;
    // Multiplies (0,0,-1) by the inverse transpose of the upper 3x3 of the global transform.
    // This is correct w/r/t to scaling and which the above getDirection is not.
    QVector3D getScalingCorrectDirection() const;

    // outMVP and outNormalMatrix are returned ready to upload to openGL, meaning they are
    // row-major.
    void calculateMVPAndNormalMatrix(const QMatrix4x4 &inViewProjection, QMatrix4x4 &outMVP, QMatrix3x3 &outNormalMatrix) const;

    // This should be in a utility file somewhere
    QMatrix3x3 calculateNormalMatrix() const;
};

QT_END_NAMESPACE

#endif
