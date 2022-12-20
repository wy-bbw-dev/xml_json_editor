#include <QDebug>
#include <model/XmlModel.h>
#include <spdlog/spdlog.h>
#include <model/DomItem.h>

XmlModel::XmlModel(QObject *parent) : QAbstractItemModel(parent) {
    connect(this, &XmlModel::textReceived, this, &XmlModel::logTextReceival);
}

void XmlModel::receiveText(QString text) {
    QString errorMessage;
    int errorLine = -1;
    int errorColumn = -1;
    xmlContent.setContent(text, &errorMessage, &errorLine, &errorColumn);
    if (!errorMessage.isEmpty()) {
        spdlog::error("error parsing xml in line {}, column {}, {}", errorLine, errorColumn, errorMessage.toStdString());
        return;
    } else {
        update();
        emit textReceived();
    }

}

void XmlModel::logTextReceival() {
    spdlog::info("xmlmodel received new text");
}

QModelIndex XmlModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) return QModelIndex();

    DomItem *parentItem = parent.isValid() ? static_cast<DomItem*>(parent.internalPointer()) : root.get();
    DomItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex XmlModel::parent(const QModelIndex& child) const {
    if (!child.isValid()) return QModelIndex();
    DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
    DomItem *parentItem = childItem->parent();
    if (!parentItem || parentItem == root.get()) return QModelIndex();
    return createIndex(parentItem->row(), 0, parentItem);
}

int XmlModel::rowCount(const QModelIndex& parent) const {
    if (parent.column() > 0) return 0;
    if (!root) return 0;
    DomItem* parentItem = parent.isValid() ? static_cast<DomItem*>(parent.internalPointer()) : root.get();
    return parentItem->node().childNodes().count();
}

QVariant XmlModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();
    if (role != Qt::DisplayRole) return QVariant();

    const DomItem  *item = static_cast<DomItem*>(index.internalPointer());
    const QDomNode node = item->node();
    switch (index.column()) {
        case 0:
            return node.nodeName();
        case 1:
        {
            const QDomNamedNodeMap attributeMap = node.attributes();
            QStringList attributes;
            for (int i = 0; i < attributeMap.count(); ++i) {
                QDomNode attribute = attributeMap.item(i);
                attributes << attribute.nodeName() + " = '" + attribute.nodeValue() + "'";
            }
            return attributes.join('\n');
        }
        case 2:
            return node.nodeValue().split('\n').join(' ');
        default:
            break;
    }
    return QVariant();
}

int XmlModel::columnCount(const QModelIndex& index) const {
    return 3;
}

void XmlModel::update() {
    emit beginResetModel();
    root = std::make_unique<DomItem>(xmlContent, 0);
    spdlog::info("roots name is: {}", root->node().nodeName().toStdString());
    emit endResetModel();
}

Qt::ItemFlags XmlModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
}

QVariant XmlModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Attribute");
            case 2:
                return tr("Value");
            default:
                break;
        }
    }
    return QVariant();
}
