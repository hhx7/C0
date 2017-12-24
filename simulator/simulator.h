//
// Created by pi on 17-12-10.
//

#ifndef C0_SIMULATOR_H
#define C0_SIMULATOR_H

#include "instruction.h"
#include "stack.h"
#include <vector>
class simulator : virtual private operation_code{
public:
    simulator(std::vector<instruction>& instructions);
    void run();
private:
    int get_variant_from(instruction& current_instruction);

    unsigned get_base_address_from(const instruction&)const;
    unsigned get_address_from(const instruction &current_instruction)const;
    void store_value_to_address_from(const instruction& current_instruction,int value);

private:
    std::vector<instruction> instructions_;
    stack<int> stack_;
    instruction current_instruction_;
    unsigned current_instruction_pos_;
    unsigned static_address_pointer;

};
#endif //C0_SIMULATOR_H
