//
//  main.cpp
//  LPTRalgorithm
//
//  Created by Alex on 15.11.16.
//  Copyright © 2016 Alex. All rights reserved.
//

/*
 *
 *  Largest Processing Time Rule algorithm gives 4/3 approximation for the scheduling problem
 *
 *  params:
 *      - tasks(N) - task complexity
 *      - M - number of available machines
 *
 *  returns:
 *      - pair<assignment,time>
 *          - assignment(N) - array of machine indices for each task
 *          - time - moment the last work is completed
 *
 *  time : O(Nlog(min{N,M}))
 *  space : O(N)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using std::pair;
using std::vector;
pair<vector<int>, int64_t> LPRTalgorithm(const vector<int> & tasks, int M) {
    int N = (int)tasks.size();
    M = std::min(N,M);
    
    // machine index for each task
    vector<int> assignment(N);
    
    // get descending order sorted tasks
    vector<std::pair<int,int> > task_complexities(N);
    for(int i = 0; i < N; ++i) {
        task_complexities[i] = pair<int,int>(tasks[i],i);
    }
    std::sort(task_complexities.begin(),task_complexities.end(),std::greater<pair<int,int> >());
    
    std::set<std::pair<int64_t,int> > workload; // ascending order priority queue of the machines
    for(int i = 0; i < M; ++i) workload.insert(std::make_pair(0,i));
    
    for(int i = 0; i < N; ++i) {
        auto it = workload.begin();
        int machine_id = it->second;
        int64_t machine_workload = it->first;
        workload.erase(it);
        
        assignment[task_complexities[i].second] = machine_id;
        machine_workload += task_complexities[i].first;
        workload.insert(std::make_pair(machine_workload,machine_id));
    }
    
    auto it = workload.end();
    --it;
    int64_t end_moment = it->first;
    return std::make_pair(assignment,end_moment);
}

/*******************************************************************************/

int main() {
    int N,M;
    std::cin >> N >> M;
    std::vector<int> tasks(N);
    for(int i = 0; i < N; ++i) {
        std::cin >> tasks[i];
    }
    
    pair<vector<int>, int64_t> result = LPRTalgorithm(tasks, M);
    
    std::cout<< result.second <<std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout<< result.first[i] << " ";
    }
    
    return 0;
}

