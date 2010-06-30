/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created: Wed 30. Jun 22:34:15 2010
**      by: Qt User Interface Compiler version 4.6.3
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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainform
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *pathLabel;
    QPushButton *selectPathButton;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboTeam1;
    QComboBox *comboTeam2;
    QPushButton *button;
    QPushButton *button2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QLineEdit *fromGoals1;
    QLineEdit *fromGoals2;
    QLineEdit *tillGoals2;
    QLineEdit *tillGoals1;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QDateEdit *dateFrom;
    QDateEdit *dateTill;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *button3;
    QTableWidget *table;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainform)
    {
        if (mainform->objectName().isEmpty())
            mainform->setObjectName(QString::fromUtf8("mainform"));
        mainform->resize(700, 600);
        centralwidget = new QWidget(mainform);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        pathLabel = new QLabel(centralwidget);
        pathLabel->setObjectName(QString::fromUtf8("pathLabel"));
        pathLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 255, 107);"));

        gridLayout->addWidget(pathLabel, 1, 3, 1, 1);

        selectPathButton = new QPushButton(centralwidget);
        selectPathButton->setObjectName(QString::fromUtf8("selectPathButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selectPathButton->sizePolicy().hasHeightForWidth());
        selectPathButton->setSizePolicy(sizePolicy);
        selectPathButton->setMinimumSize(QSize(80, 0));
        selectPathButton->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(selectPathButton, 1, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 6, 1, 1);

        comboTeam1 = new QComboBox(centralwidget);
        comboTeam1->setObjectName(QString::fromUtf8("comboTeam1"));

        gridLayout->addWidget(comboTeam1, 3, 1, 1, 1);

        comboTeam2 = new QComboBox(centralwidget);
        comboTeam2->setObjectName(QString::fromUtf8("comboTeam2"));

        gridLayout->addWidget(comboTeam2, 3, 3, 1, 1);

        button = new QPushButton(centralwidget);
        button->setObjectName(QString::fromUtf8("button"));

        gridLayout->addWidget(button, 11, 1, 1, 1);

        button2 = new QPushButton(centralwidget);
        button2->setObjectName(QString::fromUtf8("button2"));

        gridLayout->addWidget(button2, 11, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        fromGoals1 = new QLineEdit(centralwidget);
        fromGoals1->setObjectName(QString::fromUtf8("fromGoals1"));

        gridLayout->addWidget(fromGoals1, 8, 1, 1, 1);

        fromGoals2 = new QLineEdit(centralwidget);
        fromGoals2->setObjectName(QString::fromUtf8("fromGoals2"));

        gridLayout->addWidget(fromGoals2, 8, 3, 1, 1);

        tillGoals2 = new QLineEdit(centralwidget);
        tillGoals2->setObjectName(QString::fromUtf8("tillGoals2"));

        gridLayout->addWidget(tillGoals2, 10, 3, 1, 1);

        tillGoals1 = new QLineEdit(centralwidget);
        tillGoals1->setObjectName(QString::fromUtf8("tillGoals1"));

        gridLayout->addWidget(tillGoals1, 10, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 7, 1, 1, 3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 9, 1, 1, 3);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 1, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 3, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 1, 1, 3);

        dateFrom = new QDateEdit(centralwidget);
        dateFrom->setObjectName(QString::fromUtf8("dateFrom"));
        dateFrom->setDateTime(QDateTime(QDate(1900, 1, 1), QTime(0, 0, 0)));

        gridLayout->addWidget(dateFrom, 6, 1, 1, 1);

        dateTill = new QDateEdit(centralwidget);
        dateTill->setObjectName(QString::fromUtf8("dateTill"));
        dateTill->setDateTime(QDateTime(QDate(2100, 1, 1), QTime(0, 0, 0)));

        gridLayout->addWidget(dateTill, 6, 3, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 5, 1, 1, 1);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 5, 3, 1, 1);

        button3 = new QPushButton(centralwidget);
        button3->setObjectName(QString::fromUtf8("button3"));
        button3->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(button3, 11, 5, 1, 1);

        table = new QTableWidget(centralwidget);
        table->setObjectName(QString::fromUtf8("table"));

        gridLayout->addWidget(table, 12, 1, 1, 5);


        horizontalLayout->addLayout(gridLayout);

        mainform->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainform);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 20));
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
        pathLabel->setText(QString());
        selectPathButton->setText(QApplication::translate("mainform", "...", 0, QApplication::UnicodeUTF8));
        button->setText(QApplication::translate("mainform", "\320\237\320\265\321\200\320\265\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", 0, QApplication::UnicodeUTF8));
        button2->setText(QApplication::translate("mainform", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("mainform", "\320\227\320\260\320\261\320\270\321\202\320\276 \320\274\321\217\321\207\320\265\320\271 (\320\276\321\202):", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mainform", "\320\227\320\260\320\261\320\270\321\202\320\276 \320\274\321\217\321\207\320\265\320\271 (\320\264\320\276):", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mainform", "\320\232\320\276\320\274\320\274\320\260\320\275\320\264\320\260 1:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("mainform", "\320\232\320\276\320\274\320\274\320\260\320\275\320\264\320\260 2:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("mainform", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\270\320\275\321\202\320\265\321\200\320\262\320\260\320\273", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("mainform", "\320\276\321\202:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("mainform", "\320\264\320\276:", 0, QApplication::UnicodeUTF8));
        button3->setText(QApplication::translate("mainform", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainform: public Ui_mainform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
