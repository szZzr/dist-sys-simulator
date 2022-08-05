//
// Created by Giorgos Rizos on 26/4/22.
//
#ifndef INFOS_CPP
#define INFOS_CPP
#include <iostream>

struct Infos{
    float area_num_in_q, area_server_status,
            mean_interarrival, mean_service,
            mean_service_1, mean_service_2,
            prob_1, prob_2,
            total_of_delays, time;
    int num_progs_delayed, num_delays_required;
    FILE *infile, *outfile;
} ;

struct Stats{
    float total_of_delays, area_num_in_q, time,
            area_server_status;
    int num_progs_delayed;
};
#endif