#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <controller/FileController.h>
#include <model/XmlModel.h>

static constexpr const char* const URI = "xmljsoneditor";
static constexpr const int MAJOR = 1;
static constexpr const int MINOR = 0;

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;


    qmlRegisterType<FileController>(URI, MAJOR, MINOR, "FileController");
    qmlRegisterType<XmlModel>(URI, MAJOR, MINOR, "XmlModel");

    const QUrl url(u"qrc:/xmljsoneditor/ui/mainwindow/MainWindow.qml"_qs);
    engine.load(url);
    return app.exec();
}
//#include <QApplication>
//#include "mainwindow.h"
//
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    MainWindow window;
//    window.resize(640, 480);
//    window.show();
//    return app.exec();
//}
