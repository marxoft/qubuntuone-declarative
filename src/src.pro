TEMPLATE = lib
CONFIG += qt plugin
QT += declarative network

TARGET = qubuntuoneplugin

contains(MEEGO_EDITION,harmattan) {
    LIBS += -L../../qubuntuone/lib -lqubuntuone

    INCLUDEPATH += ../../qubuntuone/src

    CONFIG += link_pkgconfig

} else {
    LIBS += -L/usr/lib -lqubuntuone

    INCLUDEPATH += /usr/include/qubuntuone

    CONFIG += link_prl
    PKGCONFIG = libqubuntuone
}

HEADERS += plugin.h \
    declarativetoken.h \
    declarativetoken_p.h \
    declarativeaccount.h \
    declarativeaccount_p.h \
    declarativeuser.h \
    declarativeuser_p.h \
    declarativenodelistmodel.h \
    declarativenodelistmodel_p.h \
    declarativestoragequota.h \
    declarativestoragequota_p.h

SOURCES += plugin.cpp \
    declarativetoken.cpp \
    declarativetoken_p.cpp \
    declarativeaccount.cpp \
    declarativeaccount_p.cpp \
    declarativeuser.cpp \
    declarativeuser_p.cpp \
    declarativenodelistmodel.cpp \
    declarativenodelistmodel_p.cpp \
    declarativestoragequota.cpp \
    declarativestoragequota_p.cpp

qdeclarativesources.files = qmldir

contains(MEEGO_EDITION,harmattan) {
    qdeclarativesources.path = /usr/lib/qt4/imports/com/marxoft/qubuntuone
    target.path = /usr/lib/qt4/imports/com/marxoft/qubuntuone
} else {
    qdeclarativesources.path = $$[QT_INSTALL_IMPORTS]/com/marxoft/qubuntuone
    target.path = $$[QT_INSTALL_IMPORTS]/com/marxoft/qubuntuone
}

INSTALLS += qdeclarativesources target

symbian {
    include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
    TARGET.EPOCALLOWDLLDATA = 1
}

maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)
