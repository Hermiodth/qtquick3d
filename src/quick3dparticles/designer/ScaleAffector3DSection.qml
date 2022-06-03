/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

import QtQuick 2.15
import QtQuick.Layouts 1.15
import HelperWidgets 2.0
import StudioTheme 1.0 as StudioTheme

Section {
    caption: qsTr("Particle Scale Affector")
    width: parent.width

    SectionLayout {
        PropertyLabel {
            text: qsTr("Minimum Size")
            tooltip: qsTr("This property defines the minimum scale size.")
        }

        SecondColumnLayout {
            SpinBox {
                minimumValue: 0
                maximumValue: 999999
                decimals: 2
                backendValue: backendValues.minSize
                implicitWidth: StudioTheme.Values.singleControlColumnWidth
                               + StudioTheme.Values.actionIndicatorWidth
            }

            ExpandingSpacer {}
        }

        PropertyLabel {
            text: qsTr("Maximum Size")
            tooltip: qsTr("This property defines the maximum scale size.")
        }

        SecondColumnLayout {
            SpinBox {
                minimumValue: 0
                maximumValue: 999999
                decimals: 2
                backendValue: backendValues.maxSize
                implicitWidth: StudioTheme.Values.singleControlColumnWidth
                               + StudioTheme.Values.actionIndicatorWidth
            }

            ExpandingSpacer {}
        }

        PropertyLabel {
            text: qsTr("Duration")
            tooltip: qsTr("This property defines the duration of scaling period.")
        }

        SecondColumnLayout {
            SpinBox {
                minimumValue: 0
                maximumValue: 999999
                decimals: 0
                backendValue: backendValues.duration
                implicitWidth: StudioTheme.Values.singleControlColumnWidth
                               + StudioTheme.Values.actionIndicatorWidth
            }

            ExpandingSpacer {}
        }

        PropertyLabel {
            text: qsTr("Easing curve")
            tooltip: qsTr("Defines a custom scaling curve.")
        }

        SecondColumnLayout {
            BoolButtonRowButton {
                buttonIcon: StudioTheme.Constants.curveDesigner

                EasingCurveEditor {
                    id: easingCurveEditor
                    modelNodeBackendProperty: modelNodeBackend
                }

                onClicked: easingCurveEditor.runDialog()
            }

            ExpandingSpacer {}
        }
    }
}