//
// Created by pi on 17-12-10.
//
#include <iomanip>
#include "code_generator.h"
void error(const char msg[]){
    throw std::runtime_error(msg);
}

unsigned int code_generator::emit_instruction(Operation_code op, unsigned level, unsigned addr) {

    codes_.emplace_back(op,level,addr);
    current_code_pos_=codes_.size()-1;

    return current_code_pos_;

}

code_generator::code_generator(symbol_table& st,std::vector<instruction>& codes):
        level_(0),addr_(0),current_code_pos_(0),symbol_table_(st),codes_(codes) {}

void code_generator::record_func_pos(const std::string& name) {
    ident_pos_.insert({name,current_code_pos_+1});
}

void code_generator::emit_instruction(operation_code::Operation_code code, const std::string name) {
    if(auto sym=symbol_table_.retrieve_symbol(name);sym!= nullptr){
        unsigned current_level=symbol_table_.get_depth();
        unsigned decl_level=sym->get_depth();
        unsigned level_diff=current_level-decl_level;
        unsigned func_begin_pos=0;
        switch (sym->get_symbol_type()){
            case Symbol_type ::variable:
                emit_instruction(code,level_diff,sym->get_var_pos()+2);
                break;
            case Symbol_type ::function:
                if(auto pos=ident_pos_.find(name);pos!=ident_pos_.end()){
                    emit_instruction(code,0,pos->second);
                }else{
                    //error("undefined function");
                }

                break;
            default:
                error("no exist this type");
        }


    }else{
        error("undefined ident");
    }
}


unsigned int code_generator::emit_instruction(operation_code::Operation_code op) {
    codes_.emplace_back(op,0,0);
    current_code_pos_=codes_.size()-1;

    return current_code_pos_;
}

void code_generator::complete_instruction(unsigned code_pos) {
    codes_.at(code_pos).right_operation_num=current_code_pos_+1;
}

void code_generator::complete_instruction(unsigned code_pos, unsigned right_op_num) {
    codes_.at(code_pos).right_operation_num=right_op_num+3;
}

void code_generator::print()const{
    using namespace std;
    const int space_size=20;
    cout<<endl;
    cout<<left<<setw(10)<<"pos"<<setw(space_size)<<"Operation_code"<<setw(space_size)<<"left_operation_num"<<setw(space_size)<<"right_operation_num"<<endl;
    int i=0;
    for(auto code:codes_){
        cout<<setw(10)<<i++<<setw(space_size)<<(int)code.operation_code<<setw(space_size)<<code.left_operation_num<<setw(space_size)<<code.right_operation_num<<endl;
    }
}

unsigned int code_generator::get_current_code_pos() const {
    return current_code_pos_;
}
