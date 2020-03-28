//
// Created by Vikram Singh Rathore
//

#ifndef __TIMER_H_INCLUDED__
#define __TIMER_H_INCLUDED__

class Timer;

#include <bits/stdc++.h>
using namespace std;

class Timer {

    clock_t _timestamp;

    public:
        Timer();
        double getElapsedTime();
        void restart();

};

Timer::Timer() { _timestamp = clock(); }

double Timer::getElapsedTime() { return double(clock() - _timestamp) / double(CLOCKS_PER_SEC); }

void Timer::restart() { _timestamp = clock(); }

#endif