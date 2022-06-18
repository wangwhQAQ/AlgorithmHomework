#include <iostream>
#include "vector"
#include <iterator>
#include <queue>
#include <algorithm>

using namespace std;

#define MAXCOST 2048

class Road{
public:
    int head;
    int tail;
    int cost;
};

class Node{
public:
    int node;
    int lb;
    int deep;

    vector<int> innerPass;
    vector<int> innerToPass;

    Node(int a, int b,int d){
        node = a;
        lb = b;
        deep = d;
    }
    friend bool operator> (Node n1, Node n2){
        return n1.lb > n2.lb;
    }
};

int N;
int top;
int bottom;
int END;
Node result(0,0,0);

vector<vector<int>> matrix;
priority_queue<Node,vector<Node>,greater<Node>> nodeQueue ;

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

int predictToCost(vector<int> topassed, int k, int next){
    int cost = 0;
    if (next == END){
        return cost;
    }
    priority_queue<int,vector<int>,greater<int>> pq ;
    for (int i = 0; i < topassed.size(); ++i) {
        if (topassed[i] == next){
            continue;
        }
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
    return passedCost(passed) + matrix[passed[passed.size()-1]][next] + predictToCost(topassed,k,next);
}

bool judge(Node node, int k){
    if (node.deep > k+1){
        return false;
    }
    if (node.lb > top || node.lb < bottom){
        return false;
    } else{
        return true;
    }
}

Node branchGauge(int start, int end, vector<int> passed, vector<int> topassed, int k){

    Node top = nodeQueue.top();
    nodeQueue.pop();
    passed.push_back(top.node);
    vector <int>::iterator it = find(topassed.begin(), topassed.end(), top.node);
    topassed.erase(it);

    if (passed[passed.size()-1] == end){
        result = top;
        return top;
    }

    for (int i = 0; i < topassed.size(); ++i) {
        int next = topassed[i];
        int tempLb = lb(passed,next,topassed,k-top.deep-1);
        Node n(next,tempLb,top.deep +1);
        n.innerPass = passed;
        n.innerToPass = topassed;

        if(judge(n,k)){
            nodeQueue.push(n);
        }
    }

    Node nextTop = nodeQueue.top();
    branchGauge(start,end,nextTop.innerPass,nextTop.innerToPass,k);
}

int main() {
    cin >> N;
    int roadsSize = N*(N-1)/2;
    vector<Road> roads(roadsSize);
    matrix.resize(N);
    for (int i = 0; i < N; ++i) {
        matrix[i].resize(N);
    }

    vector<int> passed;
    vector<int> topassed;

    for (int i = 0; i < roadsSize; ++i) {
        cin >> roads[i].head >> roads[i].tail >> roads[i].cost;

    }
    for (int i = 0; i < N; ++i) {
        topassed.push_back(i);
    }

    buildMatrix(roads);

    int start, end, k;
    cin >> start >> end >> k;
    END = end;

    top = matrix[start][end];
    bottom = predictToCost(topassed,1,start);

    Node first(start,bottom,0);
    first.innerPass = passed;
    first.innerToPass = topassed;
    nodeQueue.push(first);

    branchGauge(start,end,passed,topassed,k);

    result.innerPass.push_back(result.node);
    cout<< "top: " << top << endl;
    cout<< "bottom: " << bottom << endl;
    for (int i = 0; i < result.innerPass.size(); ++i) {
        cout << result.innerPass[i] << "--";
    }
    cout << endl;
    cout << "cost: " << passedCost(result.innerPass) << endl;

    return 0;
}
