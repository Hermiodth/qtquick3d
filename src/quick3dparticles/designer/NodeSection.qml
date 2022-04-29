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
        caption: qsTr("Node")

        SectionLayout {
            PropertyLabel {
                text: qsTr("Opacity")
                tooltip: qsTr("Controls the local opacity value of the node.")
            }

            SecondColumnLayout {
                // ### should be a slider
                SpinBox {
                    minimumValue: 0
                    maximumValue: 1
                    decimals: 2
                    stepSize: 0.1
                    backendValue: backendValues.opacity
                    sliderIndicatorVisible: true
                    implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                   + StudioTheme.Values.actionIndicatorWidth
                }

                ExpandingSpacer {}
            }

            PropertyLabel {
                text: qsTr("Visibility")
                tooltip: qsTr("Sets the local visibility of the node.")
            }

            SecondColumnLayout {
                // ### should be a slider
                CheckBox {
                    text: qsTr("Is Visible")
                    backendValue: backendValues.visible
                    implicitWidth: StudioTheme.Values.twoControlColumnWidth
                                   + StudioTheme.Values.actionIndicatorWidth
                }

                ExpandingSpacer {}
            }

            PropertyLabel {
                text: qsTr("Static flags")
                tooltip: qsTr("This property defines the static flags that are used to evaluate how the node is rendered.")
            }

            SecondColumnLayout {
                LineEdit {
                    backendValue: backendValues.staticFlags
                    showTranslateCheckBox: false
                    implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                   + StudioTheme.Values.actionIndicatorWidth
                    width: implicitWidth
                }

                ExpandingSpacer {}
            }
        }
    }

    Section {
        id: transformSection
        width: parent.width
        caption: qsTr("Transform")

        ColumnLayout {
            spacing: StudioTheme.Values.transform3DSectionSpacing

            SectionLayout {
                PropertyLabel {
                    text: qsTr("Translation")
                    tooltip: qsTr("Sets the translation of the node.")
                }

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                       + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.x
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
                        backendValue: backendValues.y
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
                        backendValue: backendValues.z
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
                    tooltip: qsTr("Sets the rotation of the node in degrees.")
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

            SectionLayout {
                PropertyLabel {
                    text: qsTr("Scale")
                    tooltip: qsTr("Sets the scale of the node.")
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
                    text: qsTr("Pivot")
                    tooltip: qsTr("Sets the pivot of the node.")
                }

                SecondColumnLayout {
                    SpinBox {
                        implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                       + StudioTheme.Values.actionIndicatorWidth
                        minimumValue: -9999999
                        maximumValue: 9999999
                        decimals: 2
                        backendValue: backendValues.pivot_x
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
                        backendValue: backendValues.pivot_y
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
                        backendValue: backendValues.pivot_z
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
