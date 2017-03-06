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
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    string s, str;

    /* take input until "exit" command */
    while(true) {
        // cout << "Enter Infix expression: ";
        getline(cin, s);
        if(s == "exit") break;

        str = remove_whitespace(s);

        cout << "input: " << s << endl;
        cout << "infix: " << str << endl;

        // generate and print the postfix
        Postfix pf(str);
        // generate and print the prefix
        Prefix prf(str);

        cout << endl;
    }

    return 0;
}
