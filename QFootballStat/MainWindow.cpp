/*
Copyright (c) 2009 - 2011, Valeriy Soldatov
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

#include <QtGui/QtGui>

#include <sstream>

#include <Clubs.hpp>
#include <ClubInfo.hpp>
#include <ClubName.hpp>
#include <Results.hpp>
#include <Stat.hpp>
#include <Utils.hpp>
#include <Years.hpp>

#include "MainWindow.h"

#define CURRENT_CHAMP_ID "v2010"

using namespace std;

MainWindow::MainWindow() {
    ResultsDB::init("data");

    widget.setupUi(this);
    codec = QTextCodec::codecForName("WINDOWS-1251");

    connect(widget.actionExit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(widget.pushButton_1, SIGNAL(clicked()),
            this, SLOT(selectMode1()));
    connect(widget.pushButton_2, SIGNAL(clicked()),
            this, SLOT(selectMode2()));
    connect(widget.pushButton_3, SIGNAL(clicked()),
            this, SLOT(selectMode3()));
    connect(widget.pushButton_4, SIGNAL(clicked()),
            this, SLOT(selectMode4()));
    connect(widget.pushButton_5, SIGNAL(clicked()),
            this, SLOT(selectMode5()));
    connect(widget.pushButton_6, SIGNAL(clicked()),
            this, SLOT(selectMode6()));
    connect(widget.text, SIGNAL(anchorClicked(const QUrl &)),
            this, SLOT(linkActivated(const QUrl &)));
    selectMode1();
}

MainWindow::~MainWindow() {
}

void MainWindow::selectMode1() {
    calculateTable();
}

void MainWindow::selectMode2() {
    widget.text->setText("<b>Mode 2</b>");
}

void MainWindow::selectMode3() {
    widget.text->setText("<b>Mode 3</b>");
}

void MainWindow::selectMode4() {
    widget.text->setText("<b>Mode 4</b>");
}

void MainWindow::selectMode5() {
    QString qstr("");
    matchResults(qstr);
}

void MainWindow::selectMode6() {
    widget.text->setText("<b>Mode 6</b>");
}

void MainWindow::linkActivated(const QUrl & link) {
    QString code = link.toString().section("_", 0, 0);
    QString id = link.toString().section("_", 1, 1);
    if (code == "cl") {
        calculateClubStat(id);
        return;
    }
    if (code == "match") {
        matchReport(id);
        return;
    }
    return;
}

void MainWindow::matchReport(const QString& matchId) {
    stringstream ss;
    ss << "<h1 align='center'>"
            << "Протокол матча"
            << "</h1>";
    string file_name = "";
    string line = "";
    file_name = "data/" CURRENT_CHAMP_ID "/" + matchId.toStdString() + "p.txt";
    fstream f;
    f.open(file_name.c_str());
    if (f) {
        do {
            getline(f, line);
            ss << line << endl;
        } while (!f.eof());
        f.close();
        f.clear();
    }
    QString qstr = codec->toUnicode(ss.str().c_str());
    widget.text->setText(qstr);
}

void MainWindow::matchResults(const QString& clubId) {
    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* record_result;
    string id = clubId.toStdString();

    stringstream ss;
    if (clubId != "") {
        ss << "<h1 align='center'>"
                << ClubName::getInstance()->getName(clubId.toStdString(), CURRENT_CHAMP_ID)
                << "</h1>";
    } else {
        ss << "<h1 align='center'>"
                << "Результаты матчей"
                << "</h1>";
    }
    if (!years.open()) return;
    while ((record_year = years.next()) != NULL) {
        if (record_year->file_results == CURRENT_CHAMP_ID) {
            results.open(record_year->file_results);
            while ((record_result = results.next()) != NULL) {
                if ((clubId == "") || (record_result->played(id)))
                    ss << record_result->round
                        << "-й тур - "
                        << record_result->date
                        << " "
                        << ClubName::getInstance()->getName(record_result->team_id_1, record_year->file_results)
                    << " - "
                    << ClubName::getInstance()->getName(record_result->team_id_2, record_year->file_results)
                    << " "
                    << record_result->goals_1
                        << ":"
                        << record_result->goals_2
                        << " (<a href='match_" << record_result->id << "'>Протокол</a>)"
                        << "<br>";
            }
        }
        results.close();
    }
    years.close();

    QString qstr = codec->toUnicode(ss.str().c_str());
    widget.text->setText(qstr);
}

void MainWindow::calculateClubStat(const QString& clubId) {
    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* record_result;
    string id = clubId.toStdString();

    stringstream ss;
    ss << "<h1 align='center'>"
            << ClubName::getInstance()->getName(clubId.toStdString(), CURRENT_CHAMP_ID)
            << "</h1>";
    if (!years.open()) return;

    while ((record_year = years.next()) != NULL) {
        if (record_year->file_results == CURRENT_CHAMP_ID) {
            results.open(record_year->file_results);
            while ((record_result = results.next()) != NULL) {
                if (record_result->played(id))
                    ss << record_result->round
                        << "-й тур - "
                        << record_result->date
                        << " "
                        << ClubName::getInstance()->getName(record_result->team_id_1, record_year->file_results)
                    << " - "
                    << ClubName::getInstance()->getName(record_result->team_id_2, record_year->file_results)
                    << " "
                    << record_result->goals_1
                        << ":"
                        << record_result->goals_2
                        << " (<a href='match_" << record_result->id << "'>Протокол</a>)"
                        << "<br>";
            }
        }
        results.close();
    }
    years.close();

    QString qstr = codec->toUnicode(ss.str().c_str());
    widget.text->setText(qstr);
}

void MainWindow::calculateTable() {
    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* record_result;
    Stat stat_table;
    if (!years.open()) return;

    while ((record_year = years.next()) != NULL) {
        if (record_year->file_results == CURRENT_CHAMP_ID) {
            results.open(record_year->file_results);
            while ((record_result = results.next()) != NULL) {
                stat_table.add(record_result);
            }
        }
        results.close();
    }
    years.close();

    vector<Stat::Record*>* v = stat_table.get_sorted_vector_by_3points();
    vector<Stat::Record*>::const_iterator iter;

    stringstream ss;
    ss << "<h1 align='center'>Турнирная таблица</h1>";
    ss << "<table border='1' style='background-color: #99F899;border-color: #FFFFFF;border-width: 2px;'>";
    ss << "<tr>" <<
            "<td>М</td><td><b>Команда</b></td>" <<
            "<td>И</td><td>В</td><td>Н</td><td>П</td><td>Мячи</td><td>О</td>" <<
            "<td><b>И</b></td><td><b>В</b></td><td><b>Н</b></td><td><b>П</b></td><td><b>Мячи</b></td><td><b>О</b></td>" <<
            "<td>И</td><td>В</td><td>Н</td><td>П</td><td>Мячи</td><td>О</td>" <<
            "</tr>";

    int place = 0;
    for (iter = v->begin(); iter != v->end(); ++iter) {
        place++;
        int w = ((*iter)->w1 + (*iter)->w2);
        int d = ((*iter)->d1 + (*iter)->d2);
        int l = ((*iter)->l1 + (*iter)->l2);
        int f = ((*iter)->f1 + (*iter)->f2);
        int a = ((*iter)->a1 + (*iter)->a2);
        ss << "<tr>" <<
                "<td>" << place << "</td>" <<
                "<td><b><a href='cl_" << (*iter)->team_id << "' style='color:#080853;'>" << ClubName::getInstance()->getName((*iter)->team_id, CURRENT_CHAMP_ID) << "</a></b></td>" <<
                "<td>" << (w + d + l) << "</td>" <<
                "<td>" << w << "</td>" <<
                "<td>" << d << "</td>" <<
                "<td>" << l << "</td>" <<
                "<td>" << f << " - " << a << "</td>" <<
                "<td>" << (3 * w + d) << "</td>" <<

                "<td><b>" << ((*iter)->w1 + (*iter)->d1 + (*iter)->l1) << "</b></td>" <<
                "<td><b>" << (*iter)->w1 << "</b></td>" <<
                "<td><b>" << (*iter)->d1 << "</b></td>" <<
                "<td><b>" << (*iter)->l1 << "</b></td>" <<
                "<td><b>" << (*iter)->f1 << " - " << (*iter)->a1 << "</b></td>" <<
                "<td><b>" << (3 * (*iter)->w1 + (*iter)->d1) << "</b></td>" <<

                "<td>" << ((*iter)->w2 + (*iter)->d2 + (*iter)->l2) << "</td>" <<
                "<td>" << (*iter)->w2 << "</td>" <<
                "<td>" << (*iter)->d2 << "</td>" <<
                "<td>" << (*iter)->l2 << "</td>" <<
                "<td>" << (*iter)->f2 << " - " << (*iter)->a2 << "</td>" <<
                "<td>" << (3 * (*iter)->w2 + (*iter)->d2) << "</td>" <<

                "</tr>";
    }
    ss << "</table>";
    QString qstr = codec->toUnicode(ss.str().c_str());
    widget.text->setText(qstr);
}
