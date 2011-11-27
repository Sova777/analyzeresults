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

#include <QtGui/QtGui>
#include <QtXml/QtXml>
#include <sstream>

#include "MainWindow.h"

using namespace std;

const QString EVENT_GOAL = QString::fromUtf8("Гол");

MainWindow::MainWindow() {

    widget.setupUi(this);

    connect(widget.actionExit, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(widget.pushButton_1, SIGNAL(clicked()),
            this, SLOT(selectMode1()));
    connect(widget.pushButton_2, SIGNAL(clicked()),
            this, SLOT(selectMode2()));
    connect(widget.pushButton_3, SIGNAL(clicked()),
            this, SLOT(selectMode3()));
    connect(widget.pushButton_4, SIGNAL(clicked()),
            this, SLOT(selectMode4()));
    connect(widget.pushButton_5, SIGNAL(clicked()),
            this, SLOT(selectMode5()));
    connect(widget.pushButton_6, SIGNAL(clicked()),
            this, SLOT(selectMode6()));
    connect(widget.text, SIGNAL(anchorClicked(const QUrl &)),
            this, SLOT(linkActivated(const QUrl &)));
    selectMode1();
}

MainWindow::~MainWindow() {
}

void MainWindow::selectMode1() {
    widget.text->setText("<b>Mode 1</b>");
    calculateTable();
}

void MainWindow::selectMode2() {
    widget.text->setText("<b>Mode 2</b>");
}

void MainWindow::selectMode3() {
    IntHash hash = analyzeXml(&MainWindow::referies);
    QString qstr = "";
    QList<IntHashKey> keys = hash.keys();
    qSort(keys.begin(), keys.end());
    foreach (IntHashKey key, keys) {
        qstr += QString("<b>%1</b> = %2<br>").arg(key).arg(hash[key]);
    }
    widget.text->setText(qstr);
}

void MainWindow::selectMode4() {
    widget.text->setText("<b>Mode 4</b>");
}

void MainWindow::selectMode5() {
    IntHash hash = analyzeXml(&MainWindow::matches);
    QString qstr = "";
    QList<IntHashKey> keys = hash.keys();
    qSort(keys.begin(), keys.end());
    foreach (IntHashKey key, keys) {
        qstr += QString("<b>%1</b><br>").arg(key);
    }
    widget.text->setText(qstr);
}

void MainWindow::selectMode6() {
    IntHash hash = analyzeXml(&MainWindow::goals);
    QString qstr = "";
    QList<IntHashKey> keys = hash.keys();
    qSort(keys.begin(), keys.end());
    foreach (IntHashKey key, keys) {
        qstr += QString("<b>%1</b> = %2<br>").arg(key).arg(hash[key]);
    }
    widget.text->setText(qstr);
}

void MainWindow::goals(QDomElement& docElement, IntHash& hash) {
    QDomNodeList nodes = docElement.elementsByTagName("event");
    uint length = nodes.length();
    for (int i = 0; i < length; i++) {
        QDomElement node = nodes.at(i).toElement();
        QString eventType = node.attributes().namedItem("type").nodeValue();
        QString player = node.attributes().namedItem("player").nodeValue();
        QString club = node.attributes().namedItem("club").nodeValue();
        if (eventType == EVENT_GOAL) {
            QString key = player.append(" (").append(club).append(")");
            if (hash.contains(key)) {
                hash[key]++;
            } else {
                hash[key] = 1;
            }
        }
    }
}

void MainWindow::referies(QDomElement& docElement, IntHash& hash) {
    QDomNodeList nodes = docElement.elementsByTagName("refery");
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        QString name = node.text();
        QString city = node.attributes().namedItem("city").nodeValue();
        QString key = name.append(" (").append(city).append(")");
        if (hash.contains(key)) {
            hash[key]++;
        } else {
            hash[key] = 1;
        }
    }
}

void MainWindow::matches(QDomElement& docElement, IntHash& hash) {
    QDomNodeList nodesTeam1 = docElement.elementsByTagName("team1");
    QDomNodeList nodesTeam2 = docElement.elementsByTagName("team2");
    QDomNodeList nodesScore = docElement.elementsByTagName("score");
    if ((nodesTeam1.length() > 0) && (nodesTeam2.length() > 0) && (nodesScore.length() > 0)) {
        QDomElement nodeTeam1 = nodesTeam1.at(0).toElement();
        QDomElement nodeTeam2 = nodesTeam2.at(0).toElement();
        QDomElement nodeScore = nodesScore.at(0).toElement();
        QString team1 = nodeTeam1.text();
        QString team2 = nodeTeam2.text();
        QString score = nodeScore.text();
        QString key = team1.append(" - ")
                .append(team2)
                .append(" ")
                .append(score);
        hash[key] = 1;
    }
}

// DOM parser
MainWindow::IntHash MainWindow::analyzeXml(pointer func) {
    QTime t;
    t.start();
    QDir* qDir = new QDir("data/xml");
    qDir->setFilter(QDir::Files);
    QStringList list = qDir->entryList();
    QDomDocument xml("report");
    IntHash hash;
    for (int i = 0; i < list.size(); ++i) {
        QString fileName = list.at(i);
        QFile file(qDir->absolutePath() + "/" + fileName);
        if (!file.open(QIODevice::ReadOnly)) continue;
        if (!xml.setContent(&file)) {
            file.close();
            continue;
        }
        file.close();
        QDomElement docElement = xml.documentElement();
        (this->*func)(docElement, hash);
    }
    QString status = QString("Time: %1 ms.").arg(t.elapsed());
    statusBar()->showMessage(status, 2000);
    return hash;
}

void MainWindow::linkActivated(const QUrl & link) {
    QString code = link.toString().section("_", 0, 0);
    QString id = link.toString().section("_", 1, 1);
    if (code == "cl") {
        calculateClubStat(id);
        return;
    }
    if (code == "match") {
        matchReport(id);
        return;
    }
    return;
}

void MainWindow::matchReport(const QString& matchId) {
    //
}

void MainWindow::matchResults(const QString& clubId) {
    //
}

void MainWindow::calculateClubStat(const QString& clubId) {
    //
}

void MainWindow::calculateTable() {
    //
}
