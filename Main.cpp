#include <iostream>
#include <cstdio>
using namespace std;

string str;
char look_ahead;
int look_ahead_idx;

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
    look_ahead_idx++;
    if(look_ahead_idx < str.size())
        look_ahead = str[ look_ahead_idx ];
    else
        look_ahead = '\0';
}

void term() {
    if(look_ahead >= '0' && look_ahead <= '9') {
        cout << look_ahead;
        match(look_ahead);
    }
    else {
        cout << "\nSyntax Error!" << endl;
    }
}

void rest() {
    if(look_ahead == '+') {
        match('+');
        term();
        cout << "+";
        rest();
    }
    else if(look_ahead == '-') {
        match('-');
        term();
        cout << "-";
        rest();
    }
    else {  }
}

void expr() {
    term();
    rest();
}

void infix_to_postfix() {
    look_ahead_idx = 0;
    look_ahead = str[0];
    cout << "Postfix: ";
    expr();
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
