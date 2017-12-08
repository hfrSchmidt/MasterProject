#pragma once

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct profiler{
    
    timespec startClock, stopClock;
    
    double diffClock;
    
    unsigned long long startCycle, stopCycle, diffCycle;
    
    double clock_mean, clock_sd, clock_max, clock_min;
    double cycle_mean, cycle_sd, cycle_max, cycle_min;
    std::vector<double> clockMeasurements;
    std::vector<double> cycleMeasurements;
    
    void startClockMeasure();
    
    void stopClockMeasure();
    
    void doStats();
    
    void writeToFile(const std::string &primeSize, const std::string &fileName, int unit);
    
    static __inline__ unsigned long long cycleMeasure(){
        
        unsigned long long x;
        
        unsigned high, low;
        
        asm volatile (
                "CPUID\n\t"
                "RDTSC\n\t"
                "mov %%edx, %0\n\t"
                "mov %%eax, %1\n\t": "=r" (high), "=r" (low):: "%rax", "%rbx", "%rcx", "%rdx");
        
        x = (((unsigned long long)high << 32) | low);
        
        return x;
    }
    
};

