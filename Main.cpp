#include <iostream>
#include <cstdio>
using namespace std;

string str;
char look_ahead;
int look_ahead_idx, level;

void expr();

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

void match(char ch) {
    if(ch != look_ahead) return ;
    look_ahead_idx++;
    if(look_ahead_idx < str.size())
        look_ahead = str[ look_ahead_idx ];
    else
        look_ahead = '\0';
}

void factor() {
    if(look_ahead >= '0' && look_ahead <= '9') {
        cout << look_ahead;
        match(look_ahead);
    }
    else if(look_ahead == '(') {
        match(look_ahead);
        int pre_level = level;
        level++;
        expr();
        if(look_ahead == ')' && level-1 == pre_level) level--;
        else cout << "\nSyntax Error!" << endl;
        match(look_ahead);
    }
    else {
        cout << "\nSyntax Error!" << endl;
    }
}

void factor_rest() {
    while(true) {
        if(look_ahead == '*') {
            match('*');
            factor();
            cout << "*";
        }
        else if(look_ahead == '/') {
            match('/');
            factor();
            cout << "/";
        }
        else break;
    }
}

void term() {
    factor();
    factor_rest();
}

void rest() {
    while(true) {
        if(look_ahead == '+') {
            match('+');
            term();
            cout << "+";
        }
        else if(look_ahead == '-') {
            match('-');
            term();
            cout << "-";
        }
        else break;
    }
}

void expr() {
    term();
    rest();
}

void infix_to_postfix() {
    level = 0;
    look_ahead_idx = 0;
    look_ahead = str[0];
    cout << "Postfix: ";
    expr();
    if(look_ahead_idx < str.size())
        cout << "\nSyntax Error!" << endl;
    cout << endl;
}

int main() {
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    string s;

    getline(cin, s);

    str = remove_whitespace(s);

    cout << "input: " << s << endl;
    cout << "whitespace removed: " << str << endl;

    infix_to_postfix();

    return 0;
}

/*
TEST INPUT:

3*8- 5/6 +7*6/3

*/
