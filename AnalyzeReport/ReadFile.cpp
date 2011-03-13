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

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "ReadFile.hpp"
#include "ReportTree.hpp"

using namespace std;

ReportTree* parseFile(string file_name) {
    ifstream f;
    string line;
    string item = "";
    size_t len = 0;
    int id = 0;

    f.open(file_name.c_str());
    if (!f) {
        cerr << file_name << " " << FileNotFound << endl;
        return NULL;
    }

    ReportTree* reportTree = new ReportTree();
    getline(f, line);
    while (!f.eof()) {
        if (id != 0) reportTree->addNewLine();
        len = line.size();
        for (int i = 0; i <= len; i++) {
            switch (line[i]) {
                case ' ':
                case '\r':
                case '\n':
                case '\t':
                    reportTree->add(item);
                    item = "";
                    break;
                case ',':
                case '.':
                case ':':
                case '(':
                case ')':
                case '-':
                    reportTree->add(item);
                    reportTree->add(line[i]);
                    item = "";                    
                    break;
                default:
                    item += line[i];
                    break;
            };
        }
        reportTree->add(item);
        item = "";
        getline(f, line);
        id++;
    }
    f.close();
    f.clear();
    return reportTree;
}
