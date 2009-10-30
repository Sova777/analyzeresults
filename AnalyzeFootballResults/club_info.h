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

#ifndef _CLUB_INFO_H
#define	_CLUB_INFO_H

#include <string>
#include "parse_file.h"

struct CLUB_INFO_STRUCT {
    std::string id;
    std::string pl;
    std::string fl;
    std::string n;
    std::string w1;
    std::string d1;
    std::string l1;
    std::string f1;
    std::string a1;
    std::string p1;
    std::string w2;
    std::string d2;
    std::string l2;
    std::string f2;
    std::string a2;
    std::string p2;
    std::string w0;
    std::string d0;
    std::string l0;
    std::string f0;
    std::string a0;
    std::string p0;
    std::string pn;
};

class ClubInfoAbstract {
public:
protected:
    void print(struct CLUB_INFO_STRUCT* club_info_struct);
    void clear(struct CLUB_INFO_STRUCT* club_info_struct);
    virtual bool record(struct CLUB_INFO_STRUCT* y, std::string* key, std::string* value) = 0;
    rows load(std::string file_name);
};

#endif	/* _CLUB_INFO_H */
