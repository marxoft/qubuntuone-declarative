TEMPLATE = app
TARGET = qubuntuone-declarativemusicexample
INSTALLS += target

LIBS += -L/usr/lib -lqubuntuone

INCLUDEPATH += /usr/include/qubuntuone

CONFIG += link_prl
PKGCONFIG = libqubuntuone

QT += declarative network

SOURCES += main.cpp

unix {
    target.path = /opt/qubuntuone/bin
}
