//
// Created by Giorgos Rizos on 27/4/22.
//

#ifndef SIMULATINGPROJECT_TEST_H
#define SIMULATINGPROJECT_TEST_H
#include <iostream>

class Test {
public:
    Test(float *time);
    void do_smth();
    void show();
private:
    float *time;
};


#endif //SIMULATINGPROJECT_TEST_H
