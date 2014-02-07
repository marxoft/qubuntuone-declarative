TEMPLATE = app
TARGET = qubuntuone-declarativefilesexample
INSTALLS += target

LIBS += -L/usr/lib -lqubuntuone

INCLUDEPATH += /usr/include/qubuntuone

CONFIG += link_prl
PKGCONFIG = libqubuntuone

QT += declarative network

SOURCES += src/main.cpp

RESOURCES += src/resources.qrc

OTHER_FILES += src/*.qml

unix {
    target.path = /opt/qubuntuone/bin
}
