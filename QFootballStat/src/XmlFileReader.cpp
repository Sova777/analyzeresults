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

#include "Filter.h"
#include "Record.h"
#include "Report.h"
#include "MainWindow.h"
#include "XmlFileReader.h"
#include "constants.h"

void listOfGoals(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QVector<Report::Event> events = xmlFilter.report->getEvents();
        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString eventType = events.at(i).type;
            QString player = events.at(i).player;
            QString playerid = events.at(i).playerid;
            QString team = events.at(i).team;
            if ((eventType == EVENT_GOAL) || (eventType == EVENT_GOAL_PENALTY)) {
                QString key = getKeyPlayer(xmlFilter.filter->useID, playerid, player, team);
                Record* record = Record::getInstance(hash, key);
                record->setString(player, 0);
                record->setString(team, 1);
                record->add(1);
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_GOALS_COLUMN1
                << TABLE_GOALS_COLUMN2
                << TABLE_GOALS_COLUMN3;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);
        xmlFilter.window->widget.table->setColumnWidth(1, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(), 4));
            xmlFilter.window->setCellValue(i, 3, QString("go02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(2, Qt::DescendingOrder);
    }
}

void listOfGoals2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QDate date = xmlFilter.report->getDate();
        const QString* score = xmlFilter.report->getScore();
        QString city = xmlFilter.report->getStadiumCity();
        const QString* player = &(xmlFilter.filter->filter);
        int goals = getPlayerGoals(xmlFilter.report, player);
        if (goals > 0) {
            QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
            Record* record = Record::getInstance(hash, key);
            QString qdate = date.toString("yyyy/MM/dd");
            record->setString(qdate, 0);
            record->setString(city, 1);
            record->setString(team1, 2);
            record->setString(team2, 3);
            record->setString(*score, 4);
            record->set(goals, 0);
            record->setString(*(xmlFilter.fileName), 5);
        }
    } else {
        QStringList titles;
        titles << TABLE_GOALS2_COLUMN1
                << TABLE_GOALS2_COLUMN2
                << TABLE_GOALS2_COLUMN3
                << TABLE_GOALS2_COLUMN4
                << TABLE_GOALS2_COLUMN5
                << TABLE_GOALS2_COLUMN6;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 90);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);
        xmlFilter.window->widget.table->setColumnWidth(2, 120);
        xmlFilter.window->widget.table->setColumnWidth(3, 90);
        xmlFilter.window->widget.table->setColumnWidth(4, 90);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(0)));
            xmlFilter.window->setCellValue(i, 6, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfReferies(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString name = xmlFilter.report->getReferee();
        QString city = xmlFilter.report->getRefereeCity();
        QVector<Report::Event> events = xmlFilter.report->getEvents();
        QString key = QString("%1 (%2)").arg(name).arg(city);
        Record* record = Record::getInstance(hash, key);
        record->setString(name, 0);
        record->setString(city, 1);
        record->add(1);

        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString eventType = events.at(i).type;
            if (eventType == EVENT_RED_CARD) {
                record->add(1, 1);
            } else if (eventType == EVENT_RED_YELLOW_CARD) {
                record->add(1, 2);
            } else if (eventType == EVENT_YELLOW_CARD) {
                record->add(1, 3);
            } else if ((eventType == EVENT_GOAL_PENALTY) || (eventType == EVENT_MISSED_PENALTY)) {
                record->add(1, 4);
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_REFERIES_COLUMN1
                << TABLE_REFERIES_COLUMN2
                << TABLE_REFERIES_COLUMN3
                << TABLE_REFERIES_COLUMN4
                << TABLE_REFERIES_COLUMN5
                << TABLE_REFERIES_COLUMN6
                << TABLE_REFERIES_COLUMN7;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);
        xmlFilter.window->widget.table->setColumnWidth(1, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(1), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 6, QString("%1").arg(record->get(4), 4));
            xmlFilter.window->setCellValue(i, 7, QString("re02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(2, Qt::DescendingOrder);
    }
}

void listOfReferies2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QDate date = xmlFilter.report->getDate();
        const QString* score = xmlFilter.report->getScore();
        QString city = xmlFilter.report->getStadiumCity();
        QString referee = xmlFilter.report->getReferee();
        if (referee == xmlFilter.filter->filter) {
            QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
            Record* record = Record::getInstance(hash, key);
            QString qdate = date.toString("yyyy/MM/dd");
            record->setString(qdate, 0);
            record->setString(city, 1);
            record->setString(team1, 2);
            record->setString(team2, 3);
            record->setString(*score, 4);
            record->setString(*(xmlFilter.fileName), 5);
        }
    } else {
        QStringList titles;
        titles << TABLE_REFERIES2_COLUMN1
                << TABLE_REFERIES2_COLUMN2
                << TABLE_REFERIES2_COLUMN3
                << TABLE_REFERIES2_COLUMN4
                << TABLE_REFERIES2_COLUMN5;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 90);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);
        xmlFilter.window->widget.table->setColumnWidth(2, 120);
        xmlFilter.window->widget.table->setColumnWidth(3, 120);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfCoaches(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QString coach1 = xmlFilter.report->getCoach1();
        QString coach1id = xmlFilter.report->getCoach1id();    
        QString coach2 = xmlFilter.report->getCoach2();
        QString coach2id = xmlFilter.report->getCoach2id();
        const QString* score = xmlFilter.report->getScore();
        QString expr = xmlFilter.filter->filter;
        QString key1 = getKeyCoach(xmlFilter.filter->useID, coach1id, coach1, team1);
        QString key2 = getKeyCoach(xmlFilter.filter->useID, coach2id, coach2, team2);
        Record* record1 = NULL;
        if ((expr == "") || coach1.contains(expr)) {
            record1 = Record::getInstance(hash, key1);
            record1->setString(coach1, 0);
            record1->setString(team1, 1);
            record1->add(1);
        }
        Record* record2 = NULL;
        if ((expr == "") || coach2.contains(expr)) {
            record2 = Record::getInstance(hash, key2);
            record2->setString(coach2, 0);
            record2->setString(team2, 1);
            record2->add(1);
        }

        if (*score != "") {
            bool ok;
            int goal1 = 99999;
            int goal2 = 99999;
            goal1 = score->section(':', 0, 0).toInt(&ok);
            goal2 = score->section(':', 1, 1).toInt(&ok);
            if (record1 != NULL) {
                record1->add(goal1, 4);
                record1->add(goal2, 5);
            }
            if (record2 != NULL) {
                record2->add(goal2, 4);
                record2->add(goal1, 5);
            }
            if (goal1 > goal2) {
                if (record1 != NULL) {record1->add(1, 1);}
                if (record2 != NULL) {record2->add(1, 3);}
            } else if (goal2 > goal1) {
                if (record2 != NULL) {record2->add(1, 1);}
                if (record1 != NULL) {record1->add(1, 3);}
            } else {
                if (record2 != NULL) {record2->add(1, 2);}
                if (record1 != NULL) {record1->add(1, 2);}
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_COACHES_COLUMN1
                << TABLE_COACHES_COLUMN2
                << TABLE_COACHES_COLUMN3
                << TABLE_COACHES_COLUMN4
                << TABLE_COACHES_COLUMN5
                << TABLE_COACHES_COLUMN6
                << TABLE_COACHES_COLUMN7
                << TABLE_COACHES_COLUMN8
                << TABLE_COACHES_COLUMN9;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);
        xmlFilter.window->widget.table->setColumnWidth(1, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(1), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 6, QString("%1").arg(record->get(4), 4));
            xmlFilter.window->setCellValue(i, 7, QString("%1").arg(record->get(5), 4));
            xmlFilter.window->setCellValue(i, 8, QString("%1").arg(3 * record->get(1) + record->get(2), 4));
            xmlFilter.window->setCellValue(i, 9, QString("co02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfCoaches3(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QString coach1 = xmlFilter.report->getCoach1();
        QString coach1id = xmlFilter.report->getCoach1id();    
        QString coach2 = xmlFilter.report->getCoach2();
        QString coach2id = xmlFilter.report->getCoach2id();
        const QString* score = xmlFilter.report->getScore();
        QString expr = xmlFilter.filter->filter;
        QString key1 = getKeyCoach(xmlFilter.filter->useID, coach1id, coach1, team1);
        QString key2 = getKeyCoach(xmlFilter.filter->useID, coach2id, coach2, team2);
        Record* record1 = NULL;
        if ((expr == "") || coach1.contains(expr)) {
            record1 = Record::getInstance(hash, key1);
            record1->setString(coach1, 0);
            record1->setString(team1, 1);
            record1->add(1);
        }
        Record* record2 = NULL;
        if ((expr == "") || coach2.contains(expr)) {
            record2 = Record::getInstance(hash, key2);
            record2->setString(coach2, 0);
            record2->setString(team2, 1);
            record2->add(1);
        }

        if (*score != "") {
            bool ok;
            int goal1 = 99999;
            int goal2 = 99999;
            goal1 = score->section(':', 0, 0).toInt(&ok);
            goal2 = score->section(':', 1, 1).toInt(&ok);
            if (record1 != NULL) {
                record1->add(goal1, 4);
                record1->add(goal2, 5);
            }
            if (record2 != NULL) {
                record2->add(goal2, 4);
                record2->add(goal1, 5);
            }
            if (goal1 > goal2) {
                if (record1 != NULL) {record1->add(1, 1);}
                if (record2 != NULL) {record2->add(1, 3);}
            } else if (goal2 > goal1) {
                if (record2 != NULL) {record2->add(1, 1);}
                if (record1 != NULL) {record1->add(1, 3);}
            } else {
                if (record2 != NULL) {record2->add(1, 2);}
                if (record1 != NULL) {record1->add(1, 2);}
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_COACHES_COLUMN1
                << TABLE_COACHES_COLUMN2
                << TABLE_COACHES_COLUMN3
                << TABLE_COACHES_COLUMN4
                << TABLE_COACHES_COLUMN5
                << TABLE_COACHES_COLUMN6
                << TABLE_COACHES_COLUMN7
                << TABLE_COACHES_COLUMN8
                << TABLE_COACHES_COLUMN9;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);
        xmlFilter.window->widget.table->setColumnWidth(1, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(1), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 6, QString("%1").arg(record->get(4), 4));
            xmlFilter.window->setCellValue(i, 7, QString("%1").arg(record->get(5), 4));
            xmlFilter.window->setCellValue(i, 8, QString("%1").arg(3 * record->get(1) + record->get(2), 4));
            xmlFilter.window->setCellValue(i, 9, QString("co02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfCoaches2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QDate date = xmlFilter.report->getDate();
        const QString* score = xmlFilter.report->getScore();
        QString city = xmlFilter.report->getStadiumCity();
        QString coach1 = xmlFilter.report->getCoach1();
        QString coach2 = xmlFilter.report->getCoach2();
        if ((coach1 == xmlFilter.filter->filter) || (coach2 == xmlFilter.filter->filter)) {
            QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
            Record* record = Record::getInstance(hash, key);
            QString qdate = date.toString("yyyy/MM/dd");
            record->setString(qdate, 0);
            record->setString(city, 1);
            record->setString(team1, 2);
            record->setString(team2, 3);
            record->setString(*score, 4);
            record->setString(*(xmlFilter.fileName), 5);
        }
    } else {
        QStringList titles;
        titles << TABLE_COACHES2_COLUMN1
                << TABLE_COACHES2_COLUMN2
                << TABLE_COACHES2_COLUMN3
                << TABLE_COACHES2_COLUMN4
                << TABLE_COACHES2_COLUMN5;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 90);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);
        xmlFilter.window->widget.table->setColumnWidth(2, 120);
        xmlFilter.window->widget.table->setColumnWidth(3, 120);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
       }
}

void listOfStadiums(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString stadium = xmlFilter.report->getStadium();
        QString city = xmlFilter.report->getStadiumCity();
        QString attendance = xmlFilter.report->getStadiumAttendance();
        QString key = QString("%1 (%2)").arg(stadium).arg(city);
        Record* record = Record::getInstance(hash, key);
        record->setString(stadium, 0);
        record->setString(city, 1);
        record->add(1);
        bool ok;
        int att = 0;
        att = attendance.toInt(&ok);
        record->add(att, 1);
        if (att != 0) {
            if ((record->get(2) < att) || (record->get(2) == 0)) {
                record->set(att, 2);
            }
            if ((record->get(3) > att) || (record->get(3) == 0)) {
                record->set(att, 3);
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_STADIUMS_COLUMN1
                << TABLE_STADIUMS_COLUMN2
                << TABLE_STADIUMS_COLUMN3
                << TABLE_STADIUMS_COLUMN4
                << TABLE_STADIUMS_COLUMN5
                << TABLE_STADIUMS_COLUMN6;
        xmlFilter.window->initTable(titles, 90, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);
        xmlFilter.window->widget.table->setColumnWidth(1, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(1) / record->get(0), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 6, QString("st02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfStadiums2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QDate date = xmlFilter.report->getDate();
        const QString* score = xmlFilter.report->getScore();
        QString city = xmlFilter.report->getStadiumCity();
        QString stadium = xmlFilter.report->getStadium();
        if (stadium == xmlFilter.filter->filter) {
            QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
            Record* record = Record::getInstance(hash, key);
            QString qdate = date.toString("yyyy/MM/dd");
            record->setString(qdate, 0);
            record->setString(city, 1);
            record->setString(team1, 2);
            record->setString(team2, 3);
            record->setString(*score, 4);
            record->setString(*(xmlFilter.fileName), 5);
        }
    } else {
        QStringList titles;
        titles << TABLE_STADIUMS2_COLUMN1
                << TABLE_STADIUMS2_COLUMN2
                << TABLE_STADIUMS2_COLUMN3
                << TABLE_STADIUMS2_COLUMN4
                << TABLE_STADIUMS2_COLUMN5;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 90);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);
        xmlFilter.window->widget.table->setColumnWidth(2, 120);
        xmlFilter.window->widget.table->setColumnWidth(3, 120);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfMatches(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        const QString* score = xmlFilter.report->getScore();
        QString qdate = xmlFilter.report->getDate().toString("yyyy/MM/dd");
        Record* record = Record::newInstance(hash);
        record->setString(qdate, 0);
        record->setString(team1, 1);
        record->setString(team2, 2);
        record->setString(*score, 3);
        record->setString(*(xmlFilter.fileName), 4);
    } else {
        QStringList titles;
        titles << TABLE_MATCHES_COLUMN1
                << TABLE_MATCHES_COLUMN2
                << TABLE_MATCHES_COLUMN3
                << TABLE_MATCHES_COLUMN4;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 120);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);
        xmlFilter.window->widget.table->setColumnWidth(2, 120);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, QString(record->getString(0)));
            xmlFilter.window->setCellValue(i, 1, QString(record->getString(1)));
            xmlFilter.window->setCellValue(i, 2, QString(record->getString(2)));
            xmlFilter.window->setCellValue(i, 3, QString(record->getString(3)));
            xmlFilter.window->setCellValue(i, 4, QString("xm01_%1").arg(record->getString(4)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfPlayers(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        QString expr = xmlFilter.filter->filter;
        uint len1 = players1.size();
        for (uint i = 0; i < len1; i++) {
            QString player2 = players1.at(i).player;
            QString player2id = players1.at(i).id;
            if ((expr == "") || (player2.contains(expr))) {
                QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team1);
                Record* record = Record::getInstance(hash, key);
                record->setString(player2, 0);
                record->setString(team1, 1);
                record->add(1);
            }
        }
        uint len2 = players2.size();
        for (uint i = 0; i < len2; i++) {
            QString player2 = players2.at(i).player;
            QString player2id = players2.at(i).id;
            if ((expr == "") || (player2.contains(expr))) {
                QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team2);
                Record* record = Record::getInstance(hash, key);
                record->setString(player2, 0);
                record->setString(team2, 1);
                record->add(1);
            }
        }

        QVector<Report::Event> events = xmlFilter.report->getEvents();
        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString eventType = events.at(i).type;
            QString player1 = events.at(i).player;
            QString player1id = events.at(i).playerid;
            QString player2 = events.at(i).player2;
            QString player2id = events.at(i).playerid2;
            QString team = events.at(i).team;
            if (eventType == EVENT_SUBSTITUTION) {
                if ((expr == "") || (player2.contains(expr))) {
                    QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team);
                    Record* record = Record::getInstance(hash, key);
                    record->setString(player2, 0);
                    record->setString(team, 1);
                    record->add(1, 0);
                }
            } else {
                if ((expr == "") || (player1.contains(expr))) {
                    QString key = getKeyPlayer(xmlFilter.filter->useID, player1id, player1, team);
                    Record* record = Record::getInstance(hash, key);
                    record->setString(player1, 0);
                    record->setString(team, 1);
                    if (eventType == EVENT_RED_CARD) {
                        record->add(1, 1);
                    } else if (eventType == EVENT_RED_YELLOW_CARD) {
                        record->add(1, 2);
                    } else if (eventType == EVENT_YELLOW_CARD) {
                        record->add(1, 3);
                    } else if (eventType == EVENT_GOAL) {
                        record->add(1, 4);
                    } else if (eventType == EVENT_GOAL_PENALTY) {
                        record->add(1, 5);
                    } else if (eventType == EVENT_MISSED_PENALTY) {
                        record->add(1, 6);
                    } else if (eventType == EVENT_AUTOGOAL) {
                        record->add(1, 7);
                    }
                }
            }
        }
    } else {
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
        xmlFilter.window->initTable(titles, 70, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 120);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, QString(record->getString(0)));
            xmlFilter.window->setCellValue(i, 1, QString(record->getString(1)));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(1), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 6, QString("%1").arg(record->get(4) + record->get(5), 4));
            xmlFilter.window->setCellValue(i, 7, QString("%1").arg(record->get(5), 4));
            xmlFilter.window->setCellValue(i, 8, QString("%1").arg(record->get(6), 4));
            xmlFilter.window->setCellValue(i, 9, QString("%1").arg(record->get(7), 4));
            xmlFilter.window->setCellValue(i, 10, QString("pl02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfPlayers2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QDate date = xmlFilter.report->getDate();
        const QString* score = xmlFilter.report->getScore();
        QString city = xmlFilter.report->getStadiumCity();
        if (isPlayed(*(xmlFilter.report), xmlFilter.filter->filter)) {
            QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
            Record* record = Record::getInstance(hash, key);
            QString qdate = date.toString("yyyy/MM/dd");
            record->setString(qdate, 0);
            record->setString(city, 1);
            record->setString(team1, 2);
            record->setString(team2, 3);
            record->setString(*score, 4);
            record->setString(*(xmlFilter.fileName), 5);
        }
    } else {
        QStringList titles;
        titles << TABLE_PLAYERS2_COLUMN1
                << TABLE_PLAYERS2_COLUMN2
                << TABLE_PLAYERS2_COLUMN3
                << TABLE_PLAYERS2_COLUMN4
                << TABLE_PLAYERS2_COLUMN5;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 90);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);
        xmlFilter.window->widget.table->setColumnWidth(2, 120);
        xmlFilter.window->widget.table->setColumnWidth(3, 120);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfPlayers3(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        QString expr = xmlFilter.filter->filter;
        uint len1 = players1.size();
        for (uint i = 0; i < len1; i++) {
            QString player2 = players1.at(i).player;
            QString player2id = players1.at(i).id;
            if ((expr == "") || (player2.contains(expr))) {
                QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team1);
                Record* record = Record::getInstance(hash, key);
                record->setString(player2, 0);
                record->setString(team1, 1);
                record->add(1);
            }
        }
        uint len2 = players2.size();
        for (uint i = 0; i < len2; i++) {
            QString player2 = players2.at(i).player;
            QString player2id = players2.at(i).id;
            if ((expr == "") || (player2.contains(expr))) {
                QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team2);
                Record* record = Record::getInstance(hash, key);
                record->setString(player2, 0);
                record->setString(team2, 1);
                record->add(1);
            }
        }

        QVector<Report::Event> events = xmlFilter.report->getEvents();
        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString eventType = events.at(i).type;
            QString player1 = events.at(i).player;
            QString player1id = events.at(i).playerid;
            QString player2 = events.at(i).player2;
            QString player2id = events.at(i).playerid2;
            QString team = events.at(i).team;
            if (eventType == EVENT_SUBSTITUTION) {
                if ((expr == "") || (player2.contains(expr))) {
                    QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team);
                    Record* record = Record::getInstance(hash, key);
                    record->setString(player2, 0);
                    record->setString(team, 1);
                    record->add(1, 0);
                }
            } else {
                if ((expr == "") || (player1.contains(expr))) {
                    QString key = getKeyPlayer(xmlFilter.filter->useID, player1id, player1, team);
                    Record* record = Record::getInstance(hash, key);
                    record->setString(player1, 0);
                    record->setString(team, 1);
                    if (eventType == EVENT_RED_CARD) {
                        record->add(1, 1);
                    } else if (eventType == EVENT_RED_YELLOW_CARD) {
                        record->add(1, 2);
                    } else if (eventType == EVENT_YELLOW_CARD) {
                        record->add(1, 3);
                    } else if (eventType == EVENT_GOAL) {
                        record->add(1, 4);
                    } else if (eventType == EVENT_GOAL_PENALTY) {
                        record->add(1, 5);
                    } else if (eventType == EVENT_MISSED_PENALTY) {
                        record->add(1, 6);
                    } else if (eventType == EVENT_AUTOGOAL) {
                        record->add(1, 7);
                    }
                }
            }
        }
    } else {
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
        xmlFilter.window->initTable(titles, 70, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 120);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, QString(record->getString(0)));
            xmlFilter.window->setCellValue(i, 1, QString(record->getString(1)));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(1), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 6, QString("%1").arg(record->get(4) + record->get(5), 4));
            xmlFilter.window->setCellValue(i, 7, QString("%1").arg(record->get(5), 4));
            xmlFilter.window->setCellValue(i, 8, QString("%1").arg(record->get(6), 4));
            xmlFilter.window->setCellValue(i, 9, QString("%1").arg(record->get(7), 4));
            xmlFilter.window->setCellValue(i, 10, QString("pl02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfTeams(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team1id = xmlFilter.report->getTeam1id();
        QString team2 = xmlFilter.report->getTeam2();
        QString team2id = xmlFilter.report->getTeam2id();
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        uint len1 = players1.size();
        for (uint i = 0; i < len1; i++) {
            QString player2 = players1.at(i).player;
            QString key = QString("%1").arg(team1);
            Record* record = Record::getInstance(hash, key);
            QMap<QString, int>* map = record->getMap();
            if (!map->contains(player2)) {
                map->insert(player2, 0);
            }
            record->setString(team1, 0);
        }
        uint len2 = players2.size();
        for (uint i = 0; i < len2; i++) {
            QString player2 = players2.at(i).player;
            QString player2id = players2.at(i).id;
            QString key = QString("%1").arg(team2);
            Record* record = Record::getInstance(hash, key);
            QMap<QString, int>* map = record->getMap();
            if (!map->contains(player2)) {
                map->insert(player2, 0);
            }
            record->setString(team2, 0);
        }

        QVector<Report::Event> events = xmlFilter.report->getEvents();
        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString eventType = events.at(i).type;
            QString player1 = events.at(i).player;
            QString player1id = events.at(i).playerid;
            QString player2 = events.at(i).player2;
            QString player2id = events.at(i).playerid2;
            QString team = events.at(i).team;
            if (eventType == EVENT_SUBSTITUTION) {
                QString key = QString("%1").arg(team);
                Record* record = Record::getInstance(hash, key);
                QMap<QString, int>* map = record->getMap();
                if (!map->contains(player2)) {
                    map->insert(player2, 0);
                }
                record->setString(team, 0);
            } else {
                QString key = QString("%1").arg(team);
                Record* record = Record::getInstance(hash, key);
                QString key2 = QString("%1").arg(team2);
                Record* record2 = Record::getInstance(hash, key2);
                record->setString(team, 0);
                if (eventType == EVENT_RED_CARD) {
                    record->add(1, 1);
                } else if (eventType == EVENT_RED_YELLOW_CARD) {
                    record->add(1, 2);
                } else if (eventType == EVENT_YELLOW_CARD) {
                    record->add(1, 3);
                } else if (eventType == EVENT_GOAL) {
                    record->add(1, 4);
                } else if (eventType == EVENT_GOAL_PENALTY) {
                    record->add(1, 5);
                    record2->add(1, 8);
                } else if (eventType == EVENT_MISSED_PENALTY) {
                    record->add(1, 6);
                    record2->add(1, 8);
                } else if (eventType == EVENT_AUTOGOAL) {
                    record->add(1, 7);
                }
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_TEAMS_COLUMN1
                << TABLE_TEAMS_COLUMN2
                << TABLE_TEAMS_COLUMN3
                << TABLE_TEAMS_COLUMN4
                << TABLE_TEAMS_COLUMN5
                << TABLE_TEAMS_COLUMN6
                << TABLE_TEAMS_COLUMN7
                << TABLE_TEAMS_COLUMN8
                << TABLE_TEAMS_COLUMN9
                << TABLE_TEAMS_COLUMN10;
        xmlFilter.window->initTable(titles, 80, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 120);
        int i = 0;

        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, QString(record->getString(0)));
            xmlFilter.window->setCellValue(i, 1, QString("%1").arg(record->getMap()->size(), 4));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(1), 4));
            xmlFilter.window->setCellValue(i, 3, QString("%1").arg(record->get(2), 4));
            xmlFilter.window->setCellValue(i, 4, QString("%1").arg(record->get(3), 4));
            xmlFilter.window->setCellValue(i, 5, QString("%1").arg(record->get(4) + record->get(5), 4));
            xmlFilter.window->setCellValue(i, 6, QString("%1").arg(record->get(5), 4));
            xmlFilter.window->setCellValue(i, 7, QString("%1").arg(record->get(6), 4));
            xmlFilter.window->setCellValue(i, 8, QString("%1").arg(record->get(7), 4));
            xmlFilter.window->setCellValue(i, 9, QString("%1").arg(record->get(8), 4));
            xmlFilter.window->setCellValue(i, 10, QString("te02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfTeams2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        uint len1 = players1.size();
        for (uint i = 0; i < len1; i++) {
            QString player2 = players1.at(i).player;
            QString player2id = players1.at(i).id;
            QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team1);
            Record* record = Record::getInstance(hash, key);
            record->setString(player2, 0);
            record->setString(team1, 1);
            record->add(1);
        }
        uint len2 = players2.size();
        for (uint i = 0; i < len2; i++) {
            QString player2 = players2.at(i).player;
            QString player2id = players2.at(i).id;
            QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team2);
            Record* record = Record::getInstance(hash, key);
            record->setString(player2, 0);
            record->setString(team2, 1);
            record->add(1);
        }

        QVector<Report::Event> events = xmlFilter.report->getEvents();
        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString eventType = events.at(i).type;
            QString player1 = events.at(i).player;
            QString player1id = events.at(i).playerid;
            QString player2 = events.at(i).player2;
            QString player2id = events.at(i).playerid2;
            QString team = events.at(i).team;
            if (eventType == EVENT_SUBSTITUTION) {
                QString key = getKeyPlayer(xmlFilter.filter->useID, player2id, player2, team);
                Record* record = Record::getInstance(hash, key);
                record->setString(player2, 0);
                record->setString(team, 1);
                record->add(1, 0);
            } else {
                QString key = getKeyPlayer(xmlFilter.filter->useID, player1id, player1, team);
                Record* record = Record::getInstance(hash, key);
                record->setString(player1, 0);
                record->setString(team, 1);
                if (eventType == EVENT_RED_CARD) {
                    record->add(1, 1);
                } else if (eventType == EVENT_RED_YELLOW_CARD) {
                    record->add(1, 2);
                } else if (eventType == EVENT_YELLOW_CARD) {
                    record->add(1, 3);
                } else if (eventType == EVENT_GOAL) {
                    record->add(1, 4);
                } else if (eventType == EVENT_GOAL_PENALTY) {
                    record->add(1, 5);
                } else if (eventType == EVENT_MISSED_PENALTY) {
                    record->add(1, 6);
                } else if (eventType == EVENT_AUTOGOAL) {
                    record->add(1, 7);
                }
            }
        }
    } else {
        StatHash hash_stat;
        int i = 0;

        foreach(StatHashValue* record, *hash) {
            if (record->getString(1) == xmlFilter.filter->filter) {
                QString key = QString("%1").arg(record->getString(0));
                Record* record_stat = Record::getInstance(hash_stat, key);
                record_stat->setString(record->getString(0), 0);
                record_stat->setString(record->getString(1), 1);
                record_stat->set(record->get(0), 0);
                delete record;
                i++;
            }
        }
        hash->clear();
        QStringList titles;
        titles << TABLE_TEAMS2_COLUMN1
                << TABLE_TEAMS2_COLUMN2
                << TABLE_TEAMS2_COLUMN3;
        xmlFilter.window->initTable(titles, 60, hash_stat.size());
        xmlFilter.window->widget.table->setColumnWidth(0, 120);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);

        i = 0;
        foreach(StatHashValue* record, hash_stat) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, QString("%1").arg(record->get(0), 4));
            xmlFilter.window->setCellValue(i, 3, QString("pl02_%1").arg(record->getString(0)));
            delete record;
            i++;
        }
        hash_stat.clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void listOfTable(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        const QString* score = xmlFilter.report->getScore();
        if (*score != "") {
            bool ok;
            int goal1 = 99999;
            int goal2 = 99999;
            goal1 = score->section(':', 0, 0).toInt(&ok);
            goal2 = score->section(':', 1, 1).toInt(&ok);
            Record* recordTeam1 = Record::getInstance(hash, team1);
            Record* recordTeam2 = Record::getInstance(hash, team2);
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
    } else {
        QStringList titles;
        titles << TABLE_TABLE_COLUMN1
                << TABLE_TABLE_COLUMN2
                << TABLE_TABLE_COLUMN3
                << TABLE_TABLE_COLUMN4
                << TABLE_TABLE_COLUMN5
                << TABLE_TABLE_COLUMN6
                << TABLE_TABLE_COLUMN7
                << TABLE_TABLE_COLUMN8;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 180);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            int points = 3 * record->get(0) + record->get(1);
            int games = record->get(0) + record->get(1) + record->get(2);
            xmlFilter.window->setCellValue(i, 0, record->getString());
            xmlFilter.window->setCellValue(i, 1, QString::number(games));
            for (int k = 0; k < 5; k++) {
                xmlFilter.window->setCellValue(i, 2 + k, QString::number(record->get(k)));
            }
            xmlFilter.window->setCellValue(i, 7, QString("%1").arg(points, 4));
            xmlFilter.window->setCellValue(i, 8, QString("ta02_%1").arg(record->getString()));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(7, Qt::DescendingOrder);
    }

}

void listOfTable2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QDate date = xmlFilter.report->getDate();
        const QString* score = xmlFilter.report->getScore();
        QString city = xmlFilter.report->getStadiumCity();
        if ((team1 == xmlFilter.filter->filter) || (team2 == xmlFilter.filter->filter)) {
            QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
            Record* record = Record::getInstance(hash, key);
            QString qdate = date.toString("yyyy/MM/dd");
            record->setString(qdate, 0);
            record->setString(city, 1);
            record->setString(team1, 2);
            record->setString(team2, 3);
            record->setString(*score, 4);
            record->setString(*(xmlFilter.fileName), 5);
        }
    } else {
        QStringList titles;
        titles << TABLE_TABLE2_COLUMN1
                << TABLE_TABLE2_COLUMN2
                << TABLE_TABLE2_COLUMN3
                << TABLE_TABLE2_COLUMN4
                << TABLE_TABLE2_COLUMN5;
        xmlFilter.window->initTable(titles, 60, hash->size());
        xmlFilter.window->widget.table->setColumnWidth(0, 90);
        xmlFilter.window->widget.table->setColumnWidth(1, 120);
        xmlFilter.window->widget.table->setColumnWidth(2, 120);
        xmlFilter.window->widget.table->setColumnWidth(3, 120);

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void checkListOfPlayers(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        uint len1 = players1.size();
        uint len2 = players2.size();
        if ((len1 != 11) || (len2 != 11)) {
            addMatch(*(xmlFilter.report), *(xmlFilter.fileName), hash);
        }
    } else {
        QStringList titles;
        titles << TABLE_MATCHINFO_COLUMN1
                << TABLE_MATCHINFO_COLUMN2
                << TABLE_MATCHINFO_COLUMN3
                << TABLE_MATCHINFO_COLUMN4
                << TABLE_MATCHINFO_COLUMN5;
        xmlFilter.window->initTable(titles, 120, hash->size());

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void checkListOfPlayers2(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString team1 = xmlFilter.report->getTeam1();
        QString team2 = xmlFilter.report->getTeam2();
        QVector<Report::Player> players1 = xmlFilter.report->getPlayers1();
        QVector<Report::Player> players2 = xmlFilter.report->getPlayers2();
        uint len1 = players1.size();
        for (uint i = 0; i < len1; i++) {
            QString player = players1.at(i).player;
            QString id = players1.at(i).id;
            QString key = QString("%1,%2").arg(player).arg(team1);
            Record* record = Record::getInstance(hash, key);
            QString real_id = record->getString();
            int counter = record->get();
            if ((real_id == "") && (counter == 0)) {
                record->setString(id, 0);
                record->setString(player, 1);
                record->setString(team1, 2);
                record->setString(id, 3);
                record->add(1);
            } else {
                if (real_id != id) {
                    record->setString(id, 4);
                    record->add(1);
                }
            }
        }
        uint len2 = players2.size();
        for (uint i = 0; i < len2; i++) {
            QString player = players2.at(i).player;
            QString id = players2.at(i).id;
            QString key = QString("%1,%2").arg(player).arg(team2);
            Record* record = Record::getInstance(hash, key);
            QString real_id = record->getString();
            int counter = record->get();
            if ((real_id == "") && (counter == 0)) {
                record->setString(id, 0);
                record->setString(player, 1);
                record->setString(team2, 2);
                record->setString(id, 3);
                record->add(1);
            } else {
                if (real_id != id) {
                    record->setString(id, 4);
                    record->add(1);
                }
            }
        }
        QVector<Report::Event> events = xmlFilter.report->getEvents();
        uint length = events.size();
        for (uint i = 0; i < length; i++) {
            QString team = events.at(i).team;
            QString eventType = events.at(i).type;
            QString player = events.at(i).player;
            QString playerid = events.at(i).playerid;
            QString key = QString("%1,%2").arg(player).arg(team);
            Record* record = Record::getInstance(hash, key);
            QString real_id = record->getString();
            int counter = record->get();
            if ((real_id == "") && (counter == 0)) {
                record->setString(playerid, 0);
                record->setString(player, 1);
                record->setString(team, 2);
                record->setString(playerid, 3);
                record->add(1);
            } else {
                if (real_id != playerid) {
                    record->setString(playerid, 4);
                    record->add(1);
                }
            }
            if (eventType == EVENT_SUBSTITUTION) {
                QString player2 = events.at(i).player2;
                QString playerid2 = events.at(i).playerid2;
                QString key = QString("%1,%2").arg(player2).arg(team);
                Record* record = Record::getInstance(hash, key);
                QString real_id = record->getString();
                int counter = record->get();
                if ((real_id == "") && (counter == 0)) {
                    record->setString(playerid2, 0);
                    record->setString(player2, 1);
                    record->setString(team, 2);
                    record->setString(playerid2, 3);
                    record->add(1);
                } else {
                    if (real_id != playerid2) {
                        record->setString(playerid2, 4);
                        record->add(1);
                    }
                }
            }
        }
    } else {
        QStringList titles;
        titles << TABLE_CHECKPLAYERS2_COLUMN1
                << TABLE_CHECKPLAYERS2_COLUMN2
                << TABLE_CHECKPLAYERS2_COLUMN3
                << TABLE_CHECKPLAYERS2_COLUMN4;
        xmlFilter.window->initTable(titles, 120, hash->size());

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            if (record->get() > 1) {
                i++;
            }
        }
        xmlFilter.window->widget.table->setRowCount(i);
        i = 0;

        foreach(StatHashValue* record, *hash) {
            if (record->get() > 1) {
                xmlFilter.window->setCellValue(i, 0, record->getString(1));
                xmlFilter.window->setCellValue(i, 1, record->getString(2));
                xmlFilter.window->setCellValue(i, 2, record->getString(3));
                xmlFilter.window->setCellValue(i, 3, record->getString(4));
                xmlFilter.window->setCellValue(i, 4, QString(""));
                delete record;
                i++;
            }
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

void checkListOfAttendance(const XmlFilter& xmlFilter, StatHash* hash) {
    if (xmlFilter.window == NULL) {
        QString city = xmlFilter.report->getStadiumCity();
        QString attendance = xmlFilter.report->getStadiumAttendance();
        if (attendance == "") {
            addMatch(*(xmlFilter.report), *(xmlFilter.fileName), hash);
        }
    } else {
        QStringList titles;
        titles << TABLE_MATCHINFO_COLUMN1
                << TABLE_MATCHINFO_COLUMN2
                << TABLE_MATCHINFO_COLUMN3
                << TABLE_MATCHINFO_COLUMN4
                << TABLE_MATCHINFO_COLUMN5;
        xmlFilter.window->initTable(titles, 120, hash->size());

        int i = 0;
        foreach(StatHashValue* record, *hash) {
            xmlFilter.window->setCellValue(i, 0, record->getString(0));
            xmlFilter.window->setCellValue(i, 1, record->getString(1));
            xmlFilter.window->setCellValue(i, 2, record->getString(2));
            xmlFilter.window->setCellValue(i, 3, record->getString(3));
            xmlFilter.window->setCellValue(i, 4, record->getString(4));
            xmlFilter.window->setCellValue(i, 5, QString("xm01_%1").arg(record->getString(5)));
            delete record;
            i++;
        }
        hash->clear();
        xmlFilter.window->widget.table->setSortingEnabled(true);
        xmlFilter.window->widget.table->sortByColumn(0, Qt::AscendingOrder);
    }
}

bool isPlayed(const Report& report, const QString& player) {
    bool value = false;
    QVector<Report::Player> players1 = report.getPlayers1();
    QVector<Report::Player> players2 = report.getPlayers2();
    uint len1 = players1.size();
    for (uint i = 0; i < len1; i++) {
        QString player2 = players1.at(i).player;
        if (player2 == player) {
            return true;
        }
    }
    uint len2 = players2.size();
    for (uint i = 0; i < len2; i++) {
        QString player2 = players2.at(i).player;
        if (player2 == player) {
            return true;
        }
    }
    QVector<Report::Event> events = report.getEvents();
    uint length = events.size();
    for (uint i = 0; i < length; i++) {
        QString eventType = events.at(i).type;
        if (eventType == EVENT_SUBSTITUTION) {
            QString player2 = events.at(i).player2;
            if (player2 == player) {
                return true;
            }
        }
    }
    return value;
}

int getPlayerGoals(const Report* report, const QString* player) {
    int value = 0;
    QVector<Report::Event> events = report->getEvents();
    uint length = events.size();
    for (uint i = 0; i < length; i++) {
        QString eventType = events.at(i).type;
        if ((eventType == EVENT_GOAL) || (eventType == EVENT_GOAL_PENALTY)) {
            QString player2 = events.at(i).player;
            if (player2 == player) {
                value++;
            }
        }
    }
    return value;
}

void addMatch(const Report& report, const QString& fileName, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    const QString* score = report.getScore();
    QString city = report.getStadiumCity();
    QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
    Record* record = Record::getInstance(hash, key);
    QString qdate = date.toString("yyyy/MM/dd");
    record->setString(qdate, 0);
    record->setString(city, 1);
    record->setString(team1, 2);
    record->setString(team2, 3);
    record->setString(*score, 4);
    record->setString(fileName, 5);
}

QString getKeyPlayer(const bool useID, const QString& playerid, const QString& player, const QString& team) {
    QString qstr = (useID) ?
        ((playerid == "") ? QString("%1").arg(player) : QString("%1").arg(playerid)) :
        QString("%1 %2").arg(player).arg(team);
    return qstr;
}

QString getKeyCoach(const bool useID, const QString& coachid, const QString& coach, const QString& team) {
    QString qstr = (useID) ?
        ((coachid == "") ? QString("%1").arg(coach) : QString("%1").arg(coachid)) :
        QString("%1 %2").arg(coach).arg(team);
    return qstr;
}

QString getKeyTeam(const bool useID, const QString& teamid, const QString& team) {
    QString qstr = (useID) ?
        ((teamid == "") ? QString("%1").arg(team) : QString("%1").arg(teamid)) :
        QString("%1").arg(team);
    return qstr;
}
