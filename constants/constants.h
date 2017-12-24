//
// Created by pi on 17-12-24.
//

#ifndef C0_CONSTANTS_H
#define C0_CONSTANTS_H

#include "function.h"
#include "operation_code.h"
#include "symbol.h"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const function::Return_type &type);

std::ostream &operator<<(std::ostream &os, const operation_code::Operation_code &type);

std::ostream &operator<<(std::ostream &os, const symbol::Symbol_type &type);

std::ostream &operator<<(std::ostream &os, const symbol::Token_name &type);

#endif //C0_CONSTANTS_H
