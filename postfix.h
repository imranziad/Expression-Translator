
/**
    Contains Postfix class,
    that takes a string in constructor
    and performs the infix to postfix
    translation if the string is a valid
    infix expression otherwise shows
    syntax error.
**/

class Postfix {
    string str;
    char look_ahead;
    int look_ahead_idx, level;

public:
    Postfix(string s) {
        str = s;
        level = 0;
        look_ahead_idx = 0;
        look_ahead = str[0];
        cout << "Postfix: ";
        expr();
        if(look_ahead_idx < str.size())
            cout << "\nSyntax Error!" << endl;
        cout << endl;
    }

private:
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
};
