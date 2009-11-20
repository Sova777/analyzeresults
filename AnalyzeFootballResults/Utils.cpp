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
#include <sstream>
#include <string>
#include "Utils.hpp"

#include "Results.hpp"

using namespace std;

int Utils::toInt(string& str) {
    stringstream ss;
    int n;
    ss.str(str);
    if (!(ss >> n)) {
        return -1;
    }
    return n;
}

Utils::EVENT Utils::event(struct RESULTS_STRUCT* y, string club_id) {
    string goals_1;
    string goals_2;
    if (y->team_id_1 == club_id) {
        goals_1 = y->goals_1;
        goals_2 = y->goals_2;
    } else if (y->team_id_2 == club_id) {
        goals_1 = y->goals_2;
        goals_2 = y->goals_1;
    } else {
        return OTHER_TEAMS;
    }

    if (goals_1 == "+") return WIN;
    if (goals_1 == "-") return LOSE;
    if (goals_1 == "") return EMPTY;
    int g1 = toInt(goals_1);
    if (g1 < 0) return UNKNOWN;
    int g2 = toInt(goals_2);
    if (g2 < 0) return UNKNOWN;
    if (g1 > g2) return WIN;
    if (g1 == g2) return DRAW;
    if (g1 < g2) return LOSE;
    return UNKNOWN;
}
