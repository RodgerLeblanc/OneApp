APP_NAME = OneAppService

CONFIG += qt warn_on

include(config.pri)

LIBS += -lbb -lbbdata -lbbdevice -lbbplatform -lbbsystem
QT += sql declarative
