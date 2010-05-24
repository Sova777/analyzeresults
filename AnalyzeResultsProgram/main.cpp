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
    for (iter = stat_table.table.begin(); iter != stat_table.table.end(); ++iter) {
        int w = (iter->second->w1 + iter->second->w2);
        int d = (iter->second->d1 + iter->second->d2);
        int l = (iter->second->l1 + iter->second->l2);
        int f = (iter->second->f1 + iter->second->f2);
        int a = (iter->second->a1 + iter->second->a2);
        cout <<
                club_names_now[iter->first] << " " <<
                (w + d + l) << " " <<
                w << " " <<
                d << " " <<
                l << " " <<
                f << ":" <<
                a << " " <<
                (2 * w + d) << "   " <<
                iter->second->unknown << "?" <<
                endl;
    }

    return (EXIT_SUCCESS);
}
