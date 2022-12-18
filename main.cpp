#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/xml_json/ui/mainwindow/MainWindow.qml"_qs);
    engine.load(url);
    return app.exec();
}
