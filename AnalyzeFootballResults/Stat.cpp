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

#include <algorithm>
#include <vector>

#include "Stat.hpp"
#include "Utils.hpp"

using namespace std;

Stat::Stat() {
    Stat::TableMap::const_iterator iter;
    for (iter = table.begin(); iter != table.end(); ++iter) {
        delete iter->second;
    }
    table.clear();
}

void Stat::clear(Stat::Record* record) {
    record->team_id = "";
    record->w1 = 0;
    record->d1 = 0;
    record->l1 = 0;
    record->f1 = 0;
    record->a1 = 0;
    record->p1 = 0;
    record->w2 = 0;
    record->d2 = 0;
    record->l2 = 0;
    record->f2 = 0;
    record->a2 = 0;
    record->p2 = 0;
    record->unknown = 0;
}

void Stat::add(Results::Record* record) {
    TableMap::iterator it;
    Record* stat_record1 = NULL;
    Record* stat_record2 = NULL;

    it = table.find(record->team_id_1);
    if (it != table.end()) {
        stat_record1 = it->second;
    } else {
        stat_record1 = new Record();
        clear(stat_record1);
        table[record->team_id_1] = stat_record1;
    }

    it = table.find(record->team_id_2);
    if (it != table.end()) {
        stat_record2 = it->second;
    } else {
        stat_record2 = new Record();
        clear(stat_record2);
        stat_record2->w1 = 0;
        table[record->team_id_2] = stat_record2;
    }

    Utils::EVENT event = Utils::event(record, record->team_id_1);
    switch (event) {
        case Utils::WIN:
            stat_record1->w1++;
            stat_record2->l2++;
            break;
        case Utils::DRAW:
            stat_record1->d1++;
            stat_record2->d2++;
            break;
        case Utils::LOSE:
            stat_record1->l1++;
            stat_record2->w2++;
            break;
        default:
            stat_record1->unknown++;
            stat_record2->unknown++;
    }
    int g1 = record->get_goals_1();
    if (g1 < 0) {
        if (record->goals_1 == "+") {
            g1 = 3;
        } else {
            g1 = 0;
        }
    }
    int g2 = record->get_goals_2();
    if (g2 < 0) {
        if (record->goals_2 == "+") {
            g2 = 3;
        } else {
            g2 = 0;
        }
    }
    stat_record1->team_id = record->team_id_1;
    stat_record1->f1 += g1;
    stat_record1->a1 += g2;
    stat_record2->team_id = record->team_id_2;
    stat_record2->f2 += g2;
    stat_record2->a2 += g1;
}

vector<Stat::Record*>* Stat::get_sorted_vector_by_default() {
    Stat::TableMap::const_iterator iter;
    vector<Stat::Record*> v;
    for (iter = table.begin(); iter != table.end(); ++iter) {
        sorted_vector.push_back(iter->second);
    }
    sort(sorted_vector.begin(), sorted_vector.end(), compare_rows);
    return &sorted_vector;
}

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
