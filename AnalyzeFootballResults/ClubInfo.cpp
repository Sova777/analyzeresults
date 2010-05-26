/*
Copyright (c) 2009 - 2010, Valeriy Soldatov
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

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ClubInfo.hpp"
#include "ResultsDB.hpp"

using namespace std;

void ClubInfo::clear(struct Record* record) {
    record->id = "";
    record->pl = "";
    record->fl = "";
    record->n = "";
    record->w1 = "";
    record->d1 = "";
    record->l1 = "";
    record->fl = "";
    record->a1 = "";
    record->pl = "";
    record->w2 = "";
    record->d2 = "";
    record->l2 = "";
    record->f2 = "";
    record->a2 = "";
    record->p2 = "";
    record->w0 = "";
    record->d0 = "";
    record->l0 = "";
    record->f0 = "";
    record->a0 = "";
    record->p0 = "";
    record->pn = "";
    return;
}

bool ClubInfo::open(string file_name) {
    string line;
    string p_line;
    string full_file_name = db_path + "/" + file_name + ".txt";
    string s;

    f.open(full_file_name.c_str());
    if (!f) {
        cerr << full_file_name << " " << FileNotFound << endl;
        return false;
    }

    // читаем заголовое (1-я строка)
    getline(f, line);

    p_line = line;
    do {
        s = getColumn(p_line);
        headers.push_back(s);
    } while ((p_line = nextColumn(p_line)) != "");
    return true;
}

ClubInfo::Record* ClubInfo::next() {
    string line;
    string p_line;
    string s;

    if (f.eof()) return NULL;
    getline(f, line);
    if (line == "") return next();

    int i = 0;
    p_line = line;
    clear(&record);
    do {
        s = getColumn(p_line);
        if (headers[i] == "id") {
            record.id = s;
        } else if (headers[i] == "pl") {
            record.pl = s;
        } else if (headers[i] == "fl") {
            record.fl = s;
        } else if (headers[i] == "n") {
            record.n = s;
        } else if (headers[i] == "w1") {
            record.w1 = s;
        } else if (headers[i] == "d1") {
            record.d1 = s;
        } else if (headers[i] == "l1") {
            record.l1 = s;
        } else if (headers[i] == "f1") {
            record.f1 = s;
        } else if (headers[i] == "a1") {
            record.a1 = s;
        } else if (headers[i] == "p1") {
            record.p1 = s;
        } else if (headers[i] == "w2") {
            record.w2 = s;
        } else if (headers[i] == "d2") {
            record.d2 = s;
        } else if (headers[i] == "l2") {
            record.l2 = s;
        } else if (headers[i] == "f2") {
            record.f2 = s;
        } else if (headers[i] == "a2") {
            record.a2 = s;
        } else if (headers[i] == "p2") {
            record.p2 = s;
        } else if (headers[i] == "w0") {
            record.w0 = s;
        } else if (headers[i] == "d0") {
            record.d0 = s;
        } else if (headers[i] == "l0") {
            record.l0 = s;
        } else if (headers[i] == "f0") {
            record.f0 = s;
        } else if (headers[i] == "a0") {
            record.a0 = s;
        } else if (headers[i] == "p0") {
            record.p0 = s;
        } else if (headers[i] == "pn") {
            record.pn = s;
        }
        i++;
    } while ((p_line = nextColumn(p_line)) != "");
    return &record;
}

void ClubInfo::close() {
    f.close();
    headers.clear();
}

ostream & operator<<(ostream& output, const ClubInfo::Record* r) {
    output << r->id << ";" <<
            r->pl << ";" <<
            r->fl << ";" <<
            r->n << ";" <<
            r->w1 << ";" <<
            r->d1 << ";" <<
            r->l1 << ";" <<
            r->fl << ";" <<
            r->a1 << ";" <<
            r->pl << ";" <<
            r->w2 << ";" <<
            r->d2 << ";" <<
            r->l2 << ";" <<
            r->f2 << ";" <<
            r->a2 << ";" <<
            r->p2 << ";" <<
            r->w0 << ";" <<
            r->d0 << ";" <<
            r->l0 << ";" <<
            r->f0 << ";" <<
            r->a0 << ";" <<
            r->p0 << ";" <<
            r->pn;
    return output;
}
