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

#include "Record.h"
#include "XmlFileReader.h"
#include "constants.h"

void listOfGoals(const QDomElement& docElement, const QString& filter, StatHash* hash) {
    QDomNodeList nodes = docElement.elementsByTagName("event");
    uint length = nodes.length();
    for (uint i = 0; i < length; i++) {
        QDomElement node = nodes.at(i).toElement();
        QString eventType = node.attributes().namedItem("type").nodeValue();
        QString player = node.attributes().namedItem("player").nodeValue();
        QString team = node.attributes().namedItem("team").nodeValue();
        if ((eventType == EVENT_GOAL) || (eventType == EVENT_GOAL_PENALTY)) {
            QString key = QString("%1 (%2)").arg(player).arg(team);
            Record* record = Record::getInstance(hash, key);
            record->setString(player, 0);
            record->setString(team, 1);
            record->add(1);
        }
    }
}

void listOfReferies(const QDomElement& docElement, const QString& filter, StatHash* hash) {
    QDomNodeList nodes = docElement.elementsByTagName("referee");
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        QString name = node.text();
        QString city = node.attributes().namedItem("city").nodeValue();
        QString key = QString("%1 (%2)").arg(name).arg(city);
        Record* record = Record::getInstance(hash, key);
        record->setString(name, 0);
        record->setString(city, 1);
        record->add(1);
    }
}

void listOfReferies2(const QDomElement& docElement, const QString& filter, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QString score = getScore(docElement);
    QDate date = getDate(docElement);
    QString city;
    QString stadium = getStadium(docElement, &city);
    QString referee = getReferee(docElement);
    if (referee == filter) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("dd.MM.yyyy");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
    }
}

void listOfCoaches(const QDomElement& docElement, const QString& filter, StatHash* hash) {
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
        Record* record1 = Record::getInstance(hash, key1);
        record1->setString(coach1, 0);
        record1->setString(team1, 1);
        record1->add(1);
        Record* record2 = Record::getInstance(hash, key2);
        record2->setString(coach2, 0);
        record2->setString(team2, 1);
        record2->add(1);
    }
}

void listOfCoaches2(const QDomElement& docElement, const QString& filter, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QString score = getScore(docElement);
    QDate date = getDate(docElement);
    QString city;
    QString stadium = getStadium(docElement, &city);
    QString coach1 = getCoach1(docElement);
    QString coach2 = getCoach2(docElement);
    if ((coach1 == filter) || (coach2 == filter)) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("dd.MM.yyyy");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
    }
}

void listOfStadiums(const QDomElement& docElement, const QString& filter, StatHash* hash) {
    QDomNodeList nodes = docElement.elementsByTagName("stadium");
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        QString stadium = node.text();
        QString city = node.attributes().namedItem("city").nodeValue();
        QString key = QString("%1 (%2)").arg(stadium).arg(city);
        Record* record = Record::getInstance(hash, key);
        record->setString(stadium, 0);
        record->setString(city, 1);
        record->add(1);
    }
}

void listOfStadiums2(const QDomElement& docElement, const QString& filter, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QString score = getScore(docElement);
    QDate date = getDate(docElement);
    QString city;
    QString stadium = getStadium(docElement, &city);
    if (stadium == filter) {
        QString key = QString("%1,%2,%3").arg(date.toString("yyyyMMdd")).arg(team1).arg(team2);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("dd.MM.yyyy");
        record->setString(qdate, 0);
        record->setString(city, 1);
        record->setString(team1, 2);
        record->setString(team2, 3);
        record->setString(score, 4);
    }
}

void listOfMatches(const QDomElement& docElement, const QString& filter, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QDomNodeList nodesScore = docElement.elementsByTagName("score");
    QDate date = getDate(docElement);
    if (nodesScore.length() > 0) {
        QDomElement nodeScore = nodesScore.at(0).toElement();
        QString score = nodeScore.text();
        QString key = QString("%1 - %2 %3").arg(team1).arg(team2).arg(score);
        Record* record = Record::getInstance(hash, key);
        QString qdate = date.toString("dd.MM.yyyy");
        record->setString(qdate, 0);
        record->setString(team1, 1);
        record->setString(team2, 2);
        record->setString(score, 3);
    }
}

void listOfPlayers(const QDomElement& docElement, const QString& filter, StatHash* hash) {
    QString team1 = getTeam1(docElement);
    QString team2 = getTeam2(docElement);
    QDomNodeList nodesPlayers1 = docElement.elementsByTagName("player1");
    QDomNodeList nodesPlayers2 = docElement.elementsByTagName("player2");
    uint len1 = nodesPlayers1.length();
    for (uint i = 0; i < len1; i++) {
        QDomElement nodeElement = nodesPlayers1.at(i).toElement();
        QString player2 = nodeElement.text();
        QString key = QString("%1 (%2)").arg(player2).arg(team1);
        Record* record = Record::getInstance(hash, key);
        record->setString(player2, 0);
        record->setString(team1, 1);
        record->add(1);
    }
    uint len2 = nodesPlayers1.length();
    for (uint i = 0; i < len2; i++) {
        QDomElement nodeElement = nodesPlayers2.at(i).toElement();
        QString player2 = nodeElement.text();
        QString key = QString("%1 (%2)").arg(player2).arg(team2);
        Record* record = Record::getInstance(hash, key);
        record->setString(player2, 0);
        record->setString(team2, 1);
        record->add(1);
    }

    QDomNodeList nodes = docElement.elementsByTagName("event");
    uint length = nodes.length();
    for (uint i = 0; i < length; i++) {
        QDomElement node = nodes.at(i).toElement();
        QString eventType = node.attributes().namedItem("type").nodeValue();
        QString player2 = node.attributes().namedItem("player2").nodeValue();
        QString team = node.attributes().namedItem("team").nodeValue();
        if (eventType == EVENT_SUBSTITUTION) {
            QString key = QString("%1 (%2)").arg(player2).arg(team);
            Record* record = Record::getInstance(hash, key);
            record->setString(player2, 0);
            record->setString(team, 1);
            record->add(1);
        }
    }
}

void listOfTable(const QDomElement& docElement, const QString& filter, StatHash* hash) {
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

QString getTeam1(const QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("team1");
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
    }
    return value;
}

QString getTeam2(const QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("team2");
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
    }
    return value;
}

QDate getDate(const QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("date");    
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
        QDate date = QDate::fromString(value, "yyyyMMdd");
        return date;
    }
    return QDate(1, 1, 1);
}

QString getScore(const QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("score");
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
    }
    return value;
}

QString getStadium(const QDomElement& docElement, QString* city) {
    QDomNodeList nodes = docElement.elementsByTagName("stadium");
    QString value = "";
    if (city != NULL) {
        *city = "";
    }
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
        if (city != NULL) {
            *city = node.attributes().namedItem("city").nodeValue();
        }
    }
    return value;    
}

QString getReferee(const QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("referee");
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
    }
    return value;
}

QString getCoach1(const QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("coach1");
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
    }
    return value;
}

QString getCoach2(const QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("coach2");
    QString value = "";
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        value = node.text();
    }
    return value;
}
