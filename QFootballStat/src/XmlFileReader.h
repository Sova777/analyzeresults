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
#include "Filter.h"
#include "Report.h"
#include "constants.h"

class MainWindow;
typedef void (*pointer)(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);

void listOfGoals(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfGoals2(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfMatches(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfReferies(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfReferies2(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfTable(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfTable2(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfCoaches(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfCoaches2(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfCoaches3(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfStadiums(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfStadiums2(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfPlayers(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfPlayers2(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfPlayers3(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfTeams(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void listOfTeams2(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);

void checkListOfPlayers(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void checkListOfPlayers2(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);
void checkListOfAttendance(MainWindow* window, const Report& report, const QString& fileName, const Filter& filter, StatHash* hash);

void addMatch(const Report& report, const QString& fileName, StatHash* hash);

bool isPlayed(const Report& report, const QString& player);
int getPlayerGoals(const Report& report, const QString& player);
QString getKeyPlayer(const bool useID, const QString& playerid, const QString& player, const QString& team);
QString getKeyCoach(const bool useID, const QString& coachid, const QString& coach, const QString& team);
QString getKeyTeam(const bool useID, const QString& teamid, const QString& team);

#endif	/* XMLFILEREADER_H */
