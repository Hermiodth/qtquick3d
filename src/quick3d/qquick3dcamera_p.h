/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick 3D.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#ifndef QSSGCAMERA_H
#define QSSGCAMERA_H

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

#include <QtQuick3D/private/qquick3dnode_p.h>

QT_BEGIN_NAMESPACE

struct QSSGRenderCamera;
class Q_QUICK3D_EXPORT QQuick3DCamera : public QQuick3DNode
{
    Q_OBJECT
    Q_PROPERTY(bool frustumCullingEnabled READ frustumCullingEnabled WRITE setFrustumCullingEnabled NOTIFY frustumCullingEnabledChanged)
    QML_NAMED_ELEMENT(Camera)
    QML_UNCREATABLE("Camera is Abstract")
public:
    Q_INVOKABLE QVector3D mapToViewport(const QVector3D &scenePos) const;
    Q_INVOKABLE QVector3D mapFromViewport(const QVector3D &viewportPos) const;
    QVector3D mapToViewport(const QVector3D &scenePos,
                            qreal width,
                            qreal height);
    QVector3D mapFromViewport(const QVector3D &viewportPos,
                              qreal width,
                              qreal height);

    Q_INVOKABLE void lookAt(const QVector3D &scenePos);
    Q_INVOKABLE void lookAt(QQuick3DNode *node);

    // It will be used only after the scene was drawn.
    // It means that the spatialNode of this camera already was created.
    void updateGlobalVariables(const QRectF &inViewport);

    bool frustumCullingEnabled() const;

public Q_SLOTS:
    void setFrustumCullingEnabled(bool frustumCullingEnabled);

Q_SIGNALS:
    void frustumCullingEnabledChanged();

protected:
    explicit QQuick3DCamera(QQuick3DNodePrivate &dd, QQuick3DNode *parent = nullptr);

    QSSGRenderGraphObject *updateSpatialNode(QSSGRenderGraphObject *node) override;

private:
    bool m_frustumCullingEnabled = false;
};

QT_END_NAMESPACE

#endif // QSSGCAMERA_H
