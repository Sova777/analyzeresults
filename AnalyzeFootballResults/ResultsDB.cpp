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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

#include "ResultsDB.hpp"

using namespace std;

#define FIELD_DELIM ';'
#define DATE_DELIM ','

int ResultsDB::countColumns(const string str) {
    int i = 0, count = 0;
    if (str == "") return 0;
    int len = str.length();

    while (i < len) {
        if (str[i] == FIELD_DELIM) count++;
        i++;
    }

    return count + 1;
}

string ResultsDB::nextColumn(const string str) {
    size_t p = str.find(FIELD_DELIM);
    if (p == string::npos) return "";
    string line = str.substr(p + 1);
    int len = line.length();
    int i;
    char c;
    for (i = 0; i < len; i++) {
        c = line[len - 1 - i];
        if ((c != ' ') && (c != '\r') && (c != '\n') && (c != '\t')) {
            break;
        }
    }
    return line.substr(0, len - i);
}

string ResultsDB::getColumn(const string str) {
    int i = 0;
    string column;

    if (str == "") {
        column = "";
        return column;
    }

    column = str.substr(0, str.find(FIELD_DELIM));
    return column;
}

std::string ResultsDB::db_path = "data";

ClubName* ResultsDB::club_name = NULL;

void ResultsDB::init(const std::string str) {
    db_path = str;
    club_name = ClubName::getInstance();
}
