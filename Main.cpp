#include <iostream>
#include <cstdio>
using namespace std;

/**
    custom headers are included
    after namespace to avoid repetition
    in those files.
*/
#include "postfix.h"
#include "prefix.h"

string str;
char look_ahead;
int look_ahead_idx, level;

string remove_whitespace(string s) {
    /*
        Takes a string and
        returns it after removing
        all space characters.
    */
    string ret = "";
    int len = s.size();

    for(int i = 0; i < len; i++) {
        if(s[i] != ' ')
            ret += s[i];
    }
    return ret;
}

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    string s;

    getline(cin, s);

    str = remove_whitespace(s);

    cout << "input: " << s << endl;
    cout << "whitespace removed: " << str << endl;

    Postfix pf(str);
    Prefix prf(str);

    return 0;
}

/*
TEST INPUT:

3*8- 5/6 +7*6/3

*/
