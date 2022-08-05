//
// Created by Giorgos Rizos on 27/4/22.
//

#include "Test.h"

Test::Test(float *time){
    this->time = time;
}

void Test::do_smth(){
    *this->time=5.0;
}

void Test::show() {
    std::cout<<"Time: "<<*this->time<<std::endl;
}

void testing(){
    float *time;
    *time = 4.0;
    Test *t = new Test(time);
    t->do_smth();
    std::cout<<"MAIN-Time: "<<*time<<std::endl;
    *time = 8.0;
    t->show();
    std::cout<<"2-MAIN-Time: "<<*time;
}

