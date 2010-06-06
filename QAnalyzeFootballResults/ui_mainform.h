/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created: Mon 7. Jun 00:23:38 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainform
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pathButton;
    QTableView *table;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QDateEdit *dateEdit;
    QDateEdit *dateEdit_2;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainform)
    {
        if (mainform->objectName().isEmpty())
            mainform->setObjectName(QString::fromUtf8("mainform"));
        mainform->resize(604, 546);
        centralwidget = new QWidget(mainform);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-1, -1, 552, 356));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 255, 107);"));

        gridLayout->addWidget(label_2, 1, 3, 1, 1);

        pathButton = new QPushButton(gridLayoutWidget);
        pathButton->setObjectName(QString::fromUtf8("pathButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pathButton->sizePolicy().hasHeightForWidth());
        pathButton->setSizePolicy(sizePolicy);
        pathButton->setMinimumSize(QSize(50, 0));
        pathButton->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(pathButton, 1, 5, 1, 1);

        table = new QTableView(gridLayoutWidget);
        table->setObjectName(QString::fromUtf8("table"));

        gridLayout->addWidget(table, 12, 1, 1, 6);

        horizontalSpacer = new QSpacerItem(102, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 6, 1, 1);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 3, 1, 1, 1);

        comboBox_2 = new QComboBox(gridLayoutWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 3, 3, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 11, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 11, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 8, 1, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 8, 3, 1, 1);

        lineEdit_3 = new QLineEdit(gridLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 10, 3, 1, 1);

        lineEdit_4 = new QLineEdit(gridLayoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 10, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 7, 1, 1, 3);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 9, 1, 1, 3);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 3, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 1, 1, 3);

        dateEdit = new QDateEdit(gridLayoutWidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        gridLayout->addWidget(dateEdit, 6, 1, 1, 1);

        dateEdit_2 = new QDateEdit(gridLayoutWidget);
        dateEdit_2->setObjectName(QString::fromUtf8("dateEdit_2"));

        gridLayout->addWidget(dateEdit_2, 6, 3, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 5, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 5, 3, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 11, 5, 1, 1);

        mainform->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainform);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 604, 20));
        mainform->setMenuBar(menubar);
        statusbar = new QStatusBar(mainform);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        mainform->setStatusBar(statusbar);

        retranslateUi(mainform);

        QMetaObject::connectSlotsByName(mainform);
    } // setupUi

    void retranslateUi(QMainWindow *mainform)
    {
        mainform->setWindowTitle(QApplication::translate("mainform", "\320\220\320\275\320\260\320\273\320\270\320\267 \321\204\321\203\321\202\320\261\320\276\320\273\321\214\320\275\321\213\321\205 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainform", "\320\237\321\203\321\202\321\214 \320\272 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\260\320\274:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mainform", "./data", 0, QApplication::UnicodeUTF8));
        pathButton->setText(QApplication::translate("mainform", "...", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("mainform", "\320\237\320\265\321\200\320\265\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("mainform", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("mainform", "\320\227\320\260\320\261\320\270\321\202\320\276 \320\274\321\217\321\207\320\265\320\271 (\320\276\321\202):", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mainform", "\320\227\320\260\320\261\320\270\321\202\320\276 \320\274\321\217\321\207\320\265\320\271 (\320\264\320\276):", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mainform", "\320\232\320\276\320\274\320\274\320\260\320\275\320\264\320\260 1:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("mainform", "\320\232\320\276\320\274\320\274\320\260\320\275\320\264\320\260 2:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("mainform", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\270\320\275\321\202\320\265\321\200\320\262\320\260\320\273", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("mainform", "\320\276\321\202:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("mainform", "\320\264\320\276:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("mainform", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainform: public Ui_mainform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
