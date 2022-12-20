#include <QObject>
#include <QUrl>
#include <QtQml/qqmlregistration.h>

class FileController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QUrl file  READ name WRITE setName)
    Q_PROPERTY(QUrl folder READ currentFolder)
private:
    QUrl filename;
    void setName(QUrl name); 
    QUrl currentFolder();
public:
    FileController(QObject *parent = nullptr);
    QUrl name();
signals:
    void filenameChanged();
private slots:
    void someErrorOutput();
};
