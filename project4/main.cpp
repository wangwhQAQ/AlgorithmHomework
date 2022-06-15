#include <iostream>
#include "map"
#include "vector"
#include "math.h"

using namespace std;

#define MAXCOST 180

vector<map<int,pair<int,double>>> probabilityMatrix(5);
int cost[4] = {30, 15, 20, 25};
double p[4] = {0.1, 0.2, 0.5, 0.3};
int maxMoney[5] = {180, 150, 135, 115, 90};
int minMoney[5] = {90, 60, 45, 25, 0};

pair<int,pair<int,double>> findBestKey(int index, int money){
    pair<int,double> best = {0,0};
    int bestOffset = 0;
    if (minMoney[index] > money){
        cout << index << "||" << money << endl;
    }
    for (int i = minMoney[index]; i <= money; i = i + 5) {
        if (probabilityMatrix[index][i].second > best.second){
            bestOffset = i;
            best = probabilityMatrix[index][i];
        }
    }
    return {bestOffset, best};
}

void initMatrix(){
    map<int,pair<int,double>> temp;
    for (int i = 0; i <= maxMoney[4]; i = i + 5) {
        temp.insert({i, {0,1.0}});
    }
    probabilityMatrix[4] = temp;
}

void buildMatrix(int index){
    map<int,pair<int,double>> temp;
    for (int i = minMoney[index]; i <= maxMoney[index]; i = i + 5) {
        for (int j = 1; j <= (i-minMoney[index + 1]) / cost[index]; ++j) {
            pair<int,pair<int,double>> nextBestKey = findBestKey(index + 1, i - j * cost[index]);
            pair<int,pair<int,double>> nowBestKey = {i,{j,nextBestKey.second.second * ( 1- pow(p[index],j))}};
            if ( temp[nowBestKey.first].second == 0){
                temp[nowBestKey.first]=nowBestKey.second;
            }
            if ( temp[nowBestKey.first].second < nowBestKey.second.second ){
                temp[nowBestKey.first]=nowBestKey.second;
            }
//            temp.insert(nowBestKey);
        }
    }
    probabilityMatrix[index] = temp ;
}

int main() {
    initMatrix();
    for (int i = 3; i >= 0 ; i--) {
        buildMatrix(i);
    }
    return 0;
}
