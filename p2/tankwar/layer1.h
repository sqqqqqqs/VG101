#include <iostream>
#include <fstream>
#include <deque>
#include<string>
#include<string.h>
#include<fstream>
using namespace std;

#ifndef PROJECT2_LAYER1_H
#define PROJECT2_LAYER1_H


class Vec {
public:
    int x;int y;
    bool operator == (Vec a)const {
        return (x == a.x) && (y == a.y);

    }
};

Vec operator + (Vec a, Vec b) {
    Vec t; t.x=a.x+b.x;t.y=a.y+b.y;return t;
}

class Tank{
public:
    Vec Pos;
    Vec direction;
    int life_point;
    void initialize(int command);
    void move();
    void turn(int command);
};


class Bullet{
public:
    Vec Pos;
    Vec direction;
};




#endif //PROJECT2_LAYER1_H
