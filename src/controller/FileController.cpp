#include <controller/FileController.h>
#include <QDebug>
#include <QStandardPaths>

FileController::FileController(QObject *parent) : QObject(parent) {
    connect(this, &FileController::filenameChanged, this, &FileController::someErrorOutput);
}

void FileController::setName(QUrl name) {
    filename = name; 
    emit filenameChanged();
}

QUrl FileController::name() {return filename;}

void FileController::someErrorOutput() {
    qDebug() << "new filename: " << filename;
}

QUrl FileController::currentFolder() {
    if (filename.isEmpty()) {
        QString defaultLocation = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
        qDebug() << "default location: " << defaultLocation;
        return QUrl::fromLocalFile(defaultLocation);
    }
    return filename;
}
