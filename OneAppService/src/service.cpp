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

#include "service.hpp"
#include "commons.h"

#include <src/AppLauncher/AppLauncher.h>
#include <src/Logger/Logger.h>

#include <bb/Application>
#include <bb/PackageInfo>
#include <bb/platform/Notification>
#include <bb/platform/NotificationDefaultApplicationSettings>
#include <bb/system/InvokeManager>

#include <QTimer>

using namespace bb::platform;
using namespace bb::system;

Service::Service() :
        QObject(),
        m_deviceActive(NULL),
        m_fullscreenPid(NULL),
        m_invokeManager(new InvokeManager(this)),
        m_notificationGlobalSettings(new NotificationGlobalSettings(this)),
        m_notify(new Notification(this)),
        m_physicalButtons(new PhysicalButtons(this))
{
    m_settings = Settings::instance(this);
    m_settings->setValue(SETTINGS_IS_TRYING_TO_UNLOCK, false);
    m_settings->setValue(SETTINGS_LOCKED_PACKAGE_NAME, "");
    m_settings->setValue(SETTINGS_LOCK_MODE_ENABLED, false);

    bb::system::InvokeRequest request;
    request.setTarget(SERVICE_APP_TARGET);
    request.setAction(SERVICE_UNLOCK_REQUEST_ACTION);

    const QString iconPath = QString::fromLatin1("file://%1/app/public/native/appIcon96.png").arg(QDir::currentPath());
    qDebug() << "iconPath:" << iconPath;
    m_notify->setIconUrl(iconPath);
    QString message = tr("Click to unlock");
    m_notify->setTitle(bb::Application::applicationName());
    m_notify->setBody(message);
    m_notify->setInvokeRequest(request);

    m_invokeManager->connect(m_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
            this, SLOT(handleInvoke(const bb::system::InvokeRequest&)));

    NotificationDefaultApplicationSettings settings;
    settings.setLed(NotificationPolicy::Deny);
    settings.setPreview(NotificationPriorityPolicy::Allow);
    settings.setSound(NotificationPolicy::Deny);
    settings.setVibrate(NotificationPolicy::Deny);
    settings.apply();

    connect(m_physicalButtons, SIGNAL(plusButtonLongPressed()), this, SLOT(onPlusButtonLongPressed()));
}

void Service::handleInvoke(const bb::system::InvokeRequest & request)
{
    Logger::logThis("Service::handleInvoke(): " + request.action());

    if (request.action().compare(SERVICE_LOCK_THIS_APP_ACTION) == 0) {
        m_userNotificationMode = m_notificationGlobalSettings->mode();
        m_notificationGlobalSettings->setMode(NotificationMode::AlertsOff);

        m_settings->setValue(SETTINGS_IS_TRYING_TO_UNLOCK, false);
        m_settings->setValue(SETTINGS_LOCKED_PACKAGE_NAME, QString(request.data()));
        m_settings->setValue(SETTINGS_LOCK_MODE_ENABLED, true);

        this->openLockedApp();

        this->connectToSignals();
    }
    else if (request.action().compare(SERVICE_STOP_LOCKING_ACTION) == 0) {
        this->disconnectFromSignals();

        m_settings->setValue(SETTINGS_IS_TRYING_TO_UNLOCK, false);
        m_settings->setValue(SETTINGS_LOCKED_PACKAGE_NAME, "");
        m_settings->setValue(SETTINGS_LOCK_MODE_ENABLED, false);

        m_notificationGlobalSettings->setMode(m_userNotificationMode);

        bb::Application::instance()->requestExit();
    }
    else if (request.action().compare(SERVICE_UNLOCK_REQUEST_ACTION) == 0) {
        m_settings->setValue(SETTINGS_IS_TRYING_TO_UNLOCK, true);

        this->openLockedApp();
    }
    else if (request.action().compare(SERVICE_SHUTDOWN_ACTION) == 0) {
        bb::Application::instance()->requestExit();
    }
    else if (request.action().compare(SERVICE_WRONG_PASSWORD_ACTION) == 0) {
        m_settings->setValue(SETTINGS_IS_TRYING_TO_UNLOCK, false);

        this->openLockedApp();
    }
    else {
        m_settings->setValue(SETTINGS_IS_TRYING_TO_UNLOCK, false);
        m_settings->setValue(SETTINGS_LOCKED_PACKAGE_NAME, "");
        m_settings->setValue(SETTINGS_LOCK_MODE_ENABLED, false);
    }
}

void Service::connectToSignals() {
    if (m_deviceActive == NULL)
        m_deviceActive = new DeviceActive(this);

    if (m_fullscreenPid == NULL)
        m_fullscreenPid = new FullscreenPid(this);

    if (m_physicalButtons == NULL)
        m_physicalButtons = new PhysicalButtons(this);

    connect(m_deviceActive, SIGNAL(deviceActiveChanged(const bool&)), this, SLOT(onDeviceActiveChanged(const bool&)));
    connect(m_fullscreenPid, SIGNAL(fullscreenPidChanged(const int&)), this, SLOT(onFullscreenPidChanged(const int&)));
    connect(m_physicalButtons, SIGNAL(powerButtonLongPressed()), this, SLOT(onPowerDownAttempt()));
    connect(m_physicalButtons, SIGNAL(screenshotButtonsPressed()), this, SLOT(onPowerDownAttempt()));
}

void Service::disconnectFromSignals() {
    disconnect(m_deviceActive, SIGNAL(deviceActiveChanged(const bool&)), this, SLOT(onDeviceActiveChanged(const bool&)));
    disconnect(m_fullscreenPid, SIGNAL(fullscreenPidChanged(const int&)), this, SLOT(onFullscreenPidChanged(const int&)));
    disconnect(m_physicalButtons, SIGNAL(powerButtonLongPressed()), this, SLOT(onPowerDownAttempt()));
    disconnect(m_physicalButtons, SIGNAL(screenshotButtonsPressed()), this, SLOT(onPowerDownAttempt()));

    delete m_deviceActive;
    m_deviceActive = NULL;

    delete m_fullscreenPid;
    m_fullscreenPid = NULL;

    delete m_physicalButtons;
    m_physicalButtons = NULL;
}

void Service::onDeviceActiveChanged(const bool& deviceActive) {
    if (!deviceActive)
        return;

/*
    m_notificationGlobalSettings->setMode(NotificationMode::Normal);

    bb::platform::Notification::deleteAllFromInbox();
    m_notify->notify();
    this->onNotificationPublished();

    m_notificationGlobalSettings->setMode(NotificationMode::AlertsOff);
    */
}

void Service::onFullscreenPidChanged(const int& pid) {
    bool lockModeEnabled = m_settings->value(SETTINGS_LOCK_MODE_ENABLED, false).toBool();
    if (!lockModeEnabled)
        return;

    Logger::logThis("Service::onFullscreenPidChanged() " + QString::number(pid));

    this->openLockedApp();
}

void Service::onNotificationDone() {
    bb::platform::Notification::deleteAllFromInbox();
}

void Service::onNotificationPublished() {
    QTimer::singleShot(2000, this, SLOT(onNotificationDone()));
}

void Service::onPlusButtonLongPressed() {
    m_settings->setValue(SETTINGS_IS_TRYING_TO_UNLOCK, true);
    this->openLockedApp();
}

void Service::onPowerDownAttempt() {
    this->openLockedApp();
}

void Service::openLockedApp() {
    bool lockModeEnabled = m_settings->value(SETTINGS_LOCK_MODE_ENABLED, false).toBool();
    QString lockedPackageName = m_settings->value(SETTINGS_LOCKED_PACKAGE_NAME, "").toString();

    if (!lockModeEnabled || lockedPackageName.isEmpty())
        return;

    if (m_settings->value(SETTINGS_IS_TRYING_TO_UNLOCK, false).toBool()) {
        bb::PackageInfo packageInfo;
        AppLauncher::openThisApp(packageInfo.installId());
    }
    else
        AppLauncher::openThisApp(m_settings->value(SETTINGS_LOCKED_PACKAGE_NAME).toString());
}
