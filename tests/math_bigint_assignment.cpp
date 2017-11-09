#include "gtest/gtest.h"
#include "../include/math_bigint.h"

// BEGIN assignment operator tests

TEST(assignmentOperator, assignmentCBigInt)
{
    Math::CBigInt bigInt = new Math::CBigInt();
    Math::CBigInt bigInt2 = new Math::CBigInt("-123");
    
    bigInt = bigInt2;
    ASSERT_EQ(bigInt.getNumber(), "123");
    ASSERT_EQ(bigInt.getSign(), true);
}

TEST(assignmentOperator, assignmentInteger)
{
    Math::CBigInt bigInt = new Math::CBigInt();
    bigInt = 12345;
    
    ASSERT_EQ(bigInt.getNumber(), "12345");
    ASSERT_EQ(bigInt.getSign(), false);
    
    bigInt = -12345;
    
    ASSERT_EQ(bigInt.getNumber(), "12345");
    ASSERT_EQ(bigInt.getSign(), true);
}

TEST(assignmentOperator, assignmentLong)
{
    Math::CBigInt bigInt = new Math::CBigInt();
    bigInt = 12345L;
    
    ASSERT_EQ(bigInt.getNumber(), "12345");
    ASSERT_EQ(bigInt.getSign(), false);
    
    bigInt = -12345L;
    
    ASSERT_EQ(bigInt.getNumber(), "12345");
    ASSERT_EQ(bigInt.getSign(), true);
}

TEST(assignmentOperator, assignmentLonglong)
{
    Math::CBigInt bigInt = new Math::CBigInt();
    bigInt = 12345LL;
    
    ASSERT_EQ(bigInt.getNumber(), "12345");
    ASSERT_EQ(bigInt.getSign(), false);
    
    bigInt = -12345LL;
    
    ASSERT_EQ(bigInt.getNumber(), "12345");
    ASSERT_EQ(bigInt.getSign(), true);
}

// END assignment operator tests
// ---------------------------------------------------------------------------------
// BEGIN compound assignment operator tests

TEST(compoundAssignmentOperator, plus)
{
    Math::CBigInt bigInt1 = new Math::CBigInt(1);
    Math::CBigInt bigInt2 = new Math::CBigInt(3);
    
    bigInt1 += bigInt2;
    
    ASSERT_EQ(bigInt1.getNumber(), "4");
    
    bigInt1 += 3;
    
    ASSERT_EQ(bigInt1.getNumber(), "7");
    
    bigInt1 += 3L;
    
    ASSERT_EQ(bigInt1.getNumber(), "10");
}

TEST(compoundAssignmentOperator, minus)
{
    Math::CBigInt bigInt1 = new Math::CBigInt(8);
    Math::CBigInt bigInt2 = new Math::CBigInt(3);
    
    bigInt1 -= bigInt2;
    
    ASSERT_EQ(bigInt1.getNumber(), "5");
    
    bigInt1 -= 3;
    
    ASSERT_EQ(bigInt1.getNumber(), "2");
    
    bigInt1 -= 5L;
    
    ASSERT_EQ(bigInt1.getNumber(), "3");
    ASSERT_TRUE(bigInt1.getSign());
}
// END compound assignment operator tests