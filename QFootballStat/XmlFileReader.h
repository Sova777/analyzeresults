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

#ifndef XMLFILEREADER_H
#define	XMLFILEREADER_H

#include <QtGui>
#include <QtXml>
#include <QDate>
#include "Report.h"
#include "constants.h"

typedef void (*pointer)(const QDomElement& docElement, const QDate& date, const QString& fileName, const QString& filter, StatHash* hash);
typedef void (*pointer2)(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);

void listOfGoals(const QDomElement& docElement, const QDate& date, const QString& fileName, const QString& filter, StatHash* hash);
void listOfGoals2(const QDomElement& docElement, const QDate& date, const QString& fileName, const QString& filter, StatHash* hash);
void listOfMatches(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfReferies(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfReferies2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfTable(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfTable2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfCoaches(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfCoaches2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfStadiums(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfStadiums2(const Report& report, const QString& fileName, const QString& filter, StatHash* hash);
void listOfPlayers(const QDomElement& docElement, const QDate& date, const QString& fileName, const QString& filter, StatHash* hash);
void listOfPlayers2(const QDomElement& docElement, const QDate& date, const QString& fileName, const QString& filter, StatHash* hash);

void checkListOfPlayers(const QDomElement& docElement, const QDate& date, const QString& fileName, const QString& filter, StatHash* hash);
void checkListOfPlayers2(const QDomElement& docElement, const QDate& date, const QString& fileName, const QString& filter, StatHash* hash);
void checkListOfAttendance(const QDomElement& docElement, const QDate& date, const QString& fileName, const QString& filter, StatHash* hash);

void addMatch(const QDomElement& docElement, const QDate& date, const QString& fileName, StatHash* hash);

QString getTeam1(const QDomElement& docElement);
QString getTeam2(const QDomElement& docElement);
QDate getDate(const QDomElement& docElement, QString* time = NULL);
QString getReferee(const QDomElement& docElement, QString* city = NULL);
QString getScore(const QDomElement& docElement);
QString getStadium(const QDomElement& docElement, QString* city = NULL, QString* attendance = NULL);
QString getCoach1(const QDomElement& docElement);
QString getCoach2(const QDomElement& docElement);
QString getMatch(const QDomElement& docElement, QString* round = NULL);
bool isPlayed(const QDomElement& docElement, const QString& player);
bool isScored(const QDomElement& docElement, const QString& player);

#endif	/* XMLFILEREADER_H */
