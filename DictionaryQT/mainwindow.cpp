#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyDictionary.h"

#include<QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadFileButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open File", QString(), "*.json");
    dictionary.loadFromFile(str);
    setItemsInTableView();
}


void MainWindow::on_SaveFileButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter(tr("Text files (*.json)"));
    if (dialog.exec()) {
        QString filePath = dialog.selectedFiles().first();
        dictionary.saveToFile(filePath);
    }
}


void MainWindow::on_addFileButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open File", QString(), "*.txt");
    dictionary.addWordsFromFile(str);
    setItemsInTableView();
}


void MainWindow::setItemsInTableView() {
    QMap<QString, int> map = dictionary.getDict();

    QStandardItemModel *model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(QStringList() << "Слово" << "Встречаемость");

    int row = 0;
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        QStandardItem *item1 = new QStandardItem(it.key());
        QStandardItem *item2 = new QStandardItem(QString::number(it.value()));

        model->setItem(row, 0, item1);
        model->setItem(row, 1, item2);
        row++;
    }
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}
