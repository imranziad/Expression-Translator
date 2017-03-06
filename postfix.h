
/**
    Contains Postfix class,
    that takes a string in constructor
    and performs the infix to postfix
    translation if the string is a valid
    infix expression otherwise shows
    syntax error.
    accepted characters:
    0-9, (), +, -, *, /
**/

class Postfix {
    string str, postfix;
    char look_ahead; /*next char to read*/
    int look_ahead_idx, level;
    bool error_flag;

public:
    Postfix(string s) {
        str = s;
        error_flag = false;
        /* level starts from the root 0,
            details in factor() function */
        level = 0;
        /*first character to read*/
        look_ahead_idx = 0;
        look_ahead = str[0];
        /*the postfix will be stored here*/
        postfix = "";

        expr();

        /* if the string isn't finished,
            something wrong happened and
            the string is invalid */
        if(look_ahead_idx < str.size())
            error_flag = true;

        /* Syntax error has occurred, no valid postfix */
        if(error_flag)
            postfix = "Syntax Error!";

        cout << "Postfix: " << postfix << endl;
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
        while(true) {
            if(look_ahead == '+') {
                match('+');
                term();
                postfix += "+";
            }
            else if(look_ahead == '-') {
                match('-');
                term();
                postfix += "-";
            }
            else break;
        }
    }
    /* factor_rest -> * factor factor_rest
       factor_rest -> / factor factor_rest */
    void factor_rest() {
        while(true) {
            if(look_ahead == '*') {
                match('*');
                factor();
                postfix += "*";
            }
            else if(look_ahead == '/') {
                match('/');
                factor();
                postfix += "/";
            }
            else break;
        }
    }
    /* matches the character with current
        lookahead and points it to the next
        character to read */
    void match(char ch) {
        /*if ch is not matched return*/
        if(ch != look_ahead) return ;
        look_ahead_idx++;
        /* check if the string is finished */
        if(look_ahead_idx < str.size())
            look_ahead = str[ look_ahead_idx ];
        else
            look_ahead = '\0';
    }

    /* factor -> 0|1|2|....|9| (expr) */
    void factor() {
        if(look_ahead >= '0' && look_ahead <= '9') {
            // current character is a digit
            postfix += look_ahead;
            // point next character
            match(look_ahead);
        }
        else if(look_ahead == '(') {
            /* current character is (,
            should be like (expr),
            create a new level */
            match(look_ahead);
            int pre_level = level;
            level++;
            expr();
            /* next character is closing ')' and it
            returns to it's original level */
            if(look_ahead == ')' && level-1 == pre_level)
                level--;
            else {
                error_flag = true;
                cout << "Postfix Error: index " << look_ahead_idx << ": expected ')' character" << endl;
            }
            match(look_ahead);
        }
        else {
            error_flag = true;
            cout << "Postfix Error: index " << look_ahead_idx << ": invalid character" << endl;
        }
    }
};
