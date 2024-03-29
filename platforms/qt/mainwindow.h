#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "treeitem.h"

#include <QMainWindow>
#include <QLabel>
#include <QTreeWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QDateTimeEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCallbacks(int (*setFilename)(QString &filename),
                      int (*performReadByDate)(QDate &date, QString &key, QString &outputBody),
                      int (*performReadAllDate)(QString &key, QList<QDate *> &dateList),
                      int (*performWriteToFile)(QString &text, bool isCustomTime, QDateTime &datetime, QString &key));

    bool isCheckedCheckBoxCustomTime();
    QDateTime getCustomDateTime();
    QString getKey();
    void clearKey();

private:
    void setColorForPushButton(QPushButton *btn, QColor color);

    QPushButton *btnWrite = nullptr;
    QPushButton *btnRead = nullptr;
    QPushButton *btnOpen = nullptr;

    QTextEdit *textEdit = nullptr;

    QLineEdit *editKey = nullptr;

    QCheckBox *checkBoxCustomTime = nullptr;
    QDateTimeEdit *editCustomTime = nullptr;

    QLabel *label = nullptr;
    Ui::MainWindow *ui;

    TreeItem *treeItem = nullptr;
    QTreeWidget *treeWidget = nullptr;

// callbacks
    int (*setFilenameHandler)(QString &filename);
    int (*performReadByDateHandler)(QDate &date, QString &key, QString &outputBody);
    int (*performReadAllDateHandler)(QString &key, QList<QDate *> &dateList);
    int (*performWriteToFileHandler)(QString &text, bool isCustomTime, QDateTime &datetime, QString &key);

private slots:
    void readByTreeWidgetItem(QTreeWidgetItem *item);
    void expandedTreeWidgetItem(QTreeWidgetItem *item);
    void slotForWriteButton();
    void slotForOpenButton();
    void slotForReadButton();
    void slotForTextChanged();
    void slotCheckBoxCustomTime();
};

#endif // MAINWINDOW_H
