//
// Created by Giorgos Rizos on 26/4/22.
//

#include "Utilities.h"

Utilities::Utilities(){
    /* Read input parameters. */
    this->files_reading();
    /* Write report heading and input parameters. */
    this->report_input_par();
}

Utilities::Utilities(bool system){
    /* Read input parameters. */
    this->files_reading(DISTRIBUTED);
    this->infos.num_progs_delayed = 0;
    /* Write report heading and input parameters. */
    this->report_input_par(DISTRIBUTED);
}

Utilities::~Utilities(){
    fclose(this->infos.infile);
    fclose(this->infos.outfile);
}

void Utilities::files_reading(){
    /* Open input and output files. */
    this->infos.infile = std::fopen("../mm1.in", "r");
    this->infos.outfile = std::fopen("../mm1.out", "w");

    if (this->infos.infile== nullptr){
        std::cerr<<"fopen mm1.in";
        exit(1);
    }

    /* Read input parameters. */
        fscanf(this->infos.infile, "%f %f %d ", &this->infos.mean_interarrival,
          &this->infos.mean_service,
          &this->infos.num_delays_required);

}

void Utilities::files_reading(bool system){
    /* Open input and output files. */

    this->infos.infile = std::fopen("../mm2.in", "r");
    this->infos.outfile = std::fopen("../mm2.out", "w");

    if (this->infos.infile== nullptr){
        std::cerr<<"fopen mm2.in";
        exit(1);
    }

    /* Read input parameters. */
    fscanf(this->infos.infile, "%f %f %f %d %f %f", &this->infos.mean_interarrival,
           &this->infos.mean_service_1, &this->infos.mean_service_2,
           &this->infos.num_delays_required,
           &this->infos.prob_1, &this->infos.prob_2);
}


void Utilities::report_input_par(){
    /* Write report heading and input parameters. */
    fprintf(this->infos.outfile, "Single-server queueing system\n\n");
    fprintf(this->infos.outfile, "Mean interarrival time%11.3f minutes\n\n",
            this->infos.mean_interarrival);
    fprintf(this->infos.outfile, "Mean service time%16.3f minutes\n\n",
            this->infos.mean_service);
    fprintf(this->infos.outfile, "Number of customers%14d\n\n",
            this->infos.num_delays_required);
}

void Utilities::report_input_par(bool system){
    /* Write report heading and input parameters. */
    fprintf(this->infos.outfile, "\n\t--- Input Arguments ----\n\n");
//    fprintf(this->infos.outfile, "Single-server queueing system\n\n");
    fprintf(this->infos.outfile, "Mean interarrival time%11.3f minutes\n\n",
            this->infos.mean_interarrival);
    fprintf(this->infos.outfile, "S1: Mean service time%16.3f minutes\n\n",
            this->infos.mean_service_1);
    fprintf(this->infos.outfile, "S2: Mean service time%16.3f minutes\n\n",
            this->infos.mean_service_2);
    fprintf(this->infos.outfile, "S1: Usage probability%16d%%\n\n",
            int(this->infos.prob_1*100));
    fprintf(this->infos.outfile, "S2: Usage probability%16d%%\n\n",
            int(this->infos.prob_2*100));
    fprintf(this->infos.outfile, "Number of customers%14d\n\n",
            this->infos.num_delays_required);
}


void Utilities::report(struct Stats stats, std::string name)
/* Report generator function. */
{

    jobs_q[jobs_q[0]>0] = stats.area_num_in_q/stats.time;
    this->total_time  = stats.time;
    fprintf(this->infos.outfile, "\n\n\t--- %s ---\n\n", name.c_str());
    fprintf(this->infos.outfile, "Average delay in queue%11.3f minutes\n\n",
            stats.total_of_delays / stats.num_progs_delayed);
    fprintf(this->infos.outfile, "Average number in queue%10.3f jobs\n\n",
            stats.area_num_in_q / stats.time);
    fprintf(this->infos.outfile, "Server utilization%15.1f%%\n\n",
            100*stats.area_server_status / stats.time);
//    fprintf(this->infos.outfile, "Time simulation ended%12.3f minutes\n\n", stats.time);
    fprintf(this->infos.outfile, "Jobs completed%15d\n\n",stats.num_progs_delayed);
}

void Utilities::final_report(){
    float mean_jobs = jobs_q[0] + jobs_q[1] + (((int) jobs_q[0])>0) + (((int) jobs_q[1])>0);
    fprintf(this->infos.outfile, "\n\n\t*** System Summary***\n\n");
    fprintf(this->infos.outfile, "Mean response time at system%12.3f minutes\n\n", this->total_time/infos.num_delays_required);
    fprintf(this->infos.outfile, "Average number at system%12.3f jobs\n\n", infos.num_delays_required/this->total_time);
    fprintf(this->infos.outfile, "Time simulation ended%12.3f minutes\n\n", this->total_time);
}

struct Infos Utilities::get_infos(){
    return this->infos;
}