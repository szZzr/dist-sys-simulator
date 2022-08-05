//
// Created by Giorgos Rizos on 4/8/22.
//
#include "Server.h"
#include "Utilities.h"
#include "Results.h"
#ifndef SIMULATINGPROJECT_SIMULATOR_H
#define SIMULATINGPROJECT_SIMULATOR_H


template<class T>
class Simulator {
public:
    Simulator();
    ~Simulator();
    void simulate();
    void report();

private:
    void run(Server *s);
    Utilities *util;
    struct Infos infos;
    T *results;
};


#endif //SIMULATINGPROJECT_SIMULATOR_H
