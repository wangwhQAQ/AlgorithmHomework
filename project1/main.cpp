#include <iostream>
#include <math.h>
#include <algorithm>

#define RANGE 100.0
#define INFINATE_DISTANCE 65534

using namespace std;

typedef struct Point{
    double x;
    double y;
}Point;

void setRandomPoint(Point *points, int length){
    srand(unsigned (time(NULL)));
    for (int i = 0; i < length; ++i) {
        points[i].x = (rand() % (int)(RANGE * 200)) / RANGE - RANGE;
        points[i].y = (rand() % (int)(RANGE * 200)) / RANGE - RANGE;
    }
}

double Distance(Point point1, Point point2){
    return sqrt((point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y));
}

bool compareX(Point a, Point b){
    return a.x < b.x;
}

bool compareY(Point a, Point b){
    return a.y < b.y;
}

double findPointPair(Point points[], int length, Point &a, Point &b){
    int distance;
    Point a1, b1, a2, b2;
    if (length < 2){
        distance = INFINATE_DISTANCE;
    } else if (length == 2){
        distance = Distance(points[0], points[1]);
        a = points[0];
        b = points[1];
    } else{
        sort(points, points+length, compareX);
        Point *left = new Point[length];
        Point *right = new Point[length];
        for (int i = 0; i < length/2; ++i) {
            left[i] = points[i];
        }
        for (int i = length/2, k = 0 ; i < length ; i ++){
            right[k++] = points[i];
        }
        double d1 = findPointPair(left, length/2, a1, b1);
        double d2 = findPointPair(right, length - length/2, a2, b2);

        if (d1 < d2){
            distance = d1;
            a = a1;
            b = b1;
        } else{
            distance = d2;
            a = a2;
            b = b2;
        }

        double midLine = (points[length/2].x + points[length/2+1].x) / 2;
        int midLength = 0;
        Point *mid = new Point[length];
        for (int i = 0; i < length; ++i) {
            if (  abs(points[i].x - midLine) < 2*distance){
                mid[midLength] = points[i];
                midLength ++;
            }
        }
        sort(mid, mid+midLength, compareY);

        for (int i = 0; i < midLength ; ++i) {
            if (mid[i].x - midLine > 0 ){
                continue;
            }
            for (int j = i + 1; j < i + 6 && j < midLength ; ++j) {
                if (mid[j].x - midLine < 0){
                    continue;
                }
                if (Distance(mid[i],mid[j]) < distance){
                    distance = Distance(mid[i],mid[j]);
                    a = mid[i];
                    b = mid[j];
                }
            }
        }

        return distance;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
