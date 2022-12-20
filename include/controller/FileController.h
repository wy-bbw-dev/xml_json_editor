#include <QObject>
#include <QUrl>
#include <QtQml/qqmlregistration.h>

class FileController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QUrl file  READ name WRITE setName)
    Q_PROPERTY(QUrl folder READ currentFolder)
public:
    FileController(QObject *parent = nullptr);
    QUrl name() const;
private:
    void setName(const QUrl& name); 
    QUrl currentFolder() const;
private slots:
    void logNewFileOpened() const;
    void readNewFile() const;
signals:
    void filenameChanged() const;
    void fileContent(QString fileContent) const;
private:
    QUrl filename;
};
