# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

qt_add_library(content STATIC)

qt_add_qml_module(content
    URI "content"
    VERSION 1.0
    QML_FILES
        App.qml
        ControlPanel.qml
        Screen01.ui.qml
        SettingsPanel.qml
    RESOURCES
        colosseum_4k.hdr
)
