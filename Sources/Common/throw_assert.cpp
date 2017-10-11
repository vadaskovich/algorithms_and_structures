//
//  throw_assert.cpp
//  Common
//
//  Created by Bro on 10/11/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#include <stdexcept>
#include <cstdio>
#include <cstdarg>

#include "throw_assert.hpp"

// I really can not say whether it is safe or not
void __throw_assert(bool condition, const char* conditionString, ...) {
  if (condition == false) {
    char format_str[256];
    char message_str[256];
  
    va_list args;
    
    va_start(args, conditionString);
    vsnprintf(format_str, 256, "%s", args);
    vsnprintf(message_str, 256, format_str, args);
    va_end(args);

    throw std::runtime_error(message_str);
  }
}

