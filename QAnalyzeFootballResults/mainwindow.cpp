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
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    resize(1000, 600);

    grid = new QGridLayout(widget);

    QPushButton *button = new QPushButton(QString::fromUtf8("Обновить"));
    button->setFixedWidth(200);

    connect(button, SIGNAL(clicked()),
            this, SLOT(clicked()));

    grid->addWidget(button, 0, 0);

    QLabel* label1 = new QLabel("ddd");
    label1->setFixedWidth(20);
    grid->addWidget(label1, 1, 0);

    QFont font("Tahoma", 20);
    lblPlayer1 = new QLabel("501");
    lblPlayer1->setFixedWidth(80);
    lblPlayer1->setFont(font);
    grid->addWidget(lblPlayer1, 2, 0);

    table = new QTableWidget(1, 1);
    table->setColumnWidth(0, 500);
    grid->addWidget(table, 3, 0);

    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* record_result;
    Stat stat_table;
    Clubs clubs;

    string path = "./data";

    ResultsDB::init(path);

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
        string str2 = clubs.get_latest_club_name((*iter)->team_id);
        stringstream ss;
        ss <<
                place << " " <<
                clubs.get_latest_club_name((*iter)->team_id) << " " <<
                (w + d + l) << " " <<
                w << " " <<
                d << " " <<
                l << " " <<
                f << ":" <<
                a << " " <<
                (2 * w + d) << "   " <<
                (*iter)->unknown << "?";
        QString qstr = QString::fromStdString(ss.str());
        QTableWidgetItem* stlb = new QTableWidgetItem(qstr);
        stlb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        table->setItem(place - 1, 0, stlb);
    }
}
