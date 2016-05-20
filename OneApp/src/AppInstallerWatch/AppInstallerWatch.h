/*
 * AppInstallerWatch.h
 *
 *  Created on: 2016-02-29
 *      Author: Roger
 */

#ifndef APPINSTALLERWATCH_H_
#define APPINSTALLERWATCH_H_

#include <src/PpsWatch/PpsWatch.h>

#include <QObject>
#include <QTimer>

class AppInstallerWatch : public QObject
{
    Q_OBJECT

public:
    AppInstallerWatch(QObject *_parent = 0);

private slots:
    void onPpsFileReady(const QVariantMap&);

private:
    PpsWatch* m_pps;
    QTimer* m_initDoneTimer;

signals:
    void addThisApp(const QString& appName, const QVariantMap& thisAppMap);
    void initDone();
};

#endif /* APPINSTALLERWATCH_H_ */
