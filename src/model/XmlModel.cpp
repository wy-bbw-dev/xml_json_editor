#include <QDebug>
#include <model/XmlModel.h>
#include <spdlog/spdlog.h>

XmlModel::XmlModel(QObject *parent) : QAbstractItemModel(parent) {
    connect(this, &XmlModel::textReceived, this, &XmlModel::logTextReceival);
}

void XmlModel::receiveText(QString text) {
    this->text = text; 
    QString errorMessage;
    int errorLine = -1;
    int errorColumn = -1;
    xmlContent.setContent(text, &errorMessage, &errorLine, &errorColumn);
    if (!errorMessage.isEmpty()) {
        spdlog::error("error parsing xml in line {}, column {}, {}", errorLine, errorColumn, errorMessage.toStdString());
    }
}

void XmlModel::logTextReceival() {
    qDebug() << "text received";
    qDebug() << "text: " << text;
}

QModelIndex XmlModel::index(int row, int column, const QModelIndex& index) const {
    throw std::runtime_error("not implemented");
    return QModelIndex();
}

QModelIndex XmlModel::parent(const QModelIndex& parent) const {
    throw std::runtime_error("not implemented");
    return QModelIndex();
}

int XmlModel::rowCount(const QModelIndex& index) const {
    return -1;
}

QVariant XmlModel::data(const QModelIndex& index, int role) const {
    return QVariant();
}

int XmlModel::columnCount(const QModelIndex& index) const {
    return -1;
}
