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

#include "MainWindow.h"
#include "constants.h"

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

    directory = QString::fromLatin1("xml");
    widget.text->setVisible(false);
    widget.table->setSortingEnabled(true);
    //selectMode1();
}

MainWindow::~MainWindow() {
}

void MainWindow::selectMode1() {
    calculateTable();
}

void MainWindow::selectMode2() {
    calculateTeams();
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
    QString filter = "";
    analyzeXml(&listOfGoals, filter, &hash);
    widget.table->setSortingEnabled(false);
    widget.table->clear();
    setColumns(4);
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
        setCellValue(i, 2, QString("%1").arg(record->get(), 4));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(2, Qt::DescendingOrder);
}

void MainWindow::calculateReferies() {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfReferies, filter, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(4);
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
        setCellValue(i, 2, QString("%1").arg(record->get(), 4));
        setCellValue(i, 3, QString("re01_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(2, Qt::DescendingOrder);
}

void MainWindow::calculateReferies2(QString& referee) {
    StatHash hash;
    analyzeXml(&listOfReferies2, referee, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(6);
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
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(2, Qt::DescendingOrder);
}

void MainWindow::calculateCoaches(void) {
    StatHash hash;
    QString filter = "";
    analyzeXml(&listOfCoaches, filter, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(4);
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
        setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
        setCellValue(i, 3, QString("co01_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateCoaches2(QString& coach) {
    StatHash hash;
    analyzeXml(&listOfCoaches2, coach, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(6);
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
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
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
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(4);
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
        setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
        setCellValue(i, 3, QString("st01_%1").arg(record->getString(0)));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::calculateStadiums2(QString& stadium) {
    StatHash hash;
    analyzeXml(&listOfStadiums2, stadium, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(6);
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
    foreach (StatHashValue* record, hash) {
        setCellValue(i, 0, record->getString(0));
        setCellValue(i, 1, record->getString(1));
        setCellValue(i, 2, record->getString(2));
        setCellValue(i, 3, record->getString(3));
        setCellValue(i, 4, record->getString(4));
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
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(5);
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
    QString filter = "";
    analyzeXml(&listOfPlayers, filter, &hash);
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(4);
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
        setCellValue(i, 2, QString("%1").arg(record->get(), 4));
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
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(9);
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
        setCellValue(i, 7, QString("%1").arg(points, 4));
        delete record;
        i++;
    }
    hash.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(7, Qt::DescendingOrder);
}

void MainWindow::calculateTeams() {
    StatHash hash;
    StatHash hash_stat;
    QString filter = "";
    analyzeXml(&listOfPlayers, filter, &hash);
    int i = 0;
    foreach (StatHashValue* record, hash) {
        QString key = QString("%1").arg(record->getString(1));
        Record* record_stat = Record::getInstance(hash_stat, key);
        record_stat->setString(key);
        record_stat->add(1);
        delete record;
        i++;
    }
    hash.clear();
    widget.table->clear();
    widget.table->setSortingEnabled(false);
    setColumns(3);
    widget.table->setRowCount(hash_stat.size());
    widget.table->setColumnWidth(0, 120);
    widget.table->setColumnWidth(1, 60);
    QStringList titles;
    titles << TABLE_TEAMS_COLUMN1
            << TABLE_TEAMS_COLUMN2;
    widget.table->setHorizontalHeaderLabels(titles);
    i = 0;
    foreach (StatHashValue* record, hash_stat) {
        setCellValue(i, 0, QString(record->getString(0)));
        setCellValue(i, 1, QString("%1").arg(record->get(), 4));
        delete record;
        i++;
    }
    hash_stat.clear();
    widget.table->setSortingEnabled(true);
    widget.table->sortByColumn(0, Qt::AscendingOrder);
}

// DOM парсер
void MainWindow::analyzeXml(pointer func, const QString& filter, StatHash* hash) {
    QTime t;
    t.start();
    QDir qDir = QDir(directory);
    qDir.setFilter(QDir::Files);
    QStringList list = qDir.entryList();
    QString fullPath = qDir.absolutePath();
    QDomDocument xml("report");
    int size = list.size();
    for (int i = 0; i < size; ++i) {
        QString fileName = list.at(i);
        if (!fileName.endsWith(QLatin1String(".xml"))) continue;
        QFile file(fullPath + "/" + fileName);
        if (!file.open(QIODevice::ReadOnly)) continue;
        if (!xml.setContent(&file)) {
            file.close();
            continue;
        }
        file.close();
        QDomElement docElement = xml.documentElement();
        QDate date = getDate(docElement);
        if ((date >= widget.dateEditFrom->date()) && (date <= widget.dateEditTill->date())) {
            (*func)(docElement, filter, hash);
        }
    }
    QString status = STATUS_TIME.arg(t.elapsed());
    statusBar()->showMessage(status, 2000);
    return;
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
            if (!widget.table->isColumnHidden(j)) {
                out << widget.table->item(i, j)->text() << " | ";
            }
        }
        out << "\n";
    }
    file.close();
}

void MainWindow::setColumns(int columns) {
    if (columns < 0) {
        return;
    }
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

void MainWindow::jump(const QString& link) {
    int size = link.length();
    if (size < 5) {
        return;
    }
    QString code = link.left(5);
    QString id = link.right(size - 5);
    if (code == "st01_") {
        calculateStadiums2(id);
        return;
    }
    if (code == "re01_") {
        calculateReferies2(id);
        return;
    }
    if (code == "co01_") {
        calculateCoaches2(id);
        return;
    }
}

//void MainWindow::matchReport(const QString& matchId) {
//    //
//}
//
//void MainWindow::matchResults(const QString& teamId) {
//    //
//}
