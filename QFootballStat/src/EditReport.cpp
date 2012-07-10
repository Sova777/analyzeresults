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

#include "EditReport.h"
#include "Report.h"

EditReport::EditReport(MainWindow *parent) {
    mainWindow = parent;
    widget.setupUi(this);
    int size = mainWindow->current.length();
    if (size > 0) {
        QString code = mainWindow->current.left(5);
        QString id = mainWindow->current.right(size - 5);
        if (code == "xm01_") {
            foreach(Report report, mainWindow->reports) {
                if (report.getFileName() == id) {
                    this->widget.fChampionship->setText(report.getMatchTournament());
                    this->widget.fRound->setText(report.getMatchRound());
                    this->widget.fTeam1->setText(report.getTeam1());
                    this->widget.fTeam2->setText(report.getTeam2());
                    this->widget.fGoals1->setText(report.getGoals1());
                    this->widget.fGoals2->setText(report.getGoals2());
                    this->widget.fExtra1->setText(report.getExtra1());
                    this->widget.fExtra2->setText(report.getExtra2());
                    this->widget.fPenalty1->setText(report.getPenalties1());
                    this->widget.fPenalty2->setText(report.getPenalties2());
                    this->widget.fCity->setText(report.getStadiumCity());
                    this->widget.fStadium->setText(report.getStadium());
                    this->widget.fAttendance->setText(report.getStadiumAttendance());
                    this->widget.fReferee->setText(report.getReferee());
                    this->widget.fDate->setDate(report.getDate());
                    QTime time = QTime::fromString(report.getTime(), "hh:mm");
                    this->widget.fDate->setTime(time);
                    this->widget.fCoach1->setText(report.getCoach1());
                    this->widget.fCoach2->setText(report.getCoach2());
                    QVector<Report::Player> players1 = report.getPlayers1();
                    this->widget.fSquad1->setColumnCount(1);
                    QStringList titles1;
                    titles1 << TABLE_SQUAD_COLUMN1;
                    this->widget.fSquad1->setHorizontalHeaderLabels(titles1);
                    this->widget.fSquad1->setRowCount(players1.size());
                    int row = 0;
                    foreach(Report::Player player1, players1) {
                        QTableWidgetItem* stlb = new QTableWidgetItem(player1.player);
                        stlb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        this->widget.fSquad1->setItem(row, 0, stlb);
                        row++;
                    }
                    QVector<Report::Player> players2 = report.getPlayers2();
                    this->widget.fSquad2->setColumnCount(1);
                    QStringList titles2;
                    titles2 << TABLE_SQUAD_COLUMN1;
                    this->widget.fSquad2->setHorizontalHeaderLabels(titles2);
                    this->widget.fSquad2->setRowCount(players2.size());
                    row = 0;
                    foreach(Report::Player player2, players2) {
                        QTableWidgetItem* stlb = new QTableWidgetItem(player2.player);
                        stlb->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        this->widget.fSquad2->setItem(row, 0, stlb);
                        row++;
                    }
                    QVector<Report::Event> events = report.getEvents();
                    this->widget.fEvents->setColumnCount(6);
                    QStringList titles3;
                    titles3 << TABLE_EVENT_COLUMN1
                            << TABLE_EVENT_COLUMN2
                            << TABLE_EVENT_COLUMN3
                            << TABLE_EVENT_COLUMN4
                            << TABLE_EVENT_COLUMN5
                            << TABLE_EVENT_COLUMN6;
                    this->widget.fEvents->setHorizontalHeaderLabels(titles3);
                    this->widget.fEvents->setRowCount(events.size());
                    row = 0;
                    foreach(Report::Event event, events) {
                        QTableWidgetItem* stlb1 = new QTableWidgetItem(event.time);
                        stlb1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        this->widget.fEvents->setItem(row, 0, stlb1);
                        QTableWidgetItem* stlb2 = new QTableWidgetItem(event.type);
                        stlb2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        this->widget.fEvents->setItem(row, 1, stlb2);
                        QTableWidgetItem* stlb3 = new QTableWidgetItem(event.comment);
                        stlb3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        this->widget.fEvents->setItem(row, 2, stlb3);
                        QTableWidgetItem* stlb4 = new QTableWidgetItem(event.team);
                        stlb4->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        this->widget.fEvents->setItem(row, 3, stlb4);
                        QTableWidgetItem* stlb5 = new QTableWidgetItem(event.player);
                        stlb5->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        this->widget.fEvents->setItem(row, 4, stlb5);
                        QTableWidgetItem* stlb6 = new QTableWidgetItem(event.player2);
                        stlb6->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        this->widget.fEvents->setItem(row, 5, stlb6);
                        row++;
                    }
                }
            }
        }
    }
}

EditReport::~EditReport() {
}

void EditReport::accept() {
    QDialog::accept();
}
