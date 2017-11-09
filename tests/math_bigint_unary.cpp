#include <gtest/gtest.h>
#include "../include/math_bigint.h"


TEST(unaryOperator, minus)
{
    Math::CBigInt bigInt = new Math::CBigInt();
    bigInt = -bigInt;
    ASSERT_FALSE(bigInt.getSign());
    
    bigInt = 10;
    ASSERT_FALSE(bigInt.getSign());
    
    bigInt = -bigInt;
    ASSERT_TRUE(bigInt.getSign());
    
    bigInt = -10;
    ASSERT_TRUE(bigInt.getSign());
}

TEST(unaryOperator, incrementDecrement) {
    Math::CBigInt bigInt = new Math::CBigInt("10");
    
    ASSERT_EQ((++bigInt).getNumber(), "11");
    ASSERT_EQ((bigInt++).getNumber(), "11");
    ASSERT_EQ((--bigInt).getNumber(), "11");
    ASSERT_EQ((bigInt--).getNumber(), "11");
    ASSERT_EQ(bigInt.getNumber(), "10");
}