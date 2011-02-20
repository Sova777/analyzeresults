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

#ifndef _RESULTSDB_H
#define	_RESULTSDB_H

#include <string>
#include "ClubName.hpp"

#define FileNotFound "файл не найден"

class ResultsDB {
public:

    /**
     * Установить путь к файлам с данными
     * @param str
     */
    static void init(const std::string str);

protected:

    /**
     * функция принимает строку str
     * возвращает количество встретившихся разделителей колонок.
     * @param const std::string str
     * @return std::string
     */
    static int countColumns(const std::string str);

    /**
     * Функция принимает строку str
     * возвращает урезанную переменную str.
     * @param const std::string str
     * @return std::string
     */
    static std::string nextColumn(const std::string str);

    /**
     * функция принимает строку str, на выходе переменная column
     * содержит урезанную переменную str.
     * @param const string str
     * @return std::string
     */
    static std::string getColumn(const std::string str);

    static std::string db_path;

    static ClubName* club_name;

};

#endif	/* _RESULTSDB_H */
