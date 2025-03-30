//
// Created by jakub on 30.03.2025.
//

#ifndef SO2_P_PHILOSOPHER_HPP
#define SO2_P_PHILOSOPHER_HPP

#include "chrono"
#include "thread"
#include "vector"
#include "mutex"
#include "iostream"

using namespace std;

class Philosopher {
private:
    mutex& leftFork;        //fork with lower hierarchy
    mutex& rightFork;       //fork with higher hierarchy
    mutex& output;          //output mutex
    mutex mealMut;          //mutex for number of meals
    int count_meals=0;      //number of meals eaten by the philosopher
    int id;                 //philosopher id
    void think();   //time when philosopher doesn't need or want to eat
    void eat();     //time when philosopher keeps both forks occupied or waits for another fork
    void increment_meals(); //function that increments meals eaten by the philosopher
public:
    Philosopher(int id, mutex& left, mutex& right, mutex& output);
    static bool debug;      //enables command prompts
    void problem();         //philosophers' thread function
    int get_meals();        //returns number of meals eaten
    int get_id();           //returns personal id
};


#endif //SO2_P_PHILOSOPHER_HPP
