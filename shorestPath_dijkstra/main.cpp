#include <iostream>
#include "vector"
#include <stack>
#include <map>

using namespace std;

#define MAXCOST 2048

class Road{
public:
    int head;
    int tail;
    int cost;
};

int N;
int start, final, k;

vector<map<int,pair<int,int>>> dynamicFormat;

bool isInVector(vector<int> v, int num){
    for (int i = 0; i < v.size(); ++i) {
        if (num == v[i]){
            return true;
        }
    }
    return false;
}

void buildDynamicFormat(int index, vector<Road> roads){
    vector<int> passPoint;
    vector<pair<int,int>> passPointPair;

    map<int,pair<int,int>>::reverse_iterator it;
    for (it = dynamicFormat[index-1].rbegin(); it != dynamicFormat[index-1].rend() ; it++) {
        passPoint.push_back(it->first);
        passPointPair.push_back(it->second);
    }

    map<int,pair<int,int>> temp = dynamicFormat[index-1];
    for (int i = 0; i < passPoint.size(); ++i) {
        for (int j = 0; j < roads.size(); ++j) {
            if (isInVector(passPoint,roads[j].tail) && passPoint[i] == roads[j].head){
                int newCost = passPointPair[i].second+roads[j].cost;
                int oldCost = dynamicFormat[index-1][roads[j].tail].second;
                if (newCost < oldCost){
                    temp[roads[j].tail] = {passPoint[i],newCost};
                }
//                int tempCost = min(newCost,oldCost );
//                dynamicFormat[index-1][roads[j].tail] = tempCost;
//                temp[roads[j].tail] = tempCost;
            }
            else if (passPoint[i] == roads[j].head){
                temp[roads[j].tail] ={roads[j].tail, passPointPair[i].second+roads[j].cost} ;
            }

        }
    }
    dynamicFormat[index] = temp;
}

void initDynamicFormat(vector<Road> roads){
    map<int,pair<int,int>> temp ;
    temp[0] = {0,0};
    for (int i = 0 ; i < roads.size() ; i ++){
        if (roads[i].head == start){
            temp[roads[i].tail] = {0,roads[i].cost};
//            temp.insert(roads[i].tail, roads[i].cost);
            dynamicFormat[0] = temp;
        }
    }
}


int main() {
    cin >> N;
    int roadsSize = N*(N-1)/2;
    vector<Road> roads(roadsSize);
    for (int i = 0; i < roadsSize; ++i) {
        cin >> roads[i].head >> roads[i].tail >> roads[i].cost;

    }
    cin >> start >> final >> k;

    dynamicFormat.resize(k);
    initDynamicFormat(roads);
    for (int i = 1; i < k; ++i) {
        buildDynamicFormat(i, roads);
    }

    int x = dynamicFormat[k-1][final].first;
    int y;
    stack<int> stk;
    stk.push(final);
    for (int i = k; i > 1 ; --i) {
        y = x;
        x = dynamicFormat[i-1][y].first;
        if (y != x){
            stk.push(y);
        } else{
            break;
        }
    }
    stk.push(start);

    cout << "path:" ;
    while (stk.size()>0) {
        cout << stk.top() << '-';
        stk.pop();
    }
    cout << endl;
    cout << "cost: " << dynamicFormat[k-1][final].second;
    return 0;
}
