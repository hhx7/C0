//
// Created by pi on 17-12-10.
//

#ifndef C0_NATIVE_CODE_H
#define C0_NATIVE_CODE_H

#include <string>
#include "../constants/operation_code.h"

class instruction : virtual public operation_code{
public:
    Operation_code operation_code;
    int relative_address;
    int level;
    unsigned left_operation_num;
    unsigned right_operation_num;
public:
    instruction(Operation_code operation, unsigned arg1, unsigned arg2){
        operation_code=operation;
        this->left_operation_num=arg1;
        this->right_operation_num=arg2;
    }
    instruction(){
        operation_code=Operation_code ::NUL;
    }
};
#endif //C0_NATIVE_CODE_H
