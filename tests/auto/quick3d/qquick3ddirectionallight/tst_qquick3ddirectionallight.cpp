/****************************************************************************
**
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

#include <QTest>
#include <QSignalSpy>

#include <QtQuick3D/private/qquick3ddirectionallight_p.h>

#include <QtQuick3DRuntimeRender/private/qssgrenderlight_p.h>
#include <QtQuick3D/private/qquick3dobject_p.h>
#include <QtQuick3DUtils/private/qssgutils_p.h>

class tst_QQuick3DDirectionalLight : public QObject
{
    Q_OBJECT

    // Work-around to get access to updateSpatialNode
    class Light : public QQuick3DDirectionalLight
    {
    public:
        using QQuick3DDirectionalLight::updateSpatialNode;
    };

private slots:
    void testProperties();
    void testScope();
};

void tst_QQuick3DDirectionalLight::testProperties()
{
    Light light;
    auto node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(nullptr));
    const auto originalNode = node; // for comparisons later...
    QVERIFY(node);

    // lightType
    QCOMPARE(QSSGRenderLight::Type::DirectionalLight, node->type);

    const float brightness = 0.5f;
    light.setBrightness(brightness);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(originalNode, node);
    QCOMPARE(brightness, node->m_brightness);
    QCOMPARE(light.brightness(), node->m_brightness);

    const float shadowBias = 0.5f;
    light.setShadowBias(shadowBias);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(shadowBias, node->m_shadowBias);
    QCOMPARE(light.shadowBias(), node->m_shadowBias);

    const float shadowFactor = 4.0f;
    light.setShadowFactor(shadowFactor);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(shadowFactor, node->m_shadowFactor);
    QCOMPARE(light.shadowFactor(), node->m_shadowFactor);

    const float shadowMapFar = 2000.0f;
    light.setShadowMapFar(shadowMapFar);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(shadowMapFar, node->m_shadowMapFar);
    QCOMPARE(light.shadowMapFar(), node->m_shadowMapFar);

    const float shadowFilter = 20.0f;
    light.setShadowFilter(shadowFilter);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(shadowFilter, node->m_shadowFilter);
    QCOMPARE(light.shadowFilter(), node->m_shadowFilter);

    const QQuick3DAbstractLight::QSSGShadowMapQuality qualities[] = {
        QQuick3DAbstractLight::QSSGShadowMapQuality::ShadowMapQualityLow,
        QQuick3DAbstractLight::QSSGShadowMapQuality::ShadowMapQualityMedium,
        QQuick3DAbstractLight::QSSGShadowMapQuality::ShadowMapQualityHigh,
        QQuick3DAbstractLight::QSSGShadowMapQuality::ShadowMapQualityVeryHigh
    };
    const unsigned int mappedResolutions[] = {8, 9, 10, 11};

    for (int i = 0; i < 4; ++i) {
        const auto shadowMapQuality = qualities[i];
        const auto mappedResolution = mappedResolutions[i];
        light.setShadowMapQuality(shadowMapQuality);
        node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
        QCOMPARE(mappedResolution, node->m_shadowMapRes);
        QCOMPARE(light.shadowMapQuality(), shadowMapQuality);
    }

    light.setCastsShadow(true);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QVERIFY(node->m_castShadow);
    light.setCastsShadow(false);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QVERIFY(!node->m_castShadow);

    QColor color1("#12345678");
    QVector3D color1Vec3 = color::sRGBToLinear(color1).toVector3D();
    QColor color2("#cccccccc");
    QVector3D color2Vec3 = color::sRGBToLinear(color2).toVector3D();
    light.setColor(color1);
    light.setAmbientColor(color2);
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    QCOMPARE(originalNode, node);
    QCOMPARE(color1, light.color());
    QCOMPARE(color2, light.ambientColor());
    // Note: none of these colors contain alpha
    QCOMPARE(color1Vec3, node->m_diffuseColor);
    QCOMPARE(color1Vec3, node->m_specularColor);
    QCOMPARE(color2Vec3, node->m_ambientColor);
}

void tst_QQuick3DDirectionalLight::testScope()
{
    Light light;
    auto node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(nullptr));
    QVERIFY(node);
    QQuick3DNode nodeItem;
    QVERIFY(!light.scope());
    light.setScope(&nodeItem);
    QVERIFY(light.scope());
    node = static_cast<QSSGRenderLight *>(light.updateSpatialNode(node));
    auto scope = static_cast<QSSGRenderNode*>(QQuick3DObjectPrivate::get(light.scope())->spatialNode);
    QCOMPARE(scope, node->m_scope);
}

QTEST_APPLESS_MAIN(tst_QQuick3DDirectionalLight)
#include "tst_qquick3ddirectionallight.moc"
