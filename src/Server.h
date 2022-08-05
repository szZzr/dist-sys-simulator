//
// Created by Giorgos Rizos on 26/4/22.
//

#ifndef SIMULATINGPROJECT_SERVER_H
#define SIMULATINGPROJECT_SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <queue>
#include "Infos.cpp"
#define Q_LIMIT 40000
#define BUSY 1
#define IDLE 0
#define DISTRIBUTED false
#define LINEAR true

class Server {
public:
    Server(float mean_interarrival, float mean_service, float *time);
    Server(float mean_interarrival, float mean_service, float time, float probability, std::string name);
    ~Server();
    void timing();
    float timing(bool system, float new_time);
    void update_time_avg_stats();
    void arrive();
    void arrive(bool system);
    void depart();
    struct Stats get_stats();
    int next_event_type, num_progs_delayed, num_events, num_in_q, server_status;
    double yy, yy1, yy2;
    float area_num_in_q, area_server_status, mean_interarrival,
            mean_service, *time, time_last_event, total_of_delays,
            time_arrival[Q_LIMIT + 1], time_next_event[3];
    std::queue<double> q;
    std::string name;

    void set_time(float time);
    void show_status();
private:
    void show_stats();
    double random1(double ygen);
    double estimate_interarrival();
    double uniform_random(); //stdlib results
    double uniform_random(float mean, double ygen);
    double expon(float mean, double ygen);
    float probability=1;
};


#endif //SIMULATINGPROJECT_SERVER_H
