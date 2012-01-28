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

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QtXml>
#include "ui_MainWindow.h"
#include "XmlFileReader.h"
#include "Record.h"
#include "Report.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
private:
    Ui::MainWindow widget;
    QString directory;
    void closeEvent(QCloseEvent *event);
    void setCellValue(int row, int column, QString value);
    void report(const QString& fileName);
    void analyzeXml(pointer func, const QString& filter, StatHash* hash);
    void analyzeXml2(pointer2 func, const QString& filter, StatHash* hash);
    Report saxParser(QFile& file);

private:
    void calculateStadiums2(const QString& stadium);
    void calculateReferies2(const QString& referee);
    void calculateCoaches2(const QString& coach);
    void calculatePlayers2(const QString& player);
    void calculateGoals2(const QString& player);
    void calculateTable2(const QString& team);
    void calculateTeams2(const QString& team);
private slots:
    void open();
    void save();
    void about();

    void calculateGoals(void);
    void calculateMatches(void);
    void calculateReferies(void);
    void calculateTable(void);
    void calculateCoaches(void);
    void calculateStadiums(void);
    void calculatePlayers(void);
    void calculateTeams(void);

    void verifyPlayers(void);
    void verifyPlayers2(void);
    void verifyAttendance(void);

    void selectMode1();
    void selectMode2();
    void selectMode3();
    void selectMode4();
    void selectMode5();
    void selectMode6();
    void selectMode7();
    void selectMode8();
    void linkActivated(const QUrl & link);
    void cellSelected(int row, int column);
    void jump(const QString& link);
    void initTable(int columns);
};

#endif	/* _MAINWINDOW_H */
