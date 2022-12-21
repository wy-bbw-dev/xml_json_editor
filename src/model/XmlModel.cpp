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

QHash<int, QByteArray> XmlModel::roleNames() const {
    spdlog::info("asking for role names");
    QHash<int, QByteArray> names;
    names[NAME_ROLE] = "name";
    names[ATTRIBUTE_ROLE] = "attributes";
    names[VALUE_ROLE] = "value";
    return names;
}

void XmlModel::logTextReceival() {
    spdlog::info("xmlmodel received new text");
}

QModelIndex XmlModel::index(int row, int column, const QModelIndex& parent) const {
    spdlog::info("index:: asking for index {} {}", row, column);
    if (!hasIndex(row, column, parent)) {
        spdlog::info("index:: doesn't have index, returning empty model index");
        return QModelIndex();
    }

    DomItem *parentItem = parent.isValid() ? static_cast<DomItem*>(parent.internalPointer()) : root.get();
    {
        QDomNode node = parentItem->node();
        spdlog::info("index:: parent node name: {}", node.nodeName().toStdString());
    }
    DomItem *childItem = parentItem->child(row);
    if (childItem) {
        spdlog::info("index:: returning after creating child index");    
        return createIndex(row, column, childItem);
    }
    spdlog::info("index:: returning empty QModelIndex");
    return QModelIndex();
}

QModelIndex XmlModel::parent(const QModelIndex& child) const {
    if (!child.isValid()) {
        spdlog::info("parent:: returning empty model index because child is invalid");
        return QModelIndex();
    }
    DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
    DomItem *parentItem = childItem->parent();
    if (!parentItem) {
        spdlog::info("parent:: returning empty model index because no parent or parent is root");
        return QModelIndex();
    }
    spdlog::info("parent:: creating index for parent");
    return createIndex(parentItem->row(), 0, parentItem);
}

int XmlModel::rowCount(const QModelIndex& parent) const {
    spdlog::info("row count:: ");
    //if (parent.column() > 0) {
    //    spdlog::info("rowCount:: parentcolumn > 0, return ing 0");
    //    return 0;
    //}
    if (!root) {
        spdlog::info("rowCount:: root not initialized: 0 childnodes");
        return 0;
    }
    DomItem* parentItem = parent.isValid() ? static_cast<DomItem*>(parent.internalPointer()) : root.get();
    int noOfChildNodes = parentItem->node().childNodes().count();
    spdlog::info("rowCount:: no of childnodes {}", noOfChildNodes);
    return noOfChildNodes;
}

QVariant XmlModel::data(const QModelIndex& index, int role) const {
    spdlog::info("querying data: ");
    if (!index.isValid()) return QVariant();

    const DomItem  *item = static_cast<DomItem*>(index.internalPointer());
    const QDomNode node = item->node();
    switch (role) {
        case NAME_ROLE:
            {
                spdlog::info("first entry: {}", node.nodeName().toStdString());
                
            return node.nodeName();
            }
        case ATTRIBUTE_ROLE:
        {
            const QDomNamedNodeMap attributeMap = node.attributes();
            QStringList attributes;
            for (int i = 0; i < attributeMap.count(); ++i) {
                QDomNode attribute = attributeMap.item(i);
                attributes << attribute.nodeName() + " = '" + attribute.nodeValue() + "'";
            }
            return attributes.join('\n');
        }
        case VALUE_ROLE:
            return node.nodeValue().split('\n').join(' ');
        default:
            break;
    }
    return QVariant();
}

int XmlModel::columnCount(const QModelIndex& index) const {
    spdlog::info("columnCount");
    return 1;
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
