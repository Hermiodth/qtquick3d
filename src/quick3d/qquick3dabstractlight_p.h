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

#ifndef QSSGABSTRACTLIGHT_H
#define QSSGABSTRACTLIGHT_H

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

#include <QColor>

QT_BEGIN_NAMESPACE

class Q_QUICK3D_EXPORT QQuick3DAbstractLight : public QQuick3DNode
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor ambientColor READ ambientColor WRITE setAmbientColor NOTIFY ambientColorChanged)
    Q_PROPERTY(float brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(QQuick3DNode *scope READ scope WRITE setScope NOTIFY scopeChanged)
    Q_PROPERTY(bool castsShadow READ castsShadow WRITE setCastsShadow NOTIFY castsShadowChanged)
    Q_PROPERTY(float shadowBias READ shadowBias WRITE setShadowBias NOTIFY shadowBiasChanged)
    Q_PROPERTY(float shadowFactor READ shadowFactor WRITE setShadowFactor NOTIFY shadowFactorChanged)
    Q_PROPERTY(QSSGShadowMapQuality shadowMapQuality READ shadowMapQuality WRITE setShadowMapQuality NOTIFY shadowMapQualityChanged)
    Q_PROPERTY(float shadowMapFar READ shadowMapFar WRITE setShadowMapFar NOTIFY shadowMapFarChanged)
    Q_PROPERTY(float shadowFilter READ shadowFilter WRITE setShadowFilter NOTIFY shadowFilterChanged)

    QML_NAMED_ELEMENT(Light)
    QML_UNCREATABLE("Light is Abstract")
public:
    ~QQuick3DAbstractLight() override;

    enum class QSSGShadowMapQuality {
        ShadowMapQualityLow,
        ShadowMapQualityMedium,
        ShadowMapQualityHigh,
        ShadowMapQualityVeryHigh,
    };
    Q_ENUM(QSSGShadowMapQuality)

    QColor color() const;
    QColor ambientColor() const;
    float brightness() const;
    QQuick3DNode *scope() const;
    bool castsShadow() const;
    float shadowBias() const;
    float shadowFactor() const;
    QSSGShadowMapQuality shadowMapQuality() const;
    float shadowMapFar() const;
    float shadowFilter() const;

public Q_SLOTS:
    void setColor(const QColor &color);
    void setAmbientColor(const QColor &ambientColor);
    void setBrightness(float brightness);
    void setScope(QQuick3DNode *scope);
    void setCastsShadow(bool castsShadow);
    void setShadowBias(float shadowBias);
    void setShadowFactor(float shadowFactor);
    void setShadowMapQuality(QQuick3DAbstractLight::QSSGShadowMapQuality shadowMapQuality);
    void setShadowMapFar(float shadowMapFar);
    void setShadowFilter(float shadowFilter);

Q_SIGNALS:
    void colorChanged();
    void ambientColorChanged();
    void brightnessChanged();
    void scopeChanged();
    void castsShadowChanged();
    void shadowBiasChanged();
    void shadowFactorChanged();
    void shadowMapQualityChanged();
    void shadowMapFarChanged();
    void shadowFilterChanged();

protected:
    explicit QQuick3DAbstractLight(QQuick3DNodePrivate &dd, QQuick3DNode *parent = nullptr);

    QSSGRenderGraphObject *updateSpatialNode(QSSGRenderGraphObject *node) override;
    void markAllDirty() override;

    enum class DirtyFlag {
        ShadowDirty = (1 << 0),
        ColorDirty = (1 << 1),
        BrightnessDirty = (1 << 2),
        FadeDirty = (1 << 3),
        AreaDirty = (1 << 4),
    };
    Q_DECLARE_FLAGS(DirtyFlags, DirtyFlag)

    DirtyFlags m_dirtyFlags = DirtyFlags(DirtyFlag::ShadowDirty)
                              | DirtyFlags(DirtyFlag::ColorDirty)
                              | DirtyFlags(DirtyFlag::BrightnessDirty)
                              | DirtyFlags(DirtyFlag::FadeDirty)
                              | DirtyFlags(DirtyFlag::AreaDirty);
private:
    quint32 mapToShadowResolution(QSSGShadowMapQuality resolution);

    QColor m_color;
    QColor m_ambientColor;
    float m_brightness = 1.0f;
    QQuick3DNode *m_scope = nullptr;
    bool m_castsShadow = false;
    float m_shadowBias = 0.0f;
    float m_shadowFactor = 5.0f;
    QSSGShadowMapQuality m_shadowMapQuality = QSSGShadowMapQuality::ShadowMapQualityLow;
    float m_shadowMapFar = 5000.0f;
    float m_shadowFilter = 5.0f;
};

QT_END_NAMESPACE
#endif // QSSGDIRECTIONALLIGHT_H
