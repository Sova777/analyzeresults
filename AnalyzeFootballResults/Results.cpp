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

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ResultsDB.hpp"
#include "Results.hpp"
#include "Utils.hpp"

using namespace std;

void Results::clear(struct Record* record) {
    record->id = "";
    record->date = "";
    record->team_id_1 = "";
    record->team_id_2 = "";
    record->goals_1 = "";
    record->goals_2 = "";
    record->round = "";
    record->clear_goals_int();
    record->clear_date_int();
    return;
}

bool Results::open(string file_name) {
    string line;
    string p_line;
    string full_file_name;
    string s;

    full_file_name = db_path + "/" + file_name + ".txt";
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

Results::Record* Results::next() {
    string line;
    string p_line;
    string s;

    if (f.eof()) return NULL;
    getline(f, line);
    if (line == "") return next();

    int i = 0;
    p_line = line;
    int size = headers.size();
    clear(&record);
    do {
        s = getColumn(p_line);
        if (i >= size) {
            //cerr << i << ": " << line << endl;
        } else if (headers[i] == "id") {
            record.id = s;
        } else if (headers[i] == "d") {
            replace(s.begin(), s.end(), ',', '.');
            record.date = s;
        } else if (headers[i] == "t1") {
            record.team_id_1 = s;
        } else if (headers[i] == "t2") {
            record.team_id_2 = s;
        } else if (headers[i] == "g1") {
            record.goals_1 = s;
        } else if (headers[i] == "g2") {
            record.goals_2 = s;
        } else if (headers[i] == "r") {
            record.round = s;
        }
        i++;
    } while ((p_line = nextColumn(p_line)) != "");
    return &record;
}

void Results::close() {
    f.close();
    f.clear();
    headers.clear();
}

bool Results::Record::played(std::string team) {
    return ((team_id_1 == team) || (team_id_2 == team));
}

bool Results::Record::played(std::string team1, std::string team2) {
    return ((team_id_1 == team1) && (team_id_2 == team2)) ||
            ((team_id_1 == team2) && (team_id_2 == team1));
}

void Results::Record::clear_goals_int() {
    goals_1_int = -2;
    goals_2_int = -2;
}

void Results::Record::clear_date_int() {
    date_int = -2;
}

int Results::Record::get_goals_1() {
    if (goals_1_int != -2) return goals_1_int;
    goals_1_int = Utils::toInt(goals_1);
    return goals_1_int;
}

int Results::Record::get_goals_2() {
    if (goals_2_int != -2) return goals_2_int;
    goals_2_int = Utils::toInt(goals_2);
    return goals_2_int;
}

int Results::Record::get_goals_1(std::string team) {
    if (team == team_id_1) return get_goals_1();
    if (team == team_id_2) return get_goals_2();
    return -2;
}

int Results::Record::get_goals_2(std::string team) {
    if (team == team_id_1) return get_goals_2();
    if (team == team_id_2) return get_goals_1();
    return -2;
}

string Results::Record::get_team_name_1(std::string season) {
    return club_name->getName(team_id_1, season);
}

string Results::Record::get_team_name_2(std::string season) {
    return club_name->getName(team_id_2, season);
}

string Results::Record::get_team_name_1(Years::Record* year) {
    return club_name->getName(team_id_1, year->file_results);
}

string Results::Record::get_team_name_2(Years::Record* year) {
    return club_name->getName(team_id_2, year->file_results);
}

bool Results::Record::is_correct_game() {
    return ((get_goals_1() >= 0) || (get_goals_2() >= 0));
}

int Results::Record::get_date() {
    if (date_int > 0) return date_int;
    size_t pos1 = date.find(".");
    if (pos1 == string::npos) return -1;
    size_t pos2 = date.find(".", pos1 + 1);
    if (pos2 == string::npos) return -2;
    string s = date.substr(pos2 + 1, 4);
    date_int = Utils::toInt(s) * 10000;
    s = date.substr(pos1 + 1, 2);
    date_int += Utils::toInt(s) * 100;
    s = date.substr(0, 2);
    date_int += Utils::toInt(s);
    return date_int;
}

void Results::Record::print_result(Years::Record* year) {
    cout << ((date == "") ? year->year : date) << " "
            << get_team_name_1(year) << " - " << get_team_name_2(year)
            << " " << get_goals_1() << ":" << get_goals_2();
}

void Results::Record::println_result(Years::Record* year) {
    print_result(year);
    cout << endl;
}

ostream & operator<<(ostream& output, const Results::Record* r) {
    output << r->id << ";" <<
            r->date << ";" <<
            r->team_id_1 << ";" <<
            r->team_id_2 << ";" <<
            r->goals_1 << ";" <<
            r->goals_2 << ";" <<
            r->round;
    return output;
}
