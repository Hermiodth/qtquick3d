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

#ifndef QQUICK3DBAKEDLIGHTMAP_P_H
#define QQUICK3DBAKEDLIGHTMAP_P_H

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

QT_BEGIN_NAMESPACE

class Q_QUICK3D_EXPORT QQuick3DBakedLightmap : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QString loadPrefix READ loadPrefix WRITE setLoadPrefix NOTIFY loadPrefixChanged)

    QML_NAMED_ELEMENT(BakedLightmap)

public:
    bool isEnabled() const;
    QString key() const;
    QString loadPrefix() const;

public Q_SLOTS:
    void setEnabled(bool enabled);
    void setKey(const QString &key);
    void setLoadPrefix(const QString &loadPrefix);

Q_SIGNALS:
    void changed();
    void enabledChanged();
    void keyChanged();
    void loadPrefixChanged();

private:
    bool m_enabled = false;
    QString m_key;
    QString m_loadPrefix;
};

QT_END_NAMESPACE

#endif // QQUICK3DBAKEDLIGHTMAP_P_H