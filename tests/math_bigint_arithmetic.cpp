#include <gtest/gtest.h>
#include "../include/math_bigint.h"

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

TEST(arithmeticOperator, simpleMultiplicationNegative) {
    Math::CBigInt bigInt = new Math::CBigInt("-4");
    Math::CBigInt bigInt2 = new Math::CBigInt("2");
    Math::CBigInt result = new Math::CBigInt();
    
    result = bigInt * bigInt2;
    
    ASSERT_EQ(result.getNumber(), "8");
    ASSERT_TRUE(result.getSign());
    
    bigInt2 = -2;
    result = bigInt * bigInt2;
    
    ASSERT_EQ(result.getNumber(), "8");
    ASSERT_FALSE(result.getSign());
    
    bigInt = -2;
    bigInt2 = 4;
    result = bigInt * bigInt2;
    ASSERT_EQ(result.getNumber(), "8");
    ASSERT_TRUE(result.getSign());
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

TEST(arithmeticOperator, simpleFlooredDivision) {
    Math::CBigInt bigInt = new Math::CBigInt("5");
    Math::CBigInt bigInt2 = new Math::CBigInt("2");
    Math::CBigInt res = new Math::CBigInt();
    
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "2");
    ASSERT_FALSE(res.getSign());
    
    bigInt = -5;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "3");
    ASSERT_TRUE(res.getSign());
    
    bigInt2 = -2;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "2");
    ASSERT_FALSE(res.getSign());
    
    bigInt = 5;
    res = bigInt / bigInt2;
    ASSERT_EQ(res.getNumber(), "3");
    ASSERT_TRUE(res.getSign());
}

TEST(arithmeticOperator, simpleCeiledDivision) {
    Math::CBigInt bigInt = new Math::CBigInt("5");
    Math::CBigInt bigInt2 = new Math::CBigInt("2");
    Math::CBigInt res = new Math::CBigInt();
    
    res = res.ceiledDivision(bigInt, bigInt2);
    ASSERT_EQ(res.getNumber(), "3");
    ASSERT_FALSE(res.getSign());
    
    bigInt = -5;
    res = res.ceiledDivision(bigInt, bigInt2);
    ASSERT_EQ(res.getNumber(), "2");
    ASSERT_TRUE(res.getSign());
    
    bigInt2 = -2;
    res = res.ceiledDivision(bigInt, bigInt2);
    ASSERT_EQ(res.getNumber(), "3");
    ASSERT_FALSE(res.getSign());
    
    bigInt = 5;
    res = res.ceiledDivision(bigInt, bigInt2);
    ASSERT_EQ(res.getNumber(), "2");
    ASSERT_TRUE(res.getSign());
}

TEST(arithmeticOperator, modulo) {
    Math::CBigInt bigInt = new Math::CBigInt("11");
    Math::CBigInt bigInt2 = new Math::CBigInt("5");
    Math::CBigInt res = new Math::CBigInt();
    
    
    res = bigInt % bigInt2;
    ASSERT_EQ(res.getNumber(), "1");
    ASSERT_FALSE(res.getSign());
    
    bigInt = -11;
    res = bigInt % bigInt2;
    ASSERT_EQ(res.getNumber(), "4");
    ASSERT_FALSE(res.getSign());
    
    bigInt = 11;
    bigInt2 = -5;
    res = bigInt % bigInt2;
    ASSERT_EQ(res.getNumber(), "4");
    ASSERT_TRUE(res.getSign());
    
    bigInt = -11;
    res = bigInt % bigInt2;
    ASSERT_EQ(res.getNumber(), "1");
    ASSERT_TRUE(res.getSign());
}

TEST(arithmeticOperator, exponentiation) {
    Math::CBigInt bigInt = new Math::CBigInt("2");
    Math::CBigInt bigInt2 = new Math::CBigInt("3");
    Math::CBigInt res = new Math::CBigInt();
    
    res = bigInt ^ bigInt2;
    ASSERT_EQ(res.getNumber(), "8");
    
    bigInt = 2;
    bigInt2 = 50;
    res = bigInt ^ bigInt2;
    
    ASSERT_EQ(res.getNumber(), "1125899906842624");
    
    bigInt = 15;
    bigInt2 = 25;
    res = bigInt ^ bigInt2;
    
    ASSERT_EQ(res.getNumber(), "252511682940423488616943359375");
}

TEST(arithmeticOperator, fastModularExponentiation) {
    Math::CBigInt base = new Math::CBigInt("4");
    Math::CBigInt exponent = new Math::CBigInt("13");
    Math::CBigInt mod = new Math::CBigInt("497");
    Math::CBigInt res = new Math::CBigInt();
    
    res = Math::CBigInt::modularExponentiation(base, exponent, mod);
    ASSERT_EQ(res.getNumber(), "445");
    
    base = 13;
    exponent = 2345;
    mod = 5;
    res = Math::CBigInt::modularExponentiation(base, exponent, mod);
    ASSERT_EQ(res.getNumber(), "3");
    
    base = 519230;
    exponent = 841;
    mod = 67;
    res = Math::CBigInt::modularExponentiation(base, exponent, mod);
    ASSERT_EQ(res.getNumber(), "55");
}