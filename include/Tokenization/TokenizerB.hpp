#ifndef TOKENIZER_B_HPP
#define TOKENIZER_B_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <Token.hpp>

namespace VoltLang
{
    class TokenizerB
    {
    private:
        std::map<std::string, TokenType> dictionary;

        std::map<std::string,TokenType> CreateDictionary()
        {
            std::map<std::string, TokenType> items;

            items[":"] = TokenType::Colon;
            items["section"] = TokenType::Section;
            items["data"] = TokenType::Data;
            items["db"] = TokenType::DB;
            items["dq"] = TokenType::DQ;
            items["text"] = TokenType::Text;
            items["hlt"] = TokenType::Halt;
            items["push"] = TokenType::Push;
            items["pop"] = TokenType::Pop;
            items["mov"] = TokenType::Move;
            items["inc"] = TokenType::Increment;
            items["dec"] = TokenType::Decrement;
            items["add"] = TokenType::Add;
            items["sub"] = TokenType::Subtract;
            items["mul"] = TokenType::Multiply;
            items["div"] = TokenType::Divide;
            items["cmp"] = TokenType::Compare;
            items["jmp"] = TokenType::Jump;
            items["jg"] = TokenType::JumpIfGreaterThan;
            items["jge"] = TokenType::JumpIfGreaterThanOrEqual;
            items["jl"] = TokenType::JumpIfLessThan;
            items["jle"] = TokenType::JumpIfLessThanOrEqual;
            items["je"] = TokenType::JumpIfEqual;
            items["jne"] = TokenType::JumpIfNotEqual;
            items["jz"] = TokenType::JumpIfZero;
            items["jnz"] = TokenType::JumpIfNotZero;
            items["call"] = TokenType::Call;
            items["ret"] = TokenType::Return;
            items["nop"] = TokenType::NOP;

            return items;
        }

        TokenType GetValue(std::map<std::string,TokenType>& dictionary, Token<PrimitiveTokenType> token)
        {
            if(dictionary.count(token.text))
                return dictionary[token.text];

            return static_cast<TokenType>(token.type);
        }    

    public:
        TokenizerB()
        {
            dictionary = CreateDictionary();
        }

        std::vector<Token<TokenType>> Parse(const std::vector<Token<PrimitiveTokenType>> tokens)
        {
            std::vector<Token<TokenType>> tokenList;

            for (int i = 0; i < tokens.size(); i++)
            {
                Token<TokenType> token;
                token.lineNumber = tokens[i].lineNumber;
                token.text = tokens[i].text;
                token.type = GetValue(dictionary, tokens[i]);
                tokenList.push_back(token);
            }

            return tokenList;
        }    
    };
}
#endif