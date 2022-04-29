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

#ifndef Q_QUICK3D_GEOMETRY_P_H
#define Q_QUICK3D_GEOMETRY_P_H

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

#include <QtQuick3D/qquick3dgeometry.h>
#include <QtQuick3D/private/qquick3dobject_p.h>
#include <QtQuick3DRuntimeRender/private/qssgrendergeometry_p.h>

#include <QtGui/qvector3d.h>

QT_BEGIN_NAMESPACE

class Q_QUICK3D_PRIVATE_EXPORT QQuick3DGeometryPrivate : public QQuick3DObjectPrivate
{
public:
    QQuick3DGeometryPrivate();

    struct Subset {
        QString name;
        QVector3D boundsMin;
        QVector3D boundsMax;
        quint32 offset;
        quint32 count;
    };

    static const int MAX_ATTRIBUTE_COUNT = 16;
    QByteArray m_vertexBuffer;
    QByteArray m_indexBuffer;
    QQuick3DGeometry::Attribute m_attributes[MAX_ATTRIBUTE_COUNT];
    QVector<Subset> m_subsets;
    int m_attributeCount = 0;
    QQuick3DGeometry::PrimitiveType m_primitiveType = QQuick3DGeometry::PrimitiveType::Triangles;
    QVector3D m_min;
    QVector3D m_max;
    int m_stride = 0;
    bool m_geometryChanged = true;
    bool m_geometryBoundsChanged = true;

    static QQuick3DGeometry::Attribute::Semantic semanticFromName(const QByteArray &name);
    static QQuick3DGeometry::Attribute::ComponentType toComponentType(QSSGMesh::Mesh::ComponentType componentType);
};

QT_END_NAMESPACE

#endif
