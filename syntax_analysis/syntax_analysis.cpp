//
// Created by pi on 17-12-9.
//

#include "syntax_analysis.h"

void syntax_analysis::run(){

    /*auto x=next_token();
    while (x) {
        std::cout<<x->get_name()<<" ";
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
    std::cout << '<' << sym_ << ",";
    auto& attribute=current_token_->attribute_;
    std::visit([](auto& val){
        using T=std::remove_cv_t <std::remove_reference_t <decltype(val)>>;
        if constexpr (std::is_same_v<T,std::string>){
            std::cout<<val;
        }else if constexpr (std::is_same_v<T,char>){
            std::cout<<val;
        } else if constexpr (std::is_same_v<T, int>) {
            std::cout << val;
        }
    },attribute);

    std::cout << '>' << "\t";

}
void syntax_analysis::error(const char msg[]){
    ///throw std::runtime_error(msg);
    std::cout << std::endl << msg << std::endl;
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
        case Token_name ::ident:
        case Token_name ::number:
        case Token_name ::lparen:
            return true;
        default:
            return is_the_beginning_of(Non_terminator::function_call);
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

    symbol_table_.open_scope();
    unsigned inte_code_pos=code_generator_.emit_instruction(Operation_code::INT);

    unsigned jmp_code_pos=code_generator_.emit_instruction(Operation_code::JMP);
    if(is_the_beginning_of(Non_terminator::ident_define)){
        ident_def=ident_define();
    }
    while(is_the_beginning_of(Non_terminator::function_define)){

        func_def=function_define();
    }
    code_generator_.complete_instruction(jmp_code_pos);
    main_func=main_function();

    auto current_scope_size=symbol_table_.get_current_scope_size();
    code_generator_.complete_instruction(inte_code_pos,current_scope_size);
    return node_factory::make_family(Token_name::proc,ident_def,func_def,main_func);
}

auto syntax_analysis::ident_define()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<symbol::Token_name>> name= nullptr;
    if(accept(Token_name ::intsym)){

        auto temp=current_token_;
        expect(Token_name ::ident);

        symbol_table_.enter_symbol(temp->visit_string(),Symbol_type::variable);
        name=node_factory::make_node(Token_name::ident);
        while (sym_==Token_name ::comma){
            getsym();
            auto temp=current_token_;
            expect(Token_name ::ident);
            symbol_table_.enter_symbol(temp->visit_string(),Symbol_type::variable);
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
        Return_type return_type=Return_type ::void_type;
        if(sym_==Token_name::intsym)
            return_type=Return_type ::int_type;

        getsym();

        auto func_name=current_token_->visit_string();
        expect(Token_name::ident);
        expect(Token_name::lparen);
        expect(Token_name::rparen);

        auto func=symbol_table_.enter_symbol(func_name, Symbol_type::function, return_type);

        code_generator_.record_func_pos(func_name);//used to complete call code
        sub_proc=sub_process();
    } else{
        error("function body: syntax error");
    }

    return node_factory::make_family(Token_name::func_def, ret_type, sub_proc);
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

        /*
         * open new scope
         */
        symbol_table_.open_scope();
        unsigned inte_code_pos=code_generator_.emit_instruction(Operation_code::INT);

        if(ident_define_begin()){
            func_define=ident_define();
        }
        stmt_seq=statement_sequence();
        expect(Token_name::rbracket);

        /*
         * close new scope
         */
        auto current_scope_size=symbol_table_.get_current_scope_size();
        code_generator_.complete_instruction(inte_code_pos,current_scope_size);

        symbol_table_.close_scope();
        code_generator_.emit_instruction(Operation_code::RET);

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
    unsigned  inte_code_pos=0,current_scope_size;
    switch (sym_){
        case Token_name ::ifsym: 
            kid1=condition_statement();
            break;
        case Token_name ::whilesym: 
            kid1=loop_statement();
            break;
        case Token_name ::lbracket:
            getsym();
            //generate int code
            symbol_table_.open_scope();
            //inte_code_pos=code_generator_.emit_instruction(Operation_code::INT);
            kid1=statement_sequence();
            expect(Token_name::rbracket);

            //complete int code
            //current_scope_size=symbol_table_.get_current_scope_size();
            //code_generator_.complete_instruction(inte_code_pos,current_scope_size);

            symbol_table_.close_scope();
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
            accept(Token_name::semicolon);
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
    unsigned jpc_code_pos1=0;
    unsigned jpc_code_pos2=0;
    if(accept(Token_name::ifsym)){
        expect(Token_name::lparen);
        condition=expression();
        expect(Token_name::rparen);
        /*
         * generate jpc code
         */
        jpc_code_pos1=code_generator_.emit_instruction(Operation_code::JPC);

    }
    if(is_the_beginning_of(Non_terminator::statement)){
        if_brunch=statement();

        if (sym_ == Token_name::elsesym, accept(sym_)) {
            jpc_code_pos2 = code_generator_.emit_instruction(Operation_code::JMP);
            code_generator_.complete_instruction(jpc_code_pos1);
            else_brunch=statement();
            code_generator_.complete_instruction(jpc_code_pos2);
        }else{
            code_generator_.complete_instruction(jpc_code_pos1);
        }

    }else{
        error("condition: syntax error");
    }
    /*
     * complete jpc code
     */
    return node_factory::make_family(Token_name::ifsym,if_brunch,else_brunch);
}
auto syntax_analysis::loop_statement()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> condition= nullptr;
    std::shared_ptr<abstract_node<Token_name >> stmt= nullptr;
    unsigned jpc_code_pos1=0;

    if(accept(Token_name::whilesym)){
        expect(Token_name::lparen);
        unsigned while_begin_pos=code_generator_.get_current_code_pos()+1;
        condition=expression();
        expect(Token_name::rparen);
        /*
         * generate jpc code
         */
        jpc_code_pos1=code_generator_.emit_instruction(Operation_code::JPC);
        stmt=statement();
        code_generator_.emit_instruction(Operation_code::JMP,0,while_begin_pos);
        code_generator_.complete_instruction(jpc_code_pos1);
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

    auto ident_name=current_token_->visit_string();
    if(accept(Token_name::ident)){
        id=node_factory::make_node(Token_name::ident);
        expect(Token_name::eql);
        exp=expression();
        expect(Token_name::semicolon);

        /*
         * generate assign code
         */
        code_generator_.emit_instruction(Operation_code::STO,ident_name);


    }else{
        error("assign: syntax error");
    }
    return node_factory::make_family(Token_name::assign,id,exp);
}
auto syntax_analysis::return_statement()->std::shared_ptr<abstract_node<symbol::Token_name>>{

    std::shared_ptr<abstract_node<Token_name >> ret_value= nullptr;
    if(accept(Token_name::retsym)){
        if(sym_==Token_name::lparen,accept(sym_)){
            ret_value=expression();
            expect(Token_name::rparen);
        }else if(is_the_beginning_of(Non_terminator::expression)){
            ret_value=expression();
        }
        expect(Token_name::semicolon);

        /*
         * generate return code
         */
        //code_generator_.emit_instruction(Operation_code::RET);
    }else{
        error("return: syntax error");
    }
    return node_factory::make_family(Token_name::retsym,ret_value);
}
auto syntax_analysis::scanf()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> id= nullptr;
    if(accept(Token_name::scanf)){
        expect(Token_name::lparen);

        auto ident_name=current_token_->visit_string();
        expect(Token_name::ident);
        id=node_factory::make_node(Token_name::ident);
        expect(Token_name::rparen);
        expect(Token_name::semicolon);

        /*
         * generate scanf code
         */
        code_generator_.emit_instruction(Operation_code::RED);
        code_generator_.emit_instruction(Operation_code::STO,ident_name);


    }else{
        error("scanf: syntax error");
    }
    
    return node_factory::make_family(Token_name::scanf,id);
}

auto syntax_analysis::printf()->std::shared_ptr<abstract_node<symbol::Token_name>>{
    std::shared_ptr<abstract_node<Token_name >> exp= nullptr;
    if(accept(Token_name::printf)){
        expect(Token_name::lparen);
        if(is_the_beginning_of(Non_terminator::expression))
            exp=expression();
        expect(Token_name::rparen);
        expect(Token_name::semicolon);

        /*
         * generate printf code
         */

        code_generator_.emit_instruction(Operation_code::WRT);
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

    bool minus_flag=false;
    if(sym_==Token_name::plus || sym_==Token_name::minus){
        plus_or_minus=node_factory::make_node(sym_);
        getsym();
        if(sym_==Token_name::minus){
            minus_flag= true;
            code_generator_.emit_instruction(Operation_code::LIT,0,0);
        }
    }
    term_=term();

    if(minus_flag){
        code_generator_.emit_instruction(Operation_code::SUB);
    }

    while(sym_==Token_name::plus || sym_==Token_name::minus){
        auto sym_temp=sym_;
        kid3=node_factory::make_node(sym_);

        getsym();
        kid4=term();
        kid_temp=kid3->make_siblings(kid4);
        if(sym_temp==Token_name::plus){
            code_generator_.emit_instruction(Operation_code::ADD);
        }else if(sym_temp==Token_name::minus){
            code_generator_.emit_instruction(Operation_code::SUB);
        }
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
        auto sym_temp = sym_;
        getsym();
        kid3=factor();
        if(kid_temp== nullptr){
            kid_temp=kid2->make_siblings(kid3);
        } else{
            kid_temp=kid_temp->make_siblings(kid2)->make_siblings(kid3);
        }

        if (sym_temp == Token_name::times) {
            code_generator_.emit_instruction(Operation_code::MUL);
        } else if (sym_temp == Token_name::slash) {
            code_generator_.emit_instruction(Operation_code::DIV);
        }
    }

    return node_factory::make_family(Token_name::term,factor_,kid_temp);
}


auto syntax_analysis::factor()->std::shared_ptr<abstract_node<symbol::Token_name>>{


    std::shared_ptr<abstract_node<Token_name >> kid= nullptr;
    auto temp=current_token_;
    if(is_the_beginning_of(Non_terminator::function_call)){
        kid=function_call();

    }else if(sym_==Token_name ::number,accept(Token_name::number)){

        kid=node_factory::make_node(Token_name::number);
        code_generator_.emit_instruction(Operation_code::LIT,0,temp->visit_number());
    }else if(sym_==Token_name ::lparen,accept(Token_name::lparen)){
        kid=expression();
        expect(Token_name::rparen);

    }else if(sym_==Token_name ::ident,accept(Token_name::ident)){

        kid=node_factory::make_node(Token_name::ident);
        code_generator_.emit_instruction(Operation_code::LOD,temp->visit_string());

    }else{
        error("factor: syntax error");
    }

    return node_factory::make_family(Token_name::factor,kid);
}

auto syntax_analysis::function_call()->std::shared_ptr<abstract_node<symbol::Token_name>>{
     std::shared_ptr<abstract_node<Token_name >> func_name= nullptr;
     auto func_name1=current_token_->visit_string();
     if(accept(Token_name::ident)){
         expect(Token_name::lparen);
         expect(Token_name::rparen);
         func_name=node_factory::make_node(Token_name::ident);

         code_generator_.emit_instruction(Operation_code::CAL,func_name1);

     }else{
        error("function call:syntax error");
     }
     return node_factory::make_family(Token_name::call,func_name);
}
