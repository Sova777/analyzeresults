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

#include <cstdlib>
#include <iostream>

#include "Clubs.hpp"
#include "Years.hpp"
#include "Results.hpp"
#include "ClubInfo.hpp"
#include "ClubName.hpp"

using namespace std;

int main(int argc, char** argv) {

    Years years;
    Years::Record* record2;
    ClubName* club_name = ClubName::getInstance();
    years.open();
    while ((record2 = years.next()) != NULL) {
        Results results;
        Results::Record* record3;
        results.open(record2->file_results);
        while ((record3 = results.next()) != NULL) {
            cout << record3->id << ";" <<
                    record3->date << ";" <<
                    club_name->getName(record3->team_id_1, record2->file_results) << ";" <<
                    club_name->getName(record3->team_id_2, record2->file_results) << ";" <<
                    record3->goals_1 << ";" <<
                    record3->goals_2 << ";" <<
                    record3->round << endl;
        }
        results.close();
    }
    years.close();

    return (EXIT_SUCCESS);
}
