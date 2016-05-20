APP_NAME = OneApp
HEADLESS_SERVICE = $${APP_NAME}Service

CONFIG += qt warn_on cascades10

include(config.pri)

LIBS += -lbb -lbbdata -lbbdevice -lbbsystem

INCLUDEPATH += ../../$${HEADLESS_SERVICE}/src