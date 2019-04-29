#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QResizeEvent>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(400,400);
    this->setMaximumSize(1920,1080);


    model = new myListModel(this);

    model->setHeaderData(0,Qt::Horizontal,"X");
    model->setHeaderData(1,Qt::Horizontal,"Y");

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested,this, &MainWindow::slotCustomMenuRequested);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    int w,h;
    w = event->size().width();
    h = event->size().height();
    ui->tableView->setGeometry(20,20,w-40,h-40);
    ui->tableView->setColumnWidth(0,(w-40)/2);
    ui->tableView->setColumnWidth(1,(w-40)/2);
}

void MainWindow::slotCopy()
{
    model->copyData(ui->tableView->selectionModel()->currentIndex());
    ui->tableView->setCurrentIndex(model->index(-1, -1));
}

void MainWindow::slotPaste()
{
    model->insertRows(ui->tableView->selectionModel()->currentIndex().row(),1,QModelIndex());
    ui->tableView->setCurrentIndex(model->index(-1, -1));
}

void MainWindow::slotRemove()
{
    int row = ui->tableView->selectionModel()->currentIndex().row();
    if(row >= 0)
    {
        model->removeRows(row,1,ui->tableView->selectionModel()->currentIndex());
        ui->tableView->setCurrentIndex(model->index(-1, -1));
    }
}

void MainWindow::slotCustomMenuRequested(QPoint index)
{


    QMenu * menu = new QMenu(this);

    QAction * copyDevice = new QAction("Копировать", this);
    QAction * pasteDevice = new QAction("Вставить", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    connect(copyDevice,&QAction::triggered,this, &MainWindow::slotCopy);
    connect(pasteDevice,&QAction::triggered,this, &MainWindow::slotPaste);
    connect(deleteDevice,&QAction::triggered,this, &MainWindow::slotRemove);

    menu->addAction(copyDevice);
    menu->addAction(pasteDevice);
    if(!model->isCopied(QModelIndex()))
        pasteDevice->setEnabled(false);
    menu->addAction(deleteDevice);

    menu->popup(ui->tableView->viewport()->mapToGlobal(index));

}
