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

const QString TABLE_COACHES_COLUMN1 = QString::fromUtf8("Тренер");
const QString TABLE_COACHES_COLUMN2 = QString::fromUtf8("Клуб");
const QString TABLE_COACHES_COLUMN3 = QString::fromUtf8("Матчей");

const QString TABLE_MATCHES_COLUMN1 = QString::fromUtf8("Дата");
const QString TABLE_MATCHES_COLUMN2 = QString::fromUtf8("Хозяева");
const QString TABLE_MATCHES_COLUMN3 = QString::fromUtf8("Гости");
const QString TABLE_MATCHES_COLUMN4 = QString::fromUtf8("Счёт");

const QString TABLE_STADIUMS_COLUMN1 = QString::fromUtf8("Стадион");
const QString TABLE_STADIUMS_COLUMN2 = QString::fromUtf8("Город");
const QString TABLE_STADIUMS_COLUMN3 = QString::fromUtf8("Матчей");

const QString TABLE_PLAYERS_COLUMN1 = QString::fromUtf8("Игрок");
const QString TABLE_PLAYERS_COLUMN2 = QString::fromUtf8("Клуб");
const QString TABLE_PLAYERS_COLUMN3 = QString::fromUtf8("Матчей");

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

    directory = QString::fromLatin1("xml");
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
    calculatePlayers();
}

void MainWindow::selectMode5() {
    calculateMatches();
}

void MainWindow::selectMode6() {
    calculateGoals();
}

void MainWindow::selectMode7() {
    calculateCoaches();
}

void MainWindow::selectMode8() {
    calculateStadiums();
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
    QStringList titles;
    titles << TABLE_GOALS_COLUMN1
            << TABLE_GOALS_COLUMN2
            << TABLE_GOALS_COLUMN3;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(), 4, 10));
        delete record;
        i++;
    }
    hash.clear();
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
    QStringList titles;
    titles << TABLE_REFERIES_COLUMN1
            << TABLE_REFERIES_COLUMN2
            << TABLE_REFERIES_COLUMN3;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(), 4, 10));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(2, Qt::DescendingOrder);
}

void MainWindow::calculateCoaches(void) {
    StatHash hash;
    analyzeXml(&MainWindow::coaches, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(3);
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
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(0), 4, 10));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateStadiums(void) {
    StatHash hash;
    analyzeXml(&MainWindow::stadiums, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(3);
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
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, QString("%1").arg(record->get(0), 4, 10));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateMatches() {
    StatHash hash;
    analyzeXml(&MainWindow::matches, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(4);
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
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, QString(record->getString(0)));
        setCellValue(i, 1, QString(record->getString(1)));
        setCellValue(i, 2, QString(record->getString(2)));
        setCellValue(i, 3, QString(record->getString(3)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(1, Qt::AscendingOrder);
}

void MainWindow::calculatePlayers() {
    StatHash hash;
    analyzeXml(&MainWindow::players, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    widget.table->setColumnCount(3);
    widget.table->setRowCount(hash.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 120);
    widget.table->setColumnWidth(2, 60);
    QStringList titles;
    titles << TABLE_PLAYERS_COLUMN1
            << TABLE_PLAYERS_COLUMN2
            << TABLE_PLAYERS_COLUMN3;
    widget.table->setHorizontalHeaderLabels(titles);
    int i = 0;
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, QString(record->getString(0)));
        setCellValue(i, 1, QString(record->getString(1)));
        setCellValue(i, 2, QString("%1").arg(record->get(), 4, 10));
        delete record;
        i++;
    }
    hash.clear();
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
    foreach (StatHashValue* record, hash) {
        int points = 3 * record->get(0) + record->get(1);
        int games = record->get(0) + record->get(1) + record->get(2);
        setCellValue(i, 0, record->getString());
        setCellValue(i, 1, QString::number(games));
        for (int k = 0; k < 5; k++) {
            setCellValue(i, 2 + k, QString::number(record->get(k)));
        }
        setCellValue(i, 7, QString::number(points));
        delete record;
        i++;
    }
    hash.clear();
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
            QString key = QString(" %1 (%2)").arg(player).arg(club);
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
    QDomNodeList nodes = docElement.elementsByTagName("referee");
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

void MainWindow::coaches(QDomElement& docElement, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QDomNodeList nodes1 = docElement.elementsByTagName("coach1");
    QDomNodeList nodes2 = docElement.elementsByTagName("coach2");
    if ((nodes1.length() > 0) && (nodes2.length() > 0)) {
        QDomElement node1 = nodes1.at(0).toElement();
        QDomElement node2 = nodes2.at(0).toElement();
        QString coach1 = node1.text();
        QString coach2 = node2.text();
        QString key1 = QString("%1 (%2)").arg(coach1).arg(team1);
        QString key2 = QString("%1 (%2)").arg(coach2).arg(team2);
        if (!hash->contains(key1)) {
            hash->insert(key1, new Record());
        }
        if (!hash->contains(key2)) {
            hash->insert(key2, new Record());
        }
        Record* record1 = hash->value(key1);
        record1->setString(coach1, 0);
        record1->setString(team1, 1);
        record1->add(1);
        Record* record2 = hash->value(key2);
        record2->setString(coach2, 0);
        record2->setString(team2, 1);
        record2->add(1);
    }
}

void MainWindow::stadiums(QDomElement& docElement, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QDomNodeList nodes = docElement.elementsByTagName("stadium");
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        QString stadium = node.text();
        QString city = node.attributes().namedItem("city").nodeValue();
        QString key = QString("%1 (%2)").arg(stadium).arg(city);
        if (!hash->contains(key)) {
            hash->insert(key, new Record());
        }
        Record* record = hash->value(key);
        record->setString(stadium, 0);
        record->setString(city, 1);
        record->add(1);
    }
}

void MainWindow::matches(QDomElement& docElement, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QDomNodeList nodesScore = docElement.elementsByTagName("score");
    QDomNodeList nodesDate = docElement.elementsByTagName("date");
    if ((nodesScore.length() > 0) && (nodesDate.length() > 0)) {
        QDomElement nodeScore = nodesScore.at(0).toElement();
        QDomElement nodeDate = nodesDate.at(0).toElement();
        QString score = nodeScore.text();
        QString dateString = nodeDate.text();
        QString date = dateString.right(2)
                + "." + dateString.mid(3, 2) + "." + dateString.left(4);
        QString key = QString("%1 - %2 %3").arg(team1).arg(team2).arg(score);
        hash->insert(key, new Record());
        Record* record = hash->value(key);
        record->setString(date, 0);
        record->setString(team1, 1);
        record->setString(team2, 2);
        record->setString(score, 3);
    }
}

void MainWindow::players(QDomElement& docElement, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QDomNodeList nodesPlayers1 = docElement.elementsByTagName("player1");
    QDomNodeList nodesPlayers2 = docElement.elementsByTagName("player2");
    if (true) {
        uint len1 = nodesPlayers1.length();
        for (uint i = 0; i < len1; i++) {
            QDomElement nodeElement = nodesPlayers1.at(i).toElement();
            QString player = nodeElement.text();
            QString key = QString("%1 (%2)").arg(player).arg(team1);
            if(!hash->contains(key)) {
                hash->insert(key, new Record());
            }
            Record* record = hash->value(key);
            record->setString(player, 0);
            record->setString(team1, 1);
            record->add(1);
        }
        uint len2 = nodesPlayers1.length();
        for (uint i = 0; i < len2; i++) {
            QDomElement nodeElement = nodesPlayers2.at(i).toElement();
            QString player = nodeElement.text();
            QString key = QString("%1 (%2)").arg(player).arg(team2);
            if(!hash->contains(key)) {
                hash->insert(key, new Record());
            }
            Record* record = hash->value(key);
            record->setString(player, 0);
            record->setString(team2, 1);
            record->add(1);
        }
    }
}

void MainWindow::table(QDomElement& docElement, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QDomNodeList nodesScore = docElement.elementsByTagName("score");
    if (nodesScore.length() > 0) {
        QDomElement nodeScore = nodesScore.at(0).toElement();
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
        if (!fileName.endsWith(QLatin1String(".xml"))) continue;
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
    QString dir = QFileDialog::getExistingDirectory(this, QString::fromUtf8("Выберите директорий"), directory);
    if (dir != "") {
        directory = dir;
    }
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

QString MainWindow::getTeam1(QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("team1");
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
    }
    return value;
}

QString MainWindow::getTeam2(QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("team2");
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
    }
    return value;
}

//void MainWindow::matchReport(const QString& matchId) {
//    //
//}
//
//void MainWindow::matchResults(const QString& clubId) {
//    //
//}
