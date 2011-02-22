/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created: Tue 22. Feb 22:40:31 2011
**      by: Qt User Interface Compiler version 4.7.1
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
#include <QtGui/QToolBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainform
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QToolBox *toolBox;
    QWidget *page;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QLabel *pathLabel;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *selectPathButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboTeam1;
    QComboBox *comboTeam2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QDateEdit *dateFrom;
    QDateEdit *dateTill;
    QLabel *label_3;
    QLineEdit *fromGoals1;
    QLineEdit *fromGoals2;
    QLabel *label_4;
    QLineEdit *tillGoals1;
    QLineEdit *tillGoals2;
    QPushButton *button;
    QPushButton *button2;
    QPushButton *button3;
    QTableWidget *table;
    QWidget *page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainform)
    {
        if (mainform->objectName().isEmpty())
            mainform->setObjectName(QString::fromUtf8("mainform"));
        mainform->resize(700, 628);
        centralwidget = new QWidget(mainform);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolBox = new QToolBox(centralwidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 680, 516));
        horizontalLayout_2 = new QHBoxLayout(page);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 3, 1, 1);

        pathLabel = new QLabel(page);
        pathLabel->setObjectName(QString::fromUtf8("pathLabel"));
        pathLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(94, 255, 107);"));

        gridLayout_2->addWidget(pathLabel, 1, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 5, 1, 1);

        selectPathButton = new QPushButton(page);
        selectPathButton->setObjectName(QString::fromUtf8("selectPathButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selectPathButton->sizePolicy().hasHeightForWidth());
        selectPathButton->setSizePolicy(sizePolicy);
        selectPathButton->setMinimumSize(QSize(80, 0));
        selectPathButton->setMaximumSize(QSize(50, 16777215));

        gridLayout_2->addWidget(selectPathButton, 1, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 7, 1, 1);

        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 2, 1, 1, 1);

        label_6 = new QLabel(page);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 4, 1, 1);

        comboTeam1 = new QComboBox(page);
        comboTeam1->setObjectName(QString::fromUtf8("comboTeam1"));

        gridLayout_2->addWidget(comboTeam1, 3, 1, 1, 1);

        comboTeam2 = new QComboBox(page);
        comboTeam2->setObjectName(QString::fromUtf8("comboTeam2"));

        gridLayout_2->addWidget(comboTeam2, 3, 4, 1, 1);

        label_7 = new QLabel(page);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 4, 1, 1, 1);

        label_8 = new QLabel(page);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 5, 1, 1, 1);

        label_9 = new QLabel(page);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 5, 4, 1, 1);

        dateFrom = new QDateEdit(page);
        dateFrom->setObjectName(QString::fromUtf8("dateFrom"));
        dateFrom->setDateTime(QDateTime(QDate(1900, 1, 1), QTime(0, 0, 0)));

        gridLayout_2->addWidget(dateFrom, 6, 1, 1, 1);

        dateTill = new QDateEdit(page);
        dateTill->setObjectName(QString::fromUtf8("dateTill"));
        dateTill->setDateTime(QDateTime(QDate(2100, 1, 1), QTime(0, 0, 0)));

        gridLayout_2->addWidget(dateTill, 6, 4, 1, 1);

        label_3 = new QLabel(page);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 7, 1, 1, 1);

        fromGoals1 = new QLineEdit(page);
        fromGoals1->setObjectName(QString::fromUtf8("fromGoals1"));

        gridLayout_2->addWidget(fromGoals1, 8, 1, 1, 1);

        fromGoals2 = new QLineEdit(page);
        fromGoals2->setObjectName(QString::fromUtf8("fromGoals2"));

        gridLayout_2->addWidget(fromGoals2, 8, 4, 1, 1);

        label_4 = new QLabel(page);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 9, 1, 1, 1);

        tillGoals1 = new QLineEdit(page);
        tillGoals1->setObjectName(QString::fromUtf8("tillGoals1"));

        gridLayout_2->addWidget(tillGoals1, 10, 1, 1, 1);

        tillGoals2 = new QLineEdit(page);
        tillGoals2->setObjectName(QString::fromUtf8("tillGoals2"));

        gridLayout_2->addWidget(tillGoals2, 10, 4, 1, 1);

        button = new QPushButton(page);
        button->setObjectName(QString::fromUtf8("button"));

        gridLayout_2->addWidget(button, 11, 1, 1, 1);

        button2 = new QPushButton(page);
        button2->setObjectName(QString::fromUtf8("button2"));

        gridLayout_2->addWidget(button2, 11, 4, 1, 1);

        button3 = new QPushButton(page);
        button3->setObjectName(QString::fromUtf8("button3"));
        button3->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(button3, 11, 6, 1, 1);

        table = new QTableWidget(page);
        table->setObjectName(QString::fromUtf8("table"));

        gridLayout_2->addWidget(table, 12, 1, 1, 6);


        horizontalLayout_2->addLayout(gridLayout_2);

        toolBox->addItem(page, QString::fromUtf8("\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 680, 516));
        toolBox->addItem(page_2, QString::fromUtf8("\320\242\321\203\321\200\320\275\320\270\321\200\320\275\320\260\321\217 \321\202\320\260\320\261\320\273\320\270\321\206\320\260"));

        gridLayout->addWidget(toolBox, 1, 1, 5, 5);


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

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mainform);
    } // setupUi

    void retranslateUi(QMainWindow *mainform)
    {
        mainform->setWindowTitle(QApplication::translate("mainform", "\320\220\320\275\320\260\320\273\320\270\320\267 \321\204\321\203\321\202\320\261\320\276\320\273\321\214\320\275\321\213\321\205 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mainform", "\320\237\321\203\321\202\321\214 \320\272 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\260\320\274:", 0, QApplication::UnicodeUTF8));
        pathLabel->setText(QString());
        selectPathButton->setText(QApplication::translate("mainform", "...", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("mainform", "\320\232\320\276\320\274\320\274\320\260\320\275\320\264\320\260 1:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("mainform", "\320\232\320\276\320\274\320\274\320\260\320\275\320\264\320\260 2:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("mainform", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\270\320\275\321\202\320\265\321\200\320\262\320\260\320\273", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("mainform", "\320\276\321\202:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("mainform", "\320\264\320\276:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("mainform", "\320\227\320\260\320\261\320\270\321\202\320\276 \320\274\321\217\321\207\320\265\320\271 (\320\276\321\202):", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("mainform", "\320\227\320\260\320\261\320\270\321\202\320\276 \320\274\321\217\321\207\320\265\320\271 (\320\264\320\276):", 0, QApplication::UnicodeUTF8));
        button->setText(QApplication::translate("mainform", "\320\237\320\265\321\200\320\265\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", 0, QApplication::UnicodeUTF8));
        button2->setText(QApplication::translate("mainform", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213", 0, QApplication::UnicodeUTF8));
        button3->setText(QApplication::translate("mainform", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214...", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("mainform", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("mainform", "\320\242\321\203\321\200\320\275\320\270\321\200\320\275\320\260\321\217 \321\202\320\260\320\261\320\273\320\270\321\206\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainform: public Ui_mainform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
