#include <QApplication>
#include <QDeclarativeView>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationName("QUbuntuOne");
    app.setApplicationName("Declarative Music Example");

    QDeclarativeView view(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
