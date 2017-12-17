//
// Created by pi on 17-11-28.
//

#ifndef C0_SYNTAX_ANLYSIS_H
#define C0_SYNTAX_ANLYSIS_H

#include "../constants/symbol.h"
#include "../lexer/token.h"
#include "../lexer/lexer.h"
#include "../constants/operation_code.h"
#include "../simulator/code_generator/code_generator.h"

#include "../AST/abstract_node.h"
#include "../AST/node_factory.h"
#include <memory>
#include <stdexcept>
#include <vector>
#include <string>
#include <any>


class syntax_analysis : virtual public symbol,virtual public operation_code{
public:
    syntax_analysis(const std::string& filename,symbol_table& st):symbol_table_(st),lexer_(filename,st){
        current_token_temp_pos_=token_temp_.begin();
        root_=node_factory::make_node(Token_name::nul);
    }
    void run();
    std::shared_ptr<abstract_node<Token_name>> root_;
private:
    enum class Non_terminator{
        statement,
        function_define,
        function_call,
        ident_define,
        assign_statement,
        factor,
        expression
    };
    std::shared_ptr<token> next_token();
    void reset_current_token_temp_pos();

    Token_name getsym_from_next_token();
    void getsym();

    void error(const char msg[]);

    bool accept(Token_name token_name);
    bool expect(Token_name token_name);

    bool statement_begin();
    bool function_define_begin();
    bool function_call_begin();
    bool ident_define_begin();
    bool assign_statement_begin();
    bool factor_begin();
    bool expression_begin();
    bool is_the_beginning_of(Non_terminator non_terminator);

    std::shared_ptr<abstract_node<Token_name>> process();
    std::shared_ptr<abstract_node<Token_name>> ident_define();
    std::shared_ptr<abstract_node<Token_name>> function_define();
    std::shared_ptr<abstract_node<Token_name>> main_function();
    std::shared_ptr<abstract_node<Token_name>> sub_process();
    std::shared_ptr<abstract_node<Token_name>> statement_sequence();
    std::shared_ptr<abstract_node<Token_name>> statement();
    std::shared_ptr<abstract_node<Token_name>> condition_statement();
    std::shared_ptr<abstract_node<Token_name>> loop_statement();
    std::shared_ptr<abstract_node<Token_name>> function_call_statement();
    std::shared_ptr<abstract_node<Token_name>> assign_statement();
    std::shared_ptr<abstract_node<Token_name>> return_statement();
    std::shared_ptr<abstract_node<Token_name>> scanf();
    std::shared_ptr<abstract_node<Token_name>> printf();
    std::shared_ptr<abstract_node<Token_name>> expression();
    std::shared_ptr<abstract_node<Token_name>> term();
    std::shared_ptr<abstract_node<Token_name>> factor();
    std::shared_ptr<abstract_node<Token_name>> function_call();
private:
    Token_name sym_;
    std::shared_ptr<token> current_token_;
    std::list<std::shared_ptr<token>> token_temp_;
    decltype(token_temp_.begin()) current_token_temp_pos_;
    lexer lexer_;
    symbol_table& symbol_table_;

   // code_generator code_generator_;
};
#endif //C0_SYNTAX_ANLYSIS_H
