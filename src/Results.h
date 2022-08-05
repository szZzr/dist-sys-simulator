//
// Created by Giorgos Rizos on 27/4/22.
//

#ifndef SIMULATINGPROJECT_RESULTS_H
#define SIMULATINGPROJECT_RESULTS_H
#include "Infos.cpp"

class Results {
public:
    Results();
    Results(struct Stats stats1, struct Stats stats2);
    struct Stats *stats1;
    struct Stats *stats2;
    Results operator=(Results r);
};


#endif //SIMULATINGPROJECT_RESULTS_H
