//
// Created by hs on 14.04.17.
//
#pragma once

#include <string>
#include <vector>

namespace Math
{
    
    class CBigInt {
    private:
        std::string m_Representation;
        bool m_IsSigned = false;
        
    private:
        bool less(CBigInt _a, CBigInt _b) const;
        std::string removeLeadingZeros(std::string _input) const;
        CBigInt karatsubaMultiplication(const CBigInt &_arg1, const CBigInt &_arg2);
        CBigInt simpleMultiplication(const CBigInt &_smallArg, const CBigInt &_largerArg);
        CBigInt multPow10(size_t _exponent, CBigInt &_multiplicand);
        void split(const CBigInt &_inputNumber, size_t _at, CBigInt &_highOrder, CBigInt &_lowOrder);
        CBigInt expBySquaring(CBigInt &_base, CBigInt &_exponent);
        CBigInt simpleModulo(CBigInt &_dividend, CBigInt &_divisor);
        CBigInt simpleFlooredDivision(CBigInt _dividend, const CBigInt &_divisor);
        CBigInt simpleCeiledDivision(CBigInt _dividend, const CBigInt &_divisor);
        
    public:
        // Constructors
        CBigInt();
        //CBigInt(CBigInt& _bigInt);
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
        CBigInt operator* (CBigInt _other);
        CBigInt operator/ (const CBigInt& _other);
        CBigInt operator% (CBigInt& _other);
        CBigInt operator^ (const CBigInt& _other);
        
        //unary minus creates a new instance
        CBigInt operator- ();
        
        // prefix
        CBigInt& operator++ ();
        CBigInt& operator-- ();
        // postfix
        CBigInt operator++ (int);
        CBigInt operator-- (int);

    public:
        // utility functions
        const bool getSign() const;
        const std::string& getNumber() const;
        CBigInt ceiledDivision(CBigInt &_dividend, const CBigInt &_divisor);
        const bool isEven() const;
        const bool isPrime() const;

    public:
        static CBigInt modularExponentiation(CBigInt &_base, CBigInt _exponent, CBigInt &_mod);
        
    
    }; // class CBigInt
    
    template<>
    inline CBigInt& CBigInt::operator=(CBigInt const &_other)
    {
        m_Representation = _other.getNumber();
        m_IsSigned = _other.getSign();
        return *this;
    }
} // namespace Math