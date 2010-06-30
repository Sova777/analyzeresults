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

#include <QtGui/QtGui>

#include <Clubs.hpp>
#include <ClubInfo.hpp>
#include <ClubName.hpp>
#include <Results.hpp>
#include <Stat.hpp>
#include <Utils.hpp>
#include <Years.hpp>

#include "mainform.h"

using namespace std;

mainform::mainform() {
    widget.setupUi(this);

    codec = QTextCodec::codecForName("WINDOWS 1251");
    pathToDB = "./data";
    widget.pathLabel->setText(QString::fromStdString(pathToDB));

    connect(widget.selectPathButton, SIGNAL(clicked()),
            this, SLOT(selectPath()));

    connect(widget.button, SIGNAL(clicked()),
            this, SLOT(calculateTable()));

    connect(widget.button2, SIGNAL(clicked()),
            this, SLOT(calculateResults()));

    connect(widget.button3, SIGNAL(clicked()),
            this, SLOT(saveTable()));

    redrawForm();
}

mainform::~mainform() {
}

void mainform::selectPath() {
    QString qstr = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Укажите путь к результатам"),
            NULL, QFileDialog::ShowDirsOnly);
    pathToDB = qstr.toStdString();
    widget.pathLabel->setText(qstr);
    redrawForm();
}

void mainform::calculateTable() {
    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* record_result;
    Stat stat_table;
    Clubs clubs;

    ResultsDB::init(pathToDB);
    if (!years.open()) return;

    widget.table->setColumnCount(8);
    widget.table->setColumnWidth(0, 240);
    for (int i = 1; i < 8; i++) {
        widget.table->setColumnWidth(i, 70);
    }

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
    widget.table->setRowCount(v->size());
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

void mainform::calculateResults() {
    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* r_result;

    ResultsDB::init(pathToDB);

    if (!years.open()) return;
    statusBar()->showMessage(QString::fromUtf8("Считаем..."), 5000);
    widget.table->setColumnCount(4);
    widget.table->setRowCount(50);
    widget.table->setColumnWidth(0, 70);
    widget.table->setColumnWidth(1, 200);
    widget.table->setColumnWidth(2, 200);
    widget.table->setColumnWidth(3, 70);
    int place = 0;

    QString qteam1 = widget.comboTeam1->itemData(widget.comboTeam1->currentIndex()).toString();
    QString qteam2 = widget.comboTeam2->itemData(widget.comboTeam2->currentIndex()).toString();
    QString qfromgoals1 = widget.fromGoals1->text();
    string s1 = qfromgoals1.toStdString();
    int fromgoals1 = Utils::toInt(s1);
    QString qfromgoals2 = widget.fromGoals2->text();
    string s2 = qfromgoals2.toStdString();
    int fromgoals2 = Utils::toInt(s2);

    string team1 = qteam1.toStdString();
    string team2 = qteam2.toStdString();
    bool any = ((team1 == "") && (team2 == ""));
    while ((record_year = years.next()) != NULL) {
        results.open(record_year->file_results);
        while ((r_result = results.next()) != NULL) {
            if (any || ((team2 == "") && r_result->played(team1)) || r_result->played(team1, team2)) {
                if ((any && ((r_result->get_goals_1() >= fromgoals1) || (r_result->get_goals_2() >= fromgoals1)))
                        || (!any && r_result->get_goals_1(team1) >= fromgoals1)) {
                    if ((place % 50) == 0) widget.table->setRowCount(place + 50);
                    place++;
                    addResultToTable(place, r_result, record_year);
                }
            }
        }
        results.close();
    }
    years.close();
    widget.table->setRowCount(place);
    statusBar()->showMessage(QString::fromUtf8("Таблица обновлена."), 5000);
}

void mainform::addResultToTable(int place, Results::Record* r_result, Years::Record* record_year) {
    stringstream ss;
    ss << ((r_result->date != "") ? r_result->date : record_year->year);
    setCellValue(place - 1, 0, ss.str());

    stringstream ss2;
    ss2 << r_result->get_team_name_1(record_year->file_results);
    setCellValue(place - 1, 1, ss2.str());

    stringstream ss3;
    ss3 << r_result->get_team_name_2(record_year->file_results);
    setCellValue(place - 1, 2, ss3.str());

    stringstream ss4;
    ss4 << r_result->goals_1 << ":" << r_result->goals_2;
    setCellValue(place - 1, 3, ss4.str());
}

void mainform::redrawForm() {
    ResultsDB::init(pathToDB);
    Clubs clubs;
    Clubs::Record* r_clubs;
    if (!clubs.open()) return;
    widget.comboTeam1->clear();
    widget.comboTeam2->clear();
    widget.comboTeam1->addItem(" ---------------", "");
    widget.comboTeam2->addItem(" ---------------", "");
    while ((r_clubs = clubs.next()) != NULL) {
        string value1 = r_clubs->club + " (" + r_clubs->city + ")";
        string value2 = r_clubs->id;
        QString qstr = codec->toUnicode(value1.c_str());
        QString qvariant = codec->toUnicode(value2.c_str());
        widget.comboTeam1->addItem(qstr, qvariant);
        widget.comboTeam2->addItem(qstr, qvariant);
    }
    widget.comboTeam1->model()->sort(0);
    widget.comboTeam2->model()->sort(0);
}

void mainform::saveTable() {
    QString qstr = QFileDialog::getSaveFileName(this, QString::fromUtf8("Выберите имя файла"), NULL);
    if (qstr == "") return;
    QFile file(qstr);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    for (int i = 0; i < widget.table->rowCount(); i++) {
        for (int j = 0; j < widget.table->columnCount(); j++) {
            out << widget.table->item(i, j)->text() << " | ";
        }
        out << "\n";
    }
    file.close();
}

void mainform::setCellValue(int row, int column, string value) {
        QString qstr = codec->toUnicode(value.c_str());
        QTableWidgetItem* stlb = new QTableWidgetItem(qstr);
        stlb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        widget.table->setItem(row, column, stlb);
}
