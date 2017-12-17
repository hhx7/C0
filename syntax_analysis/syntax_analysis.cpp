//
// Created by pi on 17-12-9.
//

#include "syntax_analysis.h"

void syntax_analysis::run(){

    /*auto x=next_token();
    while (x) {
        std::cout<<(int)x->get_name()<<" ";
        auto& attribute=x->attribute_;
        std::visit([](auto& val){
            using T=std::remove_cv_t <std::remove_reference_t <decltype(val)>>;
            if constexpr (std::is_same_v<T,std::string>){
            std::cout<<val<<std::endl;
        }else if constexpr (std::is_same_v<T,char>){
            std::cout<<val<<std::endl;
        }
        },attribute);
        std::cout<<std::endl;
        x = next_token();
    }*/
    getsym();
    auto head=process();
    root_->set_leftmost_child(head);
}
std::shared_ptr<token> syntax_analysis::next_token(){
    return lexer_.next_token();
}
void syntax_analysis::reset_current_token_temp_pos(){
    current_token_temp_pos_=token_temp_.begin();
}

syntax_analysis::Token_name syntax_analysis::getsym_from_next_token(){
    std::shared_ptr<token> token_temp;
    if(current_token_temp_pos_==token_temp_.end()){
        token_temp=next_token();
        token_temp_.push_back(token_temp);
        reset_current_token_temp_pos();
    }else{
        token_temp=*current_token_temp_pos_;
    }
    ++current_token_temp_pos_;
    return token_temp->get_name();
}

void syntax_analysis::getsym(){
    if(token_temp_.empty()){
        current_token_=next_token();
    }else{
        current_token_=token_temp_.front();
        token_temp_.erase(token_temp_.begin());
        reset_current_token_temp_pos();
    }
    if(current_token_== nullptr)
        return;

    sym_=current_token_->get_name();
    std::cout<<'<'<<(int)sym_<<",";
    auto& attribute=current_token_->attribute_;
    std::visit([](auto& val){
        using T=std::remove_cv_t <std::remove_reference_t <decltype(val)>>;
        if constexpr (std::is_same_v<T,std::string>){
            std::cout<<val;
        }else if constexpr (std::is_same_v<T,char>){
            std::cout<<val;
        }
    },attribute);

    std::cout<<'>'<<std::endl;

}
void syntax_analysis::error(const char msg[]){
    throw std::runtime_error(msg);
}
bool syntax_analysis::accept(Token_name token_name){
    if(token_name==sym_){
        getsym();
        return true;
    }
    return false;
}

bool syntax_analysis::expect(Token_name token_name){
    if(accept(token_name)){
        return true;
    }
    error("expect:unexpected Token_name");
    return false;
}

bool syntax_analysis::statement_begin(){
    switch (sym_){
        case Token_name ::ifsym:
        case Token_name ::whilesym:
        case Token_name ::lbracket:
        case Token_name ::retsym:
        case Token_name ::scanf:
        case Token_name ::printf:
        case Token_name ::semicolon:
            return true;
        default:
            return is_the_beginning_of(Non_terminator::function_call)||is_the_beginning_of(Non_terminator::assign_statement);
    }
}
bool syntax_analysis::function_define_begin(){
    Token_name sym_temp=sym_;
    if(sym_temp==Token_name::intsym || sym_temp==Token_name::voidsym){
        sym_temp=getsym_from_next_token();
        if(sym_temp==Token_name::ident){
            sym_temp=getsym_from_next_token();
            if(sym_temp==Token_name::lparen){

                return true;
            }
        }
    }

    return false;
}
bool syntax_analysis::function_call_begin(){
    Token_name sym_temp=sym_;
    if(sym_temp==Token_name::ident){
        sym_temp=getsym_from_next_token();
        if(sym_temp==Token_name::lparen){
            return true;
        }
    }

    return false;
}

bool syntax_analysis::ident_define_begin(){
    Token_name sym_temp=sym_;
    if(sym_temp==Token_name::intsym){
        sym_temp=getsym_from_next_token();
        if(sym_temp==Token_name::ident){
            sym_temp=getsym_from_next_token();
            if(sym_temp==Token_name::semicolon||sym_temp==Token_name::comma){
                return true;
            }
        }
    }
    return false;
}

bool syntax_analysis::assign_statement_begin(){
    Token_name sym_temp=sym_;
    if(sym_temp==Token_name::ident){
        sym_temp=getsym_from_next_token();
        if(sym_temp==Token_name::eql){
            return true;
        }
    }
    return false;
}
bool syntax_analysis::factor_begin(){

    switch (sym_){
        case Token_name ::number:
        case Token_name ::lparen:
            return true;
        default:
            return is_the_beginning_of(Non_terminator::ident_define) || is_the_beginning_of(Non_terminator::function_call);
    }
}

bool syntax_analysis::expression_begin(){
    return (sym_==Token_name::plus || sym_==Token_name::minus ||is_the_beginning_of(Non_terminator::factor));
}

bool syntax_analysis::is_the_beginning_of(Non_terminator non_terminator){
    bool flag=false;
    switch (non_terminator){
        case Non_terminator ::statement:
            flag=statement_begin();
            break;
        case Non_terminator ::function_define:
            flag=function_define_begin();
            break;
        case Non_terminator ::function_call:
            flag=function_call_begin();
            break;
        case Non_terminator ::ident_define:
            flag=ident_define_begin();
            break;
        case Non_terminator ::assign_statement:
            flag=assign_statement_begin();
            break;
        case Non_terminator ::factor:
            flag=factor_begin();
            break;
        case Non_terminator ::expression:
            flag=expression_begin();
            break;
    }
    reset_current_token_temp_pos();
    return flag;
}

auto syntax_analysis::process()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<symbol::Token_name>> ident_def= nullptr;
    std::shared_ptr<abstract_node<symbol::Token_name>> func_def= nullptr;
    std::shared_ptr<abstract_node<symbol::Token_name>> main_func= nullptr;
    if(is_the_beginning_of(Non_terminator::ident_define)){
        ident_def=ident_define();
    }
    while(is_the_beginning_of(Non_terminator::function_define)){

        func_def=function_define();
    }
    main_func=main_function();
    return node_factory::make_family(Token_name::proc,ident_def,func_def,main_func);
}

auto syntax_analysis::ident_define()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<symbol::Token_name>> name= nullptr;
    if(accept(Token_name ::intsym)){

        expect(Token_name ::ident);
        name=node_factory::make_node(Token_name::ident);
        while (sym_==Token_name ::comma){
            getsym();
            expect(Token_name ::ident);
            name=name->make_siblings(node_factory::make_node(Token_name::ident));
        }
        expect(Token_name ::semicolon);
    } else{
        error("ident define: syntax error");
    }
    return node_factory::make_family(Token_name::ident_def,name);
}
auto syntax_analysis::function_define()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<symbol::Token_name>> ret_type= nullptr;
    std::shared_ptr<abstract_node<symbol::Token_name>> sub_proc= nullptr;
    if(sym_==Token_name::intsym || sym_==Token_name::voidsym){
        ret_type=node_factory::make_node(sym_);
        getsym();
        expect(Token_name::ident);
        expect(Token_name::lparen);
        expect(Token_name::rparen);
        sub_proc=sub_process();
    } else{
        error("function body: syntax error");
    }

    return node_factory::make_family(Token_name::func_define,ret_type,sub_proc);
}
auto syntax_analysis::main_function()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<symbol::Token_name>> sub_proc= nullptr;
    if(accept(Token_name::voidsym)){
        expect(Token_name::mainsym);
        expect(Token_name::lparen);
        expect(Token_name::rparen);
        sub_proc=sub_process();
    } else{
        error("main function: syntax error");
    }
    return node_factory::make_family(Token_name::mainsym,sub_proc);
}

auto syntax_analysis::sub_process()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<symbol::Token_name>> func_define= nullptr;
    std::shared_ptr<abstract_node<symbol::Token_name>> stmt_seq= nullptr;
    if(accept(Token_name::lbracket)){
        if(ident_define_begin()){
            func_define=ident_define();
        }
        stmt_seq=statement_sequence();
        expect(Token_name::rbracket);
    } else{
        error("sub process: syntax error");
    }


    return node_factory::make_family(Token_name::sub_proc,func_define,stmt_seq);
}


auto syntax_analysis::statement_sequence()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<symbol::Token_name>> stmt= nullptr;

    stmt=statement();
    while(is_the_beginning_of(Non_terminator::statement)){
        stmt=stmt->make_siblings(statement());
    }
    return node_factory::make_family(Token_name::stmt_seq,stmt);
}
auto syntax_analysis::statement()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<symbol::Token_name>> kid1= nullptr;
    std::shared_ptr<abstract_node<symbol::Token_name>> kid2= nullptr;
    std::shared_ptr<abstract_node<symbol::Token_name>> kid3= nullptr;
    switch (sym_){
        case Token_name ::ifsym: 
            kid1=condition_statement();
            break;
        case Token_name ::whilesym: 
            kid1=loop_statement();
            break;
        case Token_name ::lbracket: 
            kid1=statement_sequence();
            expect(Token_name::rbracket);
            break;
        case Token_name ::retsym:
            kid1=return_statement();
            break;
        case Token_name ::scanf: 
            kid1=scanf();
            break;
        case Token_name ::printf: 
            kid1=printf();
            break;
        case Token_name ::semicolon:
            break;
    }
    if(is_the_beginning_of(Non_terminator::function_call)) {
        kid2= function_call_statement();

    }
    if(is_the_beginning_of(Non_terminator::assign_statement)){
        kid3=assign_statement();
    }

    return node_factory::make_family(Token_name::stmt,kid1,kid2,kid3);
    //error("statement: syntax error");
}

auto syntax_analysis::condition_statement()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> condition= nullptr;
    std::shared_ptr<abstract_node<Token_name >> if_brunch= nullptr;
    std::shared_ptr<abstract_node<Token_name >> else_brunch= nullptr;
    if(accept(Token_name::ifsym)){
        expect(Token_name::lparen);
        condition=expression();
        expect(Token_name::rparen);
    }else if(is_the_beginning_of(Non_terminator::statement)){
        if_brunch=statement();
        if(sym_==Token_name::elsesym){
            else_brunch=statement();
        }
    }else{
        error("condition: syntax error");
    }
    return node_factory::make_family(Token_name::ifsym,if_brunch,else_brunch);
}
auto syntax_analysis::loop_statement()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> condition= nullptr;
    std::shared_ptr<abstract_node<Token_name >> stmt= nullptr;
    
    if(accept(Token_name::whilesym)){
        expect(Token_name::lparen);
        condition=expression();
        expect(Token_name::rparen);
        stmt=statement();
    }else{
        error("loop: syntax error");
    }
    return node_factory::make_family(Token_name::loop,condition,stmt);
}
auto syntax_analysis::function_call_statement()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> func_call=function_call();
    expect(Token_name::semicolon);
    return node_factory::make_family(Token_name::func_call_stmt,func_call);
}
auto syntax_analysis::assign_statement()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> id= nullptr;
    std::shared_ptr<abstract_node<Token_name >> exp= nullptr;
    if(accept(Token_name::ident)){
        id=node_factory::make_node(Token_name::ident);
        expect(Token_name::eql);
        exp=expression();
        expect(Token_name::semicolon);
    }else{
        error("assign: syntax error");
    }
    return node_factory::make_family(Token_name::assign,id,exp);
}
auto syntax_analysis::return_statement()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<Token_name >> ret_value= nullptr;
    if(accept(Token_name::retsym)){
        if(sym_==Token_name::lparen){
            ret_value=expression();
            expect(Token_name::rparen);
        }else if(is_the_beginning_of(Non_terminator::expression)){
            ret_value=expression();
        }
        expect(Token_name::semicolon);
    }else{
        error("return: syntax error");
    }
    return node_factory::make_family(Token_name::retsym,ret_value);
}
auto syntax_analysis::scanf()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> id= nullptr;
    if(accept(Token_name::scanf)){
        expect(Token_name::lparen);
        expect(Token_name::ident);
        id=node_factory::make_node(Token_name::ident);
        expect(Token_name::rparen);
        expect(Token_name::semicolon);
    }else{
        error("scanf: syntax error");
    }
    
    return node_factory::make_family(Token_name::scanf,id);
}

auto syntax_analysis::printf()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> exp= nullptr;
    if(accept(Token_name::printf)){
        expect(Token_name::lparen);
        if(expression_begin())
            exp=expression();
        expect(Token_name::rparen);
        expect(Token_name::semicolon);
    }else{
        error("printf:syntax error");
    }
    return node_factory::make_family(Token_name::printf,exp);

}

auto syntax_analysis::expression()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<Token_name >> plus_or_minus= nullptr;
    std::shared_ptr<abstract_node<Token_name >> term_= nullptr;
    std::shared_ptr<abstract_node<Token_name >> kid3= nullptr;
    std::shared_ptr<abstract_node<Token_name >> kid4= nullptr;
    std::shared_ptr<abstract_node<Token_name >> kid_temp= nullptr;
    if(sym_==Token_name::plus || sym_==Token_name::minus){
        plus_or_minus=node_factory::make_node(sym_);
        getsym();
    }
    term_=term();

    while(sym_==Token_name::plus || sym_==Token_name::minus){
        kid3=node_factory::make_node(sym_);

        getsym();
        kid4=term();
        kid_temp=kid3->make_siblings(kid4);
    }
    return node_factory::make_family(Token_name::exp,plus_or_minus,term_,kid_temp);
}

auto syntax_analysis::term()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<Token_name >> factor_= nullptr;
    std::shared_ptr<abstract_node<Token_name >> kid2= nullptr;
    std::shared_ptr<abstract_node<Token_name >> kid3= nullptr;
    std::shared_ptr<abstract_node<Token_name >> kid_temp= nullptr;

    factor_=factor();
    while(sym_==Token_name::times || sym_==Token_name::slash){
        kid2=node_factory::make_node(sym_);
        getsym();
        kid3=factor();
        if(kid_temp== nullptr){
            kid_temp=kid2->make_siblings(kid3);
        } else{
            kid_temp=kid_temp->make_siblings(kid2)->make_siblings(kid3);
        }
    }

    return node_factory::make_family(Token_name::term,factor_,kid_temp);
}


auto syntax_analysis::factor()->std::shared_ptr<abstract_node<symbol::Token_name>>{


    std::shared_ptr<abstract_node<Token_name >> kid= nullptr;
    if(is_the_beginning_of(Non_terminator::ident_define)){
        kid=ident_define();

    }else if(accept(Token_name::number)){

        kid=node_factory::make_node(Token_name::number);

    }else if(accept(Token_name::lparen)){
        kid=expression();
        expect(Token_name::rparen);

    }else if(is_the_beginning_of(Non_terminator::function_call)){

        kid=function_call();
    }else{
        error("factor: syntax error");
    }

    return node_factory::make_family(Token_name::factor,kid);
}

 auto syntax_analysis::function_call()->std::shared_ptr<abstract_node<symbol::Token_name>>{
     std::shared_ptr<abstract_node<Token_name >> func_name= nullptr;
     if(accept(Token_name::ident)){
        expect(Token_name::lparen);
        expect(Token_name::rparen);

        func_name=node_factory::make_node(Token_name::ident);
        //code_generator_.emit_instruction(Operation_code::CAL,current_token_);
     }else{
        error("function call:syntax error");
     }
     return node_factory::make_family(Token_name::call,func_name);
}
