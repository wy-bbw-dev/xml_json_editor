#include <controller/FileController.h>

FileController::FileController(QObject *parent) : QObject(parent) {}

void FileController::setName(QString name) {filename = name;}

QString FileController::name() {return filename;}
