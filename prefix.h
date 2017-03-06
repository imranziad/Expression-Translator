#include <algorithm>
/**
    Contains Prefix class,
    that takes a string in constructor
    and performs the infix to prefix
    translation if the string is a valid
    infix expression otherwise shows
    syntax error.
    accepted characters:
    0-9, (), +, -, *, /

    No support for int >= 10
**/

class Prefix {
    string str, prefix;
    char lookahead; /*next char to read*/
    int lookahead_idx, level;
    bool error_flag;

public:
    Prefix(string s) {
        /*the prefix will be stored in this*/
        prefix = "";
        if(s.empty()) goto print;

        str = s;
        error_flag = false;
        /* level starts from the root 0,
            details in factor() function */
        level = 0;
        /*first character to read*/
        lookahead_idx = (int)(str.size())-1;
        lookahead = str[(int)(str.size())-1];

        expr();

        /* if the string isn't finished,
            something wrong happened and
            the string is invalid */
        if(lookahead_idx >= 0)
            error_flag = true;

        /* Syntax error has occurred, no valid prefix */
        if(error_flag)
            prefix = "Syntax Error!";
        else
            reverse(prefix.begin(),prefix.end());

        print:
        cout << "Prefix: " << prefix << endl;
    }

private:
    /* expr -> term rest */
    void expr() {
        term();
        rest();
    }
    /* term -> factor factor_rest */
    void term() {
        factor();
        factor_rest();
    }
    /*  rest -> + term rest
        rest -> - term rest */
    void rest() {
        if(lookahead == '+') {
            match('+');
            term();
            rest();
            prefix += "+";
        }
        else if(lookahead == '-') {
            match('-');
            term();
            rest();
            prefix += "-";
        }
        else {}
    }
    /* factor_rest -> * factor factor_rest
       factor_rest -> / factor factor_rest */
    void factor_rest() {
        if(lookahead == '*') {
            match('*');
            factor();
            factor_rest();
            prefix += "*";
        }
        else if(lookahead == '/') {
            match('/');
            factor();
            factor_rest();
            prefix += "/";
        }
        else {}
    }
    /* matches the character with current
        lookahead and points it to the next
        character to read */
    void match(char ch) {
        /*if ch is not matched return*/
        if(ch != lookahead) return ;
        lookahead_idx--;
        /* check if the string is finished */
        if(lookahead_idx >= 0)
            lookahead = str[ lookahead_idx ];
        else
            lookahead = '\0';
    }

    /* factor -> 0|1|2|....|9| (expr) */
    void factor() {
        if(lookahead >= '0' && lookahead <= '9') {
            // current character is a digit
            prefix += lookahead;
            // point next character
            match(lookahead);
        }
        else if(lookahead == ')') {
            /* current character is (,
            should be like (expr),
            create a new level */
            match(lookahead);
            int pre_level = level;
            level++;
            expr();
            /* next character is closing ')' and it
            returns to it's original level */
            if(lookahead == '(' && level-1 == pre_level)
                level--;
            else {
                error_flag = true;
                cout << "Prefix Error: index " << lookahead_idx << ": expected '(' character" << endl;
            }
            match(lookahead);
        }
        else {
            error_flag = true;
            cout << "Prefix Error: index " << lookahead_idx << ": invalid character" << endl;
        }
    }
};
