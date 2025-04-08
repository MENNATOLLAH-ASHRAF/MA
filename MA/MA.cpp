#include <iostream>     // For input and output
#include <string>       // For using strings
#include <vector>       // For using dynamic arrays (vectors)
#include <unordered_set> // For fast lookup of reserved words and operators
#include <cctype>       // For character classification functions (e.g., isalpha, isdigit)
#include <iomanip>      // For formatting (not used directly here but included)

using namespace std;

// Set of reserved keywords in C++
unordered_set<string> keywords = {
    "if", "else", "for", "while", "switch", "case", "default", "return", "break", "continue",
    "do", "goto", "sizeof", "typedef", "static", "const", "class", "struct", "union",
    "enum", "namespace", "using", "try", "catch", "throw", "new", "delete", "main", "cout", "cin"
};

// Set of C++ data types
unordered_set<string> dataTypes = {
    "int", "float", "double", "char", "void", "bool", "long", "short", "unsigned", "signed", "string"
};

// Set of multi-character operators
unordered_set<string> multiCharOps = {
    "++", "--", "==", "!=", "<=", ">=", "&&", "||", "<<", ">>"
};

// Set of single-character symbols and operators
unordered_set<char> singleCharTokens = {
    '+', '-', '*', '/', '=', '<', '>', '!', ';', ',', ':', '.', '?',
    '(', ')', '{', '}', '[', ']'
};

// Function to classify a lexeme and return a specific token number
int classify(const string& lexeme) {
    if (dataTypes.count(lexeme)) return 1;   // Data type
    if (keywords.count(lexeme)) return 2;    // Reserved keyword

    // Multi-character operators
    if (lexeme == "++") return 3;   // Increment
    if (lexeme == "--") return 4;   // Decrement
    if (lexeme == "==") return 5;   // Equal to
    if (lexeme == "!=") return 6;   // Not equal to
    if (lexeme == "<=") return 7;   // Less than or equal to
    if (lexeme == ">=") return 8;   // Greater than or equal to
    if (lexeme == "<")  return 9;   // Less than
    if (lexeme == ">")  return 10;  // Greater than
    if (lexeme == "=")  return 11;  // Assignment
    if (lexeme == "+")  return 12;  // Addition
    if (lexeme == "-")  return 13;  // Subtraction
    if (lexeme == "*")  return 14;  // Multiplication
    if (lexeme == "/")  return 15;  // Division
    if (lexeme == "&&") return 16;  // Logical AND
    if (lexeme == "||") return 17;  // Logical OR
    if (lexeme == "!")  return 18;  // Logical NOT
    if (lexeme == "<<") return 19;  // Left shift
    if (lexeme == ">>") return 20;  // Right shift

    // Brackets, punctuation, etc.
    if (lexeme == "(") return 21;   // Left parenthesis
    if (lexeme == ")") return 22;   // Right parenthesis
    if (lexeme == "{") return 23;   // Left curly brace
    if (lexeme == "}") return 24;   // Right curly brace
    if (lexeme == "[") return 25;   // Left square bracket
    if (lexeme == "]") return 26;   // Right square bracket
    if (lexeme == ";") return 27;   // Semicolon
    if (lexeme == ",") return 28;   // Comma
    if (lexeme == ":") return 29;   // Colon
    if (lexeme == ".") return 30;   // Dot
    if (lexeme == "?") return 31;   // Question mark

    // Literals
    if (lexeme.size() >= 2 && lexeme.front() == '"' && lexeme.back() == '"') return 32; // String literal
    if (lexeme.size() >= 2 && lexeme.front() == '\'' && lexeme.back() == '\'') return 33; // Character literal

    // Numeric values
    if (isdigit(lexeme[0]) || (lexeme[0] == '.' && lexeme.size() > 1)) {
        if (lexeme.find('.') != string::npos) return 34; // Float literal
        return 35; // Integer literal
    }

    // Identifiers (e.g., variable names)
    if (isalpha(lexeme[0]) || lexeme[0] == '_') return 36; // Identifier

    return 37; // Unknown token
}

// Function to split the input string into tokens (lexemes)
vector<string> tokenize(const string& input) {
    vector<string> tokens;
    string temp;
    size_t i = 0;

    while (i < input.length()) {
        char ch = input[i];

        // Skip whitespace
        if (isspace(ch)) {
            i++;
            continue;
        }

        // Check for multi-character operators (e.g., "++", "==")
        if (i + 1 < input.length()) {
            string twoChar = input.substr(i, 2);
            if (multiCharOps.count(twoChar)) {
                tokens.push_back(twoChar);
                i += 2;
                continue;
            }
        }

        // Check for single-character symbols
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
            if (i < input.length()) str += input[i++]; // Add closing quote
            tokens.push_back(str);
            continue;
        }

        // Character literal
        if (ch == '\'') {
            string str = "\'";
            i++;
            while (i < input.length() && input[i] != '\'') {
                str += input[i++];
            }
            if (i < input.length()) str += input[i++]; // Add closing quote
            tokens.push_back(str);
            continue;
        }

        // Identifiers or numbers
        temp = "";
        while (i < input.length() && (isalnum(input[i]) || input[i] == '_' || input[i] == '.')) {
            temp += input[i++];
        }
        tokens.push_back(temp);
    }

    return tokens;
}

// Main function
int main() {
    string code;
    cout << "Enter C++ code (type EOF to end input):\n";
    string line;

    // Read code line by line until user types "EOF"
    while (true) {
        cout << "--> ";
        getline(cin, line);
        if (line == "EOF") break;
        code += line + " ";
    }

    // Tokenize the input code
    vector<string> lexemes = tokenize(code);

    // Print the classification result
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
