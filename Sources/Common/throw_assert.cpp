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

void __throw_assert(bool condition, const char* conditionString) {
  if (condition == false) {
    if (!conditionString) {
      throw std::runtime_error("Assertion failed");
    } else {
      char message_str[256];
      message_str[0] = '\0';
      
      snprintf(message_str, 256, "Assertion failed: %s", conditionString);
      throw std::runtime_error(message_str);
    }
  }
}

// I really can not say whether it is safe or not
void __throw_assert_explain(bool condition, const char* conditionString, int additionalParametersCount, const char* format, ...) {
  if (condition == false) {
    if (!conditionString) {
      throw std::runtime_error("Assertion failed");
    }
    if (additionalParametersCount == 0) {
      char message_str[256];
      message_str[0] = '\0';
      
      if (format) {
        snprintf(message_str, 256, "Assertion failed: %s '%s'", conditionString, format);
        throw std::runtime_error(message_str);
      } else {
        snprintf(message_str, 256, "Assertion failed: %s", conditionString);
        throw std::runtime_error(message_str);
      }
    } else {
      char message_str[256];
      message_str[0] = '\0';
      
      va_list args;
      
      va_start(args, format);
      vsnprintf(message_str, 256, format, args);
      va_end(args);
      
      throw std::runtime_error(message_str);
    }
  }
}

