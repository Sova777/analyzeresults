/*
Copyright (c) 2009 - 2014, Valeriy Soldatov
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

#include "DumpToHtml.h"
#include <QFile>
#include <QTextStream>

void DumpToHtml::save(QString directory) {
    QString qstr = directory + "/referies.html";
    QFile file(qstr);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);

//    if (reports.size() > 0) {
//        Report report = reports[0];
//        XmlFilter xmlFilter(this, &report, report.getReportId(), &filter);
//        (*func)(xmlFilter, &hash);
//    }

    out << "| ";
//    for (int k = 0; k < columns; k++) {
//        if (!widget.table->isColumnHidden(k)) {
//            QString label = widget.table->horizontalHeaderItem(k)->text();
//            int len = widget.table->columnWidth(k);
//            out << label.replace("\n", "").rightJustified(len / 7, ' ', true) << " | ";
//        }
//    }
    out << "\n";
//    for (int i = 0; i < rows; i++) {
//        out << "| ";
//        for (int j = 0; j < columns; j++) {
//            if (!widget.table->isColumnHidden(j)) {
//                int len = widget.table->columnWidth(j);
//                out << widget.table->item(i, j)->text().rightJustified(len / 7, ' ', false) << " | ";
//            }
//        }
//        out << "\n";
//    }
    file.close();
}
