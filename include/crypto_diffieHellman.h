
#pragma once

#include "math_bigint.h"    // CBigInt
#include "profiler.h"       // measurements
#include <map>              // map data structure

namespace Crypto {
    
    class CDiffieHellman {

    private:
        Math::CBigInt m_prime;
        Math::CBigInt m_generator;
        Math::CBigInt m_lowerBound;
        Math::CBigInt m_upperBound;

    public:
        // generate Alice' secret key
        void setupClientAlice(unsigned long _seed, Math::CBigInt &_secretKey);
        // generate Bob's secret key
        void setupClientBob(unsigned long _seed, Math::CBigInt &_secretKey);
        // do a full exchange and print the intermediaries
        void printExchangeSteps();
        // measure the CPU cycles and wallclock time[seconds] for primes from 64 bit to 768 bit
        // in steps of 8 bit.
        void profileExchange();

    public:
        CDiffieHellman();
        CDiffieHellman(const Math::CBigInt &_prime, const Math::CBigInt &_generator);
        ~CDiffieHellman();
    };
    
    

}

