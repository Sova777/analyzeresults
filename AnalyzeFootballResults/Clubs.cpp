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

#include "Clubs.hpp"

using namespace std;

void Clubs::clear(struct Record* record) {
    record->id = "";
    record->club = "";
    record->city = "";
    return;
}

bool Clubs::open() {
    string line;
    string p_line;
    string s;
    string file_name = "club";
    string full_file_name = "data/" + file_name + ".txt";
    f.open(full_file_name.c_str());
    if (!f) {
        cerr << full_file_name << " " << FileNotFound << endl;
        return false;
    }

    // читаем 1-ю строку
    getline(f, line);

    // читаем заголовок (2-я строка)
    getline(f, line);

    p_line = line;
    do {
        s = getColumn(p_line);
        headers.push_back(s);
    } while ((p_line = nextColumn(p_line)) != "");

    return true;
}

Clubs::Record* Clubs::next() {
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
        } else if (headers[i] == "cl") {
            record.club = s;
        } else if (headers[i] == "ct") {
            record.city = s;
        }
        i++;
    } while ((p_line = nextColumn(p_line)) != "");
    return &record;
}

void Clubs::close() {
    f.close();
    headers.clear();
}

ostream & operator<<(ostream& output, const Clubs::Record* r) {
    output << r->id << ";" <<
            r->club << ";" <<
            r->city;
    return output;
}
