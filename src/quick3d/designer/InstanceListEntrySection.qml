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

import QtQuick 2.15
import QtQuick.Layouts 1.15
import HelperWidgets 2.0
import StudioTheme 1.0 as StudioTheme

Column {
    width: parent.width

    Section {
        width: parent.width
        caption: qsTr("Instance List Entry")

        ColumnLayout {
            spacing: StudioTheme.Values.transform3DSectionSpacing

            SectionLayout {
                PropertyLabel {
                    text: qsTr("Color")
                    tooltip: qsTr("This property specifies the color for the instance.")
                }

                ColorEditor {
                    backendValue: backendValues.color
                    supportGradient: false
                }
            }

            SectionLayout {
                PropertyLabel {
                    text: qsTr("Position")
                    tooltip: qsTr("This property specifies the position for the instance.")
                }

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.position_x
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "X"
                        color: StudioTheme.Values.theme3DAxisXColor
                    }

                    ExpandingSpacer {}
                }

                PropertyLabel {}

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.position_y
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "Y"
                        color: StudioTheme.Values.theme3DAxisYColor
                    }

                    ExpandingSpacer {}
                }

                PropertyLabel {}

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.position_z
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "Z"
                        color: StudioTheme.Values.theme3DAxisZColor
                    }

                    ExpandingSpacer {}
                }
            }

            SectionLayout {
                PropertyLabel {
                    text: qsTr("Scale")
                    tooltip: qsTr("This property specifies the scale for the instance.")
                }

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.scale_x
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "X"
                        color: StudioTheme.Values.theme3DAxisXColor
                    }

                    ExpandingSpacer {}
                }

                PropertyLabel {}

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.scale_y
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "Y"
                        color: StudioTheme.Values.theme3DAxisYColor
                    }

                    ExpandingSpacer {}
                }

                PropertyLabel {}

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.scale_z
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "Z"
                        color: StudioTheme.Values.theme3DAxisZColor
                    }

                    ExpandingSpacer {}
                }
            }

            SectionLayout {
                PropertyLabel {
                    text: qsTr("Rotation")
                    tooltip: qsTr("This property specifies the rotation for the instance.")
                }

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.eulerRotation_x
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "X"
                        color: StudioTheme.Values.theme3DAxisXColor
                    }

                    ExpandingSpacer {}
                }

                PropertyLabel {}

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.eulerRotation_y
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "Y"
                        color: StudioTheme.Values.theme3DAxisYColor
                    }

                    ExpandingSpacer {}
                }

                PropertyLabel {}

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                        + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.eulerRotation_z
                    }

                    Spacer { implicitWidth: StudioTheme.Values.controlLabelGap }

                    ControlLabel {
                        text: "Z"
                        color: StudioTheme.Values.theme3DAxisZColor
                    }

                    ExpandingSpacer {}
                }
            }
        }
    }
}
