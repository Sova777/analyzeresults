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
#include <vector>
#include <string>

#include "parse_file.h"
#include "years.h"

using namespace std;

void print_years_struct(struct YEARS_STRUCT* years_struct) {
    cout << years_struct->id << ";" <<
            years_struct->year << ";" <<
            years_struct->file_results << ";" <<
            years_struct->level << ";" <<
            years_struct->file_goals << ";" <<
            years_struct->title << endl;
    return;
}

void clear_years_struct(struct YEARS_STRUCT* years_struct) {
    years_struct->file_goals = "";
    years_struct->file_results = "";
    years_struct->id = "";
    years_struct->level = "";
    years_struct->title = "";
    years_struct->year = "";
    return;
}

bool LoadYear(void (*function)(struct YEARS_STRUCT* years_struct)) {
    struct YEARS_STRUCT y;
    string line;
    string p_line;
    string s;

    ifstream f;
    f.open("data/year.txt");
    if(!f) {
      cerr << FileNotFound << endl;
        return EXIT_FAILURE;
    }

    // читаем заголовок (1-я строка)
    getline(f, line);
    vector<string> headers;

    p_line = line;
    do {
        s = get_column(p_line);
        headers.push_back(s);
    } while ((p_line = next_column(p_line)) != "");

    while (!f.eof()) {
        getline(f, line);
        if (line == "") continue;
        int i = 0;
        p_line = line;
        clear_years_struct(&y);
        do {
            s = get_column(p_line);
            if (headers[i] == "y") {
                y.year = s;
            } else if (headers[i] == "t") {
                y.title = s;
            } else if (headers[i] == "id") {
                y.id = s;
            } else if (headers[i] == "n") {
                y.file_results = s;
            } else if (headers[i] == "l") {
                y.level = s;
            } else if (headers[i] == "ag") {
                y.file_goals = s;
            }
            i++;
        } while ((p_line = next_column(p_line)) != "");
        (*function)(&y);
    }
    f.close();
    return EXIT_SUCCESS;
}
