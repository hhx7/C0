//
// Created by pi on 17-12-10.
//
#include "simulator.h"
#include <iostream>
simulator::simulator(std::vector<instruction> &instructions)
:instructions_(instructions),
 current_instruction_pos_(0),
 instruction_base_address(0) {}
/*
 * |RA| store next instruction pos
 * |DL| store call point base address
 * |SL| point base address
 */
void simulator::run()
{
    std::cout<<("start C0\n");
    int top_value=0,second_top_value=0,read_value=0;
    unsigned long top_pointer=0;
    int parent_base_address=0;
    stack_.push(0);
    stack_.push(0);
    stack_.push(0);
    do{
        current_instruction_=instructions_.at(current_instruction_pos_);
        switch (current_instruction_.operation_code){
            case Operation_code ::LIT:   /* 将a的值取到栈顶 */
                stack_.push(current_instruction_.right_operation_num);
                break;
            case Operation_code ::LOD: /* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
                stack_.push(get_variant_from(current_instruction_));
                break;
            case Operation_code ::STO:/* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
                top_value=stack_.top();
                store_value_to_address_from(current_instruction_,top_value);
                stack_.pop();
                break;
            case Operation_code ::CAL:
                /* 调用子过程 */
                parent_base_address= get_address_from(current_instruction_);
                stack_.push(parent_base_address);/* 将父过程基地址入栈 */
                top_pointer=stack_.get_top_pointer();
                stack_[top_pointer] = get_address_from(current_instruction_);
                stack_[top_pointer+1] = instruction_base_address; /* 将本过程基地址入栈，此两项用于base函数 */
                stack_[top_pointer+2] = current_instruction_pos_+1; /* 将指令指针入栈 */
                instruction_base_address = top_pointer;  /* 改变基地址指针值为新过程的基地址 */
                current_instruction_pos_ = current_instruction_.right_operation_num;    /* 跳转 */
                break;

            case Operation_code ::INT:  /* 分配内存 */
                stack_.alloc_space(current_instruction_.right_operation_num);
                break;
            case Operation_code ::JMP:   /* 直接跳转 */

                current_instruction_pos_=current_instruction_.right_operation_num;
                break;
            case Operation_code ::JPC:   /* 条件跳转 */
                if (stack_.top() == 0)
                {
                    current_instruction_pos_=current_instruction_.right_operation_num;
                }
                break;
            case Operation_code ::ADD:
                top_value=stack_.top();
                stack_.pop();
                second_top_value=stack_.top();
                stack_.pop();
                stack_.push(top_value+second_top_value);
                break;
            case Operation_code ::SUB:
                top_value=stack_.top();
                stack_.pop();
                second_top_value=stack_.top();
                stack_.pop();
                stack_.push(second_top_value-top_value);
                break;
            case Operation_code ::MUL:
                top_value=stack_.top();
                stack_.pop();
                second_top_value=stack_.top();
                stack_.pop();
                stack_.push(second_top_value*top_value);
                break;
            case Operation_code ::DIV:
                top_value=stack_.top();
                stack_.pop();
                second_top_value=stack_.top();
                stack_.pop();
                stack_.push(second_top_value/top_value);
                break;
            case Operation_code ::RED:
                std::cin>>read_value;
                stack_.push(read_value);
                break;
            case Operation_code ::WRT:
                std::cout<<stack_.top()<<"\n";
                stack_.pop();
                break;
            case Operation_code ::RET:
                stack_.jump_to(instruction_base_address);
                auto stack_top_pointer=stack_.get_top_pointer();
                instruction_base_address=stack_[stack_top_pointer+1];
                current_instruction_pos_=stack_[stack_top_pointer+2];

                break;
        }
    }while (current_instruction_pos_!=0);

}


int simulator::get_variant_from(instruction &current_instruction) {

    unsigned base_address= get_address_from(current_instruction);
    return stack_[base_address];
}

/* 通过过程基址求上l层过程的基址 */
unsigned simulator::get_address_from(instruction &current_instruction) {
    int level=current_instruction.left_operation_num;
    int base_address=instruction_base_address;
    while (level-- > 0)
    {
        base_address = stack_[base_address];
    }
    return base_address+current_instruction.right_operation_num;
}

void simulator::store_value_to_address_from(instruction &current_instruction, int value) {
    unsigned base_address= get_address_from(current_instruction);
    stack_[base_address]=value;
}