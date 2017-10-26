#include "gtest/gtest.h"
#include "../include/math_bigint.h"

// BEGIN constructor tests
// ---------------------------------------------------------------------------------

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

// END constructor tests
// ---------------------------------------------------------------------------------
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
// ---------------------------------------------------------------------------------
// BEGIN comparison operator tests

TEST(comparisonOperator, less)
{
    Math::CBigInt bigInt1 = new Math::CBigInt();
    Math::CBigInt bigInt2 = new Math::CBigInt(3);
    
    ASSERT_TRUE(bigInt1 < bigInt2);
    
    bigInt1 = -3;
    ASSERT_TRUE(bigInt1 < bigInt2);
    
    bigInt2 = -6;
    ASSERT_TRUE(bigInt2 < bigInt1);
    
    bigInt1 = -6;
    ASSERT_FALSE(bigInt1 < bigInt2);
    
    // validate that removing of leading zeros works
    bigInt2 = "-00008";
    ASSERT_TRUE(bigInt2 < bigInt1);
    
}

TEST(comparisonOperator, lessBigNum)
{
    Math::CBigInt bigInt = new Math::CBigInt("123456789123456789123456789123456789123456789123456789");
    Math::CBigInt bigInt2 = new Math::CBigInt("123456789123456789123456789123456789123456789123456789123456789");
    
    ASSERT_TRUE(bigInt < bigInt2);
}

TEST(comparisonOperator, greater)
{
    Math::CBigInt bigInt1 = new Math::CBigInt();
    Math::CBigInt bigInt2 = new Math::CBigInt(3);
    
    ASSERT_FALSE(bigInt1 > bigInt2);
    
    bigInt1 = -3;
    ASSERT_FALSE(bigInt1 > bigInt2);
    
    bigInt2 = -6;
    ASSERT_FALSE(bigInt2 > bigInt1);
    
    bigInt1 = -6;
    ASSERT_FALSE(bigInt1 > bigInt2);
}

TEST(comparisonOperator, equal)
{
    Math::CBigInt bigInt1 = new Math::CBigInt();
    Math::CBigInt bigInt2 = new Math::CBigInt(3);
    ASSERT_FALSE(bigInt1 == bigInt2);
    
    bigInt1 = 3;
    ASSERT_TRUE(bigInt1 == bigInt2);
    
    bigInt1 = -1;
    bigInt2 = bigInt1;
    ASSERT_TRUE(bigInt1 == bigInt2);
}

TEST(comparisonOperator, notEqual)
{
    Math::CBigInt bigInt1 = new Math::CBigInt();
    Math::CBigInt bigInt2 = new Math::CBigInt(3);
    ASSERT_TRUE(bigInt1 != bigInt2);
    
    bigInt1 = 3;
    ASSERT_FALSE(bigInt1 != bigInt2);
    
    bigInt1 = -1;
    bigInt2 = bigInt1;
    ASSERT_FALSE(bigInt1 != bigInt2);
    
    bigInt1 = 1;
    ASSERT_TRUE(bigInt1 != bigInt2);
}

TEST(comparisonOperator, greaterOrEqual)
{
    Math::CBigInt bigInt1 = new Math::CBigInt();
    Math::CBigInt bigInt2 = new Math::CBigInt(3);
    ASSERT_FALSE(bigInt1 >= bigInt2);
    
    bigInt1 = 3;
    ASSERT_TRUE(bigInt1 >= bigInt2);
    
    ASSERT_TRUE(bigInt1 >= -bigInt2);
}

TEST(comparisonOperator, lessOrEqual)
{
    Math::CBigInt bigInt1 = new Math::CBigInt();
    Math::CBigInt bigInt2 = new Math::CBigInt(3);
    ASSERT_TRUE(bigInt1 <= bigInt2);
    
    bigInt1 = 3;
    ASSERT_TRUE(bigInt1 <= bigInt2);
    
    ASSERT_FALSE(bigInt1 <= -bigInt2);
}

// END comparison operator tests
// ---------------------------------------------------------------------------------
// BEGIN unary operator tests

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

// END unary operator tests
// ---------------------------------------------------------------------------------
// BEGIN arithmetic operator tests

TEST(arithmeticOperator, plus){
    
    Math::CBigInt bigInt = new Math::CBigInt("2");
    Math::CBigInt bigInt2 = new Math::CBigInt("4");
    Math::CBigInt bigInt3 = new Math::CBigInt();
    bigInt3 = bigInt + bigInt2;
    
    ASSERT_EQ(bigInt3.getNumber(), "6");
    
    bigInt2 = 3456;
    bigInt3 = bigInt + bigInt2;
    
    ASSERT_EQ(bigInt3.getNumber(), "3458");
    
    bigInt = 220544;
    bigInt3 = bigInt + bigInt2;
    
    ASSERT_EQ(bigInt3.getNumber(), "224000");
    
    bigInt = 10;
    bigInt3 = bigInt3 + bigInt;
    
    ASSERT_EQ(bigInt3.getNumber(), "224010");
    
    bigInt = 4;
    bigInt2 = 8;
    bigInt3 = bigInt + bigInt2;
    
    ASSERT_EQ(bigInt3.getNumber(), "12");
    
    bigInt = "10000";
    bigInt2 = "2800";
    bigInt3 = bigInt + bigInt2;
    ASSERT_EQ(bigInt3.getNumber(), "12800");
}

TEST(arithmeticOperator, minus) {
    
    Math::CBigInt bigInt = new Math::CBigInt("10");
    Math::CBigInt bigInt2 = new Math::CBigInt("4");
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "6");
    
    bigInt = new Math::CBigInt("1000");
    bigInt2 = new Math::CBigInt("999");
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "1");
    
    bigInt = new Math::CBigInt("10");
    bigInt2 = new Math::CBigInt("15");
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "5");
    ASSERT_TRUE((bigInt - bigInt2).getSign());
    
    bigInt = "100000";
    bigInt2 = "999";
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "99001");
    
    bigInt = "-5";
    bigInt2 = "5";
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "10");
    ASSERT_TRUE((bigInt - bigInt2).getSign());
    
    bigInt = "5";
    bigInt2 = "-5";
    
    ASSERT_EQ((bigInt - bigInt2).getNumber(), "10");
    ASSERT_FALSE((bigInt - bigInt2).getSign());
}

TEST(arithmeticOperator, simpleMultiplication) {
    Math::CBigInt bigInt = new Math::CBigInt("9");
    Math::CBigInt bigInt2 = new Math::CBigInt("4");
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "36");
    
    bigInt = "0";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "0");
    
    bigInt = 50;
    bigInt2 = 9L;
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "450");
}

TEST(arithmeticOperator, karatsubaMultiplication) {
    Math::CBigInt bigInt = new Math::CBigInt("10");
    Math::CBigInt bigInt2 = new Math::CBigInt("10");
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "100");
    
    bigInt = 27;
    bigInt2 = 124;
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "3348");
    
    bigInt = 105;
    bigInt2 = 123;
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "12915");
    
    bigInt = "12345";
    bigInt2 = "6789";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "83810205");
    
    bigInt = "123456789";
    bigInt2 = "987654321";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "121932631112635269");
    
    bigInt = "123456789";
    bigInt2 = "987";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "121851850743");
    
    bigInt = "812398458302402349812093848";
    bigInt2 = "1232342341232459934812919";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "1001153018118023490350428987359513032114783550822312");
    
    bigInt2 = "123456789";
    bigInt = "987";
    
    ASSERT_EQ((bigInt * bigInt2).getNumber(), "121851850743");
}
// END arithmetic operator tests