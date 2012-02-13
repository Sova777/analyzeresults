/*
Copyright (c) 2009 - 2012, Valeriy Soldatov
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

#include <QtGui>
#include <QtXml>

#include "MainWindow.h"
#include "Report.h"
#include "constants.h"
#include "ui_MainWindow.h"

using namespace std;

MainWindow::MainWindow() {

    widget.setupUi(this);

    connect(widget.actionExit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(widget.actionSave, SIGNAL(triggered()),
            this, SLOT(save()));
    connect(widget.actionOpen, SIGNAL(triggered()),
            this, SLOT(open()));
    connect(widget.actionAbout, SIGNAL(triggered()),
            this, SLOT(about()));

    connect(widget.actionCalculateGoals, SIGNAL(triggered()),
            this, SLOT(calculateGoals()));
    connect(widget.actionCalculateMatches, SIGNAL(triggered()),
            this, SLOT(calculateMatches()));
    connect(widget.actionCalculateReferies, SIGNAL(triggered()),
            this, SLOT(calculateReferies()));
    connect(widget.actionCalculateCoaches, SIGNAL(triggered()),
            this, SLOT(calculateCoaches()));
    connect(widget.actionCalculateTable, SIGNAL(triggered()),
            this, SLOT(calculateTable()));
    connect(widget.actionCalculateStadiums, SIGNAL(triggered()),
            this, SLOT(calculateStadiums()));
    connect(widget.actionCalculatePlayers, SIGNAL(triggered()),
            this, SLOT(calculatePlayers()));
    connect(widget.actionCalculateTeams, SIGNAL(triggered()),
            this, SLOT(calculateTeams()));
    connect(widget.actionVerifyPlayers, SIGNAL(triggered()),
            this, SLOT(verifyPlayers()));
    connect(widget.actionVerifyPlayers2, SIGNAL(triggered()),
            this, SLOT(verifyPlayers2()));
    connect(widget.actionVerifyAttendance, SIGNAL(triggered()),
            this, SLOT(verifyAttendance()));
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
    connect(widget.pushButton_7, SIGNAL(clicked()),
            this, SLOT(selectMode7()));
    connect(widget.pushButton_8, SIGNAL(clicked()),
            this, SLOT(selectMode8()));
    connect(widget.text, SIGNAL(anchorClicked(const QUrl &)),
            this, SLOT(linkActivated(const QUrl &)));
    connect(widget.table, SIGNAL(cellDoubleClicked(int, int)),
            this, SLOT(cellSelected(int, int)));
    connect(widget.pushRefresh, SIGNAL(clicked()),
            this, SLOT(refresh()));
    connect(widget.pushBack, SIGNAL(clicked()),
            this, SLOT(back()));

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
            "football.mojgorod.ru", "QFootballStat");
    directory = settings.value("currentDir").toString();
    if (directory == "") {
        directory = QString::fromLatin1("xml");
    }
    widget.text->setText(FIRST_MESSAGE);
    widget.text->setVisible(true);
    widget.table->setVisible(false);
    //selectMode1();
}

MainWindow::~MainWindow() {
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
            "football.mojgorod.ru", "QFootballStat");
    settings.setValue("currentDir", directory);
    settings.sync();
    event->accept();
}

void MainWindow::selectMode1() {
    jump("ta01_");
}

void MainWindow::selectMode2() {
    jump("te01_");
}

void MainWindow::selectMode3() {
    jump("re01_");
}

void MainWindow::selectMode4() {
    jump("pl01_");
}

void MainWindow::selectMode5() {
    jump("ma01_");
}

void MainWindow::selectMode6() {
    jump("go01_");
}

void MainWindow::selectMode7() {
    jump("co01_");
}

void MainWindow::selectMode8() {
    jump("st01_");
}

void MainWindow::calculateGoals() {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfGoals, filter, &hash);
    initTable(4);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 180);
    widget.table->setColumnWidth(1, 180);
    widget.table->setColumnWidth(2, 60);
    QStringList titles;
    titles << TABLE_GOALS_COLUMN1
            << TABLE_GOALS_COLUMN2
            << TABLE_GOALS_COLUMN3;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(), 4));
        setCellValue(i, 3, QString("go02_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(2, Qt::DescendingOrder);
}

void MainWindow::calculateGoals2(const QString& player) {
    StatHash hash;
    analyzeXml(&listOfGoals2, player, &hash);
    initTable(6);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 90);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    widget.table->setColumnWidth(4, 60);
    QStringList titles;
    titles << TABLE_GOALS2_COLUMN1
            << TABLE_GOALS2_COLUMN2
            << TABLE_GOALS2_COLUMN3
            << TABLE_GOALS2_COLUMN4
            << TABLE_GOALS2_COLUMN5;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateReferies() {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfReferies, filter, &hash);
    initTable(4);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 180);
    widget.table->setColumnWidth(1, 180);
    widget.table->setColumnWidth(2, 60);
    QStringList titles;
    titles << TABLE_REFERIES_COLUMN1
            << TABLE_REFERIES_COLUMN2
            << TABLE_REFERIES_COLUMN3;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(), 4));
        setCellValue(i, 3, QString("re02_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(2, Qt::DescendingOrder);
}

void MainWindow::calculateReferies2(const QString& referee) {
    StatHash hash;
    analyzeXml(&listOfReferies2, referee, &hash);
    initTable(6);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 90);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    widget.table->setColumnWidth(4, 60);
    QStringList titles;
    titles << TABLE_REFERIES2_COLUMN1
            << TABLE_REFERIES2_COLUMN2
            << TABLE_REFERIES2_COLUMN3
            << TABLE_REFERIES2_COLUMN4
            << TABLE_REFERIES2_COLUMN5;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateCoaches(void) {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfCoaches, filter, &hash);
    initTable(4);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 180);
    widget.table->setColumnWidth(1, 180);
    widget.table->setColumnWidth(2, 60);
    QStringList titles;
    titles << TABLE_COACHES_COLUMN1
            << TABLE_COACHES_COLUMN2
            << TABLE_COACHES_COLUMN3;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
        setCellValue(i, 3, QString("co02_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateCoaches2(const QString& coach) {
    StatHash hash;
    analyzeXml(&listOfCoaches2, coach, &hash);
    initTable(6);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 90);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    widget.table->setColumnWidth(4, 60);
    QStringList titles;
    titles << TABLE_COACHES2_COLUMN1
            << TABLE_COACHES2_COLUMN2
            << TABLE_COACHES2_COLUMN3
            << TABLE_COACHES2_COLUMN4
            << TABLE_COACHES2_COLUMN5;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateStadiums(void) {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfStadiums, filter, &hash);
    initTable(4);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 180);
    widget.table->setColumnWidth(1, 180);
    widget.table->setColumnWidth(2, 60);
    QStringList titles;
    titles << TABLE_STADIUMS_COLUMN1
            << TABLE_STADIUMS_COLUMN2
            << TABLE_STADIUMS_COLUMN3;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
        setCellValue(i, 3, QString("st02_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateStadiums2(const QString& stadium) {
    StatHash hash;
    analyzeXml(&listOfStadiums2, stadium, &hash);
    initTable(6);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 90);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    widget.table->setColumnWidth(4, 60);
    QStringList titles;
    titles << TABLE_STADIUMS2_COLUMN1
            << TABLE_STADIUMS2_COLUMN2
            << TABLE_STADIUMS2_COLUMN3
            << TABLE_STADIUMS2_COLUMN4
            << TABLE_STADIUMS2_COLUMN5;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateMatches() {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfMatches, filter, &hash);
    initTable(5);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 60);
    QStringList titles;
    titles << TABLE_MATCHES_COLUMN1
            << TABLE_MATCHES_COLUMN2
            << TABLE_MATCHES_COLUMN3
            << TABLE_MATCHES_COLUMN4;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, QString(record->getString(0)));
        setCellValue(i, 1, QString(record->getString(1)));
        setCellValue(i, 2, QString(record->getString(2)));
        setCellValue(i, 3, QString(record->getString(3)));
        setCellValue(i, 4, QString("xm01_%1").arg(record->getString(4)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculatePlayers() {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfPlayers, filter, &hash);
    QStringList titles;
    titles << TABLE_PLAYERS_COLUMN1
            << TABLE_PLAYERS_COLUMN2
            << TABLE_PLAYERS_COLUMN3
            << TABLE_PLAYERS_COLUMN4
            << TABLE_PLAYERS_COLUMN5
            << TABLE_PLAYERS_COLUMN6
            << TABLE_PLAYERS_COLUMN7
            << TABLE_PLAYERS_COLUMN8
            << TABLE_PLAYERS_COLUMN9
            << TABLE_PLAYERS_COLUMN10;
    initTable(titles.length() + 1);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 70);
    widget.table->setColumnWidth(3, 70);
    widget.table->setColumnWidth(4, 70);
    widget.table->setColumnWidth(5, 70);
    widget.table->setColumnWidth(6, 70);
    widget.table->setColumnWidth(7, 70);
    widget.table->setColumnWidth(8, 70);
    widget.table->setColumnWidth(9, 70);
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, QString(record->getString(0)));
        setCellValue(i, 1, QString(record->getString(1)));
        setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
        setCellValue(i, 3, QString("%1").arg(record->get(1), 4));
        setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
        setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
        setCellValue(i, 6, QString("%1").arg(record->get(4) + record->get(5), 4));
        setCellValue(i, 7, QString("%1").arg(record->get(5), 4));
        setCellValue(i, 8, QString("%1").arg(record->get(6), 4));
        setCellValue(i, 9, QString("%1").arg(record->get(7), 4));
        setCellValue(i, 10, QString("pl02_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculatePlayers2(const QString& player) {
    StatHash hash;
    analyzeXml(&listOfPlayers2, player, &hash);
    initTable(6);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 90);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    widget.table->setColumnWidth(4, 60);
    QStringList titles;
    titles << TABLE_PLAYERS2_COLUMN1
            << TABLE_PLAYERS2_COLUMN2
            << TABLE_PLAYERS2_COLUMN3
            << TABLE_PLAYERS2_COLUMN4
            << TABLE_PLAYERS2_COLUMN5;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateTable() {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfTable, filter, &hash);
    initTable(9);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 180);
    QStringList titles;
    titles << TABLE_TABLE_COLUMN1
            << TABLE_TABLE_COLUMN2
            << TABLE_TABLE_COLUMN3
            << TABLE_TABLE_COLUMN4
            << TABLE_TABLE_COLUMN5
            << TABLE_TABLE_COLUMN6
            << TABLE_TABLE_COLUMN7
            << TABLE_TABLE_COLUMN8;
    widget.table->setHorizontalHeaderLabels(titles);
    for (int j = 1; j < 8; j++) {
        widget.table->setColumnWidth(j, 60);
    }
    int i = 0;

    foreach(StatHashValue* record, hash) {
        int points = 3 * record->get(0) + record->get(1);
        int games = record->get(0) + record->get(1) + record->get(2);
        setCellValue(i, 0, record->getString());
        setCellValue(i, 1, QString::number(games));
        for (int k = 0; k < 5; k++) {
            setCellValue(i, 2 + k, QString::number(record->get(k)));
        }
        setCellValue(i, 7, QString("%1").arg(points, 4));
        setCellValue(i, 8, QString("ta02_%1").arg(record->getString()));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(7, Qt::DescendingOrder);
}

void MainWindow::calculateTable2(const QString& team) {
    StatHash hash;
    analyzeXml(&listOfTable2, team, &hash);
    initTable(6);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 90);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    widget.table->setColumnWidth(4, 60);
    QStringList titles;
    titles << TABLE_TABLE2_COLUMN1
            << TABLE_TABLE2_COLUMN2
            << TABLE_TABLE2_COLUMN3
            << TABLE_TABLE2_COLUMN4
            << TABLE_TABLE2_COLUMN5;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateTeams() {
    StatHash hash;
    StatHash hash_stat;
    QString filter = "";
    analyzeXml(&listOfPlayers, filter, &hash);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        QString key = QString("%1").arg(record->getString(1));
        Record* record_stat = Record::getInstance(hash_stat, key);
        record_stat->setString(key);
        record_stat->add(1);
        delete record;
        i++;
    }
    hash.clear();
    initTable(3);
    widget.table->setRowCount(hash_stat.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 60);
    QStringList titles;
    titles << TABLE_TEAMS_COLUMN1
            << TABLE_TEAMS_COLUMN2;
    widget.table->setHorizontalHeaderLabels(titles);
    i = 0;

    foreach(StatHashValue* record, hash_stat) {
        setCellValue(i, 0, QString(record->getString(0)));
        setCellValue(i, 1, QString("%1").arg(record->get(), 4));
        setCellValue(i, 2, QString("te02_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash_stat.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateTeams2(const QString& team) {
    StatHash hash;
    StatHash hash_stat;
    QString filter = "";
    analyzeXml(&listOfPlayers, filter, &hash);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        if (record->getString(1) == team) {
            QString key = QString("%1").arg(record->getString(0));
            Record* record_stat = Record::getInstance(hash_stat, key);
            record_stat->setString(record->getString(0), 0);
            record_stat->setString(record->getString(1), 1);
            record_stat->set(record->get(0), 0);
            delete record;
            i++;
        }
    }
    hash.clear();
    initTable(4);
    widget.table->setRowCount(hash_stat.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 60);
    QStringList titles;
    titles << TABLE_TEAMS2_COLUMN1
            << TABLE_TEAMS2_COLUMN2
            << TABLE_TEAMS2_COLUMN3;
    widget.table->setHorizontalHeaderLabels(titles);
    i = 0;

    foreach(StatHashValue* record, hash_stat) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
        setCellValue(i, 3, QString("pl02_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash_stat.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::verifyPlayers(void) {
    StatHash hash;
    QString filter = "";
    analyzeXml(&checkListOfPlayers, filter, &hash);
    initTable(6);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    widget.table->setColumnWidth(4, 120);
    QStringList titles;
    titles << TABLE_MATCHINFO_COLUMN1
            << TABLE_MATCHINFO_COLUMN2
            << TABLE_MATCHINFO_COLUMN3
            << TABLE_MATCHINFO_COLUMN4
            << TABLE_MATCHINFO_COLUMN5;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::verifyPlayers2(void) {
    StatHash hash;
    QString filter = "";
    analyzeXml(&checkListOfPlayers2, filter, &hash);
    initTable(5);
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    QStringList titles;
    titles << TABLE_CHECKPLAYERS2_COLUMN1
            << TABLE_CHECKPLAYERS2_COLUMN2
            << TABLE_CHECKPLAYERS2_COLUMN3
            << TABLE_CHECKPLAYERS2_COLUMN4;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        if (record->get() > 1) {
            i++;
        }
    }
    widget.table->setRowCount(i);
    i = 0;

    foreach(StatHashValue* record, hash) {
        if (record->get() > 1) {
            setCellValue(i, 0, record->getString(1));
            setCellValue(i, 1, record->getString(2));
            setCellValue(i, 2, record->getString(3));
            setCellValue(i, 3, record->getString(4));
            setCellValue(i, 4, QString(""));
            delete record;
            i++;
        }
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::verifyAttendance(void) {
    StatHash hash;
    QString filter = "";
    analyzeXml(&checkListOfAttendance, filter, &hash);
    initTable(6);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setColumnWidth(3, 120);
    widget.table->setColumnWidth(4, 120);
    QStringList titles;
    titles << TABLE_MATCHINFO_COLUMN1
            << TABLE_MATCHINFO_COLUMN2
            << TABLE_MATCHINFO_COLUMN3
            << TABLE_MATCHINFO_COLUMN4
            << TABLE_MATCHINFO_COLUMN5;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;

    foreach(StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

// SAX парсер
void MainWindow::analyzeXml(pointer func, const QString& filter, StatHash* hash) {
    bool emptyCache = (reports.size() == 0) ? true : false;
    int counter = 0;
    statusBar()->showMessage(STATUS_CALCULATING);
    const QCursor cursor = this->cursor();
    this->setCursor(Qt::WaitCursor);
    QApplication::processEvents();
    QTime t;
    t.start();
    QDate fromDate = widget.dateEditFrom->date();
    QDate tillDate = widget.dateEditTill->date();
    if (emptyCache) {
        QDir qDir = QDir(directory);
        QDirIterator it(qDir.absolutePath(), QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            if (!it.fileInfo().isDir()) {
                counter++;
                QString fileName = it.fileName();
                if (!fileName.endsWith(QLatin1String(".xml"))) continue;
                QString fullFileName = it.fileInfo().absoluteFilePath();
                QFile file(fullFileName);
                if (!file.open(QIODevice::ReadOnly)) continue;
                Report report = saxParser(file);
                reports.append(report);
                file.close();
            }
            if ((counter % 100) == 0) {
                statusBar()->showMessage(QString("%1 (%2 %3)")
                        .arg(STATUS_CALCULATING)
                        .arg(counter)
                        .arg(STATUS_CALCULATING2));
                QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
            }
        }
    }
    counter = 0;
    foreach(Report report, reports) {
        counter++;
        QDate date = report.getDate();
        if ((date >= fromDate) && (date <= tillDate)) {
            (*func)(report, report.getFileName(), filter, hash);
        }
        if ((counter % 1000) == 0) {
            statusBar()->showMessage(QString("%1 (%2 %3)")
                    .arg(STATUS_CALCULATING_MEMORY)
                    .arg(counter)
                    .arg(STATUS_CALCULATING_MEMORY2));
            QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
        }
    }
    this->setCursor(cursor);
    QString status = STATUS_TIME.arg(t.elapsed());
    statusBar()->showMessage(status, 2000);
    return;
}

Report MainWindow::saxParser(QFile& file) {
    Report report;
    report.setFileName(file);
    QXmlStreamReader xml(&file);
    QString currentTag;
    QString currentId;
    while (!xml.atEnd()) {
        xml.readNext();
        QStringRef ref = xml.name();
        if (xml.isStartElement()) {
            currentTag = ref.toString();
            if (currentTag == "team1") {
                report.setTeam1Attributes(xml);
            } else if (currentTag == "team2") {
                report.setTeam2Attributes(xml);
            } else if (currentTag == "date") {
                report.setDateAttributes(xml);
            } else if (currentTag == "coach1") {
                report.setCoach1Attributes(xml);
            } else if (currentTag == "coach2") {
                report.setCoach2Attributes(xml);
            } else if (currentTag == "stadium") {
                report.setStadiumAttributes(xml);
            } else if (currentTag == "referee") {
                report.setRefereeAttributes(xml);
            } else if (currentTag == "match") {
                report.setMatchAttributes(xml);
            } else if (currentTag == "event") {
                report.addEvent(xml);
            } else if (currentTag == "player1") {
                currentId = xml.attributes().value("id").toString();
            } else if (currentTag == "player2") {
                currentId = xml.attributes().value("id").toString();
            }
        } else if (xml.isCharacters()) {
            if (currentTag == "team1") {
                report.setTeam1(xml);
            } else if (currentTag == "team2") {
                report.setTeam2(xml);
            } else if (currentTag == "date") {
                report.setDate(xml);
            } else if (currentTag == "score") {
                report.setScore(xml);
            } else if (currentTag == "coach1") {
                report.setCoach1(xml);
            } else if (currentTag == "coach2") {
                report.setCoach2(xml);
            } else if (currentTag == "stadium") {
                report.setStadium(xml);
            } else if (currentTag == "referee") {
                report.setReferee(xml);
            } else if (currentTag == "player1") {
                report.addPlayer1(xml, currentId);
            } else if (currentTag == "player2") {
                report.addPlayer2(xml, currentId);
            }
        } else {
            currentTag = "";
        }
    }
    if (xml.hasError()) {
        qDebug() << "file has error";
    }
    return report;
}

void MainWindow::linkActivated(const QUrl & link) {
    QString code = link.toString().section("_", 0, 0);
    QString id = link.toString().section("_", 1, 1);
    if (code == "cl") {
        //calculateTeamStat(id);
        return;
    }
    if (code == "match") {
        //matchReport(id);
        return;
    }
    return;
}

void MainWindow::setCellValue(int row, int column, QString value) {
    QTableWidgetItem* stlb = new QTableWidgetItem(value);
    stlb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    widget.table->setItem(row, column, stlb);
}

void MainWindow::open() {
    QString dir = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Выберите директорий"), directory);
    if (dir != "") {
        directory = dir;
        reports.clear();
    }
    widget.text->setText(FIRST_MESSAGE);
    widget.text->setVisible(true);
    widget.table->setVisible(false);
}

void MainWindow::about() {
    QMessageBox::about(this, QString::fromUtf8("О программе QFootballStat"), QString::fromUtf8("<h2>QFootballStat</h2><p>Создана Солдатовым Валерием Фёдоровичем для сайта <a href='http://football.mojgorod.ru'>http://football.mojgorod.ru</a></p>"));
}

void MainWindow::save() {
    QString qstr = QFileDialog::getSaveFileName(this, QString::fromUtf8("Выберите имя файла"), NULL);
    if (qstr == "") return;
    QFile file(qstr);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);
    int rows = widget.table->rowCount();
    int columns = widget.table->columnCount();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (!widget.table->isColumnHidden(j)) {
                out << widget.table->item(i, j)->text() << " | ";
            }
        }
        out << "\n";
    }
    file.close();
}

void MainWindow::initTable(int columns) {
    if (columns < 0) {
        return;
    }
    widget.table->setVisible(true);
    widget.text->setVisible(false);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(columns);
    for (int j = 0; j < (columns - 1); j++) {
        widget.table->setColumnHidden(j, false);
    }
    widget.table->setColumnHidden(columns - 1, true);
}

void MainWindow::cellSelected(int row, int column) {
    QTableWidgetItem* item = widget.table->item(row, widget.table->columnCount() - 1);
    if (item != NULL) {
        QString link = item->text();
        jump(link);
    }
}

void MainWindow::jump(const QString link) {
    int size = link.length();
    if (size < 5) {
        return;
    }
    previous = current;
    current = link;
    QString code = link.left(5);
    QString id = link.right(size - 5);
    if (code == "xm01_") {
        report(id);
        return;
    }
    if (code == "ma01_") {
        calculateMatches();
        return;
    }
    if (code == "st01_") {
        calculateStadiums();
        return;
    }
    if (code == "st02_") {
        calculateStadiums2(id);
        return;
    }
    if (code == "re01_") {
        calculateReferies();
        return;
    }
    if (code == "re02_") {
        calculateReferies2(id);
        return;
    }
    if (code == "co01_") {
        calculateCoaches();
        return;
    }
    if (code == "co02_") {
        calculateCoaches2(id);
        return;
    }
    if (code == "pl01_") {
        calculatePlayers();
        return;
    }
    if (code == "pl02_") {
        calculatePlayers2(id);
        return;
    }
    if (code == "go01_") {
        calculateGoals();
        return;
    }
    if (code == "go02_") {
        calculateGoals2(id);
        return;
    }
    if (code == "te01_") {
        calculateTeams();
        return;
    }
    if (code == "te02_") {
        calculateTeams2(id);
        return;
    }
    if (code == "ta01_") {
        calculateTable();
        return;
    }
    if (code == "ta02_") {
        calculateTable2(id);
        return;
    }
}

void MainWindow::report(const QString& fileName) {
    widget.table->setVisible(false);
    widget.text->setVisible(true);
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        widget.text->setText("");
        return;
    }
    Report report = saxParser(file);
    file.close();
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QString coach1 = report.getCoach1();
    QString coach2 = report.getCoach2();
    QString score = report.getScore();
    QString time = report.getTime();
    QDate date = report.getDate();
    QString rcity = report.getRefereeCity();
    QString referee = report.getReferee();
    QString round = report.getMatchRound();
    QString tournament = report.getMatchTournament();
    QString city = report.getStadiumCity();
    QString attendance = report.getStadiumAttendance();
    QString stadium = report.getStadium();
    QString text = QString::fromUtf8("<h1 align='center'>%1</h1>")
            .arg(tournament);
    text.append(QString::fromUtf8("<h2 align='center'>Тур: %1</h2>")
            .arg(round));
    text.append(QString::fromUtf8("<h2 align='center'>%1 - %2 - %3</h2>")
            .arg(team1)
            .arg(team2)
            .arg(score));
    text.append(QString::fromUtf8("<p>%2. %1. %3 зрителей<br><b>Судья:</b> %4 (%5)<br>%7 %6</p>")
            .arg(stadium)
            .arg(city)
            .arg(attendance)
            .arg(referee)
            .arg(rcity)
            .arg(time)
            .arg(date.toString(Qt::DefaultLocaleLongDate)));

    // игроки
    QVector<Report::Player> players1 = report.getPlayers1();
    text.append(QString::fromLatin1("<table border='0' width='100%'>"));
    text.append(QString::fromLatin1("<tr><td>"));
    uint length1 = players1.size();
    for (uint i = 0; i < length1; i++) {
        QString value = players1.at(i).player;
        if (i != 0) {
            text.append(QString("<br>"));
        }
        text.append(QString("%1").arg(value));
    }
    text.append(QString::fromLatin1("</td><td>"));
    QVector<Report::Player> players2 = report.getPlayers2();
    uint length2 = players2.size();
    for (uint i = 0; i < length2; i++) {
        QString value = players2.at(i).player;
        if (i != 0) {
            text.append(QString("<br>"));
        }
        text.append(QString("%1").arg(value));
    }
    text.append(QString::fromLatin1("</td></tr>"));
    text.append(QString::fromUtf8("<tr><td><b>Тренер:</b> %1</td><td><b>Тренер:</b> %2</td></tr>").arg(coach1).arg(coach2));
    text.append(QString::fromLatin1("</table>"));

    // события в матче
    text.append(QString::fromLatin1("<table border='0' width='100%'>"));
    QVector<Report::Event> events = report.getEvents();
    uint length = events.size();
    for (uint i = 0; i < length; i++) {
        QString eventType = events.at(i).type;
        QString player = events.at(i).player;
        QString player2 = events.at(i).player2;
        QString team = events.at(i).team;
        QString time = events.at(i).time;
        if (eventType == EVENT_GOAL) {
            text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/goal.png'>").arg(eventType).arg(team).arg(player));
        } else if (eventType == EVENT_GOAL_PENALTY) {
            text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/pen.png'>").arg(eventType).arg(team).arg(player));
        } else if (eventType == EVENT_MISSED_PENALTY) {
            text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/missed.png'>").arg(eventType).arg(team).arg(player));
        } else if (eventType == EVENT_AUTOGOAL) {
            text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/autogoal.png'>").arg(eventType).arg(team).arg(player));
        } else if (eventType == EVENT_RED_CARD) {
            text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/red.png'>").arg(eventType).arg(team).arg(player));
        } else if (eventType == EVENT_RED_YELLOW_CARD) {
            text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/yellow2.png'>").arg(eventType).arg(team).arg(player));
        } else if (eventType == EVENT_YELLOW_CARD) {
            text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5</td></tr>").arg(time).arg("<img src=':/icon/images/yellow.png'>").arg(eventType).arg(team).arg(player));
        } else if (eventType == EVENT_SUBSTITUTION) {
            text.append(QString("<tr><td>%1'</td><td>%2 %3</td><td>%4</td><td>%5 - %6</td></tr>").arg(time).arg("<img src=':/icon/images/subs.png'>").arg(eventType).arg(team).arg(player).arg(player2));
        } else if (player2 == "") {
            text.append(QString("<tr><td>%1'</td><td>%2</td><td>%3</td><td>%4</td></tr>").arg(time).arg(eventType).arg(team).arg(player));
        } else {
            text.append(QString("<tr><td>%1'</td><td>%2</td><td>%3</td><td>%4 - %5</td></tr>").arg(time).arg(eventType).arg(team).arg(player).arg(player2));
        }
    }
    text.append(QString::fromLatin1("</table>"));
    widget.text->setText(text);
}

void MainWindow::refresh() {
    jump(current);
}

void MainWindow::back() {
    jump(previous);
}
