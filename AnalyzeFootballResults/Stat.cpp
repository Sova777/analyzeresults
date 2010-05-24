
#include "Stat.hpp"
#include "Utils.hpp"

Stat::Stat() {
    Stat::TableMap::const_iterator iter;
    for (iter = table.begin(); iter != table.end(); ++iter) {
        delete iter->second;
    }
    table.clear();
}

void Stat::clear(Stat::Record* record) {
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
    stat_record1->f1 += g1;
    stat_record1->a1 += g2;
    stat_record2->f2 += g2;
    stat_record2->a2 += g1;
}
