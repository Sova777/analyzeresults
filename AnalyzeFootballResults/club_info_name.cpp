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

#include <string>
#include <iostream>
#include "club_info_name.h"

using namespace std;

ClubInfoName* ClubInfoName::instance = NULL;

ClubInfoName* ClubInfoName::getInstance() {
    if (instance != NULL) return instance;
    instance = new ClubInfoName();
    return instance;
}

string ClubInfoName::getName(string id, string season_code) {
    string uniqKey = id + "/" + season_code;
    ClubNames::iterator it;
    it = club_names.find(uniqKey);
    if (it != club_names.end()) {
        return it->second;
    }
    this->season = season_code;
    isFound = false;
    rows r = load(id);
    club_names[uniqKey] = r[""];
    isFound = false;
    return r[""];
}

bool ClubInfoName::record(struct CLUB_INFO_STRUCT* y, std::string* key, std::string* value) {
    if (isFound == true) return false;
    if (y->fl == season) {
        *key = "";
        *value = y->n;
        isFound = true;
        return true;
    }
    return false;
}
