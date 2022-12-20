//
// Created by ich on 12/20/22.
//
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <controller/FileController.h>
#include <model/XmlModel.h>

class DomModel;
QT_BEGIN_NAMESPACE
class QMenu;
class QTreeView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void openFile();

private:
    XmlModel *model;
    QMenu *fileMenu;
    QString xmlPath;
    QTreeView *view;
    FileController fileController;
};

#endif //XML_JSON_EDITOR_MAINWINDOW_H
