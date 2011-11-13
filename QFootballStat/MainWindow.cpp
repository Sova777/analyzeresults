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

void MainWindow::referies(QString &qstr, QDomElement& docElement) {
    QDomNodeList nodes = docElement.elementsByTagName("refery");
    if (nodes.length() > 0) {
        QDomElement node = nodes.at(0).toElement();
        qstr += "<b>" + node.text() +
            " (" + node.attributes().namedItem("city").nodeValue() +
            ")</b><br>";
    }    
}

void MainWindow::selectMode3() {
    QString qstr = analyzeXml(&MainWindow::referies);
    widget.text->setText(qstr);
}

void MainWindow::selectMode4() {
    widget.text->setText("<b>Mode 4</b>");
}

void MainWindow::selectMode5() {
    widget.text->setText("<b>Mode 5</b>");
    QString qstr("");
    matchResults(qstr);
}

void MainWindow::selectMode6() {
    widget.text->setText("<b>Mode 6</b>");
}

QString MainWindow::analyzeXml(void (MainWindow::*func)(QString &qstr, QDomElement& docElement)) {
    QString qstr;
    QDir* qDir = new QDir("data/xml");
    qDir->setFilter(QDir::Files);
    QStringList list = qDir->entryList();
    QDomDocument doc("report");
    stringstream ss;
    for (int i = 0; i < list.size(); ++i) {
        QString fileName = list.at(i);
        QFile file(qDir->absolutePath() + "/" + fileName);
        if (!file.open(QIODevice::ReadOnly)) continue;
        if (!doc.setContent(&file)) {
            file.close();
            continue;
        }
        file.close();
        QDomElement docElement = doc.documentElement();
        (this->*func)(qstr, docElement);
    }
    return qstr;
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
