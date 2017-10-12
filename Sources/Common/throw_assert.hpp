//
//  throw_assert.hpp
//  Common
//
//  Created by Bro on 10/11/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef throw_assert_hpp
#define throw_assert_hpp

#include "define_parameters_amount.hpp"

// Asserts that throw an exception if condition is false
#define throw_assert_explain(__condition__, ...) \
__throw_assert_explain( (bool)(__condition__), #__condition__, PP_NARG(__VA_ARGS__), __VA_ARGS__ )

#define throw_assert(__condition__) \
__throw_assert( (bool)(__condition__), #__condition__, )


void __throw_assert(bool condition, const char* conditionString);
void __throw_assert_explain(bool condition, const char* conditionString, int additionalParametersCount, const char* format, ...)
#ifdef __GNUC__
__attribute__((format(printf, 4, 5))) // compiler will tell if the format parameters are wrong
#endif
;

#endif /* throw_assert_hpp */
