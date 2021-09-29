/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick3D
import QtQuick3D.Particles3D
import QtQuick3D.Helpers
import QtQuick.Controls

Window {
    id: window
    width: 640
    height: 640
    visible: true
    color: "black"

    WasdController {
        controlledObject: camera
    }

    View3D {
        id: view
        anchors.fill: parent

        environment: SceneEnvironment {
            clearColor: window.color
            backgroundMode: SceneEnvironment.SkyBox
            lightProbe: Texture {
                source: "qrc:///OpenfootageNET_garage-1024.hdr"
            }
            probeOrientation: Qt.vector3d(0, -90, 0)
        }

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 200, 400)
            eulerRotation.x: -30
        }

        DirectionalLight {
            eulerRotation.x: -60
            castsShadow: true
        }

        Model {
            property real angle: 0
            source: "#Sphere"
            x: Math.cos(angle) * 100
            z: Math.sin(angle) * 100
            receivesReflections: true

            NumberAnimation on angle {
                from: 0
                to: Math.PI * 2
                duration: 8000
                loops: Animation.Infinite
            }

            materials: PrincipledMaterial {
                metalness: 1
                roughness: 0

                SequentialAnimation on roughness {
                    loops: Animation.Infinite
                    NumberAnimation {
                        from: 0
                        to: 1.0
                        duration: 5000
                    }
                    NumberAnimation {
                        from: 1
                        to: 0.0
                        duration: 5000
                    }
                }
            }

            ReflectionProbe {
                timeSlicing: {
                    if (comboTimeSlicing.currentIndex === 0) ReflectionProbe.None
                    else if (comboTimeSlicing.currentIndex === 1) ReflectionProbe.AllFacesAtOnce
                    else ReflectionProbe.IndividualFaces
                }
                refreshMode: {
                    if (comboRefreshMode.currentIndex === 0) ReflectionProbe.EveryFrame
                    else ReflectionProbe.FirstFrame
                }
                quality: {
                    if (comboQuality.currentIndex === 0) ReflectionProbe.Low
                    else if (comboQuality.currentIndex === 1) ReflectionProbe.Medium
                    else if (comboQuality.currentIndex === 2) ReflectionProbe.High
                    else ReflectionProbe.VeryHigh
                }
                parallaxCorrection: checkParallax.checked
                boxSize: Qt.vector3d(sliderBoxX.value, sliderBoxY.value, sliderBoxZ.value)
            }
        }

        ParticleSystem3D {
            position: Qt.vector3d(200, 0, 0)
            SpriteParticle3D {
                id: starParticle
                sprite: Texture {
                    source: "snowflake.png"
                }
                maxAmount: 200
                color: "#ffff00"
                particleScale: 20.0
                fadeOutDuration: 500
                billboard: true
            }
            ParticleEmitter3D {
                particle: starParticle
                velocity: VectorDirection3D {
                    direction: Qt.vector3d(100, 200, 0)
                    directionVariation: Qt.vector3d(20, 20, 20)
                }
                particleScaleVariation: 0.4
                emitRate: 50
                lifeSpan: 4000
            }
            Gravity3D {
                magnitude: 100
            }
        }

        Model {
            source: "#Sphere"
            materials: DefaultMaterial {}
        }

        Model {
            position: Qt.vector3d(0, 0, 200)
            source: "#Sphere"
            materials: DefaultMaterial {}
        }

        Model {
            source: "#Cube"

            materials: [
                CustomMaterial {
                    shadingMode: CustomMaterial.Shaded
                    fragmentShader: "material_simple.frag"
                    property color uDiffuse: "fuchsia"
                    property real uSpecular: 1.0
                }
            ]

            //materials: PrincipledMaterial {}

            y: -200
            scale: Qt.vector3d(10, 1, 10)
        }
    }

    Frame {
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 10
        background: Rectangle {
            color: "#e0e0e0"
            border.color: "#000000"
            border.width: 1
            opacity: 0.8
        }
        Column {
            id: settingsArea
            ComboBox {
                id: comboTimeSlicing
                width: 200
                model: [ "None", "All Faces At Once", "Individual Faces" ]
            }
            ComboBox {
                id: comboRefreshMode
                width: 200
                model: [ "Every Frame", "First Frame" ]
            }
            ComboBox {
                id: comboQuality
                width: 200
                model: [ "Low", "Medium", "High", "Very High" ]
            }
            CheckBox {
                id: checkParallax
                checked: false
                text: qsTr("Parallax")
            }
            Slider {
                id: sliderBoxX
                from: 0
                value: 0
                to: 1000
            }
            Slider {
                id: sliderBoxY
                from: 0
                value: 0
                to: 1000
            }
            Slider {
                id: sliderBoxZ
                from: 0
                value: 0
                to: 1000
            }
        }
    }

    DebugView {
        anchors.right: parent.right
        source: view
    }
}
