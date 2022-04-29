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

import QtQuick
import QtQuick3D

View3D {
    width: 400
    height: 400
    environment: sceneEnvironment

    SceneEnvironment {
        id: sceneEnvironment
        antialiasingMode: SceneEnvironment.MSAA
        antialiasingQuality: SceneEnvironment.High
    }

    Node {
        id: scene

        DirectionalLight {
            id: directionalLight
        }

        PerspectiveCamera {
            id: sceneCamera
            z: 350
        }

        Model {
            id: cubeModel
            eulerRotation.x: 30
            eulerRotation.y: 45

            source: "#Cube"

            materials: cubeMaterial
            DefaultMaterial {
                id: cubeMaterial
                diffuseColor: "#4aee45"
            }
        }
    }
}
