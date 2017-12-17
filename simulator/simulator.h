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

    unsigned get_address_from(instruction &current_instruction);
    void store_value_to_address_from(instruction& current_instruction,int value);

private:
    std::vector<instruction> instructions_;
    stack<int> stack_;
    instruction current_instruction_;
    unsigned current_instruction_pos_;
    unsigned instruction_base_address;

};
#endif //C0_SIMULATOR_H
