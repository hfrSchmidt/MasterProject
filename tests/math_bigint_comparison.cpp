#include <gtest/gtest.h>
#include "../include/math_bigint.h"

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