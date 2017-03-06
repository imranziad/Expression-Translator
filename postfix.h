/**
    Contains Postfix class,
    that takes a string in constructor
    and performs the infix to postfix
    translation if the string is a valid
    infix expression otherwise shows
    syntax error.
    accepted characters:
    0-9, (), +, -, *, /

    to support int >= 10, modify match()
    and factor digit check() accordingly.
**/

class Postfix {
    string str, postfix;
    char lookahead; /*next char to read*/
    int lookahead_idx, level;
    int idx;
    double value;
    bool error_flag;

public:
    Postfix(string s) {
        /*the postfix will be stored in this*/
        postfix = "";
        value = 0.0;
        if(s.empty()) goto print;

        str = s;
        error_flag = false;
        /* level starts from the root 0,
            details in factor() function */
        level = 0;
        /*first character to read*/
        lookahead_idx = 0;
        lookahead = str[0];

        expr();

        /* if the string isn't finished,
            something wrong happened and
            the string is invalid */
        if(lookahead_idx < str.size())
            error_flag = true;

        idx = (int)(postfix.size())-1;
        /* Syntax error has occurred, no valid postfix */
        if(error_flag)
            postfix = "Syntax Error!";
        else
            value = calculate_value(idx);

        print:
        cout << "Postfix: " << postfix << endl;
        cout << setprecision(3) << "  Value: " << value << endl;
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
            if(lookahead == '+') {
                match('+');
                term();
                postfix += "+";
            }
            else if(lookahead == '-') {
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
            if(lookahead == '*') {
                match('*');
                factor();
                postfix += "*";
            }
            else if(lookahead == '/') {
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
        if(ch != lookahead) return ;
        lookahead_idx++;
        /* check if the string is finished */
        if(lookahead_idx < str.size())
            lookahead = str[ lookahead_idx ];
        else
            lookahead = '\0';
    }

    /* factor -> 0|1|2|....|9| (expr) */
    void factor() {
        if(lookahead >= '0' && lookahead <= '9') {
            // current character is a digit
            postfix += lookahead;
            // point next character
            match(lookahead);
        }
        else if(lookahead == '(') {
            /* current character is (,
            should be like (expr),
            create a new level */
            match(lookahead);
            int pre_level = level;
            level++;
            expr();
            /* next character is closing ')' and it
            returns to it's original level */
            if(lookahead == ')' && level-1 == pre_level)
                level--;
            else {
                error_flag = true;
                cout << "Postfix Error: index " << lookahead_idx << ": expected ')' character" << endl;
            }
            match(lookahead);
        }
        else {
            error_flag = true;
            cout << "Postfix Error: index " << lookahead_idx << ": invalid character" << endl;
        }
    }
    /*  calculate the value from the postfix
        this function uses depth first search
    */
    double calculate_value(int &pos) {
        if(pos < 0) return 0.0;
        //if(pos == 0) return (int)(s[pos]-'0');
        if(postfix[pos] >= '0' && postfix[pos] <= '9') {
            double num = (int)(postfix[pos]-'0');
            pos--;
            return num;
        }
        char ch = postfix[pos]; --pos;
        double x = calculate_value(pos);
        double y = calculate_value(pos);
        if(ch == '+') return y+x;
        if(ch == '-') return y-x;
        if(ch == '*') return y*x;
        return y/x; // it's definitely '/'
    }
};
