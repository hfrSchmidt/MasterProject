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
    
    unsigned long long startCycle, stopCycle;
    
    double clock_mean, clock_sd, clock_max, clock_min;
    double cycle_mean, cycle_sd, cycle_max, cycle_min;
    std::vector<double> clockMeasurements;
    std::vector<double> cycleMeasurements;
    
    void startClockMeasure();
    
    void stopClockMeasure();
    
    // Calculate the mean, standard deviation, minimum and maximum of the measured values.
    // Uses member variables. Should be called after stopping a measurement.
    void doStats();
    
    // writes the measurement for the specified prime size to a file called fileName.
    // unit specifies whether wallclock time or CPU cycles are supposed to be written.
    // --> possible options are 1 [integer] for wallclock or 2 [integer] for CPU cycles.
    void writeToFile(const std::string &primeSize, const std::string &fileName, int unit);
    
    // measuring CPU cycles currently has only been tested on a x86_64 CPU architecture.
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

