//
// Created by jakub on 30.03.2025.
//

#include "Philosopher.hpp"

bool Philosopher::debug = false;
bool Philosopher::random = true;

Philosopher::Philosopher(int id, mutex& left, mutex& right, mutex& output): id(id), leftFork(left), rightFork(right), output(output){}

void Philosopher::think() {
    if(debug){
        //try to reserve an output for now
        lock_guard<mutex> out(output);
        cout<<"Philosopher "<<this->id<<" is thinking\n";
    }
    if(random) {
        this_thread::sleep_for(chrono::milliseconds(10 + rand() % 1000));
    }else{
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int Philosopher::get_id() {
    return id;
}

void Philosopher::eat() {
    //try to reserve both forks
    lock_guard<mutex> left(leftFork);
    lock_guard<mutex> right(rightFork);
    if(debug) {
        //try to reserve an output for now
        lock_guard<mutex> out(output);
        cout << "Philosopher " << this->id << " is eating\n";
    }
    if(random) {
        this_thread::sleep_for(chrono::milliseconds(10 + rand() % 1000));
    }else{
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    increment_meals();
}

void Philosopher::increment_meals() {
    //reserve time for writing
    lock_guard<mutex> mut(mealMut);
    count_meals++;
}

int Philosopher::get_meals() {
    //reserve time for reading
   lock_guard<mutex> mut(mealMut);
   return count_meals;
}

void Philosopher::problem() {
    //philosopher thread function
    while(true) {
        eat();
        think();
    }
}
