//
//  throw_assert.hpp
//  Common
//
//  Created by Bro on 10/11/17.
//  Copyright © 2017 vadaskovich. All rights reserved.
//

#ifndef throw_assert_hpp
#define throw_assert_hpp

void __throw_assert(bool condition, const char* conditionString, ...);

// Asserts that throw an exception if condition is false
#define throw_assert_explain(__condition__, ...) \
__throw_assert( (bool)(__condition__), #__condition__, __VA_ARGS__ )

#define throw_assert(__condition__) \
__throw_assert( (bool)(__condition__), #__condition__ )

#endif /* throw_assert_hpp */
