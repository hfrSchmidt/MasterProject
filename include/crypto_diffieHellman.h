
#pragma once

#include "math_bigint.h"
#include "profiler.h"
#include <map>

namespace Crypto {
    
    class CDiffieHellman {

    private:
        Math::CBigInt m_prime;
        Math::CBigInt m_generator;
        Math::CBigInt m_lowerBound;
        Math::CBigInt m_upperBound;

    public:
        void setupClientAlice(unsigned long _seed, Math::CBigInt &_secretKey);
        void setupClientBob(unsigned long _seed, Math::CBigInt &_secretKey);
        void printExchangeSteps();
        void profileExchange();

    public:
        CDiffieHellman();
        CDiffieHellman(const Math::CBigInt &_prime, const Math::CBigInt &_generator);
        ~CDiffieHellman();
    };
    
    

}

