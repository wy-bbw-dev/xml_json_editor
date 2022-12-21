#pragma once
#include <QObject>
#include <QAbstractItemModel>
#include <QString>
#include <model/DomItem.h>
#include <QDomDocument>

class XmlModel : public QAbstractItemModel {
    Q_OBJECT
public:
    enum {
        NAME_ROLE = Qt::UserRole,
        ATTRIBUTE_ROLE,
        VALUE_ROLE
    };
    explicit XmlModel(QObject *parent = nullptr);
    QModelIndex index(int row, int column, const QModelIndex &index) const override;
    QModelIndex parent(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void update();
public slots:
    void receiveText(QString text);
    void logTextReceival();
signals:
    void textReceived();
private:
    QDomDocument xmlContent;
    std::unique_ptr<DomItem> root = nullptr;
};
