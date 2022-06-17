#include <iostream>
#include "vector"
#include "fstream"
#include "string.h"
#include "set"
#include <algorithm>

using namespace std;

class Node{
public:
    char a;
    char b;
    int cost;
    bool judge = false;

    Node(char i, char j, int c) {
        this->a = i;
        this->b = j;
        this->cost = c;
    }
};

class Path{
public:
    char start;
    char end;
    vector<char> path;
    int cost;
};

const string outFileName = "LOG.txt";
const string inputFileName = "input.txt";

int **matrix;
vector<int> sNode;
vector<Node> nList;

//构建矩阵（没有用到）
int** initVector(int num, vector<Node> nodeList){
    set<char> collection;
    for (int i = 0; i < num; ++i) {
        collection.insert(nodeList[i].a);
        collection.insert(nodeList[i].b);
    }

    int n = collection.size();

    int** matrix = (int **) malloc(n*sizeof (int *));
    for (int i = 0; i < n; ++i) {
        matrix[i] = (int*) malloc(n*sizeof (int*));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = 2048;
        }
    }

    for (int i = 0; i < num; ++i) {
        matrix[nodeList[i].a-'a'][nodeList[i].b-'a'] = nodeList[i].cost;
        matrix[nodeList[i].b-'a'][nodeList[i].a-'a'] = nodeList[i].cost;
    }

    return matrix;
}
//排序（没有用到）
vector<int> sortedNode(int num, vector<Node> nodeList){
    vector<int> sortNode;
    for (int i = 0; i < num; ++i) {
        int initCost = 1024;
        int offset;
        for (int j = 0; j < num; ++j) {
            if (nodeList[j].cost < initCost && nodeList[j].judge == false){
                offset = j;
                initCost = nodeList[j].cost;
            }
        }
        sortNode.push_back(offset);
        nodeList[offset].judge = true;
    }

    return sortNode;
}

void readFile(){
    vector<Node> nodeList;
    ifstream fin;
    fin.open("input.txt", ios::in);

    string buff;
    int num = 0;
    cout << "读入路径:" << endl;
    while (getline(fin,buff)){
        cout << buff << endl;
        char head = buff[0];
        char tail = buff[2];
        int cost = stoi(buff.substr(4,buff.size()-1));
        Node temp = *new Node(head,tail,cost);
        nodeList.push_back(temp);
        num ++;
    }

    matrix = initVector(num,nodeList);
    sNode = sortedNode(num, nodeList);
    nList = nodeList;
}

void outFile(char start, vector<Path> passWay){
    vector<Node> nodeList;
    ofstream fout;
    fout.open("LOG.txt", ios::app);

    fout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<输入点：" << start << "开始<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    for (int i = 0; i < passWay.size(); ++i) {
        fout << "起点:"<<passWay[i].start << endl;
        fout << "终点:" << passWay[i].end << endl ;
        fout << "路径:";
        for (int j = 0; j < passWay[i].path.size(); ++j) {
            fout <<  passWay[i].path[j] << '-';
        }
        fout << "总路径长:" << passWay[i].cost << endl;
        fout << endl;
    }
    fout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<输入点：" << start << "结束<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    fout.close();
}

//判定顶点是否在链表中
bool isInVector(vector<char> v, char c){
    for (int i = 0; i < v.size(); ++i) {
        if (c == v[i]){
            return true;
        }
    }
    return false;
}

//根据 已经路过的点 寻找 接下来可以到达的点（没用到）
vector<char> findNextNode(vector<char> passNode, vector<Node> nodeList) {
    vector<char> nextNode;
    for (int i = 0; i < nodeList.size(); ++i) {
        if ( (isInVector(passNode,nodeList[i].a) && !isInVector(passNode,nodeList[i].b)) ) {
            nextNode.push_back(nodeList[i].b);
        } else if (  isInVector(passNode,nodeList[i].b) && !isInVector(passNode,nodeList[i].a)){
            nextNode.push_back(nodeList[i].a);
        }
    }
    return nextNode;
}

//寻找所有可以走的路中最短的一条
int findMinCost(vector<Path> possiableWay){
    int min = 1024;
    int offset = 0;
    for (int i = 0; i < possiableWay.size(); ++i) {
        if (possiableWay[i].cost < min){
            min = possiableWay[i].cost;
            offset = i;
        }
    }
    return offset;
}

vector<Path> djkstra(char start, vector<int> sortNode, vector<Node> nodeList){

    set<char> collection;
    for (int i = 0; i < nodeList.size(); ++i) {
        collection.insert(nodeList[i].a);
        collection.insert(nodeList[i].b);
    }

    int size = collection.size();

    vector<Path> passWay;

    vector<char> initpath;
    initpath.push_back(start);
    Path startPath = {start,start,initpath,0};
    passWay.push_back(startPath);

    vector<char> passNode;
    passNode.push_back(start);

    vector<char> nextNode;

    while (passNode.size() < size){
        vector<Path> posiiableWay;
        nextNode = findNextNode(passNode,nodeList);
        for (int i = 0; i < nodeList.size(); ++i) {
            for (int j = 0; j < passWay.size(); ++j) {
                if (passWay[j].end == nodeList[i].a && !isInVector(passNode,nodeList[i].b)){
                    Path temp = *new Path();
                    temp.start = start;
                    temp.end = nodeList[i].b;
                    temp.path = passWay[j].path;
                    temp.path.push_back(nodeList[i].b);
                    temp.cost = passWay[j].cost + nodeList[i].cost;

                    posiiableWay.push_back(temp);
                } else if (passWay[j].end == nodeList[i].b && !isInVector(passNode,nodeList[i].a)){
                    Path temp = *new Path();
                    temp.start = start;
                    temp.end = nodeList[i].a;
                    temp.path = passWay[j].path;
                    temp.path.push_back(nodeList[i].a);
                    temp.cost = passWay[j].cost + nodeList[i].cost;

                    posiiableWay.push_back(temp);
                }
            }
        }

        int minOffset = findMinCost(posiiableWay);
        passWay.push_back(posiiableWay[minOffset]);
        passNode.push_back(posiiableWay[minOffset].end);

    }

    return passWay;
}

int main() {
    readFile();
    char start;
    cout << "请输入起点:(每次输入都会在LOG.txt中打印输出,输入/终止程序)" << endl;
    while (cin >> start){
        if (start == '/'){
            break;
        }
        vector<Path> passWay = djkstra(start,sNode,nList);
    //    for (int i = 0; i < passWay.size(); ++i) {
    //        cout << "start:"<<passWay[i].start << endl;
    //        cout << "end:" << passWay[i].end << endl ;
    //        cout << "path:";
    //        for (int j = 0; j < passWay[i].path.size(); ++j) {
    //            cout <<  passWay[i].path[j] << '-';
    //        }
    //        cout << endl;
    //        cout << "cost:" << passWay[i].cost << endl;
    //        cout << endl;
    //    }
        outFile(start,passWay);
    }

    system("pause");
    return 0;
}
