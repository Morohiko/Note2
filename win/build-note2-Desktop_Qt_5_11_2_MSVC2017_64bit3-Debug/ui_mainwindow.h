/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QPushButton *btnWrite;
    QTreeWidget *treeWidget;
    QCheckBox *checkBoxCustomTime;
    QLabel *labeldbg;
    QPushButton *btnOpen;
    QDateTimeEdit *editCustomTime;
    QPushButton *btnRead;
    QLineEdit *editKey;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1037, 606);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(16777215, 16777215));
        textEdit->setSizeIncrement(QSize(0, 0));
        textEdit->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        textEdit->setAutoFormatting(QTextEdit::AutoNone);

        gridLayout->addWidget(textEdit, 0, 2, 1, 1);

        btnWrite = new QPushButton(centralWidget);
        btnWrite->setObjectName(QStringLiteral("btnWrite"));

        gridLayout->addWidget(btnWrite, 1, 2, 1, 1);

        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 2);

        checkBoxCustomTime = new QCheckBox(centralWidget);
        checkBoxCustomTime->setObjectName(QStringLiteral("checkBoxCustomTime"));

        gridLayout->addWidget(checkBoxCustomTime, 1, 1, 1, 1);

        labeldbg = new QLabel(centralWidget);
        labeldbg->setObjectName(QStringLiteral("labeldbg"));

        gridLayout->addWidget(labeldbg, 2, 0, 1, 1);

        btnOpen = new QPushButton(centralWidget);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));

        gridLayout->addWidget(btnOpen, 2, 2, 1, 1);

        editCustomTime = new QDateTimeEdit(centralWidget);
        editCustomTime->setObjectName(QStringLiteral("editCustomTime"));

        gridLayout->addWidget(editCustomTime, 1, 0, 1, 1);

        btnRead = new QPushButton(centralWidget);
        btnRead->setObjectName(QStringLiteral("btnRead"));

        gridLayout->addWidget(btnRead, 3, 2, 1, 1);

        editKey = new QLineEdit(centralWidget);
        editKey->setObjectName(QStringLiteral("editKey"));
        editKey->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        editKey->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(editKey, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btnWrite->setText(QApplication::translate("MainWindow", "Write", nullptr));
        checkBoxCustomTime->setText(QApplication::translate("MainWindow", "Custom Time", nullptr));
        labeldbg->setText(QString());
        btnOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
        btnRead->setText(QApplication::translate("MainWindow", "Read", nullptr));
#ifndef QT_NO_ACCESSIBILITY
        editKey->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        editKey->setText(QString());
        editKey->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
