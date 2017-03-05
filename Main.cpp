#include <iostream>
#include <cstdio>
using namespace std;

string str;

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

    return 0;
}
