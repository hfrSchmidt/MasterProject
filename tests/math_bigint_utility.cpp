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


TEST(utilityFunction, isPrimeSmallPrimes) {
    Math::CBigInt bigInt = 13;
    
    ASSERT_TRUE(bigInt.isPrime());
    
    bigInt = 17;
    
    ASSERT_TRUE(bigInt.isPrime());
    
    bigInt = 2879;
    
    ASSERT_TRUE(bigInt.isPrime());
    
    bigInt = "3041";
    
    ASSERT_TRUE(bigInt.isPrime());
    
    bigInt = "21143";
    
    ASSERT_TRUE(bigInt.isPrime());
}

TEST(utilityFunction, isPrimeCarmichaelNumbers) {
    Math::CBigInt bigInt = 1729;
    
    ASSERT_FALSE(bigInt.isPrime());
    
    bigInt = 561;
    
    ASSERT_FALSE(bigInt.isPrime());
    
    bigInt = 1105;
    
    ASSERT_FALSE(bigInt.isPrime());
}

TEST(utilityFunction, isPrimeLargePrimes) {
    
    Math::CBigInt bigInt = 999331;
    
    ASSERT_TRUE(bigInt.isPrime());
    
    bigInt = "32416175167";
    
    ASSERT_TRUE(bigInt.isPrime());
    
    bigInt = "74838457648748954900050464578792347604359487509026452654305481";
    
    ASSERT_TRUE(bigInt.isPrime());
}

TEST(utilityFunction, generateRandom) {
    Math::CBigInt lo = 0;
    Math::CBigInt hi = "1238373293474293892938420938409283409823948";
    Math::CBigInt bigInt;
    
    for (size_t i = 0; i < 10; ++i) {
        Math::CBigInt::genRand(lo, hi, (unsigned long) i, bigInt);
        ASSERT_TRUE(bigInt < hi && bigInt > lo);
    }
}