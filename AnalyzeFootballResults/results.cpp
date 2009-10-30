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

THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "parse_file.h"
#include "results.h"

using namespace std;

void print_results_struct(struct RESULTS_STRUCT* results_struct) {
    cout << results_struct->id << ";" <<
            results_struct->date << ";" <<
            results_struct->team_id_1 << ";" <<
            results_struct->team_id_2 << ";" <<
            results_struct->goals_1 << ";" <<
            results_struct->goals_2 << ";" <<
            results_struct->round << endl;
    return;
}

void clear_results_struct(struct RESULTS_STRUCT* results_struct) {
    results_struct->id = "";
    results_struct->date = "";
    results_struct->team_id_1 = "";
    results_struct->team_id_2 = "";
    results_struct->goals_1 = "";
    results_struct->goals_2 = "";
    results_struct->round = "";
    return;
}

int LoadResults(string file_name, void (*function)(struct RESULTS_STRUCT* results_struct, string parameter), string par) {
    struct RESULTS_STRUCT y;
    string line;
    string p_line = line;
    string full_file_name;
    string s;

    full_file_name = "data/" + file_name + ".txt";
    ifstream f;
    f.open(full_file_name.c_str());
    if (!f) {
        cerr << full_file_name << " " << FileNotFound << endl;
        return EXIT_FAILURE;
    }

    // ������ 1-� ������
    getline(f, line);

    // ������ ��������� (2-� ������)
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
        clear_results_struct(&y);
        do {
            s = get_column(p_line);
            if (headers[i] == "id") {
                y.id = s;
            } else if (headers[i] == "d") {
                y.date = s;
            } else if (headers[i] == "t1") {
                y.team_id_1 = s;
            } else if (headers[i] == "t2") {
                y.team_id_2 = s;
            } else if (headers[i] == "g1") {
                y.goals_1 = s;
            } else if (headers[i] == "g2") {
                y.goals_2 = s;
            } else if (headers[i] == "r") {
                y.round = s;
            }
            i++;
        } while ((p_line = next_column(p_line)) != "");
        (*function)(&y, par);
    }
    f.close();
    return EXIT_SUCCESS;
}
