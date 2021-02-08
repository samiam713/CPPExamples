//
//  main.cpp
//  Scheduling Problem
//
//  Created by Samuel Donovan on 1/27/21.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    
    int start;
    int end;
    
    Task(int start, int end);
};

struct CompareTaskEnds {
  bool operator() (Task i,Task j) { return (i.end<j.end);}
};

Task::Task(int start, int end)
: start(start), end(end) {}

vector<Task> scheduleTasks(vector<Task> tasks) {
    sort(tasks.begin(),tasks.end(),CompareTaskEnds());
    
    vector<Task> toReturn;
    int startsAfter = -1;
    
    for (Task const & task : tasks) {
        if (startsAfter < task.start) {
            toReturn.push_back(task);
            startsAfter = task.end;
        }
    }
    
    return toReturn;
}

int main(int argc, const char * argv[]) {
    
    vector<Task> tasks {
        Task(0,5),
        Task(0,2),
        Task(1,3),
        Task(3,5),
    };
    
    for (Task const & task : scheduleTasks(tasks)) {
        cout << task.start << ' ' << task.end << endl;
    }
}
