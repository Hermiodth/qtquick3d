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

#ifndef QSSGORTHOGRAPHICCAMERA_H
#define QSSGORTHOGRAPHICCAMERA_H

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

#include <QtQuick3D/private/qquick3dcamera_p.h>

QT_BEGIN_NAMESPACE

struct QSSGRenderCamera;
class Q_QUICK3D_EXPORT QQuick3DOrthographicCamera : public QQuick3DCamera
{
    Q_OBJECT
    Q_PROPERTY(float clipNear READ clipNear WRITE setClipNear NOTIFY clipNearChanged)
    Q_PROPERTY(float clipFar READ clipFar WRITE setClipFar NOTIFY clipFarChanged)
    Q_PROPERTY(float horizontalMagnification READ horizontalMagnification WRITE setHorizontalMagnification NOTIFY horizontalMagnificationChanged)
    Q_PROPERTY(float verticalMagnification READ verticalMagnification WRITE setVerticalMagnification NOTIFY verticalMagnificationChanged)

    QML_NAMED_ELEMENT(OrthographicCamera)

public:
    explicit QQuick3DOrthographicCamera(QQuick3DNode *parent = nullptr);

    float clipNear() const;
    float clipFar() const;
    float horizontalMagnification() const;
    float verticalMagnification() const;

public Q_SLOTS:
    void setClipNear(float clipNear);
    void setClipFar(float clipFar);
    void setHorizontalMagnification(float horizontalMagnification);
    void setVerticalMagnification(float horizontalMagnification);

Q_SIGNALS:
    void clipNearChanged();
    void clipFarChanged();
    void horizontalMagnificationChanged();
    void verticalMagnificationChanged();

protected:
    QSSGRenderGraphObject *updateSpatialNode(QSSGRenderGraphObject *node) override;

private:
    float m_clipNear = 10.0f;
    float m_clipFar = 10000.0f;
    float m_horizontalMagnification = 1.0f;
    float m_verticalMagnification = 1.0f;
};

QT_END_NAMESPACE

#endif // QSSGORTHOGRAPHICCAMERA_H
