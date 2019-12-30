#include "interface/mainwindow.h"
#include "ui_mainwindow.h"
#include "treeitem.h"

#include <QDebug>
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    btnWrite = ui->btnWrite;
    btnRead = ui->btnRead;
    textEdit = ui->textEdit;
    btnOpen = ui->btnOpen;

    label = ui->labeldbg;

    editKey = ui->editKey;

    checkBoxCustomTime = ui->checkBoxCustomTime;
    editCustomTime = ui->editCustomTime;

    editCustomTime->setEnabled(false);

    editCustomTime->setDateTime(QDateTime::currentDateTimeUtc());

    connect(btnWrite, SIGNAL(clicked()), this, SLOT(slotForWriteButton()));
    connect(btnOpen, SIGNAL(clicked()), this, SLOT(slotForOpenButton()));
    connect(btnRead, SIGNAL(clicked()), this, SLOT(slotForReadButton()));
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(slotForTextChanged()));
    connect(checkBoxCustomTime, SIGNAL(stateChanged(int)), this, SLOT(slotCheckBoxCustomTime()));

    treeItem = new TreeItem(ui->treeWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slotForTextChanged() {
    label->setText(QString::number(textEdit->toPlainText().length()) + "/999999");
}

void MainWindow::slotForWriteButton() {
    QString text = textEdit->toPlainText();
    if (performWriteToFileHandler(text)) {
        setColorForPushButton(btnWrite, QColor(Qt::red));
    } else {
        setColorForPushButton(btnWrite, QColor(Qt::green));
        textEdit->clear();
    }
}

void MainWindow::slotForOpenButton() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"));

    if (filename.size() < 1 || filename == nullptr) {
        setColorForPushButton(btnOpen, QColor(Qt::red));
    } else {
        setColorForPushButton(btnOpen, QColor(Qt::green));
        setFilenameHandler(filename);
    }
}

void MainWindow::readByTreeWidgetItem(QTreeWidgetItem *item) {
    int year = 0; int month = 0; int day = 0;
    if (item == nullptr || item->parent() == nullptr || item->parent()->parent() == nullptr) return;
    day = item->text(1).toInt();
    month = item->parent()->text(1).toInt();
    year = item->parent()->parent()->text(1).toInt();
    qDebug() << "installConnect item->text = year:" << year << "month:" << month << "day:" << day;
    QDate date(year, month, day);
    QString text;
    performReadByDateHandler(&date, &text);
    textEdit->clear();
    textEdit->setText(text);
}

void MainWindow::expandedTreeWidgetItem(QTreeWidgetItem *item) {
    qDebug() << "DEBUG: expandedTreeWidgetItem item->text(1):" << item->text(1);
    treeItem->sortChildrenOfItem(item);
}

void MainWindow::slotForReadButton() {
    QList<QDate *> dateList;

    if (performReadAllDateHandler(&dateList) > 0) {
        setColorForPushButton(btnRead, QColor(Qt::green));
        qDebug() << "DEBUG performReadAllDatetime is good";
    } else {
        setColorForPushButton(btnRead, QColor(Qt::red));
        qDebug() << "DEBUG performReadAllDatetime <= 0";
        return;
    }
    treeItem->fillTreeByDateList(&dateList);

    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(readByTreeWidgetItem(QTreeWidgetItem *)));
    connect(ui->treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(expandedTreeWidgetItem(QTreeWidgetItem *)));
}

QDateTime MainWindow::getCustomDateTime() {
    return editCustomTime->dateTime();
}

bool MainWindow::isCheckedCheckBoxCustomTime() {
    switch (checkBoxCustomTime->checkState()) {
        case Qt::CheckState::Checked: {
            return true;
        }
        case Qt::CheckState::Unchecked: {
            return false;
        }
        default: {
            qDebug() << "ERROR: slotCheckBoxCustomTime unknown check state = " << checkBoxCustomTime->checkState();
            return false;
        }
    }
}

void MainWindow::slotCheckBoxCustomTime() {
    qDebug() << "DEBUG: slotCheckBoxCustomTime = " << checkBoxCustomTime->checkState();
    editCustomTime->setDateTime(QDateTime::currentDateTimeUtc());
    editCustomTime->setEnabled(isCheckedCheckBoxCustomTime());
}

void MainWindow::setColorForPushButton(QPushButton *btn, QColor color) {
    QPalette pal = btn->palette();
    pal.setColor(QPalette::Button, color);
    btn->setAutoFillBackground(true);
    btn->setPalette(pal);
    btn->update();
}

void MainWindow::setCallbacks(void (*setFilename)(QString filename),
                              int (*performReadByDate)(QDate *date, QString *text),
                              int (*performReadAllDate)(QList<QDate *> *dateList),
                              int (*performWriteToFile)(QString text)) {
    setFilenameHandler = setFilename;
    performReadByDateHandler = performReadByDate;
    performReadAllDateHandler = performReadAllDate;
    performWriteToFileHandler = performWriteToFile;
}

QString MainWindow::getKey() {
    return editKey->text();
}

void MainWindow::clearKey() {
    editKey->clear();
}
