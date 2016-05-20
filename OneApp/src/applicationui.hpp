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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <bb/cascades/ArrayDataModel>

#include <src/AppInstallerWatch/AppInstallerWatch.h>
#include <src/DesignUnits/DesignUnits.h>
#include <src/Settings/Settings.h>

namespace bb {
    namespace cascades {
        class LocaleHandler;
    }
    namespace system {
        class InvokeManager;
    }
}

class QTranslator;

/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bb::cascades::ArrayDataModel *dataModel READ getDataModel WRITE setDataModel NOTIFY dataModelChanged);
    Q_PROPERTY(QVariantMap deviceInfo READ getDeviceInfo WRITE setDeviceInfo NOTIFY deviceInfoChanged);

public:
    ApplicationUI();
    virtual ~ApplicationUI() { }

    Q_INVOKABLE QString hashThis(const QString& toHash);
    Q_INVOKABLE void lockThisApp(const QString& app);
    Q_INVOKABLE void sendToHL(const QString& command, QString data = "");

public slots:
    Q_INVOKABLE void stopLocking();

private slots:
    void onAddThisApp(const QString&, const QVariantMap&);
    void onAppInstallerWatchInitDone();
    void onSystemLanguageChanged();

private:
    bb::cascades::ArrayDataModel* getDataModel() { return m_dataModel; }
    void setDataModel(bb::cascades::ArrayDataModel *newValue) { m_dataModel = newValue; emit dataModelChanged(); }

    QVariantMap getDeviceInfo() { return m_deviceInfo; }
    void setDeviceInfo(const QVariantMap & newValue) { m_deviceInfo = newValue; emit deviceInfoChanged(); }

    void checkForChangelog();

    AppInstallerWatch* m_appInstallerWatch;
    bb::cascades::ArrayDataModel* m_dataModel;
    DesignUnits* m_designUnits;
    bb::system::InvokeManager* m_invokeManager;
    bb::cascades::LocaleHandler* m_localeHandler;
    Settings* m_settings;
    QTranslator* m_translator;

    QVariantMap m_allAppsMap;
    QVariantMap m_deviceInfo;

signals:
    void dataModelChanged();
    void deviceInfoChanged();
    void newChangelog(const QString&);
};

#endif /* ApplicationUI_HPP_ */
