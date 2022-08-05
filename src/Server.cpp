//
// Created by Giorgos Rizos on 26/4/22.
//
#include "Server.h"
/**
 * Example
 */
Server::Server(float mean_interarrival, float mean_service, float *time){
    this->time = time;

    this->mean_interarrival = mean_interarrival;
    this->mean_service = mean_service;

    /* Initialize the state variables. */
    this->server_status = IDLE;
    this->num_in_q = 0;
    this->time_last_event = 0.0;

    /* Initialize the statistical counters. */
    this->num_progs_delayed = 0;
    this->total_of_delays = 0.0;
    this->area_num_in_q = 0.0;
    this->area_server_status = 0.0;

    /* Random seeds */
    this->yy1= 99275.0;
    this->yy2= 48612.0;

    /* Initialize event list. */
    this->time_next_event[1] = *this->time + expon(mean_interarrival, this->yy1);
    this->time_next_event[2] = 1.0e+30;

    /* Specify the number of events for the timing function. */
    this->num_events = 2;
    this->next_event_type = 0;
}

/**
 * Distributed
 */
Server::Server(float mean_interarrival, float mean_service, float time, float probability, std::string name) {
    this->time = new float;
    *this->time = time;

    this->mean_interarrival = mean_interarrival;
    this->probability = probability;
    this->mean_service = mean_service;

    /* Initialize the state variables. */
    this->server_status = IDLE;
    this->num_in_q = 0;
    this->time_last_event = 0.0;

    /* Initialize the statistical counters. */
    this->num_progs_delayed = 0;
    this->total_of_delays = 0.0;
    this->area_num_in_q = 0.0;
    this->area_server_status = 0.0;

    /* Random seeds */
    this->yy1= 99275.0;
    this->yy2= 48612.0;

    /* Initialize event list. */
    this->time_next_event[1] = *this->time + estimate_interarrival(); //uniform distribution
    this->time_next_event[2] = 1.0e+30;


    /* Specify the number of events for the timing function. */
    this->num_events = 2;
    this->next_event_type = 0;

    this->name = name;

    printf("%s) INIT[%.2f]: %.3f\n", this->name.c_str(), this->mean_interarrival, this->mean_service);
}

Server::~Server(){
//    delete[] *time_next_event;
}


void Server::timing()
/* Timing function. */
{
    int i;
    float min_time_next_event;

    min_time_next_event = 1.0e+29; //First initialization
    this->next_event_type = 0;

    /* Determine the event type of the next event to occur. */
    for (i = 1; i <= this->num_events; ++i) {
        if (this->time_next_event[i] < min_time_next_event) {
            min_time_next_event = this->time_next_event[i];
            this->next_event_type = i;
        }
    }

    /* Check to see whether the event list is empty. */
    if (this->next_event_type == 0) {
        /* The event list is empty, so stop the simulation. */
//        fprintf(outfile, "\nEvent list empty at time %f", time);
        std::cout<<"\nEvent list empty at time "<<this->time<<std::endl;
        exit(1);
    }

    /* The event list is not empty, so advance the simulation clock. */
    *this->time = min_time_next_event;
}

/**
 * Distributed
 */
float Server::timing(bool system, float new_time)
/* Timing function. */
{
    int i;
    float min_time_next_event;

    min_time_next_event = 1.0e+29; //First initialization
    this->next_event_type = 0;

    /* Determine the event type of the next event to occur. */
    for (i = 1; i <= this->num_events; ++i) {
        if (this->time_next_event[i] < min_time_next_event) {
            min_time_next_event = this->time_next_event[i];
            this->next_event_type = i;
        }
    }
    /* Check to see whether the event list is empty. */
    if (this->next_event_type == 0) {
        /* The event list is empty, so stop the simulation. */
//        fprintf(outfile, "\nEvent list empty at time %f", time);
        std::cout<<std::endl<<name<<": Event list empty at time "<<*this->time<<std::endl;
        exit(1);
    }

    return min_time_next_event;
}


void Server::arrive()
{
    /* Schedule next arrival. */
//    this->time_next_event[1] = this->time + this->uniform_random(this->mean_interarrival, yy1);
    this->time_next_event[1] = *this->time + this->expon(this->mean_interarrival, this->yy1);
    this->yy1=this->yy;
    this->q.push(this->time_next_event[1]);
    /* Check to see whether server is busy. */
    if (this->server_status == BUSY) {
        /* Server is busy, so increment number of customers in queue. */
        ++this->num_in_q;

        /* Check to see whether an overflow condition exists. */
        if (this->num_in_q > Q_LIMIT) {
            /* The queue has overflowed, so stop the simulation. */
//            fprintf(outfile, "\nOverflow of the array time_arrival at");
//            fprintf(outfile, " time %f", this->time);
            std::cout<<"\nOverflow of the array time_arrival at time "<<this->time<<std::endl;
            exit(2);
        }

        /* There is still room in the queue */
        this->time_arrival[this->num_in_q] = *this->time;


    }

    else {
        /* Server is idle, so arriving customer has a delay of zero. */
        /* Increment the number of customers delayed, and make server
        busy. */
        ++this->num_progs_delayed;
        this->server_status = BUSY;

        /* Schedule a departure (service completion). */
        this->time_next_event[2] = *this->time + this->expon(mean_service, yy2);
        this->yy2=this->yy;
    }
}

/**
 * Distributed
 */
void Server::arrive(bool system)
/* Schedule next arrival. */
{
    /*Inter-arrival time follows the uniform distribution and claim that λ1=λ*p1*/
    this->time_next_event[1] = *this->time + estimate_interarrival();
    this->q.push(this->time_next_event[1]);

    /* Check to see whether server is busy. */
    if (this->server_status == BUSY) {
        /* Server is busy, so increment number of customers in queue. */
        ++this->num_in_q;

        /* Check to see whether an overflow condition exists. */
        if (this->num_in_q > Q_LIMIT) {
            /* The queue has overflowed, so stop the simulation. */
//            fprintf(outfile, "\nOverflow of the array time_arrival at");
//            fprintf(outfile, " time %f", this->time);
            std::cout<<std::endl<<name<<": Overflow of the array time_arrival at time "<<*this->time<<std::endl;
            exit(2);
        }

        /* There is still room in the queue */
        this->time_arrival[this->num_in_q] = *this->time;
    }

    else {
        /* Server is idle, so arriving customer has a delay of zero. */
        /* Increment the number of customers delayed, and make server
        busy. */
        ++this->num_progs_delayed;
        this->server_status = BUSY;

        /* Schedule a departure (service completion). */
//        this->time_next_event[2] = *this->time + this->expon(this->mean_service, this->yy2);
        this->time_next_event[2] = *this->time + expon(this->mean_service, this->yy1);//this->uniform_random(this->yy2);
        this->yy1=this->yy;
    }
}


void Server::depart()
/* Departure event function. */
{
    int i;
    float delay;

    /* Check to see whether the queue is empty. */
    if (this->num_in_q == 0) {
        /* The queue is empty so make the server idle and eliminate the
        departure (service completion) event from consideration. */
        this->server_status = IDLE;
        this->time_next_event[2] = 1.0e+30;
    }
    else {
        /* The queue is nonempty, so decrement the number of customers
        in queue. */
        --this->num_in_q;

        /* Compute the delay of the customer who is beginning service
        nd update the total delay accumulator. */

        delay = *this->time - this->time_arrival[1];
        this->total_of_delays += delay;

        /* Increment the number of customers delayed, and schedule
        departure. */
        double nextTime = expon(this->mean_service, this->yy2);
//        std::cout<<"random: "<<nextTime<<std::endl;

        ++this->num_progs_delayed;
        this->time_next_event[2] = *this->time + nextTime;
        this->yy2=this->yy;

        /* Move each customer in queue (if any) up one place. */
        for (i = 1; i <= this->num_in_q; ++i) {
            this->time_arrival[i] = this->time_arrival[i + 1];
        }
        if(!q.empty())
            this->q.pop();
    }
}

double Server::random1(double ygen)
/* Random number generator*/
{
    const double A = 455470314.0, B = 2147483647.0;
    double r;
    ygen = A * ygen;
    ygen = fmod(ygen, B);
    r = ygen / B;
    this->yy = ygen;
    return r;
}

double Server::uniform_random(float mean, double ygen)
/* Random number generator according to uniform distribution
 * This function doesn't used.
 * */
{
    const double a = 0.8, b=1.2;
    double range = b-a;
    double myRand = this->random1(ygen)/(RAND_MAX + mean);
    std::cout<<"random: "<<(myRand*range +a)<<" = "<<myRand*range<<" + "<< a;
    return myRand*range+a;
}

double Server::uniform_random() {
/*With usage of STL find a random variable that follows the uniform distribution
 * according with given bounds*/
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dist(mean_interarrival-0.2, mean_interarrival+0.2);
    return dist(gen);
}

double Server::estimate_interarrival(){
    /*
     * return: 1 / ( λ * p_i)
     */
    return 1/(uniform_random()*this->probability);
}

double Server::expon(float mean, double ygen)
/* Exponential variate generation function. */
{
    double U;

    /* Generate a U(0,1) random variate. */
    U = this->random1(ygen);

    /* Return an exponential random variate with mean "mean". */
    return -mean * log(U);
}

void Server::update_time_avg_stats()
/* Update area accumulators for time-average statistics. */
{
    float time_since_last_event;

    /* Compute time since last event, and update last-event-time marker. */
    time_since_last_event = *this->time - this->time_last_event;
    this->time_last_event = *this->time;

    /* Update area under number-in-queue function. */
    this->area_num_in_q += this->num_in_q * time_since_last_event;

    /* Update area under server-busy indicator function. */
    this->area_server_status += this->server_status * time_since_last_event;
}

struct Stats Server::get_stats()
{
    show_stats();
    struct Stats stats{};
    stats.area_num_in_q = this->area_num_in_q;
    stats.area_server_status = this->area_server_status;
    stats.num_progs_delayed = this->num_progs_delayed;
    stats.time = *this->time;
    stats.total_of_delays = this->total_of_delays;
    return stats;
}

void Server::show_stats(){
    std::cout<<"area_num_in_q"<<" - "<<
            "area_server_status"<<" - "<<
            "num_progs_delayed"<<" - "<<"time"<<" - "<<
            "total_of_delays"<<std::endl;
    std::cout<<this->area_num_in_q<<" - "<<
        this->area_server_status<<" - "<<
        this->num_progs_delayed<<" - "<<*this->time<<" - "<<
        this->total_of_delays<<std::endl;
}

void Server::show_status(){
    std::stringstream status;
    printf("%s) QJobs[%d]: i) %f ii) %f", this->name.c_str(), this->num_progs_delayed, this->time_next_event[1], this->time_next_event[2]);
    std::queue<double> q_temp = this->q;
    status<<"Arrivals: [";
    while(!q_temp.empty()){
        status<<q_temp.front()<<", ";
        q_temp.pop();
    }
//    for (int i=1; i<=this->num_in_q; i++){
//        status<<time_to_serve[i]<<", ";
//    }
    status<<"]";
    std::cout<<"\n\t\t"<<status.str()<<std::endl;
}