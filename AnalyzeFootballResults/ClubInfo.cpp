/*
Copyright (c) 2009, Valeriy Soldatov
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
#include "ParseLine.hpp"

using namespace std;

void ClubInfo::print(struct CLUB_INFO_STRUCT* club_info_struct) {
    cout << club_info_struct->id << ";" <<
            club_info_struct->pl << ";" <<
            club_info_struct->fl << ";" <<
            club_info_struct->n << ";" <<
            club_info_struct->w1 << ";" <<
            club_info_struct->d1 << ";" <<
            club_info_struct->l1 << ";" <<
            club_info_struct->fl << ";" <<
            club_info_struct->a1 << ";" <<
            club_info_struct->pl << ";" <<
            club_info_struct->w2 << ";" <<
            club_info_struct->d2 << ";" <<
            club_info_struct->l2 << ";" <<
            club_info_struct->f2 << ";" <<
            club_info_struct->a2 << ";" <<
            club_info_struct->p2 << ";" <<
            club_info_struct->w0 << ";" <<
            club_info_struct->d0 << ";" <<
            club_info_struct->l0 << ";" <<
            club_info_struct->f0 << ";" <<
            club_info_struct->a0 << ";" <<
            club_info_struct->p0 << ";" <<
            club_info_struct->pn << ";" <<
            endl;
    return;
}

void ClubInfo::clear(struct CLUB_INFO_STRUCT* club_info_struct) {
    club_info_struct->id = "";
    club_info_struct->pl = "";
    club_info_struct->fl = "";
    club_info_struct->n = "";
    club_info_struct->w1 = "";
    club_info_struct->d1 = "";
    club_info_struct->l1 = "";
    club_info_struct->fl = "";
    club_info_struct->a1 = "";
    club_info_struct->pl = "";
    club_info_struct->w2 = "";
    club_info_struct->d2 = "";
    club_info_struct->l2 = "";
    club_info_struct->f2 = "";
    club_info_struct->a2 = "";
    club_info_struct->p2 == "";
    club_info_struct->w0 = "";
    club_info_struct->d0 = "";
    club_info_struct->l0 = "";
    club_info_struct->f0 = "";
    club_info_struct->a0 = "";
    club_info_struct->p0 = "";
    club_info_struct->pn = "";
    return;
}

ParseLine::rows ClubInfo::load(string file_name) {
    rows rows;
    struct CLUB_INFO_STRUCT club_info;
    string line;
    string p_line;
    string full_file_name = "data/" + file_name + ".txt";
    string s;
    string key;
    string value;

    ifstream f;
    f.open(full_file_name.c_str());
    if (!f) {
        cerr << full_file_name << " " << FileNotFound << endl;
        throw new string(full_file_name + " " + FileNotFound);
    }

    // читаем заголовое (1-я строка)
    getline(f, line);
    vector<string> headers;

    p_line = line;
    do {
        s = getColumn(p_line);
        headers.push_back(s);
    } while ((p_line = nextColumn(p_line)) != "");

    while (!f.eof()) {
        getline(f, line);
        if (line == "") continue;
        int i = 0;
        p_line = line;
        clear(&club_info);
        do {
            s = getColumn(p_line);
            if (headers[i] == "id") {
                club_info.id = s;
            } else if (headers[i] == "pl") {
                club_info.pl = s;
            } else if (headers[i] == "fl") {
                club_info.fl = s;
            } else if (headers[i] == "n") {
                club_info.n = s;
            } else if (headers[i] == "w1") {
                club_info.w1 = s;
            } else if (headers[i] == "d1") {
                club_info.d1 = s;
            } else if (headers[i] == "l1") {
                club_info.l1 = s;
            } else if (headers[i] == "f1") {
                club_info.f1 = s;
            } else if (headers[i] == "a1") {
                club_info.a1 = s;
            } else if (headers[i] == "p1") {
                club_info.p1 = s;
            } else if (headers[i] == "w2") {
                club_info.w2 = s;
            } else if (headers[i] == "d2") {
                club_info.d2 = s;
            } else if (headers[i] == "l2") {
                club_info.l2 = s;
            } else if (headers[i] == "f2") {
                club_info.f2 = s;
            } else if (headers[i] == "a2") {
                club_info.a2 = s;
            } else if (headers[i] == "p2") {
                club_info.p2 = s;
            } else if (headers[i] == "w0") {
                club_info.w0 = s;
            } else if (headers[i] == "d0") {
                club_info.d0 = s;
            } else if (headers[i] == "l0") {
                club_info.l0 = s;
            } else if (headers[i] == "f0") {
                club_info.f0 = s;
            } else if (headers[i] == "a0") {
                club_info.a0 = s;
            } else if (headers[i] == "p0") {
                club_info.p0 = s;
            } else if (headers[i] == "pn") {
                club_info.pn = s;
            }
            i++;
        } while ((p_line = nextColumn(p_line)) != "");
        if (record(&club_info, &key, &value)) {
            rows[key] = value;
        }
    }
    f.close();
    return rows;
}
