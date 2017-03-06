#include <algorithm>
/**
    Contains Prefix class,
    that takes a string in constructor
    and performs the infix to prefix
    translation if the string is a valid
    infix expression otherwise shows
    syntax error.
**/

class Prefix {
    string str, pfx = "";
    char look_ahead;
    int look_ahead_idx, level;
    bool error_flag;

public:
    Prefix(string s) {
        // check empty string
        str = s;
        level = 0;
        look_ahead_idx = (int)(str.size())-1;
        look_ahead = str[(int)(str.size())-1];
        error_flag = false;
        expr();
        if(look_ahead_idx < str.size())
            error_flag = true;
        if(error_flag)
            pfx = "Syntax Error!";
        else
            reverse(pfx.begin(),pfx.end());
        cout << "Prefix: " << pfx << endl;
    }

private:
    void match(char ch) {
        if(ch != look_ahead) return ;
        look_ahead_idx--;
        if(look_ahead_idx >= 0)
            look_ahead = str[ look_ahead_idx ];
        else
            look_ahead = '\0';
    }

    void factor() {
        if(look_ahead >= '0' && look_ahead <= '9') {
            pfx += look_ahead;
            match(look_ahead);
        }
        else if(look_ahead == ')') {
            match(look_ahead);
            int pre_level = level;
            level++;
            expr();
            if(look_ahead == '(' && level-1 == pre_level) level--;
            else error_flag = true;
            match(look_ahead);
        }
        else {
            error_flag = true;
        }
    }

    void factor_rest() {
        if(look_ahead == '*') {
            match('*');
            factor();
            factor_rest();
            pfx += "*";
        }
        else if(look_ahead == '/') {
            match('/');
            factor();
            factor_rest();
            pfx += "/";
        }
        else {}
    }

    void term() {
        factor();
        factor_rest();
    }

    void rest() {
        if(look_ahead == '+') {
            match('+');
            term();
            rest();
            pfx += "+";
        }
        else if(look_ahead == '-') {
            match('-');
            term();
            rest();
            pfx += "-";
        }
        else {}
    }

    void expr() {
        term();
        rest();
    }
};

