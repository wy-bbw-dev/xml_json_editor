#include <controller/FileController.h>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>
#include <spdlog/spdlog.h>

FileController::FileController(QObject *parent) : QObject(parent) {
    connect(this, &FileController::filenameChanged, this, &FileController::logNewFileOpened);
    connect(this, &FileController::filenameChanged, this, &FileController::readNewFile);
}

void FileController::setName(const QUrl& name) {
    filename = name; 
    emit filenameChanged();
}

QUrl FileController::name() const {return filename;}

void FileController::logNewFileOpened() const {
    spdlog::info("opening file: {}", filename.path().toStdString());
}

QUrl FileController::currentFolder() const {
    if (filename.isEmpty()) {
        const QString defaultLocation = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];
        return QUrl::fromLocalFile(defaultLocation);
    }
    return filename;
}

void FileController::readNewFile() const {
    QFile file(filename.path());
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream text(&file);
        QString content = text.readAll();
        emit fileContent(content);
    } else {
        spdlog::error("could not open file {}. Resource may be busy or does not exist",  filename.path().toStdString());
    }
}
