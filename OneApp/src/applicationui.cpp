/*
 * Copyright (c) 2013-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"
#include "commons.h"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/system/InvokeManager>

#include <bb/cascades/SceneCover>
#include <bb/cascades/AbstractCover>

#include <bb/PackageInfo>
#include <QTimer>
#include <bb/data/JsonDataAccess>

using namespace bb::cascades;
using namespace bb::system;

ApplicationUI::ApplicationUI() :
        QObject(),
        m_appInstallerWatch(NULL),
        m_dataModel(new bb::cascades::ArrayDataModel(this)),
        m_designUnits(new DesignUnits(this)),
        m_invokeManager(new InvokeManager(this)),
        m_localeHandler(new LocaleHandler(this)),
        m_translator(new QTranslator(this))
{
    m_settings = Settings::instance(this);

    // Save this device screen size infos to make it available to QML
    // The getenv() method doesn't need any lib added and is available since 10.0
    QVariantMap tempDeviceInfo = getDeviceInfo();
    tempDeviceInfo.insert("deviceWidth", getenv("WIDTH"));
    tempDeviceInfo.insert("deviceHeight", getenv("HEIGHT"));
    tempDeviceInfo.insert("activeFrameWidth", getenv("COVERWIDTH"));
    tempDeviceInfo.insert("activeFrameHeight", getenv("COVERHEIGHT"));
    setDeviceInfo(tempDeviceInfo);
    qDebug() << getDeviceInfo();

    // Registering QTimer for easy QML access
    qmlRegisterType<QTimer>("QTimer", 1, 0, "QTimer");

    // This is for Active Frame support for 10.2.1 or lower (not needed anymore in 10.3)
    qmlRegisterType<SceneCover>("bb.cascades", 1, 0, "SceneCover");
    qmlRegisterUncreatableType<AbstractCover>("bb.cascades", 1, 0, "AbstractCover", "");

    // prepare the localization
    if (!QObject::connect(m_localeHandler, SIGNAL(systemLanguageChanged()),
            this, SLOT(onSystemLanguageChanged()))) {
        // This is an abnormal situation! Something went wrong!
        // Add own code to recover here
        qWarning() << "Recovering from a failed connect()";
    }

    // initial load
    onSystemLanguageChanged();

    m_dataModel->clear();
    setDataModel(m_dataModel);

    m_appInstallerWatch = new AppInstallerWatch(this);
    connect(m_appInstallerWatch, SIGNAL(addThisApp(const QString&, const QVariantMap&)), this, SLOT(onAddThisApp(const QString&, const QVariantMap&)));
    connect(m_appInstallerWatch, SIGNAL(initDone()), this, SLOT(onAppInstallerWatchInitDone()));

    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Make app available to the qml.
    qml->setContextProperty("_app", this);
    qml->setContextProperty("_settings", m_settings);
    qml->setContextProperty("_ui", m_designUnits);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    Application::instance()->setScene(root);

    checkForChangelog();

    m_settings->setValue("lastVersionLoaded", bb::Application::applicationVersion());
}

void ApplicationUI::checkForChangelog() {
    qDebug() << "ApplicationUI::checkForChangelog()";
    bb::data::JsonDataAccess jda;
    QString path = "app/native/assets/Changelog/changelog.json";
    QVariantMap changelog = jda.load(path).toMap();
    QString newChangelogForThisUser;
    QStringList allKeys = changelog.keys();
    qDebug() << "allKeys:" << allKeys;
    for(int i = (allKeys.size() - 1); i >= 0; i--) {
        QStringList thisKey = allKeys[i].split(".");
        QStringList lastVersionLoadedInSettings = m_settings->value("lastVersionLoaded", "0.0.0.0").toString().split(".");
        qDebug() << thisKey << lastVersionLoadedInSettings;
        bool showThisChangelog = false;
        if (thisKey.size() == lastVersionLoadedInSettings.size()) {
            for (int j = 0; j < thisKey.size(); j++) {
                if (thisKey[j] > lastVersionLoadedInSettings[j]) {
                    showThisChangelog = true;
                    j = thisKey.size();
                }
                else {
                    if (thisKey[j] < lastVersionLoadedInSettings[j]) {
                        j = thisKey.size();
                    }
                }
            }
        }
        if (showThisChangelog) {
            newChangelogForThisUser.append(allKeys[i] + "\n" + changelog.value(allKeys[i]).toString() + "\n\n");
            qDebug() << "appending:" << QString(allKeys[i] + "\n" + changelog.value(allKeys[i]).toString() + "\n\n");
        }
    }
    qDebug() << "newChangelogForThisUser:" << newChangelogForThisUser;
    if (!newChangelogForThisUser.isEmpty())
        emit newChangelog(newChangelogForThisUser);
}

QString ApplicationUI::hashThis(const QString& toHash) {
    /*
     * Hash a string.
     * We add a salt made of packageName of the app (com.example.myApp.fsajkfdrtw324fas) and vendor name to the hashing method
     */
    bb::PackageInfo packageInfo;
    QString appTarget = packageInfo.installId();
    QString author = packageInfo.author();
    return QCryptographicHash::hash(QString(toHash + appTarget + author).toAscii(), QCryptographicHash::Md5).toHex();
}

void ApplicationUI::lockThisApp(const QString& app)
{
    InvokeRequest request;
    request.setTarget(SERVICE_APP_TARGET);
    request.setAction(SERVICE_LOCK_THIS_APP_ACTION);
    request.setData(app.toUtf8());
    m_invokeManager->invoke(request);

    bb::Application::instance()->requestExit();
}

void ApplicationUI::onAddThisApp(const QString& appName, const QVariantMap& thisAppMap) {
    m_allAppsMap.insert(appName.toLower(), thisAppMap);
}

void ApplicationUI::onAppInstallerWatchInitDone() {
    m_dataModel->clear();

    QMapIterator<QString, QVariant> i(m_allAppsMap);
    while (i.hasNext()) {
        i.next();

        QVariantMap thisAppMap = i.value().toMap();

        m_dataModel->append(thisAppMap);
    }

    setDataModel(m_dataModel);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_translator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("OneApp_%1").arg(locale_string);
    if (m_translator->load(file_name, "app/native/qm")) {
    QCoreApplication::instance()->installTranslator(m_translator);
    }
}

void ApplicationUI::sendToHL(const QString& command, QString data) {
    InvokeRequest request;
    request.setTarget(SERVICE_APP_TARGET);
    request.setAction(QString(SERVICE_APP_TARGET) + "." + command.toUpper());
    if (!data.isEmpty())
        request.setData(data.toUtf8());
    m_invokeManager->invoke(request);
}

void ApplicationUI::stopLocking()
{
    InvokeRequest request;
    request.setTarget(SERVICE_APP_TARGET);
    request.setAction(SERVICE_STOP_LOCKING_ACTION);
    m_invokeManager->invoke(request);
}
