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
    resize(900, 700);

    grid = new QGridLayout(widget);

    QLabel* label1 = new QLabel(QString::fromUtf8("Путь к результатам:"));
    label1->setFixedWidth(240);
    grid->addWidget(label1, 0, 0);

    pathLabel = new QLabel(QString::fromUtf8(pathToDB.c_str()));
    pathLabel->setStyleSheet("background-color: #33FF33");
    pathLabel->setFixedWidth(320);
    grid->addWidget(pathLabel, 0, 1, 1, 2);

    QPushButton* selectPathButton = new QPushButton(QString::fromUtf8("..."));
    selectPathButton->setFixedWidth(40);
    connect(selectPathButton, SIGNAL(clicked()),
            this, SLOT(selectPath()));
    grid->addWidget(selectPathButton, 0, 3);

    QLabel* team1Label = new QLabel(QString::fromUtf8("Комманда 1:"));
    grid->addWidget(team1Label, 1, 0);

    QLabel* team2Label = new QLabel(QString::fromUtf8("Комманда 2:"));
    grid->addWidget(team2Label, 1, 1);

    comboTeam1 = new QComboBox();
    comboTeam1->setFixedWidth(240);
    grid->addWidget(comboTeam1, 2, 0);

    comboTeam2 = new QComboBox();
    comboTeam2->setFixedWidth(240);
    grid->addWidget(comboTeam2, 2, 1);

    QLabel* timeLabel = new QLabel(QString::fromUtf8("Выбрать интервал"));
    grid->addWidget(timeLabel, 3, 0, 1, 2);

    QLabel* fromLabel = new QLabel(QString::fromUtf8("от:"));
    grid->addWidget(fromLabel, 4, 0);

    QLabel* tillLabel = new QLabel(QString::fromUtf8("до:"));
    grid->addWidget(tillLabel, 4, 1);

    QDate date1(1800, 1, 1);
    QDateEdit* fromDataEdit = new QDateEdit(date1);
    fromDataEdit->setFixedWidth(240);
    grid->addWidget(fromDataEdit, 5, 0);
    
    QDate date2(2100, 1, 1);
    QDateEdit* tillDataEdit = new QDateEdit(date2);
    tillDataEdit->setFixedWidth(240);
    grid->addWidget(tillDataEdit, 5, 1);

    QLabel* fromGoals1Label = new QLabel(QString::fromUtf8("Забито мячей (от):"));
    grid->addWidget(fromGoals1Label, 6, 0, 1, 2);

    fromGoals1LineEdit = new QLineEdit();
    fromGoals1LineEdit->setFixedWidth(240);
    grid->addWidget(fromGoals1LineEdit, 7, 0);

    fromGoals2LineEdit = new QLineEdit();
    fromGoals2LineEdit->setFixedWidth(240);
    grid->addWidget(fromGoals2LineEdit, 7, 1);

    QLabel* fromGoals2Label = new QLabel(QString::fromUtf8("Забито мячей (до):"));
    grid->addWidget(fromGoals2Label, 8, 0, 1, 2);

    QLineEdit* tillGoals1LineEdit = new QLineEdit();
    tillGoals1LineEdit->setFixedWidth(240);
    grid->addWidget(tillGoals1LineEdit, 9, 0);

    QLineEdit* tillGoals2LineEdit = new QLineEdit();
    tillGoals2LineEdit->setFixedWidth(240);
    grid->addWidget(tillGoals2LineEdit, 9, 1);

    QPushButton *button = new QPushButton(QString::fromUtf8("Пересчитать таблицу"));
    connect(button, SIGNAL(clicked()),
            this, SLOT(calculateTable()));
    grid->addWidget(button, 10, 0);

    QPushButton *button2 = new QPushButton(QString::fromUtf8("Показать результаты"));
    connect(button2, SIGNAL(clicked()),
            this, SLOT(calculateResults()));
    grid->addWidget(button2, 10, 1);

    QPushButton *button3 = new QPushButton(QString::fromUtf8("Сохранить..."));
    connect(button3, SIGNAL(clicked()),
            this, SLOT(saveTable()));
    grid->addWidget(button3, 10, 2, 1, 2);

    table = new QTableWidget(0, 1);
    grid->addWidget(table, 11, 0, 1, 5);
    
    redrawForm();
}

void MainWindow::selectPath() {
    QString qstr = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Укажите путь к результатам"),
            NULL, QFileDialog::ShowDirsOnly);
    pathToDB = qstr.toStdString();
    pathLabel->setText(qstr);
    redrawForm();
}

void MainWindow::calculateTable() {
    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* record_result;
    Stat stat_table;
    Clubs clubs;

    ResultsDB::init(pathToDB);
    if (!years.open()) return;

    table->setColumnCount(8);
    table->setColumnWidth(0, 240);
    for (int i = 1; i < 8; i++) {
        table->setColumnWidth(i, 70);
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

void MainWindow::calculateResults() {
    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* r_result;

    ResultsDB::init(pathToDB);

    if (!years.open()) return;
    statusBar()->showMessage(QString::fromUtf8("Считаем..."), 5000);
    table->setColumnCount(4);
    table->setRowCount(50);
    table->setColumnWidth(0, 70);
    table->setColumnWidth(1, 200);
    table->setColumnWidth(2, 200);
    table->setColumnWidth(3, 70);
    int place = 0;

    QString qteam1 = comboTeam1->itemData(comboTeam1->currentIndex()).toString();
    QString qteam2 = comboTeam2->itemData(comboTeam2->currentIndex()).toString();
    QString qfromgoals1 = fromGoals1LineEdit->text();
    string s1 = qfromgoals1.toStdString();
    int fromgoals1 = Utils::toInt(s1);
    QString qfromgoals2 = fromGoals2LineEdit->text();
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
                    if ((place % 50) == 0) table->setRowCount(place + 50);
                    place++;
                    addResultToTable(place, r_result, record_year);
                }
            }
        }
        results.close();
    }
    years.close();
    table->setRowCount(place);
    statusBar()->showMessage(QString::fromUtf8("Таблица обновлена."), 5000);
}

void MainWindow::addResultToTable(int place, Results::Record* r_result, Years::Record* record_year) {
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

void MainWindow::redrawForm() {
    ResultsDB::init(pathToDB);
    Clubs clubs;
    Clubs::Record* r_clubs;
    if (!clubs.open()) return;
    comboTeam1->clear();
    comboTeam2->clear();
    comboTeam1->addItem(" ---------------", "");
    comboTeam2->addItem(" ---------------", "");
    while ((r_clubs = clubs.next()) != NULL) {
        string value1 = r_clubs->club + " (" + r_clubs->city + ")";
        string value2 = r_clubs->id;
        QString qstr = codec->toUnicode(value1.c_str());
        QString qvariant = codec->toUnicode(value2.c_str());
        comboTeam1->addItem(qstr, qvariant);
        comboTeam2->addItem(qstr, qvariant);
    }
    comboTeam1->model()->sort(0);
    comboTeam2->model()->sort(0);
}

void MainWindow::saveTable() {
    return;
}

void MainWindow::setCellValue(int row, int column, string value) {
        QString qstr = codec->toUnicode(value.c_str());
        QTableWidgetItem* stlb = new QTableWidgetItem(qstr);
        stlb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        table->setItem(row, column, stlb);
}
