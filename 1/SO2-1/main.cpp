#include <iostream>
#include "Philosopher.hpp"
#include "chrono"
#include "thread"
#include "vector"
#include "mutex"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

//function that visualize how many times did philosopher eat
void table(vector<unique_ptr<Philosopher>>& philosophers){
    while(true){
        //wait
        this_thread::sleep_for(chrono::milliseconds(2));
        //clear terminal
        system(CLEAR);

        //get data from Philosopher
        cout << "Philosopher x got both forks that many times:\n";
        for (unique_ptr<Philosopher>& p : philosophers) {
            cout << "Philosopher " << p.get()->get_id() << ":    " << p->get_meals() << "\n";
        }
        cout.flush();
    }
}

int main(int argc, char* argv[]) {
    //standard number of philosophers
    int NO_PHILOSOPHERS = 5;

    //read the parameters
    if(argc != 1){
        string x = argv[1];
        if(x.compare("-d")==0){
            Philosopher::debug = true;
        }else{
        NO_PHILOSOPHERS = stoi(argv[1]);
        }
        if(argc > 2){
            for(int i=2;i<argc;i++){
                string x = argv[i];
                if(x.compare("-d")==0){
                    Philosopher::debug = true;
                }
            }
        }
    }

    //declare vectors for mutex, threads and pointers for philosophers
    vector<mutex> forks(NO_PHILOSOPHERS);
    vector<unique_ptr<Philosopher>> philosophers;
    vector<thread> threads;
    mutex output;

    //for all philosophers set appropriate mutexes
    for(int i=0;i<NO_PHILOSOPHERS;i++){
        int left = i%NO_PHILOSOPHERS;
        int right = (i+1)%NO_PHILOSOPHERS;
        //Resource hierarchy solution
        if(left>right){swap(left,right);}
        philosophers.emplace_back(make_unique<Philosopher>(i,forks[left],forks[right],output));
    }

    //start philosopher and display threads
    for(int i=0;i<NO_PHILOSOPHERS;i++){
        threads.emplace_back(&Philosopher::problem, philosophers[i].get());
    }

    if(!Philosopher::debug) {
        thread tablet(table, ref(philosophers));
        tablet.join();
    }

    for(thread& t : threads){
        t.join();
    }


    return 0;
}
