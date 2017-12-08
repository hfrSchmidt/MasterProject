#pragma once

#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <gmpxx.h>

/*
defines the number of repetitions of the miller-rabin test
The probability of obtaining a false positive is 4^-l [1],
with l = No. of repetitions.
Therefore 10 repetitions yield an error probability of less than 9.54*10^-7,
which should be enough in this case of application.

[1] Dietzfelbinger, M. (2004) "Primality Testing in Polynomial Time - From
randomized algorithms to PRIMES is in P". Lecture Notes in Computer Science:3000.
Berlin: Springer-Verlag
*/
#define MR_REPETITIONS 10

namespace Math
{
    
    class CBigInt {
    private:
        std::string m_Representation;
        bool m_IsSigned = false;
        
    private:
        bool less(CBigInt _a, CBigInt _b) const;
        std::string removeLeadingZeros(std::string _input) const;
        CBigInt karatsubaMultiplication(const CBigInt &_arg1, const CBigInt &_arg2) const;
        CBigInt simpleMultiplication(const CBigInt &_smallArg, const CBigInt &_largerArg) const;
        
        // multiplies the multiplicand with 10^_exponent
        CBigInt multPow10(size_t _exponent, const CBigInt &_multiplicand) const;
        
        // splits the given input string into two substrings at the position "_at" counting from the right (end) of the
        // original string. E.g. when _inputNumber = 1234567, _at = 2 then _highOrder = 1234 and _lowOrder = 567
        void split(const CBigInt &_inputNumber, size_t _at, CBigInt &_highOrder, CBigInt &_lowOrder) const;
        
        // calculates _base ^ _exponent
        // time-complexity: O(log n) assuming constant time for multiplication and division
        CBigInt expBySquaring(CBigInt &_base, CBigInt &_exponent);
    
        /*
         * Throughout this implementation the definitions of modulus and remainder from the Ada'83 language specification
         * is used.
         * Integer division is defined as follows in this context:
         * A = (A/B)*B + (A rem B)
         * where (A rem B) has the sign of A and |(A rem B)| < B
         *
         * The result of the modulus operation (A mod B) is such that it has the sign of B and |(A mod B)| < B
         * Additionally for some Integer Value N the following holds:
         * A = B*N + (A mod B)
         *
         *  A   B   A/B   A rem B  A mod B     A     B    A/B   A rem B   A mod B
    
            10   5    2       0        0      -10     5    -2       0         0
            11   5    2       1        1      -11     5    -2      -1         4
            12   5    2       2        2      -12     5    -2      -2         3
            13   5    2       3        3      -13     5    -2      -3         2
            14   5    2       4        4      -14     5    -2      -4         1
        
            10  -5   -2       0        0      -10    -5     2       0         0
            11  -5   -2       1       -4      -11    -5     2      -1        -1
            12  -5   -2       2       -3      -12    -5     2      -2        -2
            13  -5   -2       3       -2      -13    -5     2      -3        -3
            14  -5   -2       4       -1      -14    -5     2      -4        -4
         * Source: http://archive.adaic.com/standards/83lrm/html/lrm-04-05.html
         */
        CBigInt simpleModulo(CBigInt &_dividend, CBigInt &_divisor);
        
        CBigInt longDivisionModulo(CBigInt &_dividend, CBigInt &_divisor) const;
        
        // The result of the floored division is the largest whole number smaller or equal to the result of the
        // division. E.g. 5 / 2 = 2, -5 / 2 = -3
        CBigInt simpleFlooredDivision(CBigInt _dividend, const CBigInt &_divisor) const;
        
        // implementation of the simple pen and paper division method taught in primary schools.
        CBigInt longDivision(CBigInt &_dividend, const CBigInt &_divisor, CBigInt &_result) const;
        
        CBigInt simpleCeiledDivision(CBigInt _dividend, const CBigInt &_divisor);
    
        // this primality test should not be used for large numbers, as it would be too computationally intensive.
        // Always returns composite (false) if *this is composite otherwise *this is prime.
        const bool simplePrimalityTest() const;
        
        // returns composite (false) if *this is composite, otherwise *this is probably prime
        // for details on the _repetitions argument see definition of MR_REPETITIONS.
        const bool millerRabin(size_t _repetitions) const;
        
    public:
        // Constructors
        CBigInt();
        CBigInt(CBigInt* _bigInt);
        CBigInt(const char* _string);
        CBigInt(std::string _string);
        CBigInt(int _number);
        CBigInt(long _number);
        CBigInt(long long _number);
        
    public:
        // operators
        template<typename T>
        CBigInt& operator=(T _other)
        {
            *this = CBigInt(_other);
            return *this;
        }
        
        template <typename T>
        CBigInt& operator+=(T _other)
        {
            *this = *this + CBigInt(_other);
            return *this;
        }
        
        template <typename T>
        CBigInt&operator-=(T _other)
        {
            *this = *this - CBigInt(_other);
            return *this;
        }
        
        // note: comparisons are only implemented for the CBigInt type.
        // comparisons with other types are done through constructing a new CBigInt object
        bool operator<(const CBigInt& _rhs) const;
        bool operator>(const CBigInt& _rhs) const;
        bool operator<=(const CBigInt& _rhs) const;
        bool operator>=(const CBigInt& _rhs) const;
        bool operator==(const CBigInt& _rhs) const;
        bool operator!=(const CBigInt& _rhs) const;
    
        CBigInt operator+ (const CBigInt& _other);
        CBigInt operator- (const CBigInt& _other);
        // for replacing the implementation of multiplication, division, modulo and exponentiation change the
        // respective function call in the operators.
        CBigInt operator* (CBigInt _other) const;
        CBigInt operator/ (const CBigInt& _other);
        CBigInt operator% (CBigInt& _other);
        CBigInt operator^ (const CBigInt& _other);
        
        //unary minus creates a new instance
        CBigInt operator- ();
        
        // prefix operators directly modify the original value without first copying it.
        CBigInt& operator++ ();
        CBigInt& operator-- ();
        // postfix operators always return a copy of the value before the operation took place.
        // The original value is however altered.
        CBigInt operator++ (int);
        CBigInt operator-- (int);

    public:
        // utility functions
        const bool getSign() const;
        const std::string& getNumber() const;
        
        // public interface to ceiledDivision for testing purposes.
        CBigInt ceiledDivision(CBigInt &_dividend, const CBigInt &_divisor);
        const bool isEven() const;
        
        // for further descriptions see simplePrimalityTest() and millerRabin()
        const bool isPrime() const;

    public:
        // calculates _base^_exponent % _mod
        // time-complexity: O(log N) assuming constant time for multiplication, division and modulo
        static CBigInt modularExponentiation(CBigInt &_base, CBigInt _exponent, CBigInt &_mod);
    
        // implementing a pseudo-random number generator would have exceeded the scope of this work. Therefore the
        // GMP library (GNU multiprecision library) has been used for this purpose.
        // The result of the calculation is stored in _target. For non-repeating results use a random value for _seed.
        static void genRand(CBigInt &_lowerBound, CBigInt &_upperBound, unsigned long _seed, CBigInt &_target);
    
    }; // class CBigInt
    
    template<>
    inline CBigInt& CBigInt::operator=(CBigInt const &_other)
    {
        m_Representation = _other.getNumber();
        m_IsSigned = _other.getSign();
        return *this;
    }
} // namespace Math