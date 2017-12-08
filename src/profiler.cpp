#include "../include/profiler.h"

using namespace std;

#define BILLION  1000000000L
#define MICROCONVERT 1000000.0

void profiler::startClockMeasure(){
    if (clock_gettime(CLOCK_MONOTONIC, &startClock) == -1){
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }
}

void profiler::stopClockMeasure(){
    if (clock_gettime(CLOCK_MONOTONIC, &stopClock) == -1){
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }
    diffClock = (double)(stopClock.tv_sec - startClock.tv_sec)
                + (double)(stopClock.tv_nsec - startClock.tv_nsec) / BILLION;
                //* MICROCONVERT;
}

void profiler::doStats(){
    if (clockMeasurements.empty()|| cycleMeasurements.empty()) exit(EXIT_FAILURE);
    
    clock_min = *std::min_element(clockMeasurements.begin(), clockMeasurements.end());
    clock_max = *std::max_element(clockMeasurements.begin(), clockMeasurements.end());
    
    cycle_min = *std::min_element(cycleMeasurements.begin(), cycleMeasurements.end());
    cycle_max = *std::max_element(cycleMeasurements.begin(), cycleMeasurements.end());
    //printf("Min, max: %f %f\n", p.min, p.max);
    
    double sum_clock = 0;
    double sum_cycle = 0;
    
    for(unsigned int j = 0; j < clockMeasurements.size(); j++){
        sum_clock += (double)clockMeasurements[j];
        sum_cycle += (double)cycleMeasurements[j];
    }
    
    clock_mean = sum_clock / (double)clockMeasurements.size();
    cycle_mean = sum_cycle / (double)cycleMeasurements.size();
    //printf("\nMean: %f \n", p.mean);
    
    double tmp1 = 0, tmp2 = 0;
    for(unsigned int i = 0; i < clockMeasurements.size(); i++){
        tmp1 += pow((double)clockMeasurements[i] - clock_mean, 2);
        tmp2 += pow((double)cycleMeasurements[i] - cycle_mean, 2);
    }
    clock_sd = sqrt((1.0 / (double)clockMeasurements.size()) * tmp1);
    cycle_sd = sqrt((1.0 / (double)cycleMeasurements.size()) * tmp2);
    //printf("SD: %f\n", p.sd);
}

void profiler::writeToFile(const string &primeSize, const string &fileName, int unit){
    FILE *cFile;
    cFile = fopen(fileName.c_str(), "r");
    
    if (unit == 1){
        if (clockMeasurements.empty()) exit(EXIT_FAILURE);
        if (cFile){
            fclose(cFile);
        }else{
            cFile = fopen(fileName.c_str(), "w");
            
            fprintf(cFile, "%11s\t%12s\t%12s\t%12s\t%12s\t%20s\n", "prime [bit]", "min [s]", "max [s]", "mean [s]",
                    "sd [s]", "measurements [s]");
            fclose(cFile);
        }
        
        cFile = fopen(fileName.c_str(), "a");
        
        fprintf(cFile, "%11s\t%12f\t%12f\t%12f\t%12f\t", primeSize.c_str(), clock_min, clock_max, clock_mean, clock_sd);
        
        for (vector<double>::const_iterator i = clockMeasurements.begin(); i != clockMeasurements.end(); ++i){
            fprintf(cFile, "%f ", *i);
        }
        fprintf(cFile, "\n");
        fclose(cFile);
        
    }
    
    if (unit == 2){
        if (cycleMeasurements.empty()) exit(EXIT_FAILURE);
        if (cFile){
            fclose(cFile);
        }else{
            cFile = fopen(fileName.c_str(), "w");
            fprintf(cFile, "%11s\t%15s\t%15s\t%15s\t%15s\t%25s\n", "prime [bit]", "min [Gcycles]", "max [Gcycles]",
                    "mean [Gcycles]", "sd [Gcycles]", "measurements [Gcycles]");
            fclose(cFile);
        }
        
        cFile = fopen(fileName.c_str(), "a");
        
        fprintf(cFile, "%11s\t%15f\t%15f\t%15f\t%15f\t\t", primeSize.c_str(), cycle_min/BILLION, cycle_max/BILLION,
                cycle_mean/BILLION, cycle_sd/BILLION);
        
        for (vector<double>::const_iterator i = cycleMeasurements.begin(); i != cycleMeasurements.end(); ++i){
            fprintf(cFile, "%f ", *i/BILLION);
        }
        
        fprintf(cFile, "\n");
        fclose(cFile);
        
    }
    
}
