#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treeitem.h"
#include "converter.h"

#include <QDebug>
#include "QFileDialog"
#include <string>

#define DEFAULT_COLUMN 1

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

    treeItem = new TreeItem(ui->treeWidget, DEFAULT_COLUMN);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slotForTextChanged() {
    label->setText(QString::number(textEdit->toPlainText().length()) + "/999999");
}

void MainWindow::slotForWriteButton() {
    QString text = textEdit->toPlainText();
    bool isCheckBox = this->isCheckedCheckBoxCustomTime();
    QDateTime datetime = this->getCustomDateTime();
    QString key = getKey();
    std::wstring wtext = Converter::toStdWString(text);
    std::wstring wkey = Converter::toStdWString(key);
    tm datetime_tm = Converter::dateTimeToTm(datetime);
    int stat = performWriteToFile(wtext, isCheckBox, datetime_tm, wkey);
    if (stat) {
        setColorForPushButton(btnWrite, QColor(Qt::red));
    } else {
        setColorForPushButton(btnWrite, QColor(Qt::green));
        textEdit->clear();
    }
}

void MainWindow::slotForOpenButton() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"));

    int retval = 0;
    if (filename.size() >= 1 || filename != nullptr) {
        std::string sfilename = Converter::toStdString(filename);
        retval = this->setFilename(sfilename);
    } else {
        retval = -1;
    }

    QColor color = (retval == 0) ? Qt::green : Qt::red;
    setColorForPushButton(btnOpen, QColor(color));
}

void MainWindow::readByTreeWidgetItem(QTreeWidgetItem *item) {
    int year = 0; int month = 0; int day = 0;
    if (item == nullptr || item->parent() == nullptr || item->parent()->parent() == nullptr) return;
    day = item->text(1).toInt();
    month = item->parent()->text(1).toInt();
    year = item->parent()->parent()->text(1).toInt();
    qDebug() << "installConnect item->text = year:" << year << "month:" << month << "day:" << day;
    QDate date(year, month, day);
    QString key = getKey();
    std::wstring output;
    tm date_tm = Converter::dateToTm(date);
    std::wstring wkey = Converter::toStdWString(key);
    performReadByDate(date_tm, wkey, output);
    textEdit->clear();
    textEdit->setText(Converter::toQString(output));
}

void MainWindow::expandedTreeWidgetItem(QTreeWidgetItem *item) {
    qDebug() << "DEBUG: expandedTreeWidgetItem item->text(1):" << item->text(1);
    treeItem->sortChildrenOfItem(item);
}

void MainWindow::slotForReadButton() {
    QList<QDate *> dateList;
    QString key = getKey();
    std::wstring stdkey = Converter::toStdWString(key);

    std::list<std::wstring> list;
    if (performReadAllDate(stdkey, list) == 0) {
        setColorForPushButton(btnRead, QColor(Qt::green));
        qDebug() << "DEBUG performReadAllDatetime is good";
    } else {
        setColorForPushButton(btnRead, QColor(Qt::red));
        qDebug() << "DEBUG performReadAllDatetime <= 0";
        return;
    }

    std::list<std::wstring>::iterator it;
    for (it = list.begin(); it != list.end(); ++it){
        QString qstring = QString::fromStdWString(*it);
        QDate *qdate = new QDate(QDate::fromString(qstring, QString("yyyy/M/dd")));
        dateList.append(qdate);
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
    // TODO: need set time from tm??
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

QString MainWindow::getKey() {
    return editKey->text();
}

void MainWindow::clearKey() {
    editKey->clear();
}
