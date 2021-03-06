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

#ifndef _YEARS_H
#define	_YEARS_H

#include <string>
#include <fstream>

#include "ResultsDB.hpp"

class Years : protected ResultsDB {
public:

    struct Record {
        std::string id;
        std::string year;
        std::string file_results;
        std::string level;
        std::string file_goals;
        std::string title;
    };
    /**
     * Получить следующую запись
     * @return Years::Record*
     */
    Years::Record* next();

    /**
     * Открыть файл с данными
     * @return bool
     */
    bool open();

    /**
     * Закрыть файл с данными
     */
    void close();
private:
    /**
     * Стереть данные в структуре
     * @param struct Record* record
     */
    static void clear(struct Record* record);
    std::ifstream f;
    std::vector<std::string> headers;
    struct Record record;
};

std::ostream & operator<<(std::ostream& output, const Years::Record* r);

#endif	/* _YEARS_H */
