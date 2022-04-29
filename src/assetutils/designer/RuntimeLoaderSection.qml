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
        caption: qsTr("Runtime Loader")

        SectionLayout {
            PropertyLabel {
                text: qsTr("Source")
                tooltip: qsTr("The URL of the 3D asset to import at runtime.")
            }

            SecondColumnLayout {
                UrlChooser {
                    backendValue: backendValues.source
                    filter: "*.*"
                }

                ExpandingSpacer {}
            }

            PropertyLabel {
                text: qsTr("Instancing")
                tooltip: qsTr("If this property is set, the imported model will not be rendered normally. Instead, a number of instances of the model will be rendered, as defined by the instance table.")
            }

            SecondColumnLayout {
                IdComboBox {
                    typeFilter: "QtQuick3D.Instancing"
                    backendValue: backendValues.instancing
                    implicitWidth: StudioTheme.Values.singleControlColumnWidth
                                   + StudioTheme.Values.actionIndicatorWidth
                }

                ExpandingSpacer {}
            }
        }
    }
}
