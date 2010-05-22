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

#ifndef _RESULTS_H
#define	_RESULTS_H

#include <string>
#include <fstream>
#include <string>
#include <vector>

#include "ResultsDB.hpp"
#include "Years.hpp"

class Results : protected ResultsDB {
public:

    struct Record {
    public:
        std::string id;
        std::string date;
        std::string team_id_1;
        std::string team_id_2;
        std::string goals_1;
        std::string goals_2;
        std::string round;

    private:
        int goals_1_int;
        int goals_2_int;

    public:

        /**
         * Играла ли команда в этом матче
         * @param team
         * @return bool
         */
        bool played(std::string team);

        /**
         * Встречвлись ли команды в этом матче
         * @param std::string team1
         * @param std::string team2
         */
        bool played(std::string team1, std::string team2);

        /**
         * Очистить поля goals_1_int и goals_int_2
         * Присвоить -2
         */
        void clear_goals_int();

        /**
         * Получить имя команды
         * @param std::string season
         * @return std::string
         */
        std::string get_team_name_1(std::string season);

        /**
         * Получить имя команды
         * @param std::string season
         * @return std::string
         */
        std::string get_team_name_2(std::string season);

        /**
         * Получить имя команды
         * @param Years::Record* year
         * @return std::string
         */
        std::string get_team_name_1(Years::Record* year);

        /**
         * Получить имя команды
         * @param Years::Record* year
         * @return std::string
         */
        std::string get_team_name_2(Years::Record* year);

        /**
         * Получить количество голов (целое число)
         * @return int
         */
        int get_goals_1();

        /**
         * Получить количество голов (целое число)
         * @return int
         */
        int get_goals_2();

        /**
         * Забито мячей командой
         * @param team1
         * @return int
         */
        int get_goals_1(std::string team);

        /**
         * Пропущено мячей командой
         * @param team1
         * @return int
         */
        int get_goals_2(std::string team);

        /**
         * Обычная игра (счет не содержит "+", "-" или "")
         * @return bool
         */
        bool is_correct_game();

        /**
         * Распечатать результат матча
         * @param Years::Record* year
         */
        void print_result(Years::Record* year);


        /**
         * Распечатать результат матча
         * @param Years::Record* year
         */
        void println_result(Years::Record* year);

    };
    /**
     * Получить следующую запись
     * @return Results::Record*
     */
    Results::Record* next();

    /**
     * Открыть файл с данными
     * @param file_name
     * @return bool
     */
    bool open(std::string file_name);

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

std::ostream & operator<<(std::ostream& output, const Results::Record* r);

#endif	/* _RESULTS_H */
