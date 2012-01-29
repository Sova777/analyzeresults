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

#ifndef REPORT_H
#define	REPORT_H

#include <QDate>
#include <QString>
#include <QXmlStreamReader>

class Report {
public:
    void setScore(QXmlStreamReader& xml);
    const QString& getScore() const;
    void setDateAttributes(QXmlStreamReader& xml);
    const QString& getTime() const;
    void setDate(QXmlStreamReader& xml);
    const QDate& getDate() const;
    void setCoach2Attributes(QXmlStreamReader& xml);
    const QString& getCoach2id() const;
    void setCoach1Attributes(QXmlStreamReader& xml);
    const QString& getCoach1id() const;
    void setCoach2(QXmlStreamReader& xml);
    const QString& getCoach2() const;
    void setCoach1(QXmlStreamReader& xml);
    const QString& getCoach1() const;
    void setTeam2Attributes(QXmlStreamReader& xml);
    const QString& getTeam2id() const;
    void setTeam1Attributes(QXmlStreamReader& xml);
    const QString& getTeam1id() const;
    void setTeam2(QXmlStreamReader& xml);
    const QString& getTeam2() const;
    void setTeam1(QXmlStreamReader& xml);
    const QString& getTeam1() const;
private:
    QString team1;
    QString team2;
    QString team1id;
    QString team2id;
    QString coach1;
    QString coach2;
    QString coach1id;
    QString coach2id;
    QDate date;
    QString time;
    QString score;
};

#endif	/* REPORT_H */
