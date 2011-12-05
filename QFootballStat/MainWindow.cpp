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

#include <QtGui>
#include <QtXml>
#include <sstream>

#include "MainWindow.h"

using namespace std;

const QString EVENT_GOAL = QString::fromUtf8("Гол");
const QString EVENT_GOAL_PENALTY = QString::fromUtf8("Гол с пенальти");
const QString EVENT_AUTOGOAL = QString::fromUtf8("Гол в свои ворота");
const QString EVENT_MISSED_PENALTY = QString::fromUtf8("Незабитый пенальти");
const QString EVENT_SUBSTITUTION = QString::fromUtf8("Замена");
const QString EVENT_YELLOW_CARD = QString::fromUtf8("Предупреждение");
const QString EVENT_RED_CARD = QString::fromUtf8("Удаление");
const QString EVENT_RED_YELLOW_CARD = QString::fromUtf8("Удаление и предупреждение");
const QString STATUS_TIME = QString::fromUtf8("Время: %1 мс.");

const QString TABLE_TABLE_COLUMN1 = QString::fromUtf8("Клуб");
const QString TABLE_TABLE_COLUMN2 = QString::fromUtf8("И");
const QString TABLE_TABLE_COLUMN3 = QString::fromUtf8("В");
const QString TABLE_TABLE_COLUMN4 = QString::fromUtf8("Н");
const QString TABLE_TABLE_COLUMN5 = QString::fromUtf8("П");
const QString TABLE_TABLE_COLUMN6 = QString::fromUtf8("Заб.");
const QString TABLE_TABLE_COLUMN7 = QString::fromUtf8("Проп.");
const QString TABLE_TABLE_COLUMN8 = QString::fromUtf8("О");

const QString TABLE_REFERIES_COLUMN1 = QString::fromUtf8("Судья");
const QString TABLE_REFERIES_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_REFERIES_COLUMN3 = QString::fromUtf8("Игр");

const QString TABLE_GOALS_COLUMN1 = QString::fromUtf8("Игрок");
const QString TABLE_GOALS_COLUMN2 = QString::fromUtf8("Клуб");
const QString TABLE_GOALS_COLUMN3 = QString::fromUtf8("Мячей");

const QString TABLE_MATCHES_COLUMN1 = QString::fromUtf8("Хозяева");
const QString TABLE_MATCHES_COLUMN2 = QString::fromUtf8("Гости");
const QString TABLE_MATCHES_COLUMN3 = QString::fromUtf8("Счёт");

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
    connect(widget.actionCalculateTable, SIGNAL(triggered()),
            this, SLOT(calculateTable()));

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

    directory = QString::fromLatin1("data/xml");
    widget.text->setVisible(false);
    widget.table->setSortingEnabled(true);
    selectMode1();
}

MainWindow::~MainWindow() {
}

void MainWindow::selectMode1() {
    calculateTable();
}

void MainWindow::selectMode2() {
    widget.table->setColumnCount(1);
    widget.table->setRowCount(1);
    widget.table->clear();
}

void MainWindow::selectMode3() {
    calculateReferies();
}

void MainWindow::selectMode4() {
    widget.table->setColumnCount(1);
    widget.table->setRowCount(1);
    widget.table->clear();
}

void MainWindow::selectMode5() {
    calculateMatches();
}

void MainWindow::selectMode6() {
    calculateGoals();
}

void MainWindow::calculateGoals() {
    StatHash hash;
    analyzeXml(&MainWindow::goals, &hash);
    widget.table->setSortingEnabled(false);
    widget.table->clear();
    widget.table->setColumnCount(3);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 180);
    widget.table->setColumnWidth(1, 180);
    widget.table->setColumnWidth(2, 60);
    widget.table->setHorizontalHeaderItem(0, new QTableWidgetItem(TABLE_GOALS_COLUMN1));
    widget.table->setHorizontalHeaderItem(1, new QTableWidgetItem(TABLE_GOALS_COLUMN2));
    widget.table->setHorizontalHeaderItem(2, new QTableWidgetItem(TABLE_GOALS_COLUMN3));
    int i = 0;
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(), 4, 10));
        i++;
    }
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(2, Qt::DescendingOrder);
}

void MainWindow::calculateReferies() {
    StatHash hash;
    analyzeXml(&MainWindow::referies, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(3);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 180);
    widget.table->setColumnWidth(1, 180);
    widget.table->setColumnWidth(2, 60);
    widget.table->setHorizontalHeaderItem(0, new QTableWidgetItem(TABLE_REFERIES_COLUMN1));
    widget.table->setHorizontalHeaderItem(1, new QTableWidgetItem(TABLE_REFERIES_COLUMN2));
    widget.table->setHorizontalHeaderItem(2, new QTableWidgetItem(TABLE_REFERIES_COLUMN3));
    int i = 0;
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(), 4, 10));
        i++;
    }
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(2, Qt::DescendingOrder);
}

void MainWindow::calculateMatches() {
    StatHash hash;
    analyzeXml(&MainWindow::matches, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(3);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 120);
    widget.table->setHorizontalHeaderItem(0, new QTableWidgetItem(TABLE_MATCHES_COLUMN1));
    widget.table->setHorizontalHeaderItem(1, new QTableWidgetItem(TABLE_MATCHES_COLUMN2));
    widget.table->setHorizontalHeaderItem(2, new QTableWidgetItem(TABLE_MATCHES_COLUMN3));
    int i = 0;
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, QString(record->getString(0)));
        setCellValue(i, 1, QString(record->getString(1)));
        setCellValue(i, 2, QString(record->getString(2)));
        i++;
    }
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateTable() {
    StatHash hash;
    analyzeXml(&MainWindow::table, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(8);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 180);
    widget.table->setHorizontalHeaderItem(0, new QTableWidgetItem(TABLE_TABLE_COLUMN1));
    widget.table->setHorizontalHeaderItem(1, new QTableWidgetItem(TABLE_TABLE_COLUMN2));
    widget.table->setHorizontalHeaderItem(2, new QTableWidgetItem(TABLE_TABLE_COLUMN3));
    widget.table->setHorizontalHeaderItem(3, new QTableWidgetItem(TABLE_TABLE_COLUMN4));
    widget.table->setHorizontalHeaderItem(4, new QTableWidgetItem(TABLE_TABLE_COLUMN5));
    widget.table->setHorizontalHeaderItem(5, new QTableWidgetItem(TABLE_TABLE_COLUMN6));
    widget.table->setHorizontalHeaderItem(6, new QTableWidgetItem(TABLE_TABLE_COLUMN7));
    widget.table->setHorizontalHeaderItem(7, new QTableWidgetItem(TABLE_TABLE_COLUMN8));
    for (int j = 1; j < 8; j++) {
        widget.table->setColumnWidth(j, 60);
    }
    int i = 0;
    foreach (StatHashValue* record, hash) {
        int points = 3 * record->get(0) + record->get(1);
        int games = record->get(0) + record->get(1) + record->get(2);
        setCellValue(i, 0, record->getString());
        setCellValue(i, 1, QString::number(games));
        for (int k = 0; k < 5; k++) {
            setCellValue(i, 2 + k, QString::number(record->get(k)));
        }
        setCellValue(i, 7, QString::number(points));
        i++;
    }
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(7, Qt::DescendingOrder);
}

void MainWindow::goals(QDomElement& docElement, StatHash* hash) {
    QDomNodeList nodes = docElement.elementsByTagName("event");
    uint length = nodes.length();
    for (uint i = 0; i < length; i++) {
        QDomElement node = nodes.at(i).toElement();
        QString eventType = node.attributes().namedItem("type").nodeValue();
        QString player = node.attributes().namedItem("player").nodeValue();
        QString club = node.attributes().namedItem("club").nodeValue();
        if ((eventType == EVENT_GOAL) || (eventType == EVENT_GOAL_PENALTY)) {
            QString key = player.append(" (").append(club).append(")");
            if (!hash->contains(key)) {
                hash->insert(key, new Record());
            }
            Record* record = hash->value(key);
            record->setString(player, 0);
            record->setString(club, 1);
            record->add(1);
        }
    }
}

void MainWindow::referies(QDomElement& docElement, StatHash* hash) {
    QDomNodeList nodes = docElement.elementsByTagName("refery");
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        QString name = node.text();
        QString city = node.attributes().namedItem("city").nodeValue();
        QString key = QString("%1 (%2)").arg(name).arg(city);
        if (!hash->contains(key)) {
            hash->insert(key, new Record());
        }
        Record* record = hash->value(key);
        record->setString(name, 0);
        record->setString(city, 1);
        record->add(1);
    }
}

void MainWindow::matches(QDomElement& docElement, StatHash* hash) {
    QDomNodeList nodesTeam1 = docElement.elementsByTagName("team1");
    QDomNodeList nodesTeam2 = docElement.elementsByTagName("team2");
    QDomNodeList nodesScore = docElement.elementsByTagName("score");
    if ((nodesTeam1.length() > 0) && (nodesTeam2.length() > 0) && (nodesScore.length() > 0)) {
        QDomElement nodeTeam1 = nodesTeam1.at(0).toElement();
        QDomElement nodeTeam2 = nodesTeam2.at(0).toElement();
        QDomElement nodeScore = nodesScore.at(0).toElement();
        QString team1 = nodeTeam1.text();
        QString team2 = nodeTeam2.text();
        QString score = nodeScore.text();
        QString key = QString("%1 - %2 %3").arg(team1).arg(team2).arg(score);
        hash->insert(key, new Record());
        Record* record = hash->value(key);
        record->setString(team1, 0);
        record->setString(team2, 1);
        record->setString(score, 2);
    }
}

void MainWindow::table(QDomElement& docElement, StatHash* hash) {
    QDomNodeList nodesTeam1 = docElement.elementsByTagName("team1");
    QDomNodeList nodesTeam2 = docElement.elementsByTagName("team2");
    QDomNodeList nodesScore = docElement.elementsByTagName("score");
    if ((nodesTeam1.length() > 0) && (nodesTeam2.length() > 0) && (nodesScore.length() > 0)) {
        QDomElement nodeTeam1 = nodesTeam1.at(0).toElement();
        QDomElement nodeTeam2 = nodesTeam2.at(0).toElement();
        QDomElement nodeScore = nodesScore.at(0).toElement();
        QString team1 = nodeTeam1.text();
        QString team2 = nodeTeam2.text();
        QString score = nodeScore.text();
        bool ok;
        int goal1 = 99999;
        int goal2 = 99999;
        goal1 = score.section(':', 0, 0).toInt(&ok);
        goal2 = score.section(':', 1, 1).toInt(&ok);
        if(!hash->contains(team1)) {
            hash->insert(team1, new Record());
        }
        if(!hash->contains(team2)) {
            hash->insert(team2, new Record());
        }
        Record* recordTeam1 = hash->value(team1);
        Record* recordTeam2 = hash->value(team2);
        if (recordTeam1->getString() == "") {
            recordTeam1->setString(team1);
        }
        recordTeam1->add(goal1, 3);
        recordTeam1->add(goal2, 4);
        if (recordTeam2->getString() == "") {
            recordTeam2->setString(team2);
        }
        recordTeam2->add(goal2, 3);
        recordTeam2->add(goal1, 4);
        if (goal1 > goal2) {
            recordTeam1->add(1, 0);
            recordTeam2->add(1, 2);
        } else if (goal2 > goal1) {
            recordTeam2->add(1, 0);
            recordTeam1->add(1, 2);
        } else {
            recordTeam2->add(1, 1);
            recordTeam1->add(1, 1);
        }
    }
}

// DOM парсер
void MainWindow::analyzeXml(pointer func, StatHash* hash) {
    QTime t;
    t.start();
    QDir qDir = QDir(directory);
    qDir.setFilter(QDir::Files);
    QStringList list = qDir.entryList();
    QDomDocument xml("report");
    for (int i = 0; i < list.size(); ++i) {
        QString fileName = list.at(i);
        QFile file(qDir.absolutePath() + "/" + fileName);
        if (!file.open(QIODevice::ReadOnly)) continue;
        if (!xml.setContent(&file)) {
            file.close();
            continue;
        }
        file.close();
        QDomElement docElement = xml.documentElement();
        (this->*func)(docElement, hash);
    }
    QString status = STATUS_TIME.arg(t.elapsed());
    statusBar()->showMessage(status, 2000);
    return;
}

void MainWindow::linkActivated(const QUrl & link) {
    QString code = link.toString().section("_", 0, 0);
    QString id = link.toString().section("_", 1, 1);
    if (code == "cl") {
        //calculateClubStat(id);
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
    directory = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Выберите директорий"), directory);
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
            out << widget.table->item(i, j)->text() << " | ";
        }
        out << "\n";
    }
    file.close();
}

//void MainWindow::matchReport(const QString& matchId) {
//    //
//}
//
//void MainWindow::matchResults(const QString& clubId) {
//    //
//}
