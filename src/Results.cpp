//
// Created by Giorgos Rizos on 27/4/22.
//

#include "Results.h"
Results::Results() {
    this->stats1 = new Stats;
    this->stats2 = new Stats;
}

Results::Results(struct Stats stats1, struct Stats stats2)
{
    this->stats1 = new Stats;
    this->stats2 = new Stats;
    *this->stats1 = stats1;
    *this->stats2 = stats2;
}

Results Results::operator=(Results r){
    this->stats1 = r.stats1;
    this->stats2 = r.stats2;
    return *this;
}
