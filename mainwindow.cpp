//
// Created by ich on 12/20/22.
//

#include "mainwindow.h"
#include <model/XmlModel.h>

#include <QDomDocument>
#include <QTreeView>
#include <QMenuBar>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          //model(new DomModel(QDomDocument(), this)),
          view(new QTreeView(this))
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), QKeySequence::Open, this, &MainWindow::openFile);
    fileMenu->addAction(tr("E&xit"), QKeySequence::Quit, this, &QWidget::close);

    model = new XmlModel();

    view->setModel(model);

    setCentralWidget(view);
    setWindowTitle(tr("Simple DOM Model"));
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    xmlPath );



    if (!filePath.isEmpty()) {
        QUrl fileUrl = QUrl::fromLocalFile(filePath);
        QString content;
        auto transmitFileContent = [&content] (const QString & transmission ) {content = transmission;};
        connect(&fileController, &FileController::fileContent, transmitFileContent);
        fileController.setName(fileUrl);
        qDebug() << content;
        model->receiveText(content);

        //QFile file(filePath);
        //if (file.open(QIODevice::ReadOnly)) {
        //    QDomDocument document;
        //    if (document.setContent(&file)) {
        //        DomModel *newModel = new DomModel(document, this);
        //        view->setModel(newModel);
        //        delete model;
        //        model = newModel;
        //        xmlPath = filePath;
        //    }
        //    file.close();
        //}
    }
}