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

#ifndef SERVICE_H_
#define SERVICE_H_

#include <src/DeviceActive/DeviceActive.h>
#include <src/FullscreenPid/FullscreenPid.h>
#include <src/PhysicalButtons/PhysicalButtons.h>
#include <src/Settings/Settings.h>

#include <QObject>
#include <bb/platform/NotificationGlobalSettings>
#include <bb/platform/NotificationMode>

namespace bb {
    class Application;
    namespace platform {
        class Notification;
    }
    namespace system {
        class InvokeManager;
        class InvokeRequest;
    }
}

class Service: public QObject
{
    Q_OBJECT
public:
    Service();
    virtual ~Service() {}

private slots:
    void handleInvoke(const bb::system::InvokeRequest &);
    void onDeviceActiveChanged(const bool&);
    void onFullscreenPidChanged(const int&);
    void onNotificationDone();
    void onNotificationPublished();
    void onPlusButtonLongPressed();
    void onPowerDownAttempt();

private:
    void connectToSignals();
    void disconnectFromSignals();
    void openLockedApp();

    DeviceActive* m_deviceActive;
    FullscreenPid* m_fullscreenPid;
    bb::system::InvokeManager * m_invokeManager;
    bb::platform::NotificationGlobalSettings* m_notificationGlobalSettings;
    bb::platform::Notification * m_notify;
    PhysicalButtons* m_physicalButtons;
    Settings* m_settings;

    bb::platform::NotificationMode::Type m_userNotificationMode;
};

#endif /* SERVICE_H_ */
