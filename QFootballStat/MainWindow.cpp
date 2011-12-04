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

const QString TABLE_REFERIES_COLUMN1 = QString::fromUtf8("Имя");
const QString TABLE_REFERIES_COLUMN2 = QString::fromUtf8("Игр");

MainWindow::MainWindow() {

    widget.setupUi(this);

    connect(widget.actionExit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(widget.actionSave, SIGNAL(triggered()),
            this, SLOT(save()));
    connect(widget.actionOpen, SIGNAL(triggered()),
            this, SLOT(open()));

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
    QList<StatHashKey> keys = hash.keys();
    qSort(keys.begin(), keys.end());
    widget.table->clear();
    widget.table->setColumnCount(2);
    widget.table->setRowCount(keys.length());
    widget.table->setColumnWidth(0, 240);
    widget.table->setColumnWidth(1, 60);
    int i = 0;
    foreach (StatHashKey key, keys) {
        setCellValue(i, 0, key);
        setCellValue(i, 1, QString::number(hash[key]->get()));
        i++;
    }
}

void MainWindow::calculateReferies() {
    StatHash hash;
    analyzeXml(&MainWindow::referies, &hash);
    QList<StatHashKey> keys = hash.keys();
    qSort(keys.begin(), keys.end());
    widget.table->clear();
    widget.table->setColumnCount(2);
    widget.table->setRowCount(keys.length());
    widget.table->setColumnWidth(0, 240);
    widget.table->setColumnWidth(1, 60);
    widget.table->setHorizontalHeaderItem(0, new QTableWidgetItem(TABLE_REFERIES_COLUMN1));
    widget.table->setHorizontalHeaderItem(1, new QTableWidgetItem(TABLE_REFERIES_COLUMN2));
    int i = 0;
    foreach (StatHashKey key, keys) {
        setCellValue(i, 0, key);
        setCellValue(i, 1, QString::number(hash[key]->get()));
        i++;
    }
}

void MainWindow::calculateMatches() {
    StatHash hash;
    analyzeXml(&MainWindow::matches, &hash);
    QList<StatHashKey> keys = hash.keys();
    qSort(keys.begin(), keys.end());
    widget.table->clear();
    widget.table->setColumnCount(1);
    widget.table->setRowCount(keys.length());
    widget.table->setColumnWidth(0, 360);
    int i = 0;
    foreach (StatHashKey key, keys) {
        setCellValue(i, 0, key);
        i++;
    }
}

void MainWindow::calculateTable() {
    StatHash hash;
    analyzeXml(&MainWindow::table, &hash);
    QList<StatHashValue*> keys = hash.values();
    qSort(keys.begin(), keys.end(), Record::less);
    widget.table->clear();
    widget.table->setColumnCount(8);
    widget.table->setRowCount(keys.length());
    widget.table->setColumnWidth(0, 180);
    for (int j = 1; j < 8; j++) {
        widget.table->setColumnWidth(j, 60);
    }
    int i = 0;
    foreach (StatHashValue* key, keys) {
        int points = 3 * key->get(0) + key->get(1);
        int games = key->get(0) + key->get(1) + key->get(2);
        setCellValue(i, 0, key->getString());
        setCellValue(i, 1, QString::number(games));
        for (int k = 0; k < 5; k++) {
            setCellValue(i, 2 + k, QString::number(key->get(k)));
        }
        setCellValue(i, 7, QString::number(points));
        i++;
    }
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
                hash->insert(key, new Record(key));
            }
            hash->value(key)->add(1);
        }
    }
}

void MainWindow::referies(QDomElement& docElement, StatHash* hash) {
    QDomNodeList nodes = docElement.elementsByTagName("refery");
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        QString name = node.text();
        QString city = node.attributes().namedItem("city").nodeValue();
        QString key = name.append(" (").append(city).append(")");
        if (!hash->contains(key)) {
            hash->insert(key, new Record(key));
        }
        hash->value(key)->add(1);
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
        QString key = team1.append(" - ")
                .append(team2)
                .append(" ")
                .append(score);
        hash->insert(key, new Record(key));
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
            hash->insert(team1, new Record(team1));
        }
        if(!hash->contains(team2)) {
            hash->insert(team2, new Record(team2));
        }
        Record* recordTeam1 = hash->value(team1);
        Record* recordTeam2 = hash->value(team2);
        recordTeam1->add(goal1, 3);
        recordTeam1->add(goal2, 4);
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
    QDir* qDir = new QDir(directory);
    qDir->setFilter(QDir::Files);
    QStringList list = qDir->entryList();
    QDomDocument xml("report");
    for (int i = 0; i < list.size(); ++i) {
        QString fileName = list.at(i);
        QFile file(qDir->absolutePath() + "/" + fileName);
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
    directory = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Выберите имя файла"), directory);
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

void MainWindow::matchReport(const QString& matchId) {
    //
}

void MainWindow::matchResults(const QString& clubId) {
    //
}
