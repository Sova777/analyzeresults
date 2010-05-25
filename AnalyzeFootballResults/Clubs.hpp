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

#ifndef _CLUBS_H
#define	_CLUBS_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "ResultsDB.hpp"

class Clubs : protected ResultsDB {
public:

    struct Record {
        std::string id;
        std::string club;
        std::string city;
    };

    /**
     * Получить следующую запись
     * @return Clubs::Record*
     */
    Clubs::Record* next();

    /**
     * Открыть файл с данными
     * @return bool
     */
    bool open();

    /**
     * Закрыть файл с данными
     */
    void close();

    /**
     * Получить последнее имя клубаа
     * @param team_id
     * @return std::string
     */
    std::string get_latest_club_name(std::string team_id);

private:

    /**
     * Стереть данные в структуре
     * @param struct Record* clubs_struct
     */
    static void clear(struct Record* record);
    std::ifstream f;
    std::vector<std::string> headers;
    struct Record record;
    typedef std::map<std::string, std::string> ClubNamesNow;
    ClubNamesNow club_names_now;

};

std::ostream & operator<<(std::ostream& output, const Clubs::Record* r);

#endif	/* _CLUBS_H */
