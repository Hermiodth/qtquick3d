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

#ifndef CONVERTERTHREAD_H
#define CONVERTERTHREAD_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QDir>
#include <QStringList>

class ConverterThread : public QThread
{
    Q_OBJECT

public:
    ConverterThread(QObject *parent = nullptr);
    ~ConverterThread();

    void convert(QStringList filenames, QDir outputPath, QVariantMap options);

protected:
    void run() override;

signals:
    void convertStart(const QString &text);
    void convertUpdate(const QString &text);
    void convertDone(const QString &text);

private:
    QMutex mutex;
    QWaitCondition condition;

    bool abort = false;

    QStringList m_filenames;
    QDir m_outputPath;
    QVariantMap m_options;
};

#endif
