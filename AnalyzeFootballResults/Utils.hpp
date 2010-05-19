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

#ifndef _UTILS_H
#define	_UTILS_H

#include <string>

#include "Results.hpp"

class Utils {
public:
    /**
     * WIN - победа, DRAW - ничья, LOSE -поражение
     * OTHER_TEAM - команда не участвовала в этом матче
     * EMPTY - счет не указан (поле пусто)
     * UNKNOWN - исход матча непонятен для программы
     */
    enum EVENT { WIN, DRAW, LOSE, OTHER_TEAMS, EMPTY, UNKNOWN };

    /**
     * Преобразовать строку в число
     * если строка не содержит число, то вернуть -1
     * @param str
     * @return int
     */
    static int toInt(std::string& str);

    /**
     * Определить, команда выйграла, проиграла или сыграла в ничью
     * @param y
     * @param club_id
     * @return enum EVENT
     */
    static EVENT event(struct Results::Record* y, std::string club_id);

};

#endif	/* _UTILS_H */
