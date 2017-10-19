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
    const CBigInt CBigInt::ZERO = new CBigInt(0);
    const CBigInt CBigInt::ONE = new CBigInt(1);
    
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
            CBigInt temp = new CBigInt(_other.getNumber());
            m_IsSigned = !m_IsSigned;
            return -(*this + temp);
        }
        if (!m_IsSigned && _other.getSign()) {
            CBigInt temp = new CBigInt(_other.getNumber());
            return *this + temp;
        }
        if (m_IsSigned && _other.getSign()) {
            CBigInt temp = new CBigInt(_other.getNumber());
            m_IsSigned = !m_IsSigned;
            return temp - *this;
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
        if (_other == ZERO || *this == ZERO) return ZERO;
        
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
        if (_arg1.getNumber().length() <= 1)
        {
            return simpleMultiplication(_arg1, _arg2);
        }
        else if (_arg2.getNumber().length() <= 1)
        {
            return simpleMultiplication(_arg2, _arg1);
        }
        
        std::string result;
        std::string num1 = _arg1.getNumber();
        std::string num2 = _arg2.getNumber();
        
        size_t maxLength = num1.length() > num2.length() ? num1.length() : num2.length();
        
        size_t b = 10 ^ (maxLength / 2);
        std::string x1 = "";
    }
    
    CBigInt CBigInt::simpleMultiplication(CBigInt &_smallArg, CBigInt &_largerArg) {
        assert(_smallArg.getNumber().length() <= 1);
        
        if (_smallArg == ZERO || _largerArg == ZERO) return *(new CBigInt(0));
        
        CBigInt tmp = new CBigInt();
        for (CBigInt i = 0; i < _smallArg; ++i)
        {
            tmp = tmp + _largerArg;
        }
        
        return tmp;
    }
}