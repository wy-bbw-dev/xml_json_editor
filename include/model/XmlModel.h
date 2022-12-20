#include <QObject>
#include <QAbstractItemModel>
#include <QString>
#include <QDomDocument>


class XmlModel : public QAbstractItemModel {
    Q_OBJECT
public:
    XmlModel(QObject *parent = nullptr);
    QModelIndex index(int row, int column, const QModelIndex &index) const override;
    QModelIndex parent(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

public slots:
    void receiveText(QString text);
    void logTextReceival();
signals:
    void textReceived();
private:
    QString text;
    QDomDocument xmlContent;
};
