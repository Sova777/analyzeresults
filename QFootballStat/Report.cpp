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

#include "Report.h"

void Report::addPlayer1(QXmlStreamReader& xml, QString& id) {
    Player player;
    player.player = xml.text().toString();
    player.id = id;
    players1.append(player);
}

void Report::addPlayer2(QXmlStreamReader& xml, QString& id) {
    Player player;
    player.player = xml.text().toString();
    player.id = id;
    players2.append(player);
}

void Report::addEvent(QXmlStreamReader& xml) {
    Event event;
    QXmlStreamAttributes attributes = xml.attributes();
    event.comment = attributes.value("comment").toString();
    event.player = attributes.value("player").toString();
    event.player2 = attributes.value("player2").toString();
    event.playerid = attributes.value("playerid").toString();
    event.playerid2 = attributes.value("playerid2").toString();
    event.team = attributes.value("team").toString();
    event.time = attributes.value("time").toString();
    event.type = attributes.value("type").toString();
    events.append(event);
}

const QVector<Report::Event>& Report::getEvents() const {
    return events;
}

const QVector<Report::Player>& Report::getPlayers1() const {
    return players1;
}

const QVector<Report::Player>& Report::getPlayers2() const {
    return players2;
}

void Report::setScore(QXmlStreamReader& xml) {
    this->score = xml.text().toString();
}

const QString& Report::getScore() const {
    return score;
}

void Report::setDateAttributes(QXmlStreamReader& xml) {
    this->time = xml.attributes().value("time").toString();
}

const QString& Report::getTime() const {
    return time;
}

void Report::setDate(QXmlStreamReader& xml) {
    this->date = QDate::fromString(xml.text().toString(), "yyyyMMdd");
}

const QDate& Report::getDate() const {
    return date;
}

void Report::setCoach2Attributes(QXmlStreamReader& xml) {
    this->coach2id = xml.attributes().value("id").toString();
}

const QString& Report::getCoach2id() const {
    return coach2id;
}

void Report::setCoach1Attributes(QXmlStreamReader& xml) {
    this->coach1id = xml.attributes().value("id").toString();
}

const QString& Report::getCoach1id() const {
    return coach1id;
}

void Report::setCoach2(QXmlStreamReader& xml) {
    this->coach2 = xml.text().toString();
}

const QString& Report::getCoach2() const {
    return coach2;
}

void Report::setCoach1(QXmlStreamReader& xml) {
    this->coach1 = xml.text().toString();
}

const QString& Report::getCoach1() const {
    return Report::coach1;
}

void Report::setTeam2Attributes(QXmlStreamReader& xml) {
    this->team2id = xml.attributes().value("id").toString();
}

const QString& Report::getTeam2id() const {
    return team2id;
}

void Report::setTeam1Attributes(QXmlStreamReader& xml) {
    this->team1id = xml.attributes().value("id").toString();
}

const QString& Report::getTeam1id() const {
    return team1id;
}

void Report::setTeam2(QXmlStreamReader& xml) {
    this->team2 = xml.text().toString();
}

const QString& Report::getTeam2() const {
    return team2;
}

void Report::setTeam1(QXmlStreamReader& xml) {
    this->team1 = xml.text().toString();
}

const QString& Report::getTeam1() const {
    return team1;
}

void Report::setStadium(QXmlStreamReader& xml) {
    this->stadium = xml.text().toString();
}

const QString& Report::getStadium() const {
    return stadium;
}

void Report::setStadiumAttributes(QXmlStreamReader& xml) {
    QXmlStreamAttributes attributes = xml.attributes();
    this->stadiumId = attributes.value("id").toString();
    this->stadiumCity = attributes.value("city").toString();
    this->stadiumAttendance = attributes.value("attendance").toString();
}

const QString& Report::getStadiumId() const {
    return stadiumId;
}

const QString& Report::getStadiumCity() const {
    return stadiumCity;
}

const QString& Report::getStadiumAttendance() const {
    return stadiumAttendance;
}

void Report::setRefereeAttributes(QXmlStreamReader& xml) {
    QXmlStreamAttributes attributes = xml.attributes();
    this->refereeId = attributes.value("id").toString();
    this->refereeCity = attributes.value("city").toString();
}

void Report::setReferee(QXmlStreamReader& xml) {
    this->referee = xml.text().toString();
}

const QString& Report::getReferee() const {
    return referee;
}

const QString& Report::getRefereeId() const {
    return refereeId;
}

const QString& Report::getRefereeCity() const {
    return refereeCity;    
}

void Report::setMatchAttributes(QXmlStreamReader& xml) {
    QXmlStreamAttributes attributes = xml.attributes();
    this->matchId = attributes.value("id").toString();
    this->matchRound = attributes.value("round").toString();
    this->matchTournament = attributes.value("tournament").toString();
}

const QString& Report::getMatchId() const {
    return matchId;
}

const QString& Report::getMatchRound() const {
    return matchRound;
}

const QString& Report::getMatchTournament() const {
    return matchTournament;
}
