#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mylistmodel.h"
#include <QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent * event);
private slots:
    void slotCopy();
    void slotPaste();
    void slotRemove();
    void slotCustomMenuRequested(QPoint index);
private:
    Ui::MainWindow *ui;
    myListModel *model;
    QModelIndex *buff, *tmp;
    QPoint point;
    quintptr buffer;
};

#endif // MAINWINDOW_H
