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

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_MainWindow.h"
#include "Record.h"
#include <QtXml>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    typedef QString StatHashKey;
    typedef Record StatHashValue;
    typedef QHash<StatHashKey, StatHashValue*> StatHash;
    typedef void (MainWindow::*pointer)(QDomElement& docElement, StatHash* hash);
    MainWindow();
    virtual ~MainWindow();
private:
    Ui::MainWindow widget;
    QString directory;
    void setCellValue(int row, int column, QString value);
    void matchReport(const QString& matchId);
    void matchResults(const QString& clubId);
    void analyzeXml(pointer func, StatHash* hash);

    void goals(QDomElement& docElement, StatHash* hash);
    void matches(QDomElement& docElement, StatHash* hash);
    void referies(QDomElement& docElement, StatHash* hash);
    void table(QDomElement& docElement, StatHash* hash);
private slots:
    void open();
    void save();

    void calculateGoals(void);
    void calculateMatches(void);
    void calculateReferies(void);
    void calculateTable(void);

    void selectMode1();
    void selectMode2();
    void selectMode3();
    void selectMode4();
    void selectMode5();
    void selectMode6();
    void linkActivated(const QUrl & link);
};

#endif	/* _MAINWINDOW_H */
