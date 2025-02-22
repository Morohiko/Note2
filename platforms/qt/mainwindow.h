#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "treeitem.h"
#include "note.h"

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

class MainWindow : public QMainWindow, public Note {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
