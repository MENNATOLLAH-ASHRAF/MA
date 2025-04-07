#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cctype>
#include <iomanip>
using namespace std;

// Reserved words
unordered_set<string> keywords = {
    "if", "else", "for", "while", "switch", "case", "default", "return", "break", "continue",
    "do", "goto", "sizeof", "typedef", "static", "const", "class", "struct", "union",
    "enum", "namespace", "using", "try", "catch", "throw", "new", "delete", "main","cout","cin"
};

// Data types
unordered_set<string> dataTypes = {
    "int", "float", "double", "char", "void", "bool", "long", "short", "unsigned", "signed", "string"
};

// Multi-character operators
unordered_set<string> multiCharOps = {
    "++", "--", "==", "!=", "<=", ">=", "&&", "||", "<<", ">>"
};

// Single-character tokens (punctuation and operators)
unordered_set<char> singleCharTokens = {
    '+', '-', '*', '/', '=', '<', '>', '!', ';', ',', ':', '.', '?',
    '(', ')', '{', '}', '[', ']'
};

// Function to classify a lexeme and return the token number
int classify(const string& lexeme) {
    if (dataTypes.count(lexeme)) return 1;   // Data Type
    if (keywords.count(lexeme)) return 2;    // Reserved word

    if (lexeme == "++") return 3;   // Inc_Op
    if (lexeme == "--") return 4;   // Dec_Op
    if (lexeme == "==") return 5;   // Equal_Op
    if (lexeme == "!=") return 6;   // Inequal_Op
    if (lexeme == "<=") return 7;   // LE_comparison
    if (lexeme == ">=") return 8;   // GE_comparison
    if (lexeme == "<")  return 9;   // Less_Op
    if (lexeme == ">")  return 10;  // Greater_Op
    if (lexeme == "=")  return 11;  // Assign_Op
    if (lexeme == "+")  return 12;  // Plus_Op
    if (lexeme == "-")  return 13;  // Sub_Op
    if (lexeme == "*")  return 14;  // Mult_Op
    if (lexeme == "/")  return 15;  // Div_Op
    if (lexeme == "&&") return 16;  // AND_Gate
    if (lexeme == "||") return 17;  // OR_Gate
    if (lexeme == "!")  return 18;  // NOT_Gate
    if (lexeme == "<<") return 19;  // LS_Op
    if (lexeme == ">>") return 20;  // RS_Op

    if (lexeme == "(") return 21;   // LPAREN
    if (lexeme == ")") return 22;   // RPAREN
    if (lexeme == "{") return 23;   // LBRACE
    if (lexeme == "}") return 24;   // RBRACE
    if (lexeme == "[") return 25;   // LBRACKET
    if (lexeme == "]") return 26;   // RBRACKET
    if (lexeme == ";") return 27;   // Semicolon
    if (lexeme == ",") return 28;   // Comma
    if (lexeme == ":") return 29;   // Colon
    if (lexeme == ".") return 30;   // Dot
    if (lexeme == "?") return 31;   // Question Mark

    if (lexeme.size() >= 2 && lexeme.front() == '"' && lexeme.back() == '"') return 32; // Literal
    if (lexeme.size() >= 2 && lexeme.front() == '\'' && lexeme.back() == '\'') return 33; // Character Literal
    if (isdigit(lexeme[0]) || (lexeme[0] == '.' && lexeme.size() > 1)) {
        if (lexeme.find('.') != string::npos) return 34; // Float_Literal
        return 35; // Integer_Literal
    }
    if (isalpha(lexeme[0]) || lexeme[0] == '_') return 36; // Identifier
    return 37; // Unknown
}

// Tokenization function
vector<string> tokenize(const string& input) {
    vector<string> tokens;
    string temp;
    size_t i = 0;
    while (i < input.length()) {
        char ch = input[i];
        if (isspace(ch)) {
            i++;
            continue;
        }

        // Multi-character operators
        if (i + 1 < input.length()) {
            string twoChar = input.substr(i, 2);
            if (multiCharOps.count(twoChar)) {
                tokens.push_back(twoChar);
                i += 2;
                continue;
            }
        }

        // Single-character symbols
        if (singleCharTokens.count(ch)) {
            tokens.push_back(string(1, ch));
            i++;
            continue;
        }

        // String literal
        if (ch == '"') {
            string str = "\"";
            i++;
            while (i < input.length() && input[i] != '"') {
                str += input[i++];
            }
            if (i < input.length()) str += input[i++]; // closing quote
            tokens.push_back(str);
            continue;
        }

        // Char literal
        if (ch == '\'') {
            string str = "\'";
            i++;
            while (i < input.length() && input[i] != '\'') {
                str += input[i++];
            }
            if (i < input.length()) str += input[i++];
            tokens.push_back(str);
            continue;
        }

        // Identifiers, numbers
        temp = "";
        while (i < input.length() && (isalnum(input[i]) || input[i] == '_' || input[i] == '.')) {
            temp += input[i++];
        }
        tokens.push_back(temp);
    }
    return tokens;
}

int main() {
    string code;
    cout << "Enter C++ code (type EOF to end input):\n";
    string line;
    while (true) {
        cout << "--> ";
        getline(cin, line);
        if (line == "EOF") break;
        code += line + " ";
    }

    vector<string> lexemes = tokenize(code);
    cout << "\nLexeme Classification:\n";
    cout << "----------------------------------------------------------\n";
    for (const string& lexeme : lexemes) {
        int tokenNumber = classify(lexeme);
        cout << "Next token is: " << tokenNumber << " Next lexeme is " << lexeme << endl;
    }
    cout << "----------------------------------------------------------\n";
    cout << "End of tokenization\n";
    return 0;
}
