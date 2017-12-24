//
// Created by pi on 17-12-9.
//

#include "lexer.h"


lexer::lexer(const std::string& file_name,symbol_table& st):input_stream_(file_name,std::ios::in),symbol_table_(st){
    input_stream_>>std::noskipws;
    last_char_=' ';
    std::cout << std::endl << "-------------------------Start Compiling-------------------------" << std::endl;
}



bool lexer::next_char(){

    if(input_stream_>>std::noskipws>>last_char_){
        return true;
    }else{
        last_char_='\0';
        return false;
    }
}

bool lexer::is_skipper_symbol() {
    return (last_char_==32 || last_char_==10 || last_char_==13 || last_char_==9);
}


bool lexer::is_operator_token() {

    switch (last_char_){
        case '+':
            current_symbol_=Token_name ::plus;
            break;
        case '-':
            current_symbol_=Token_name ::minus;
            break;
        case '*':
            current_symbol_=Token_name ::times;
            break;
        case '/':
            current_symbol_=Token_name ::slash;
            break;
        case '=':
            current_symbol_=Token_name ::eql;
            break;
        default:
            return false;
    }
    return true;

}

bool lexer::is_punctuator_token() {
    switch (last_char_){
        case '(':
            current_symbol_=Token_name ::lparen;
            break;
        case ')':
            current_symbol_=Token_name ::rparen;
            break;
        case '{':
            current_symbol_=Token_name ::lbracket;
            break;
        case '}':
            current_symbol_=Token_name ::rbracket;
            break;
        case ',':
            current_symbol_=Token_name ::comma;
            break;
        case ';':
            current_symbol_=Token_name ::semicolon;
            break;
        default:
            return false;
    }
    return true;
}

void lexer::get_identifier_or_keyword_token() {
    std::string lexeme;
    while(isalnum(last_char_) || last_char_=='_' ){
        lexeme+=last_char_;
        next_char();
    }

    handler_indent(lexeme, Symbol_type::variable);
}

void lexer::get_literal_token(){
    std::string lexeme;
    while(isdigit(last_char_)){
        lexeme+=last_char_;
        next_char();
    }
    int num=std::stoi(lexeme);
    current_token_->name_=Token_name ::number;
    current_token_->attribute_=num;
}
void lexer::get_operator_token(){

    if(is_operator_token()){
        current_token_->name_=current_symbol_;

        current_token_->attribute_=last_char_;
    }
    next_char();
}
void lexer::get_punctuator_token(){

    if(is_punctuator_token()){
        current_token_->name_=current_symbol_;
        current_token_->attribute_=last_char_;
    }
    next_char();

}


std::shared_ptr<token> lexer::next_token(){

    current_token_= std::make_shared<token>(0,0,Token_name::nul);
    while(is_skipper_symbol()){
        std::cout << last_char_;
        next_char();
    }
    if(isdigit(last_char_)){
        get_literal_token();
    }else if(isalpha(last_char_) || last_char_=='_'){
        get_identifier_or_keyword_token();
    }else if(is_punctuator_token()){
        get_punctuator_token();
    }else if(is_operator_token()){
        get_operator_token();
    }else{
        current_token_= nullptr;
        //throw std::runtime_error("illeagl token!");
    }
    return current_token_;
}
