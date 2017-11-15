#include <gtest/gtest.h>
#include "../include/math_bigint.h"


TEST(utilityFunction, isEven) {
    Math::CBigInt bigInt = 123;
    
    ASSERT_FALSE(bigInt.isEven());
    
    bigInt = "8740213471023740189273478";
    ASSERT_TRUE(bigInt.isEven());
    
    bigInt = -123;
    ASSERT_FALSE(bigInt.isEven());
    
    bigInt = "-8740213471023740189273478";
    ASSERT_TRUE(bigInt.isEven());
}

