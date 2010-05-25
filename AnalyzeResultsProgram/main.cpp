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

#include <Clubs.hpp>
#include <ClubInfo.hpp>
#include <ClubName.hpp>
#include <Results.hpp>
#include <Stat.hpp>
#include <Utils.hpp>
#include <Years.hpp>

using namespace std;

//void sample1() {
//    Years years;
//    Years::Record* record_year;
//    Results results;
//    Results::Record* record_result;
//
//    ResultsDB::init("/export/home/sova/football/data/");
//
//    years.open();
//    while ((record_year = years.next()) != NULL) {
//        results.open(record_year->file_results);
//        while ((record_result = results.next()) != NULL) {
//            if (record_result->played("22")) {
//                if (record_result->get_goals_1("22") > 4) {
//                    record_result->println_result(record_year);
//                }
//            }
//        }
//        results.close();
//    }
//    years.close();
//}

 bool compare_rows(const Stat::Record* s1, const Stat::Record* s2) {
    int w1 = (s1->w1 + s1->w2);
    int w2 = (s2->w1 + s2->w2);
    int diff1 = (s1->f1 + s1->f2) - (s1->a1 + s1->a2);
    int diff2 = (s2->f1 + s2->f2) - (s2->a1 + s2->a2);
    int points1 = 2 * w1 + (s1->d1 + s1->d2);
    int points2 = 2 * w2 + (s2->d1 + s2->d2);
    if (points1 > points2) return true;
    if (points1 < points2) return false;
    if (w1 > w2) return true;
    if (w1 < w2) return false;
    return (diff1 > diff2);
}

int main(int argc, char** argv) {

    Years years;
    Years::Record* record_year;
    Results results;
    Results::Record* record_result;
    Stat stat_table;

    string path;
    if (argc > 1) {
        path = argv[1];
    } else {
        path = "./data";
    }

    ResultsDB::init(path);

    if (!years.open()) return EXIT_FAILURE;
    while ((record_year = years.next()) != NULL) {
        results.open(record_year->file_results);
        while ((record_result = results.next()) != NULL) {
            stat_table.add(record_result);
        }
        results.close();
    }
    years.close();

    typedef std::map<string, string> ClubNamesNow;
    ClubNamesNow club_names_now;
    Clubs clubs;
    Clubs::Record* record_clubs;
    clubs.open();
    while ((record_clubs = clubs.next()) != NULL) {
        club_names_now[record_clubs->id] =
                record_clubs->club + " (" +record_clubs->city + ")";
    }
    clubs.close();

    Stat::TableMap::const_iterator iter;
    vector<Stat::Record*> v;
    for (iter = stat_table.table.begin(); iter != stat_table.table.end(); ++iter) {
        v.push_back(iter->second);
    }

    sort(v.begin(), v.end(), compare_rows);
    vector<Stat::Record*>::const_iterator iter2;
    int place = 0;
    for (iter2 = v.begin(); iter2 != v.end(); ++iter2) {
        place++;
        int w = ((*iter2)->w1 + (*iter2)->w2);
        int d = ((*iter2)->d1 + (*iter2)->d2);
        int l = ((*iter2)->l1 + (*iter2)->l2);
        int f = ((*iter2)->f1 + (*iter2)->f2);
        int a = ((*iter2)->a1 + (*iter2)->a2);
        cout <<
                place << " " <<
                club_names_now[(*iter2)->team_id] << " " <<
                (w + d + l) << " " <<
                w << " " <<
                d << " " <<
                l << " " <<
                f << ":" <<
                a << " " <<
                (2 * w + d) << "   " <<
                (*iter2)->unknown << "?" <<
                endl;
    }

    return (EXIT_SUCCESS);
}
