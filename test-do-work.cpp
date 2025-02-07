#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

class Token {
    public:
        Token(string type, string value, int line, int column) {
            this->_type   = type;
            this->_value  = value;
            this->_line   = line;
            this->_column = column;
        }
        string type() {
            return this->_type;
        }
        string value() {
            return this->_value;
        }
        int line() {
            return this->_line;
        }
        int column() {
            return this->_column;
        }
    private:
        string _type;
        string _value;
        int _line;
        int _column;
};

class Lexeme {
    public:
        Lexeme(string type, string value) {
            this->_type   = type;
            this->_value  = value;
        }
        string type() {
            return this->_type;
        }
        regex value() {
            return this->_value;
        }
    private:
        string _type;
        regex _value;
};

using IT = vector<Token>::iterator;

void create_lexemes(vector<Lexeme> &lexemes);

vector<Token> lex(string code) {
    vector<Lexeme> lexemes;
    create_lexemes(lexemes);

    vector<Token> tokens = vector<Token>();

    while(code.size() > 0) {
        bool found = false;
        for(long unsigned int i = 0; i != lexemes.size(); ++i) {
            regex re(lexemes[i].value());
            smatch match;
            if(regex_search(code, match, re)) {
                if(match.position() == 0 && match.length() > 0) {
                    tokens.push_back(Token(lexemes[i].type(), match.str(), 0, 0));
                    code = match.suffix();
                    found = true;
                    break;
                }
            }
        }
        if(!found) {
            code = code.substr(1);
        }
    }

    return tokens;
}

void create_lexemes(vector<Lexeme> &lexemes) {
    lexemes.push_back(Lexeme("a", "(a)"));
    lexemes.push_back(Lexeme("b", "(b)"));
    lexemes.push_back(Lexeme("c", "(c)"));
    lexemes.push_back(Lexeme("d", "(d)"));
    lexemes.push_back(Lexeme("e", "(e)"));
}

void ___or(IT&it, IT e, vector<void (*)(IT&, IT)> foo) {
    for(long unsigned int i = 0; i != foo.size(); ++i) {
        try {
            foo[i](it, e);
            return;
        } catch(const char* msg) {
            continue;
        }
    }
    throw "BAD";
}

void ___option(IT&it, IT e, void (*foo)(IT&, IT)) {
    try {
        foo(it, e);
    } catch(const char* msg) {
        return;
    }
}

void ___loop(IT&it, IT e, void (*foo)(IT&, IT)) {
    foo(it, e);
    while(true) {
        try {
            foo(it, e);
        } catch(const char* msg) {
            return;
        }
    }
}

void __a(IT&it, IT e) { if(it == e) throw "BAD"; if(it->type() != "a") throw "BAD"; it++; }
void __b(IT&it, IT e) { if(it == e) throw "BAD"; if(it->type() != "b") throw "BAD"; it++; }
void __c(IT&it, IT e) { if(it == e) throw "BAD"; if(it->type() != "c") throw "BAD"; it++; }
void __d(IT&it, IT e) { if(it == e) throw "BAD"; if(it->type() != "d") throw "BAD"; it++; }
void __e(IT&it, IT e) { if(it == e) throw "BAD"; if(it->type() != "e") throw "BAD"; it++; }

void __expr(IT&it, IT e);

void __expr(IT&it, IT e) {
    if(it == e) throw "BAD";

    __a(it, e);
    ___or(it, e, (vector<void (*)(IT&, IT)>){
        __b,
        [](IT&it, IT e) {
            ___option(it, e, __c);
            __expr(it, e);
        },
        [](IT&it, IT e) {
            ___loop(it, e, __d);
        }
    });
    __e(it, e);
}

int main() {
    string code;
    getline(cin, code);
    vector<Token> tokens = lex(code);
    IT it = tokens.begin();
    
    try {
        __expr(it, tokens.end());
    } catch(const char* msg) {
        cout << "BAD" << endl;
        return 0;
    }

    return 0;
}
