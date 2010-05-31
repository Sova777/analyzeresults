/*
Copyright (c) 2009 - 2010, Valeriy Soldatov
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
 * Neither the name of the football.mojgorod.ru nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include <Clubs.hpp>
#include <ClubInfo.hpp>
#include <ClubName.hpp>
#include <Results.hpp>
#include <Stat.hpp>
#include <Utils.hpp>
#include <Years.hpp>

#include "mainwindow.hpp"

using namespace std;

MainWindow::MainWindow() {

    codec = QTextCodec::codecForName("WINDOWS 1251");
    pathToDB = "./data";

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    resize(800, 500);

    grid = new QGridLayout(widget);

    QLabel* label1 = new QLabel(QString::fromUtf8("Путь к результатам:"));
    label1->setFixedWidth(160);
    grid->addWidget(label1, 0, 0);

    pathButton = new QLabel(QString::fromUtf8(pathToDB.c_str()));
    pathButton->setStyleSheet("background-color: #33FF33");
    pathButton->setFixedWidth(320);
    grid->addWidget(pathButton, 0, 1);

    QPushButton* selectPathButton = new QPushButton(QString::fromUtf8("..."));
    selectPathButton->setFixedWidth(40);
    connect(selectPathButton, SIGNAL(clicked()),
            this, SLOT(selectPath()));
    grid->addWidget(selectPathButton, 0, 2);

    QLabel* label2 = new QLabel(QString::fromUtf8(""));
    label2->setFixedWidth(160);
    grid->addWidget(label2, 1, 0);

    QPushButton *button = new QPushButton(QString::fromUtf8("Обновить"));
    button->setFixedWidth(150);
    connect(button, SIGNAL(clicked()),
            this, SLOT(clicked()));
    grid->addWidget(button, 2, 0);

    table = new QTableWidget(0, 8);
    table->setColumnWidth(0, 240);
    for (int i = 1; i < 8; i++) {
        table->setColumnWidth(i, 70);
    }

    grid->addWidget(table, 3, 0, 1, 4);
}

void MainWindow::selectPath() {
    QString qstr = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Укажите путь к результатам"),
            NULL, QFileDialog::ShowDirsOnly);
    pathToDB = qstr.toStdString();
    pathButton->setText(qstr);
}

void MainWindow::clicked() {
    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* record_result;
    Stat stat_table;
    Clubs clubs;

    ResultsDB::init(pathToDB);

    if (!years.open()) return;
    while ((record_year = years.next()) != NULL) {
        results.open(record_year->file_results);
        while ((record_result = results.next()) != NULL) {
            stat_table.add(record_result);
        }
        results.close();
    }
    years.close();

    vector<Stat::Record*>* v = stat_table.get_sorted_vector_by_default();
    vector<Stat::Record*>::const_iterator iter;
    table->setRowCount(v->size());
    int place = 0;
    for (iter = v->begin(); iter != v->end(); ++iter) {
        place++;
        int w = ((*iter)->w1 + (*iter)->w2);
        int d = ((*iter)->d1 + (*iter)->d2);
        int l = ((*iter)->l1 + (*iter)->l2);
        int f = ((*iter)->f1 + (*iter)->f2);
        int a = ((*iter)->a1 + (*iter)->a2);

        stringstream ss;
        ss << clubs.get_latest_club_name((*iter)->team_id);
        setCellValue(place - 1, 0, ss.str());

        stringstream ss2;
        ss2 << (w + d + l);
        setCellValue(place - 1, 1, ss2.str());

        stringstream ss3;
        ss3 << w;
        setCellValue(place - 1, 2, ss3.str());

        stringstream ss4;
        ss4 << d;
        setCellValue(place - 1, 3, ss4.str());

        stringstream ss5;
        ss5 << l;
        setCellValue(place - 1, 4, ss5.str());

        stringstream ss6;
        ss6 << f << " : " << a;
        setCellValue(place - 1, 5, ss6.str());

        stringstream ss7;
        ss7 << (2 * w + d);
        setCellValue(place - 1, 6, ss7.str());

        stringstream ss8;
        ss8 << (*iter)->unknown << "?";
        setCellValue(place - 1, 7, ss8.str());
    }
    statusBar()->showMessage(QString::fromUtf8("Таблица обновлена."), 5000);
}

void MainWindow::setCellValue(int row, int column, string value) {
        QString qstr = codec->toUnicode(value.c_str());
        QTableWidgetItem* stlb = new QTableWidgetItem(qstr);
        stlb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        table->setItem(row, column, stlb);
}
