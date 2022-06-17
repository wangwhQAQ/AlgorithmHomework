#include <iostream>
#include "map"
#include "vector"
#include "math.h"

using namespace std;

int N;
vector<map<int,pair<int,double>>> probabilityMatrix;
//int cost[4] = {30, 15, 20, 25};
//double p[4] = {0.1, 0.2, 0.5, 0.3};
//int maxMoney[5] = {180, 150, 135, 115, 90};
//int minMoney[5] = {90, 60, 45, 25, 0};
vector<int> cost;
vector<double> p;
vector<int> maxMoney;
vector<int> minMoney;


pair<int,pair<int,double>> findBestKey(int index, int money){
    pair<int,double> best = {0,0};
    int bestOffset = 0;

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
    for (int i = 0; i <= maxMoney[N]; i = i + 5) {
        temp.insert({i, {0,1.0}});
    }
    probabilityMatrix[N] = temp;
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
    int m;
    cout << "请输入元件数量"<< endl;
    cin >> N;
    cout << "请输入最大金额"<< endl;
    cin >> m;
    cout << "请依次输入每个元件的花费，空格隔开"<< endl;
    for (int i = 0; i < N; ++i) {
        int temp;
        cin >> temp;
        cost.push_back(temp);
    }
    cout << "请依次输入每个元件的失效概率，空格隔开"<< endl;
    for (int i = 0; i < N; ++i) {
        double temp;
        cin >> temp;
        p.push_back(temp);
    }

    maxMoney.push_back(m);
    for (int i = 1; i <= N; ++i) {
        maxMoney.push_back(maxMoney[i-1] - cost[i-1]);
    }

    for (int i = 0; i <= N; ++i) {
        minMoney.push_back(0);
    }
    for (int i = N-1; i >= 0; --i) {
        minMoney[i] = minMoney[i+1] + cost[i];
    }

    probabilityMatrix.resize(N+1) ;

    initMatrix();
    for (int i = N-1; i >= 0 ; i--) {
        buildMatrix(i);
    }


    cout<< "系统最大可靠性:" << probabilityMatrix[0][m].second << endl;
    cout<< "各元件的数量依次为："<< endl;
    int c[N],tool[N];
    c[0] = m;
    tool[0] = probabilityMatrix[0][m].first;
    for (int i = 1; i < N; ++i) {
        c[i] = c[i-1] - tool[i-1]*cost[i-1];
        tool[i] = probabilityMatrix[i][c[i]].first;
    }
    for (int i = 0; i < N; ++i) {
        cout << tool[i] << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
