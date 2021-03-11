//
//  Scanner.cpp
//  ContextFreeGrammarDecoder
//
//  Created by Samuel Donovan on 2/23/21.
//

#include "Scanner.hpp"

#include <vector>
#include <string>
#include <optional>
#include <map>

using namespace std;

typedef string::const_iterator strItr;

enum Token: int {lesser = -1, greater = -2, colon = -3, newLine =4, tab = -5, space = -6};

bool lowerOrUpper(char c) {return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');}

// perhaps return (tokens: [Token]?, [Token:string]
// perhaps ObjectOrientify the scan function into an object
// perhaps output a vector mapping Tokens of value > 0 to their respective type
// also output a map for each type T mapping Tokens of value > 0 && type T to their respective type data
// eg token 2 is of type identifier, there is a map letting you know which identifier it is

class Scanner {
    
    int customToken {0};
    
    optional<vector<int>> scan(string const & input) {
        
        map<string,int> identifierToToken;
        
        strItr end = input.cend();
        strItr currentIter = input.cbegin();
        
        optional<vector<int>> tokens((vector<int>()));
        
        // loop invariant:
        // use currentToken to produce the next token
        // if it is not a valid token, return nil
        // if it is a valid token, currentToken points to the next char to use
        
        while (true) {
            if (currentIter == end) return tokens;
            char current = *(currentIter++);
            
            switch (current) {
                case '<':
                    tokens->push_back(Token::lesser);
                    break;
                case '>':
                    tokens->push_back(Token::greater);
                    break;
                case ' ':
                    tokens->push_back(Token::space);
                    break;
                case '\n':
                    tokens->push_back(Token::newLine);
                case '\t':
                    tokens->push_back(Token::tab);
                case ':':
                    tokens->push_back(Token::colon);
                default:
                    if (lowerOrUpper(current)) {
                        string identifier;
                        identifier.push_back(current);
                        
                        // we have pushed back the current.
                        // if we need to push back what currentIter points to, we do so and increment currentIter
                        // if we don't, we update currentIter and
                        
                        while (currentIter != end) {
                            current = *currentIter;
                            if (!lowerOrUpper(current)) break;
                            identifier.push_back(current);
                            ++currentIter;
                        }
                        
                        // add a new token with of type identifier pointing to this string
                        registerIdentifier(identifier);
                    }
                    else return nullopt;
            }
        }
        return tokens;
    }
    
    // add a new token with of type identifier pointing to this string (if you already registered this string, reuuse the token)
    void registerIdentifier(string const & identifier) {
        // check if we already used this identifier
        //     if so, reuse the customToken
        // if we have not already used this identifier
        //     register this identifier in the map of identifier to customToken
        //     push_back the current customToken
        //     increment customToken
    }
    
};
