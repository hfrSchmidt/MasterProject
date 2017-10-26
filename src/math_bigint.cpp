//
// Created by hs on 14.04.17.
//

#include <cstring>
#include <cstdlib>
#include <cassert>
#include "../include/math_bigint.h"

#include <iostream>

namespace Math
{
    // ---------------------------------------------------------------------------------
    // BEGIN constructors
    CBigInt::CBigInt()
    {
        m_Representation = "0";
        m_IsSigned = false;
    }
    
    /*
    CBigInt::CBigInt(CBigInt &_bigInt)
    {
        m_Representation = _bigInt.getNumber();
        m_IsSigned = _bigInt.getSign();
    }*/
    
    CBigInt::CBigInt(CBigInt *_bigInt)
    {
        m_Representation = _bigInt->getNumber();
        m_IsSigned = _bigInt->getSign();
    }
    
    CBigInt::CBigInt(const char *_string)
    {
        if (!isdigit(_string[0])) m_IsSigned = !m_IsSigned;
        
        for (int i = 0; i < strlen(_string); i++)
        {
            if (isdigit(_string[i]))
            {
                m_Representation.push_back(_string[i]);
            }
        }
        m_Representation = removeLeadingZeros(m_Representation);
    }
    
    CBigInt::CBigInt(std::string _string)
    {
        if (!isdigit(_string.at(0)))
        {
            m_IsSigned = !m_IsSigned;
            m_Representation = removeLeadingZeros(_string.substr(1));
        } else
        {
            m_Representation = removeLeadingZeros(_string);
        }
    }
    
    CBigInt::CBigInt(int _number)
    {
        m_Representation = std::to_string(_number);
        if (_number < 0)
        {
            m_IsSigned = true;
            m_Representation = m_Representation.substr(1);
        }
    }
    
    CBigInt::CBigInt(long _number)
    {
        m_Representation = std::to_string(_number);
        if (_number < 0)
        {
            m_IsSigned = true;
            m_Representation = m_Representation.substr(1);
        }
    }
    
    CBigInt::CBigInt(long long _number)
    {
        m_Representation = std::to_string(_number);
        if (_number < 0)
        {
            m_IsSigned = true;
            m_Representation = m_Representation.substr(1);
        }
    }
    
    
    // END constructors
    // ---------------------------------------------------------------------------------
    
    // ---------------------------------------------------------------------------------
    // BEGIN operators
    
    // unary minus operator returns a copy
    CBigInt CBigInt::operator-() {
        CBigInt tmp = new CBigInt(this);
        if (tmp.getNumber() != "0") {
            tmp.m_IsSigned = !tmp.m_IsSigned;
        }
        return tmp;
    }
    
    // prefix increment operators directly modify the original value without first copying it.
    CBigInt& CBigInt::operator++() {
        *this += 1;
        return *this;
    }
    
    CBigInt& CBigInt::operator--() {
        *this -= 1;
        return *this;
    }
    
    // postfix increment operators always return a copy of the value before the operation took place.
    // The original value is however altered.
    CBigInt CBigInt::operator++(int) {
        CBigInt copy(*this);
        *this += 1;
        return copy;
    }
    
    CBigInt CBigInt::operator--(int) {
        CBigInt copy(*this);
        *this -= 1;
        return copy;
    }
    
    CBigInt CBigInt::operator+(const CBigInt &_other) {
        
        if (m_IsSigned && !_other.getSign()) {
            m_IsSigned = !m_IsSigned;
            return *(new CBigInt(_other)) - *this;
        }
        if (!m_IsSigned && _other.getSign()) {
            CBigInt temp = new CBigInt(_other);
            temp.m_IsSigned = !temp.m_IsSigned;
            return *this - temp;
        }
        if (m_IsSigned && _other.getSign()) {
            CBigInt temp = new CBigInt(_other);
            temp.m_IsSigned = !temp.m_IsSigned;
            m_IsSigned = !m_IsSigned;
            return -(*this + temp);
        }
        
        int carry = 0;
        int intermediate = 0;
        std::string result;
        
        
        size_t len_max = _other.getNumber().length();
        size_t len_min = m_Representation.length();
        bool otherIsLarger = _other > this;
        if (!otherIsLarger) {
            len_max = m_Representation.length();
            len_min = _other.getNumber().length();
        }
        
        for (size_t i = 0; i < len_max; i++) {
            if (i >= len_min) {
                if (carry != 0) {
                    if (otherIsLarger) intermediate = _other.getNumber().at(len_max - i - 1) - '0';
                    else intermediate = m_Representation.at(len_max - i - 1) - '0';
                    intermediate += carry;
                    carry = 0;
                    if (intermediate > 9) {
                        carry = 1;
                        intermediate -= 10;
                    }
                    result.insert(0, 1, (char)(intermediate + '0'));
                    continue;
                }
                if (otherIsLarger) {
                    result.insert(0, _other.getNumber().substr(0, len_max - i));
                } else {
                    result.insert(0, m_Representation.substr(0, len_max - i));
                }
                break;
            }
            if (carry > 0) {
                intermediate += carry;
                carry = 0;
            }
            if (otherIsLarger) {
                intermediate += (m_Representation.at(len_min - i - 1) - '0')
                                + (_other.getNumber().at(len_max - i - 1) - '0');
            } else {
                intermediate += (m_Representation.at(len_max - i - 1) - '0')
                                + (_other.getNumber().at(len_min - i - 1) - '0');
            }
            if (intermediate > 9) {
                carry = 1;
                intermediate -= 10;
            }
            result.insert(0, 1, (char)('0' + intermediate));
            //result.push_back((char)('0' + intermediate));
            intermediate = 0;
        }
        if (carry) result.insert(0, 1, (char)('0' + carry));
        return new CBigInt(result);
    }
    
    // m_IsSigned = true --> negative
    // m_IsSigned = false --> positive
    
    CBigInt CBigInt::operator-(const CBigInt &_other) {
        
        if (m_IsSigned && !_other.getSign())
        {
            // newly constructed CBigInts are always positive. Therefor constructing a CBigInt only from the pure
            // number-string of another results in the absolute value of the other CBigInt.
            CBigInt temp = new CBigInt(_other.getNumber());
            return -(-*this + temp);
        }
        if (!m_IsSigned && _other.getSign()) {
            CBigInt temp = new CBigInt(_other.getNumber());
            return *this + temp;
        }
        if (m_IsSigned && _other.getSign()) {
            CBigInt temp = new CBigInt(_other.getNumber());
            return temp - -*this;
        }
        
        short borrow = 0;
        int intermediate = 0;
        std::string result;
    
        size_t len_max = _other.getNumber().length();
        size_t len_min = m_Representation.length();
        bool otherIsLarger = _other > this;
        if (!otherIsLarger) {
            len_max = m_Representation.length();
            len_min = _other.getNumber().length();
        }
    
        CBigInt first_operand;
        CBigInt second_operand;
        if (otherIsLarger) {
            first_operand = _other;
            second_operand = this;
        }
        else {
            first_operand = this;
            second_operand = _other;
        }
        
        assert(first_operand >= second_operand);
        
        for (size_t i = 0; i < len_max; i++) {
            
            if (i >= len_min)
            {
                if (borrow < 1)
                {
                    result.insert(0, 1, first_operand.getNumber().at(len_max - i - 1));
                    continue;
                }
                intermediate = (first_operand.getNumber().at(len_max - i - 1) - '0') - borrow;
                borrow = 0;
                if (intermediate < 0)
                {
                    borrow += 1;
                    intermediate += 10;
                }
                result.insert(0, 1, (char) ('0' + intermediate));
                continue;
            }
            
            intermediate = (first_operand.getNumber().at(len_max - i - 1) - '0') -
                    (second_operand.getNumber().at(len_min - i - 1) - '0') - borrow;
            
            borrow = 0;
            if (intermediate < 0) {
                borrow++;
                intermediate += 10;
            }
            
            result.insert(0, 1, (char) ('0' + intermediate));
        }
        if (otherIsLarger) result.insert(0, 1, '-');
        return new CBigInt(result);
    }
    
    CBigInt CBigInt::operator*(CBigInt &_other) {
        CBigInt zero = new CBigInt(0);
        if (_other == zero || *this == zero) return zero;
        
        return karatsubaMultiplication(*this, _other);
    }
    
    bool CBigInt::operator==(const CBigInt& _rhs) const {
        return m_Representation == _rhs.m_Representation &&
               m_IsSigned == _rhs.m_IsSigned;
    }
    
    bool CBigInt::operator!=(const CBigInt& _rhs) const {
        return !(_rhs == *this);
    }
    
    bool CBigInt::operator<(const CBigInt& _rhs) const {
        return less((*this), _rhs);
    }
    
    bool CBigInt::operator>(const CBigInt& _rhs) const {
        return _rhs < *this;
    }
    
    bool CBigInt::operator<=(const CBigInt& _rhs) const {
        return !(_rhs < *this);
    }
    
    bool CBigInt::operator>=(const CBigInt& _rhs) const {
        return !(*this < _rhs);
    }
    
    // END operators
    // ---------------------------------------------------------------------------------
    
    
    const bool& CBigInt::getSign() const {
        return m_IsSigned;
    }
    
    const std::string& CBigInt::getNumber() const {
        return m_Representation;
    }
    
    // is the first argument less than the second?
    bool CBigInt::less(CBigInt _a, CBigInt _b) const {
        if (_a.getSign() && _b.getSign()) return less(-_b, -_a);
        if (_a.getSign()) return true;
        if (_b.getSign()) return false;
        
        if (_a.getNumber().length() > _b.getNumber().length())
            return false;
        if (_a.getNumber().length() < _b.getNumber().length())
            return true;
        
        for (unsigned long i = 0; i < _a.getNumber().length(); ++i)
        {
            if (_a.getNumber().at(i) - '0' > _b.getNumber().at(i) - '0') return false;
            if (_a.getNumber().at(i) - '0' < _b.getNumber().at(i) - '0') return true;
        }
        return false;
    }
    
    std::string CBigInt::removeLeadingZeros(const std::string _input) const {
        size_t foundNonZero = _input.find_first_not_of('0');
        if (foundNonZero != std::string::npos)
            return _input.substr(foundNonZero);
        return "0";
    }
    
    
    CBigInt CBigInt::karatsubaMultiplication(CBigInt &_arg1, CBigInt &_arg2) {
        if (_arg1.getNumber().length() <= 2)
        {
            return simpleMultiplication(_arg1, _arg2);
        }
        else if (_arg2.getNumber().length() <= 2)
        {
            return simpleMultiplication(_arg2, _arg1);
        }
        
        CBigInt result;
        std::string num1 = _arg1.getNumber();
        std::string num2 = _arg2.getNumber();
        
        size_t maxLength, minLength;
        if (num1.length() > num2.length()) {
            maxLength = num1.length();
            minLength = num2.length();
        } else {
            maxLength = num2.length();
            minLength = num1.length();
        }
        
        size_t halfMaxLength = (maxLength) / 2;
        /*
        if (maxLength % 2) {
            halfMaxLength = (maxLength + 1) / 2;
        }*/
        if (halfMaxLength >= minLength) {
            halfMaxLength = minLength - 1;
        }
        
        CBigInt high1, low1, high2, low2;
        split(_arg1, halfMaxLength, high1, low1);
        split(_arg2, halfMaxLength, high2, low2);
        
        CBigInt lowHigh1 = low1 + high1;
        CBigInt lowHigh2 = low2 + high2;
        
        CBigInt z0 = karatsubaMultiplication(low1, low2);
        CBigInt z1 = karatsubaMultiplication(lowHigh1, lowHigh2);
        CBigInt z2 = karatsubaMultiplication(high1, high2);
        
        CBigInt z1z2z0 = z1 - z2 - z0;
        
        size_t m2 = (_arg1.getNumber().length()-high1.getNumber().length())
                    + (_arg2.getNumber().length()-high2.getNumber().length());
        
        return (multPow10(m2, z2) + multPow10(m2/2, z1z2z0) + z0);
    }
    
    CBigInt CBigInt::multPow10(size_t _exponent, CBigInt &_multiplicand) {
        CBigInt result(_multiplicand);
        result.m_Representation.append(_exponent, '0');
        return result;
    }
    
    
    // splits the given input string into two substrings at the position "_at" counting from the right (end) of the
    // original string. E.g. when _inputNumber = 1234567, _at = 2 then _highOrder = 1234 and _lowOrder = 567
    
    void CBigInt::split(CBigInt &_inputNumber, size_t _at, CBigInt &_highOrder, CBigInt &_lowOrder) {
        size_t inputLength = _inputNumber.getNumber().length();
        // substr extracts the string starting at the first argument and ending with the character at first + second
        // i.e. _highOrder = _inputNumber[first, second]. Endpoints are included in the interval.
        // If no second argument is given it extracts the string starting at the first argument until the end.
        _highOrder = new CBigInt(_inputNumber.getNumber().substr(0, inputLength - _at)); // - 1 is problematic
        try {
            _lowOrder = new CBigInt(_inputNumber.getNumber().substr(inputLength - _at));
            
            //std::cout << "1st: " << _highOrder.getNumber() << "\t2nd: " << _lowOrder.getNumber() << std::endl;
            
        } catch (const std::out_of_range &e) {
            std::cerr << "Split is out of range. Continuing with zero as second argument." << std::endl;
            _lowOrder = new CBigInt(0);
        }
    }
    
    CBigInt CBigInt::simpleMultiplication(CBigInt &_smallArg, CBigInt &_largerArg) {
        assert(_smallArg.getNumber().length() <= 2);
        CBigInt tmp = new CBigInt();
        
        for (CBigInt i = 0; i < _smallArg; ++i)
        {
            tmp += _largerArg;
        }
        
        return tmp;
    }
}