//
// Created by hs on 14.04.17.
//

#include "../include/math_bigint.h"

namespace Math
{
    CBigInt g_Zero = CBigInt(0);
    CBigInt g_One = CBigInt(1);
    CBigInt g_Two = CBigInt(2);
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
        CBigInt tmp = CBigInt(this);
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
        if (_other == g_Zero) return *this;
        if (*this == g_Zero) return _other;
        if (m_IsSigned && !_other.getSign()) {
            CBigInt cpy = CBigInt(this);
            cpy.m_IsSigned = !cpy.m_IsSigned;
            return CBigInt(_other) - cpy;
        }
        if (!m_IsSigned && _other.getSign()) {
            CBigInt temp = CBigInt(_other);
            temp.m_IsSigned = !temp.m_IsSigned;
            return *this - temp;
        }
        if (m_IsSigned && _other.getSign()) {
            CBigInt temp = CBigInt(_other);
            temp.m_IsSigned = !temp.m_IsSigned;
            CBigInt cpy = CBigInt(this);
            cpy.m_IsSigned = !cpy.m_IsSigned;
            return -(cpy + temp);
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
        return CBigInt(result);
    }
    
    // m_IsSigned = true --> negative
    // m_IsSigned = false --> positive
    
    CBigInt CBigInt::operator-(const CBigInt &_other) {
        
        if (_other == g_Zero) return *this;
        if (*this == g_Zero) return -CBigInt(_other);
        if (m_IsSigned && !_other.getSign())
        {
            // newly constructed CBigInts are always positive. Therefor constructing a CBigInt only from the pure
            // number-string of another results in the absolute value of the other CBigInt.
            CBigInt temp = CBigInt(_other.getNumber());
            return -(-*this + temp);
        }
        if (!m_IsSigned && _other.getSign()) {
            CBigInt temp = CBigInt(_other.getNumber());
            return *this + temp;
        }
        if (m_IsSigned && _other.getSign()) {
            CBigInt temp = CBigInt(_other.getNumber());
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
        return CBigInt(result);
    }
    
    CBigInt CBigInt::operator*(CBigInt _other) const {
        if (_other == g_Zero || *this == g_Zero) return CBigInt();
        CBigInt cpy = CBigInt(*this);
        CBigInt cpyOther = CBigInt(_other);
    
        return karatsubaMultiplication(cpy,cpyOther);
    }
    
    CBigInt CBigInt::operator/ (const CBigInt& _other) {
        CBigInt res = CBigInt();
        return longDivision(*this, _other, res);
        //return simpleFlooredDivision(*this, _other);
    }
    
    CBigInt CBigInt::operator^ (const CBigInt& _other) {
        CBigInt cpy = CBigInt(_other);
        return expBySquaring(*this, cpy);
    }
    
    CBigInt CBigInt::operator% (CBigInt& _other) {
        return longDivisionModulo(*this, _other);
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
    
    
    const bool CBigInt::getSign() const {
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
    
    
    CBigInt CBigInt::karatsubaMultiplication(const CBigInt &_arg1, const CBigInt &_arg2) const{
        
        CBigInt result;
        // signs are different --> negative result
        bool resultSign = _arg1.getSign() != _arg2.getSign();
        CBigInt arg1Absolute = CBigInt(_arg1.getNumber());
        CBigInt arg2Absolute = CBigInt(_arg2.getNumber());
        
        if (_arg1.getNumber().length() <= 2) {
            result = simpleMultiplication(arg1Absolute, arg2Absolute);
            result.m_IsSigned = resultSign;
            return result;
        }
        else if (_arg2.getNumber().length() <= 2) {
            result = simpleMultiplication(arg2Absolute, arg1Absolute);
            result.m_IsSigned = resultSign;
            return result;
        }
        
        const std::string &num1 = _arg1.getNumber();
        const std::string &num2 = _arg2.getNumber();
        
        size_t maxLength, minLength;
        if (num1.length() > num2.length()) {
            maxLength = num1.length();
            minLength = num2.length();
        } else {
            maxLength = num2.length();
            minLength = num1.length();
        }
        
        size_t halfMaxLength = (maxLength) / 2;
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
        
        result = (multPow10(m2, z2) + multPow10(m2/2, z1z2z0) + z0);
        result.m_IsSigned = resultSign;
        return result;
    }
    
    CBigInt CBigInt::multPow10(size_t _exponent, const CBigInt &_multiplicand) const{
        CBigInt result(_multiplicand);
        result.m_Representation.append(_exponent, '0');
        return result;
    }
    
    
    // splits the given input string into two substrings at the position "_at" counting from the right (end) of the
    // original string. E.g. when _inputNumber = 1234567, _at = 2 then _highOrder = 1234 and _lowOrder = 567
    
    void CBigInt::split(const CBigInt &_inputNumber, size_t _at, CBigInt &_highOrder, CBigInt &_lowOrder) const{
        size_t inputLength = _inputNumber.getNumber().length();
        
        // substr extracts the string starting at the first argument and ending with the character at first + second
        // i.e. _highOrder = _inputNumber[first, second]. Endpoints are included in the interval.
        // If no second argument is given it extracts the string starting at the first argument until the end.
        
        _highOrder = CBigInt(_inputNumber.getNumber().substr(0, inputLength - _at));
        try {
            _lowOrder = CBigInt(_inputNumber.getNumber().substr(inputLength - _at));
        } catch (const std::out_of_range &e) {
            std::cerr << "Split is out of range. Continuing with zero as second argument." << std::endl;
            _lowOrder = CBigInt(0);
        }
    }
    
    CBigInt CBigInt::simpleMultiplication(const CBigInt &_smallArg, const CBigInt &_largerArg) const{
        assert(_smallArg.getNumber().length() <= 2);
        CBigInt tmp = CBigInt();
        
        for (CBigInt i = 0; i < _smallArg; ++i)
        {
            tmp += _largerArg;
        }
        
        return tmp;
    }
    
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
    
    CBigInt CBigInt::simpleModulo(CBigInt &_dividend, CBigInt &_divisor) {
        // _dividend mod _divisor
        // modulo is defined as x mod y = x - y * floor(x / y)
        return  _dividend - _divisor * simpleFlooredDivision(_dividend, _divisor);
    }
    
    CBigInt CBigInt::longDivisionModulo(CBigInt &_dividend, CBigInt &_divisor) const{
        CBigInt res;
        return  _dividend - _divisor * longDivision(_dividend, _divisor, res);
    }
    
    
    // The result of the floored division is the largest whole number smaller or equal to the result of the
    // division. E.g. 5 / 2 = 2, -5 / 2 = -3
    CBigInt CBigInt::simpleFlooredDivision(CBigInt _dividend, const CBigInt &_divisor) const{
        assert(_divisor != g_Zero);
        
        CBigInt result = CBigInt();
        
        // dividend negative and divisor positive
        // e.g. -5 / 2 = -3
        if (_dividend.getSign() && !_divisor.getSign()) {
            while (_dividend <= g_Zero ) {
                _dividend += _divisor;
                --result;
            }
        }
        // dividend negative and divisor positive
        // e.g. 5 / -2 = -3
        else if (!_dividend.getSign() && _divisor.getSign()) {
            while (_dividend >= g_Zero) {
                _dividend += _divisor;
                --result;
            }
        }
        // dividend and divisor negative
        // -5 / -2 = 2
        else if (_dividend.getSign()) {
            while ((_dividend - _divisor) <= g_Zero) {
                _dividend -= _divisor;
                ++result;
            }
        }
        // both dividend and divisor positive
        // e.g. 5 / 2 = 2
        else {
            while ((_dividend - _divisor) >= g_Zero) {
                _dividend -= _divisor;
                ++result;
            }
        }
        
        return result;
    }
    
    CBigInt CBigInt::longDivision(CBigInt &_dividend, const CBigInt &_divisor, CBigInt &_result) const{
        assert(_divisor != g_Zero);
    
        bool resultSign = _dividend.getSign() != _divisor.getSign();
        CBigInt positiveDivisor = CBigInt(_divisor.m_Representation);
        CBigInt positiveDividend = CBigInt(_dividend.m_Representation);
        if (positiveDivisor > positiveDividend) return CBigInt();
        
        if ((_dividend.getNumber().length() - _divisor.getNumber().length()) < 3) {
            return simpleFlooredDivision(_dividend, _divisor);
        }
        _result.m_Representation = "";
    
        size_t shiftingPoint = _divisor.getNumber().length() - 1;
        CBigInt tempDivisor = 0;
        CBigInt tempDividend = CBigInt(_dividend.m_Representation.substr(0, shiftingPoint + 1));
        u_short currentResultDigit = 0;
        char partial_char;
        std::string partial("0");
        
        for (size_t i = 0; i < (_dividend.getNumber().length() - _divisor.getNumber().length()); ++i) {
            while (tempDividend >= (tempDivisor + positiveDivisor) ) {
                if (tempDividend < positiveDivisor) break;
                tempDivisor += positiveDivisor;
                ++currentResultDigit;
            }
            ++shiftingPoint;
            _result.m_Representation.append(std::to_string(currentResultDigit));
            
            if (currentResultDigit != 0) {
                tempDividend -= tempDivisor;
                currentResultDigit = 0;
            }
            partial_char = _dividend.m_Representation.at(shiftingPoint);
            partial = std::string(1, partial_char);
            tempDividend.m_Representation.append(partial);
            tempDividend.m_Representation = removeLeadingZeros(tempDividend.m_Representation);
            tempDivisor = 0;
        }
        
        
        while (tempDividend >= (tempDivisor + positiveDivisor) ) {
            if (tempDividend < positiveDivisor) break;
            tempDivisor += positiveDivisor;
            ++currentResultDigit;
        }
        
        _result.m_Representation.append(std::to_string(currentResultDigit));
        _result.m_Representation = removeLeadingZeros(_result.m_Representation);
        _result.m_IsSigned = resultSign;
        
        return _result;
    }
    
    CBigInt CBigInt::simpleCeiledDivision(CBigInt _dividend, const CBigInt &_divisor) {
        assert(_divisor != g_Zero);
        
        bool dividendSign = _dividend.getSign();
        bool divisorSign = _divisor.getSign();
    
        CBigInt result = CBigInt();
    
        // dividend negative and divisor positive
        // e.g. -5 / 2 = -2
        if (dividendSign && !divisorSign) {
            while ((_dividend + _divisor) <= g_Zero) {
                _dividend += _divisor;
                --result;
            }
        }
            // dividend negative and divisor positive
            // e.g. 5 / -2 = -2
        else if (!dividendSign && divisorSign) {
            while ((_dividend + _divisor) >= g_Zero) {
                _dividend += _divisor;
                --result;
            }
        }
            // dividend and divisor negative
            // -5 / -2 = 3
        else if (dividendSign) {
            while (_dividend  <= g_Zero) {
                _dividend -= _divisor;
                ++result;
            }
        }
            // both dividend and divisor positive
            // e.g. 5 / 2 = 3
        else {
            while (_dividend >= g_Zero) {
                _dividend -= _divisor;
                ++result;
            }
        }
    
        return result;
    }
    
    CBigInt CBigInt::ceiledDivision(CBigInt &_dividend, const CBigInt &_divisor) {
        return simpleCeiledDivision(_dividend, _divisor);
    }
    
    
    // time-complexity: O(log n) assuming constant time for multiplication
    CBigInt CBigInt::expBySquaring(CBigInt& _base, CBigInt& _exponent){
        if (_exponent == g_Zero ) return CBigInt(g_One);
        
        CBigInt y = CBigInt(1);
        
        while (_exponent > g_One) {
            if (_exponent.isEven()) {
                _base = _base * _base;
                _exponent = _exponent / g_Two;
            } else {
                y = _base * y;
                _base = _base * _base;
                _exponent = (_exponent - g_One) / g_Two;
            }
            //std::cout << "base: " << _base.getNumber() << "\texponent: " << _exponent.getNumber() << std::endl;
        }
        return _base * y;
    }
    
    // calculates _base^_exponent % _mod
    // time-complexity: O(log N)
    // function consumes a lot of memory for large inputs due to memory inefficient multiplication, modulo and division
    CBigInt CBigInt::modularExponentiation(CBigInt &_base, CBigInt _exponent, CBigInt &_mod) {
        CBigInt s = _base % _mod;
        CBigInt c = 1;
        
        while (_exponent >= g_One) {
            if (!_exponent.isEven()) c = (c * s) % _mod;
            s = (s * s) % _mod;
            _exponent = _exponent / g_Two;
        }
        return c;
    }
    
    const bool CBigInt::isEven() const {
        char lastDigit = this->getNumber().back();
        int intLastDigit = lastDigit - '0';
        bool ret = (intLastDigit & 1) == 0;
        return ret;
    }
    
    const bool CBigInt::isPrime() const {
        return millerRabin(MR_REPETITIONS);
    }
    
    void CBigInt::genRand(CBigInt &_lowerBound, CBigInt &_upperBound, unsigned long _seed, CBigInt &_target) {
        
        gmp_randclass rand (gmp_randinit_default);
        rand.seed(_seed);
        
        mpz_class arg(_upperBound.getNumber());
        mpz_class result = rand.get_z_range(arg);
        
        _target = result.get_str(10);
    }
    
    const bool CBigInt::simplePrimalityTest() const {
        CBigInt three = CBigInt(3);
        CBigInt six = CBigInt(6);
        CBigInt cpy = CBigInt(*this);
        if (*this <= g_One) return false;
        else if (*this <= three) return true;
        else if (this->isEven() || cpy % three == g_Zero) return false;
        CBigInt i = 5;
        CBigInt iPlusTwo = 0;
        while (i * i <= *this) {
            iPlusTwo = i + g_Two;
            if (cpy % i == 0 || cpy % iPlusTwo == 0) return false;
            i += six;
        }
        return true;
    }
    
    // returns composite if *this is composite, otherwise *this is probably prime
    const bool CBigInt::millerRabin(const size_t _repetitions) const {
        if (*this < CBigInt(500)) {
            return simplePrimalityTest();
        }
        
        if (this->isEven()) return false;
        
        CBigInt copy = CBigInt(*this);
        CBigInt d = copy - g_One;
        CBigInt temp = d - g_One;
        
        CBigInt a, x, r = 0;
        bool breakToOuterLoop = false;
        
        // write n-1 as 2^r * d with d odd
        while (d.isEven()) {
            d = d / g_Two;
            ++r;
        }
        
        for (size_t i = 0; i < _repetitions; ++i) {
            // generate a random number a in the interval [2, n-2]
            genRand(g_Two, temp, (unsigned long) i, a);
            x = CBigInt::modularExponentiation(a, d, copy);
            
            if (x == g_One || x == (copy - g_One)) continue;
            
            for (CBigInt j = 1; j < r; ++j) {
                x = CBigInt::modularExponentiation(x, g_Two, copy);
                //x = (x*x) % copy;
                if (x == g_One) return false;
                if (x == (copy - g_One)) {
                    breakToOuterLoop = true;
                    break;
                }
            }
            if (breakToOuterLoop) continue;
            return false;
        }
        return true;
    }
}