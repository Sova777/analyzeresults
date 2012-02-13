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

#include "Record.h"
#include "Report.h"
#include "XmlFileReader.h"
#include "constants.h"

void listOfGoals(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QVector<Report::Event> events = report.getEvents();
    uint length = events.size();
    for (uint i = 0; i < length; i++) {
        QString eventType = events.at(i).type;
        QString player = events.at(i).player;
        QString team = events.at(i).team;
        if ((eventType == EVENT_GOAL) || (eventType == EVENT_GOAL_PENALTY)) {
            QString key = QString("%1 (%2)").arg(player).arg(team);
            Record* record = Record::getInstance(hash, key);
            record->setString(player, 0);
            record->setString(team, 1);
            record->add(1);
        }
    }
}

void listOfGoals2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    QString score = report.getScore();
    QString city = report.getStadiumCity();
    if (isScored(report, filter)) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("yyyy/MM/dd");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
        record->setString(fileName, 5);
    }
}

void listOfReferies(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString name = report.getReferee();
    QString city = report.getRefereeCity();
    QString key = QString("%1 (%2)").arg(name).arg(city);
    Record* record = Record::getInstance(hash, key);
    record->setString(name, 0);
    record->setString(city, 1);
    record->add(1);
}

void listOfReferies2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    QString score = report.getScore();
    QString city = report.getStadiumCity();
    QString referee = report.getReferee();
    if (referee == filter) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("yyyy/MM/dd");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
        record->setString(fileName, 5);
    }
}

void listOfCoaches(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QString coach1 = report.getCoach1();
    QString coach2 = report.getCoach2();
    QString key1 = QString("%1 (%2)").arg(coach1).arg(team1);
    QString key2 = QString("%1 (%2)").arg(coach2).arg(team2);
    Record* record1 = Record::getInstance(hash, key1);
    record1->setString(coach1, 0);
    record1->setString(team1, 1);
    record1->add(1);
    Record* record2 = Record::getInstance(hash, key2);
    record2->setString(coach2, 0);
    record2->setString(team2, 1);
    record2->add(1);
}

void listOfCoaches2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    QString score = report.getScore();
    QString city = report.getStadiumCity();
    QString coach1 = report.getCoach1();
    QString coach2 = report.getCoach2();
    if ((coach1 == filter) || (coach2 == filter)) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("yyyy/MM/dd");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
        record->setString(fileName, 5);
    }
}

void listOfStadiums(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString stadium = report.getStadium();
    QString city = report.getStadiumCity();
    QString key = QString("%1 (%2)").arg(stadium).arg(city);
    Record* record = Record::getInstance(hash, key);
    record->setString(stadium, 0);
    record->setString(city, 1);
    record->add(1);
}

void listOfStadiums2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    QString score = report.getScore();
    QString city = report.getStadiumCity();
    QString stadium = report.getStadium();
    if (stadium == filter) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("yyyy/MM/dd");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
        record->setString(fileName, 5);
    }
}

void listOfMatches(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QString score = report.getScore();
    QString qdate = report.getDate().toString("yyyy/MM/dd");
    Record* record = Record::newInstance(hash);
    record->setString(qdate, 0);
    record->setString(team1, 1);
    record->setString(team2, 2);
    record->setString(score, 3);
    record->setString(fileName, 4);
}

void listOfPlayers(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QVector<Report::Player> players1 = report.getPlayers1();
    QVector<Report::Player> players2 = report.getPlayers2();
    uint len1 = players1.size();
    for (uint i = 0; i < len1; i++) {
        QString player2 = players1.at(i).player;
        QString key = QString("%1 (%2)").arg(player2).arg(team1);
        Record* record = Record::getInstance(hash, key);
        record->setString(player2, 0);
        record->setString(team1, 1);
        record->add(1);
    }
    uint len2 = players2.size();
    for (uint i = 0; i < len2; i++) {
        QString player2 = players2.at(i).player;
        QString key = QString("%1 (%2)").arg(player2).arg(team2);
        Record* record = Record::getInstance(hash, key);
        record->setString(player2, 0);
        record->setString(team2, 1);
        record->add(1);
    }

    QVector<Report::Event> events = report.getEvents();
    uint length = events.size();
    for (uint i = 0; i < length; i++) {
        QString eventType = events.at(i).type;
        QString player1 = events.at(i).player;
        QString player2 = events.at(i).player2;
        QString team = events.at(i).team;
        if (eventType == EVENT_SUBSTITUTION) {
            QString key = QString("%1 (%2)").arg(player2).arg(team);
            Record* record = Record::getInstance(hash, key);
            record->setString(player2, 0);
            record->setString(team, 1);
            record->add(1, 0);
        } else {
            QString key = QString("%1 (%2)").arg(player1).arg(team);
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

void listOfPlayers2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    QString score = report.getScore();
    QString city = report.getStadiumCity();
    if (isPlayed(report, filter)) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("yyyy/MM/dd");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
        record->setString(fileName, 5);
    }
}

void listOfTable(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QString score = report.getScore();
    if (score != "") {
        bool ok;
        int goal1 = 99999;
        int goal2 = 99999;
        goal1 = score.section(':', 0, 0).toInt(&ok);
        goal2 = score.section(':', 1, 1).toInt(&ok);
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

}

void listOfTable2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    QString score = report.getScore();
    QString city = report.getStadiumCity();
    if ((team1 == filter) || (team2 == filter)) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("yyyy/MM/dd");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
        record->setString(fileName, 5);
    }
}

void checkListOfPlayers(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QVector<Report::Player> players1 = report.getPlayers1();
    QVector<Report::Player> players2 = report.getPlayers2();
    uint len1 = players1.size();
    uint len2 = players2.size();
    if ((len1 != 11) || (len2 != 11)) {
        addMatch(report, fileName, hash);
    }
}

void checkListOfPlayers2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QVector<Report::Player> players1 = report.getPlayers1();
    QVector<Report::Player> players2 = report.getPlayers2();
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
    QVector<Report::Event> events = report.getEvents();
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
}

void checkListOfAttendance(const Report& report, const QString& fileName, const QString& filter, StatHash* hash) {
    QString city = report.getStadiumCity();
    QString attendance = report.getStadiumAttendance();
    if (attendance == "") {
        addMatch(report, fileName, hash);
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

bool isScored(const Report& report, const QString& player) {
    bool value = false;
    QVector<Report::Event> events = report.getEvents();
    uint length = events.size();
    for (uint i = 0; i < length; i++) {
        QString eventType = events.at(i).type;
        if ((eventType == EVENT_GOAL) || (eventType == EVENT_GOAL_PENALTY)) {
            QString player2 = events.at(i).player;
            if (player2 == player) {
                return true;
            }
        }
    }
    return value;
}

void addMatch(const Report& report, const QString& fileName, StatHash* hash) {
    QString team1 = report.getTeam1();
    QString team2 = report.getTeam2();
    QDate date = report.getDate();
    QString score = report.getScore();
    QString city = report.getStadiumCity();
    QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
    Record* record = Record::getInstance(hash, key);
    QString qdate = date.toString("yyyy/MM/dd");
    record->setString(qdate, 0);
    record->setString(city, 1);
    record->setString(team1, 2);
    record->setString(team2, 3);
    record->setString(score, 4);
    record->setString(fileName, 5);
}

// QDataStream &operator<<(QDataStream& stream, const Report& report);
// QDataStream &operator>>(QDataStream& stream, Report& report);
// QFile file("file.xxx");
// file.open(QIODevice::WriteOnly);
// QDataStream out(&file);
// out << (quint32)0xA0B0C0D0;
// out << (qint32)123;
// out.setVersion(QDataStream::Qt_4_0);
// out << lots_of_interesting_data;
 