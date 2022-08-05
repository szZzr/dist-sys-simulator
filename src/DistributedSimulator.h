//
// Created by Giorgos Rizos on 4/8/22.
//

#ifndef SIMULATINGPROJECT_DISTRIBUTEDSIMULATOR_H
#define SIMULATINGPROJECT_DISTRIBUTEDSIMULATOR_H
#include "Simulator.h"


class DistributedSimulator{
public:
    DistributedSimulator();
    ~DistributedSimulator();
    void simulate();
    void report();
private:
    void run(Server *s);
    void set_time(std::size_t index, int &prev_time, float *time, Server *s1, Server *s2, float *events);
    Utilities *util;
    struct Infos infos;
    Results *results;
};


#endif //SIMULATINGPROJECT_DISTRIBUTEDSIMULATOR_H
