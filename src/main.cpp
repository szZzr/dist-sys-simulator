//#include <iostream>

#include "Simulator.h"
#include "DistributedSimulator.h"


void run_single();
void run_double();

int main() {

    /*Simulate single-processor linear system*/
//    run_single();

    /*Simulate a distributed system, that consists of two single processor machines*/
    run_double();

    return 0;
}

void run_single(){
    Simulator<struct Stats> single;
    single.simulate();
    single.report();
}

void run_double(){
    DistributedSimulator<Results> distributed;
    distributed.simulate();
    distributed.report();
}