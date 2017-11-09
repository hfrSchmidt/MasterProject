#include "gtest/gtest.h"
#include "../include/math_bigint.h"


TEST(constructor, emptyConstructorWorks)
{
    const Math::CBigInt bigInt = Math::CBigInt();
    EXPECT_EQ(bigInt.getNumber(), "0");
    EXPECT_EQ(bigInt.getSign(), false);
}

TEST(constructor, stringNegative)
{
    Math::CBigInt bigInt = new Math::CBigInt("-123");
    Math::CBigInt bigInt2 = new Math::CBigInt(bigInt);
    
    EXPECT_EQ(bigInt2.getNumber(), "123");
    EXPECT_EQ(bigInt2.getSign(), true);
}

TEST(constructor, stringPositive)
{
    Math::CBigInt bigInt = new Math::CBigInt("123");
    Math::CBigInt bigInt2 = new Math::CBigInt(bigInt);
    
    EXPECT_EQ(bigInt2.getNumber(), "123");
    EXPECT_EQ(bigInt2.getSign(), false);
}

TEST(constructor, unsignedInteger)
{
    Math::CBigInt bigInt = new Math::CBigInt(123);
    
    EXPECT_EQ(bigInt.getNumber(), "123");
    EXPECT_EQ(bigInt.getSign(), false);
}

TEST(constructor, signedInteger)
{
    Math::CBigInt bigInt = new Math::CBigInt(-123);
    
    EXPECT_EQ(bigInt.getNumber(), "123");
    EXPECT_EQ(bigInt.getSign(), true);
}

TEST(constructor, characterArrayPositive)
{
    char bigInt[] = "456";
    Math::CBigInt bigIntFromChar = new Math::CBigInt(bigInt);
    
    EXPECT_EQ(bigIntFromChar.getNumber(), "456");
    EXPECT_EQ(bigIntFromChar.getSign(), false);
}

TEST(constructor, characterArrayNegative)
{
    char bigInt[] = "-456";
    Math::CBigInt bigIntFromChar = new Math::CBigInt(bigInt);
    
    EXPECT_EQ(bigIntFromChar.getNumber(), "456");
    EXPECT_EQ(bigIntFromChar.getSign(), true);
}

TEST(constructor, longPositive)
{
    Math::CBigInt bigInt = new Math::CBigInt(4353456L);
    
    EXPECT_EQ(bigInt.getNumber(), "4353456");
    EXPECT_EQ(bigInt.getSign(), false);
}

TEST(constructor, longNegative)
{
    Math::CBigInt bigInt = new Math::CBigInt(-4353456L);
    
    EXPECT_EQ(bigInt.getNumber(), "4353456");
    EXPECT_EQ(bigInt.getSign(), true);
}

TEST(constructor, longlongPositive)
{
    Math::CBigInt bigInt = new Math::CBigInt(4353444556LL);
    
    EXPECT_EQ(bigInt.getNumber(), "4353444556");
    EXPECT_EQ(bigInt.getSign(), false);
}

TEST(constructor, longlongNegative)
{
    Math::CBigInt bigInt = new Math::CBigInt(-4353444556LL);
    
    EXPECT_EQ(bigInt.getNumber(), "4353444556");
    EXPECT_EQ(bigInt.getSign(), true);
}