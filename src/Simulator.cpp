//
// Created by Giorgos Rizos on 4/8/22.
//

#include "Simulator.h"
template<class T>
/*The template class determines the type of result.*/
Simulator<T>::Simulator() {
    util = new Utilities();
    infos = util->get_infos();
}

template<class T>
Simulator<T>::~Simulator(){
    delete util;
};

template<class T>
void Simulator<T>::run(Server *s){
    s->update_time_avg_stats();
    /* Invoke the appropriate event function. */
    switch (s->next_event_type) {
        case 1:
            s->arrive();
//            s->arrive(DISTRIBUTED);
            break;
        case 2:
            s->depart();
            break;
    }
}

template<class T>
void Simulator<T>::simulate(){
    float time = 0;
    auto *s = new Server(infos.mean_interarrival, infos.mean_service, &time);
    /* Run the simulation while more delays are still needed. */

    while (s->num_progs_delayed < infos.num_delays_required) {
        /* Determine the next event. */
        s->timing();
//        s->timing(DISTRIBUTED);

        /*Simulates server's execution*/
        run(s);

        printf(" [%d] time -%.4f-\n\n",s->num_progs_delayed,time);
        s->show_status();
        std::cout<<"--------------------------------------------------------------------------------\n\n";
    }
    *results= s->get_stats();
}

template<class T>
void Simulator<T>::report(){
    util->report(*results);
}

//DEFINE OBJECTS
template class Simulator<struct Stats>;