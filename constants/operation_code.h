//
// Created by pi on 17-12-11.
//

#ifndef C0_OPERATION_CODE_H
#define C0_OPERATION_CODE_H
struct operation_code{
    enum class Operation_code{
        LIT,    LOD,    STO,
        CAL,    INT,    JMP,
        JPC,    ADD,    SUB,
        MUL,    DIV,    RED,
        WRT,    RET,    NUL
    };
};
#endif //C0_OPERATION_CODE_H
