//
// Created by Giorgos Rizos on 4/8/22.
//
#include "DistributedSimulator.h"


DistributedSimulator::DistributedSimulator(){
    util = new Utilities(DISTRIBUTED);
    infos = util->get_infos();
    results = new Results();
}

DistributedSimulator::~DistributedSimulator(){
    delete util;
    delete results;
}

void DistributedSimulator::set_time(std::size_t index, int &prev_time, float *time, Server *s1, Server *s2, float *events)
/* The event list is not empty, so advance the simulation clock. */
{
    prev_time = index;
    *time = events[index];
    *s1->time= *time;
    *s2->time= *time;
}


void DistributedSimulator::simulate(){
    /* Initialize the simulation. */
    Server *s1, *s2;
    const int num_of_servers = 2;
    float time_next_event[num_of_servers];
    float time =1.0e+29;

    s1 = new Server(infos.mean_interarrival, infos.mean_service_1, 0.0, infos.prob_1, "S1");
    s2 = new Server(infos.mean_interarrival, infos.mean_service_2, 0.0, infos.prob_2, "S2");
    /* Run the simulation while more delays are still needed. */
    std::cout << "JOBS: " << infos.num_delays_required << std::endl;

    int prev_time = -1;
    /*First event for each server*/
    time_next_event[0] = s1->timing(DISTRIBUTED, time);
    time_next_event[1] = s2->timing(DISTRIBUTED, time);


    while (infos.num_progs_delayed < infos.num_delays_required ) {
        /* Determine the next event except the first. */
        if (prev_time==0){
            time_next_event[0] = s1->timing(DISTRIBUTED, time);
        }else if(prev_time==1){
            time_next_event[1] = s2->timing(DISTRIBUTED, time);
        }

        /*Determine if the next event comes from server -1- or -2-
         * and whichever is preceding executes at corresponding server.*/
        if (time_next_event[0] < time_next_event[1]) {
            set_time(0, prev_time, &time, s1, s2, time_next_event);
            run(s1);
        } else {
            set_time(1, prev_time, &time, s1, s2, time_next_event);
            run(s2);
        }

        /* In each round estimates the total number of jobs that have been completed*/
        infos.num_progs_delayed = s1->num_progs_delayed + s2->num_progs_delayed;
    }
    auto r = new Results(s1->get_stats(), s2->get_stats());
    results = r;
}

void DistributedSimulator::run(Server *s)
/*Simulates server's execution*/
{
    /* Update time-average statistical accumulators. */
    s->update_time_avg_stats();
    /* Invoke the appropriate event function. */
    switch (s->next_event_type) {
        case 1:
            s->arrive(DISTRIBUTED);
            break;
        case 2:
            s->depart();
            break;
    }
}


void DistributedSimulator::report(){

    util->report(*results->stats1,"Server-1");
    util->report(*results->stats2,"Server-2");
    util->final_report();
}

