#include <iostream>
#include "vector"
#include <queue>

using namespace std;

#define MAXCOST 2048

class Road{
public:
    int head;
    int tail;
    int cost;
};

int N;

vector<vector<int>> matrix;

void buildMatrix(vector<Road> roads){
    for (int i = 0; i < roads.size(); ++i) {
        matrix[roads[i].head][roads[i].tail] = roads[i].cost;
        matrix[roads[i].tail][roads[i].head] = roads[i].cost;
    }
    for (int i = 0; i < N; ++i) {
        matrix[i][i] = MAXCOST;
    }
}

int passedCost(vector<int> passed){
    if (passed.size() == 1){
        return 0;
    }
    int cost = 0;
    for (int i = 0; i < passed.size() -1 ; ++i) {
        cost = cost + matrix[passed[i]][passed[i+1]];
    }
    return cost;
}

int predictToCost(vector<int> topassed, int k){
    int cost = 0;
    priority_queue<int,vector<int>,greater<int>> pq ;
    for (int i = 0; i < topassed.size(); ++i) {
        priority_queue<int,vector<int>,greater<int>> priorityQueue;
        for (int j = 0; j < topassed.size(); ++j) {
            priorityQueue.push(matrix[i][j]);
        }
        pq.push(priorityQueue.top());
        //priorityQueue.pop();
    }
    for (int i = 0; i < k; ++i) {
        cost = cost + pq.top();
        pq.pop();
    }
    return cost;
}
int lb(vector<int> passed, int next, vector<int> topassed, int k){
    return passedCost(passed) + matrix[passed[passed.size()-1]][next] + predictToCost(topassed,k);
}



int main() {
    cin >> N;
    int roadsSize = N*(N-1)/2;
    vector<Road> roads(roadsSize);
    matrix.resize(N);
    for (int i = 0; i < N; ++i) {
        matrix[i].resize(N);
    }

    for (int i = 0; i < roadsSize; ++i) {
        cin >> roads[i].head >> roads[i].tail >> roads[i].cost;
    }

    buildMatrix(roads);

    int start, end;
    cin >> start >> end;

    vector<int> passed;
    vector<int> topassed;

    passed.push_back(start);


}
