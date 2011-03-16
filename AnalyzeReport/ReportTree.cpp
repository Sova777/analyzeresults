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

#include <string>
#include <iostream>
#include "ReportTree.hpp"

using namespace std;

ReportTree::ReportTree() {
    currentLine = 0;
    tree.push_back(TreeLine());
}

void ReportTree::addNewLine() {
    currentLine++;
    tree.push_back(TreeLine());
}

void ReportTree::add(string& item) {
    if ((item != "") && (item.c_str()[0] != '\x00')) {
        tree[currentLine].push_back(item);
    }
}

void ReportTree::add(char& item) {
    string str = "";
    str += item;
    tree[currentLine].push_back(str);
}

void ReportTree::print() {
    unsigned int len = tree.size();
    unsigned int len2;
    for (int i = 0; i < len; i++) {
        cout << "=====================" << endl;
        len2 = tree[i].size();
        for (int j = 0; j < len2; j++) {
            if (tree[i][j] != ",") {
                cout << tree[i][j] << endl;
            }
        }
    }
}
