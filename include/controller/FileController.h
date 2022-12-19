#include <QObject>
#include <QtQml/qqmlregistration.h>

class FileController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString file  READ name WRITE setName NOTIFY filenameChanged)
private:
    QString filename;
    void setName(QString name); 
public:
    FileController(QObject *parent);
    QString name();
signals:
    void filenameChanged();
};
