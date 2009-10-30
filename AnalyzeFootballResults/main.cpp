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
#include <map>
#include <string>

#include "clubs.h"
#include "parse_file.h"
#include "results.h"
#include "years.h"
#include "club_info_name.h"
#include "utils.h"

using namespace std;

typedef map<string, string> ClubsMap;
ClubsMap clubs;
typedef map<string, CLUB_INFO_STRUCT> ClubsInfo;
ClubsInfo clubs_info;


int w = 0;
int d = 0;
int l = 0;
string clubID = "1";

void analize_results(struct RESULTS_STRUCT* y, string par) {
//    if ((y->team_id_1 == clubID) || (y->team_id_2 == clubID)) {
    ClubInfoName* clubInfo = ClubInfoName::getInstance();
//        EVENT e = event(y, clubID);
//        switch (e) {
//            case WIN:
//                w++;
//                break;
//            case DRAW:
//                d++;
//                break;
//            case LOSE:
//                l++;
//                break;
//            default:
//                cerr << "Wrong line: " << y->id << endl;
//                break;
//        }

        cout << y->id << ";" << y->date << ";" <<
            clubInfo->getName(y->team_id_1, par) << ";" <<
            clubInfo->getName(y->team_id_2, par) << ";" <<
            y->goals_1 << ";" << y->goals_2 << ";" <<
            y->round << " тур" << endl;

    //print_results_struct(y);
//    }
    return;
}
//
void analize_years(struct YEARS_STRUCT* y) {
    /*if (y->year == "2009")*/
    LoadResults(y->file_results, analize_results, y->file_results);
    return;
}

void analize_clubs(struct CLUBS_STRUCT* y) {
    clubs[y->id] = y->club + "(" + y->city + ")";
    cout << clubs[y->id] << endl;
    return;
}

int main(int argc, char** argv) {
    cout << endl << "Список клубов" << endl << "------------------" << endl;
    LoadClubs(analize_clubs);
    w = 0; d = 0; l = 0;
    cout << endl << "Список матчей" << endl << "------------------" << endl;
    LoadYear(analize_years);

    return (EXIT_SUCCESS);
}
