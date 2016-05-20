/*
 * AppInstallerWatch.cpp
 *
 *  Created on: 2016-02-29
 *      Author: Roger
 */

#include <src/AppInstallerWatch/AppInstallerWatch.h>

#include <QDebug>
#include <QStringList>
#include <bb/data/JsonDataAccess>
#include <bb/PpsObject>

AppInstallerWatch::AppInstallerWatch(QObject *_parent) :
    QObject(_parent),
    m_pps(new PpsWatch("/pps/system/installer/appdetails/.all", this)),
    m_initDoneTimer(new QTimer(this))
{
    connect(m_pps, SIGNAL(ppsFileReady(const QVariantMap&)), this, SLOT(onPpsFileReady(const QVariantMap&)));
    connect(m_initDoneTimer, SIGNAL(timeout()), this, SIGNAL(initDone()));

    m_initDoneTimer->setSingleShot(true);
    m_initDoneTimer->setInterval(200);
}

void AppInstallerWatch::onPpsFileReady(const QVariantMap& map) {
    if (m_initDoneTimer->isActive())
        m_initDoneTimer->stop();

    foreach(const QString key, map.keys()) {
        if (key == "_ppsMapTitle")
            continue;

        QVariantMap thisAppMap;
        QString appName, appDescription, packageName, packageType;
        QStringList icons;

        const QVariantMap thisKey = map[key].toMap();

        QStringList dnamePath = thisKey["dnamepath"].toString().split("/");
        if (!dnamePath.isEmpty())
            packageName = dnamePath.last();

        // Skip Hub for now
        if ((packageName.contains("sys.uri.bbhub.")) || (packageName.contains("sys.pim.messages.")))
            continue;

        QStringList caps = thisKey["caps"].toStringList();

        const QVariantList sections = thisKey["_"].toMap()["sections"].toList();

        foreach(const QVariant section, sections) {
            const QVariantMap thisSection = section.toMap();
            if (thisSection["kind"].toString() == "Application") {
                const QVariantMap attributes = thisSection["_"].toMap()["attributes"].toMap();
                appName = attributes["Application-Name"].toString();
                appDescription = attributes["Application-Description"].toString();
            }
            else if (thisSection["kind"].toString() == "Entry-Point") {
                const QVariantMap attributes = thisSection["_"].toMap()["attributes"].toMap();
                icons = attributes["Entry-Point-Icon"].toString().split(":");
            }
            else if (thisSection["kind"].toString() == "Package") {
                const QVariantMap attributes = thisSection["_"].toMap()["attributes"].toMap();
                packageType = attributes["Package-Type"].toString();
            }
        }

        QString appIconPath, oneIcon;
        if (!icons.isEmpty()) {
            oneIcon = icons.first();
            int firstCurlyBrace = oneIcon.indexOf("{");
            if (firstCurlyBrace >= 0) {
                int secondCurlyBrace = oneIcon.indexOf("}");
                oneIcon.remove(firstCurlyBrace, (secondCurlyBrace - firstCurlyBrace) + 1);
            }
            appIconPath = "file://" + thisKey["dnamepath"].toString() + "/public/" + oneIcon;
        }

        thisAppMap.insert("description", appDescription);
        thisAppMap.insert("icon", appIconPath);
        thisAppMap.insert("name", appName);
        thisAppMap.insert("packageName", packageName);

        if ((!packageName.isEmpty()) && !thisAppMap.isEmpty()) {
            if ((packageType == "application") && !caps.contains("hidden")) {
                emit addThisApp(appName, thisAppMap);
            }
        }
    }

    m_initDoneTimer->start();
}
