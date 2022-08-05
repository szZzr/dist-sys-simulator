//
// Created by Giorgos Rizos on 26/4/22.
//

#ifndef SIMULATINGPROJECT_UTILITIES_H
#define SIMULATINGPROJECT_UTILITIES_H
#include "Infos.cpp"
#define DISTRIBUTED false

class Utilities {
public:
    Utilities();
    Utilities(bool system);
    ~Utilities();
    struct Infos get_infos();
    void report(struct Stats stats, std::string name="Server");
    void final_report();
private:
    void report_input_par();
    void report_input_par(bool system);
    void files_reading();
    void files_reading(bool system);
    struct Infos infos{};
//    struct Stats stats{};
    float jobs_q[2];
    float total_time;
};


#endif //SIMULATINGPROJECT_UTILITIES_H
