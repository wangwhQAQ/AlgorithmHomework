#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;


const int N = 3;

void copyArr(int (&a)[N][N] , int b[N][N]){
    for (int i = 0 ; i < N ; i ++){
        for(int j = 0 ; j < N ; j ++){
            a[i][j] = b[i][j];
        }
    }
}

typedef class Node{
public:
        char name;
        Node *father;
        int chart[3][3];
        int distance;
        int cost;
        void print(){
            cout<< "name:" << name << endl;
            for (int i = 0 ; i < 3 ; i ++){
                for(int j = 0 ; j < 3 ; j ++){
                    cout << chart[i][j]<< ",";
                }
                cout<< endl;
            }
            cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
        }
        Node(char name,Node* father, int chart[3][3],int distance,int cost){
            this->name = name;
            this->father = father;
            copyArr(this->chart,chart);
            this->distance = distance;
            this->cost = cost;
        }
}Node;

//上下左右
vector<int> Move = {1,2,3,4};

bool flag = false;

bool compare1(Node *A, Node *B){
    return (A->cost+A->distance) > (B->cost + B->distance) ;
}

bool compare2(Node *A, Node *B){
    return A->cost > B->cost;
}

priority_queue<Node*,vector<Node*>,decltype(&compare1)> open(compare1);
priority_queue<Node*,vector<Node*>,decltype(&compare2)> close(compare2);

int init[N][N]
     = {{2, 8, 3},
        {1, 6, 4},
        {7, 0, 5}};
int final[N][N] = {
        {2, 8, 3},
        {1, 4, 5},
        {7, 6, 0}};

//设置目标位置，0为2,2   1为1,0   2为0,0    遍历一次final数组可以得到
int status[N*N][2] = {{2, 2},
                      {1, 0},
                      {0, 0},
                      {0, 2},
                      {1, 1},
                      {1, 2},
                      {2, 1},
                      {2, 0},
                      {0, 1}};

bool isEqual(int a[3][3] , int b[3][3]){
    for (int i = 0 ; i < N ; i ++){
        for(int j = 0 ; j < N ; j ++){
            if(a[i][j] != b[i][j]){
                return false;
            }
        }
    }
    return true;
}

//当前状态到目标状态的代价
int getDistance(int a[3][3]){
    int d = 0 ;
    for(int i = 0 ; i < N ; i ++ ){
        for(int j = 0 ; j < N ; j ++){
            d = d + abs(status[a[i][j]][0]-i) + abs(status[a[i][j]][1]-j) ;
        }
    }
    return d ;
}

int* getZero(int a[3][3]){
    for(int i = 0 ; i < N ; i ++){
        for(int j = 0 ; j < N ; j ++){
            if(a[i][j] == 0){
                int * res = new int[2];
                res[0]=i;
                res[1]=j;
                return res;
            }
        }
    }
}

Node* createNode(Node *father,int move, int offset, int* zero){
    Node* child = new Node((char)father->name+offset,father,father->chart,0,father->cost + 1);

    if (move == 1){
        child->chart[zero[0]][zero[1]] = child->chart[zero[0]-1][zero[1]];
        child->chart[zero[0]-1][zero[1]] = 0;
    }else if (move == 2){
        child->chart[zero[0]][zero[1]] = child->chart[zero[0]+1][zero[1]];
        child->chart[zero[0]+1][zero[1]] = 0;
    }else if (move == 3){
        child->chart[zero[0]][zero[1]] = child->chart[zero[0]][zero[1]-1];
        child->chart[zero[0]][zero[1]-1] = 0;
    }else if (move == 4){
        child->chart[zero[0]][zero[1]] = child->chart[zero[0]][zero[1]+1];
        child->chart[zero[0]][zero[1]+1] = 0;
    }
    child -> distance = getDistance(child->chart);
    return child;
}

void AStar(Node *node){
    if (flag){
        return;
    }
    if (node->father != NULL && isEqual(node->chart, node->father->chart)){
        return;
    }
    if (isEqual(node->chart, final)){
        flag = true;
        return;
    }

    int* zero = getZero(node->chart);
    if (zero[0] == 0 && zero[1] == 1){
        Node* down = createNode(node,Move[1],1,zero);
        Node* left = createNode(node,Move[2],2,zero);
        Node* right = createNode(node,Move[3],3,zero);
        open.push(down);
        open.push(left);
        open.push(right);
    }
    else if (zero[0] == 2 && zero[1] == 1){
        Node* up = createNode(node,Move[0],1,zero);
        Node* left = createNode(node,Move[2],2,zero);
        Node* right = createNode(node,Move[3],3,zero);
        open.push(up);
        open.push(left);
        open.push(right);
    }
    else if (zero[0] == 1 && zero[1] == 0){
        Node* up = createNode(node,Move[0],1,zero);
        Node* down = createNode(node,Move[1],2,zero);
        Node* right = createNode(node,Move[3],3,zero);
        open.push(up);
        open.push(down);
        open.push(right);
    }
    else if (zero[0] == 1 && zero[1] == 2){
        Node* up = createNode(node,Move[0],1,zero);
        Node* down = createNode(node,Move[1],2,zero);
        Node* left = createNode(node,Move[2],3,zero);
        open.push(up);
        open.push(down);
        open.push(left);
    }
    else if (zero[0] == 0 && zero[1] == 0){
        Node* down = createNode(node,Move[1],1,zero);
        Node* right = createNode(node,Move[3],2,zero);
        open.push(down);
        open.push(right);
    }
    else if (zero[0] == 0 && zero[1] == 2){
        Node* down = createNode(node,Move[1],1,zero);
        Node* left = createNode(node,Move[2],2,zero);
        open.push(down);
        open.push(left);
    }
    else if (zero[0] == 2 && zero[1] == 0){
        Node* up = createNode(node,Move[0],1,zero);
        Node* left = createNode(node,Move[2],2,zero);
        open.push(up);
        open.push(left);
    }
    else if (zero[0] == 2 && zero[1] == 2){
        Node* up = createNode(node,Move[0],1,zero);
        Node* right = createNode(node,Move[3],2,zero);
        open.push(up);
        open.push(right);
    } else{
        Node* down = createNode(node,Move[1],1,zero);
        Node* left = createNode(node,Move[2],2,zero);
        Node* up = createNode(node,Move[0],1,zero);
        Node* right = createNode(node,Move[3],2,zero);
        open.push(up);
        open.push(right);
        open.push(down);
        open.push(left);
    }
    close.push(node);
}

int main() {
    for (int i = 0; i < N; ++i) {
        cout << "请输入初始状态 第" << i << "行,中间用空格隔开：" <<endl;
        for (int j = 0; j < N; ++j) {
            cin >> init[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        cout << "请输入结束状态 第" << i << "行,中间用空格隔开：" <<endl;
        for (int j = 0; j < N; ++j) {
            cin >> final[i][j];
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            status[final[i][j]][0] = i;
            status[final[i][j]][1] = j;
        }
    }

    Node* first = new Node('A', NULL, init, getDistance(init), 0);
    open.push(first);
    while(open.size() > 0  &&  !flag){
        Node* temp = open.top();
        close.push(temp);
        open.pop();
        AStar(temp);
    }

    Node* last;
    while(!close.empty()){
        last = close.top();
        close.pop();
    }

    stack<Node*> stk ;
    stk.push(last);
    while (last->father != NULL){
        last = last -> father;
        stk.push(last);
    }
    while (stk.size() > 0){
        stk.top()->print();
        stk.pop();
    }

    system("pause");
    return 0;
}
