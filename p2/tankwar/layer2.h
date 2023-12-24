#include <iostream>
#include <fstream>
#include <deque>
#include<string>
#include<string.h>
#include<fstream>
#include "layer1.h"
using namespace std;

#ifndef PROJECT2_LAYER2_H
#define PROJECT2_LAYER2_H


int cont=1;int turn = 0;
int win = -1;//1 A,2 B,3 draw
int direct_A;int direct_B;
int lower = 0; int upper = 19;

Tank Tank_A;Tank Tank_B;

void Tank::initialize(int command) {
    switch (command) {
        case 0:direction.x = -1;direction.y = 0;break;//0 左
        case 1:direction.x = 1;direction.y = 0;break;//1 右
        case 2:direction.x = 0;direction.y = 1;break;//2 下
        case 3:direction.x = 0;direction.y = -1;break;//3 上
    }
}

void Tank::turn(int command) {//0 向前，1 向左，2 向右
    switch (command) {
        case 0:direction.x = direction.x;direction.y = direction.y;break;//向前
        case 1:if (direction.x == -1 && direction.y == 0){direction.x = 0;direction.y = 1;}//左转朝左变朝下
            else if (direction.x == 1 && direction.y == 0){direction.x = 0;direction.y = -1;}//左转朝右变朝上
            else if (direction.x == 0 && direction.y == 1){direction.x = 1;direction.y = 0;}//左转朝下变朝右
            else {direction.x = -1;direction.y = 0;}break;//左转朝上变朝左
        case 2: if (direction.x == -1 && direction.y == 0){direction.x = 0;direction.y = -1;}//右转朝左变朝上
            else if (direction.x == 1 && direction.y == 0){direction.x = 0;direction.y = 1;}//右转朝右变朝下
            else if (direction.x == 0 && direction.y == 1){direction.x = -1;direction.y = 0;}//右转朝下变朝左
            else {direction.x = 1;direction.y = 0;}break;//右转朝上变朝右

    }
}

void Tank::move() {
    Pos = Pos + direction;
}

deque <Bullet> bull;

void generate_bullet(Tank x) {
    Bullet a;a.direction = x.direction;a.Pos = x.Pos + x.direction;
    bull.push_back(a);
}

void  judge_crash(Tank a, Tank b) {
    if (a.Pos == b.Pos && (a.Pos.x+b.Pos.x!=0 || a.Pos.y+b.Pos.y != 0)) {//crash
        cont = 0;
        if (a.life_point > b.life_point) { win = 1; cout<<"Tank A Wins";}//A 赢了
        else if (a.life_point < b.life_point) { win = 2; cout<<"Tank B Wins";}//B 赢了
        else { win = 3; cout<<"Draw";}//平局
    }
}

void move_bullet(){
    int i;
    int bull_size=bull.size();
    for(i=1;i<=bull_size;i++) {
        Bullet temp = bull.front();bull.pop_front();
        temp.Pos = temp.Pos + temp.direction;
        bull.push_back(temp);
    }
}
void judge_collisionA(){
    int bull_size=bull.size();
    int i;
    for(i=1;i<=bull_size;i++) {
        Bullet temp = bull.front();bull.pop_front();
        if (temp.Pos==Tank_A.Pos) {
            Tank_A.life_point = Tank_A.life_point - 2;
            continue;
        }
        bull.push_back(temp);
    }
}
void judge_collisionB(){
    int bull_size=bull.size();
    int i;
    for(i=1;i<=bull_size;i++) {
        Bullet temp = bull.front();bull.pop_front();
        if (temp.Pos==Tank_B.Pos) {
            Tank_B.life_point = Tank_B.life_point - 2;
            continue;
        }
        bull.push_back(temp);
    }
}

void shrink() {
    lower++;upper--;
}

void judge_border(){
    if ((Tank_A.Pos.x < lower || Tank_A.Pos.x > upper) || (Tank_A.Pos.y < lower || Tank_A.Pos.y > upper)){
        Tank_A.life_point--;
    }
    if ((Tank_B.Pos.x < lower || Tank_B.Pos.x > upper) || (Tank_B.Pos.y < lower || Tank_B.Pos.y > upper)){
        Tank_B.life_point--;
    }
}

void judge_life(Tank &a,Tank &b){
    if (a.life_point <= 0 && b.life_point > 0){win = 2;cont=0;cout<<"Tank B Wins";}
    else if (b.life_point <= 0 && a.life_point > 0){win = 1;cont=0;cout<<"Tank A Wins";}
    else if (a.life_point <= 0 && b.life_point <= 0){win = 3;cont=0;cout<<"Draw";}
    else {cont=1;}
}

void AI_judgeA() {
    int bull_size = bull.size();
    int i;
    int judge = 0;
    if ((Tank_B.Pos.x == Tank_A.Pos.x - 1 || Tank_B.Pos.x == Tank_A.Pos.x || Tank_B.Pos.x == Tank_A.Pos.x + 1) &&
        (Tank_B.Pos.y == Tank_A.Pos.y - 1 || Tank_B.Pos.y == Tank_A.Pos.y ||
         Tank_B.Pos.y == Tank_A.Pos.y + 1)) {//判断是否在周围的9格中有玩家坦克
        if (Tank_B.life_point <= Tank_A.life_point) {//如果生命值高于或等于玩家坦克，进行追击
            if (Tank_B.Pos.x < Tank_A.Pos.x) {
                if (Tank_A.direction.x == 1 && Tank_A.direction.y == 0) {
                    Tank_A.turn(1);
                } else {
                    Tank_A.direction.x = -1;
                    Tank_A.direction.y = 0;
                }
            } else if (Tank_B.Pos.x > Tank_A.Pos.x) {
                if (Tank_A.direction.x == -1 && Tank_A.direction.y == 0) {
                    Tank_A.turn(2);
                } else {
                    Tank_A.direction.x = 1;
                    Tank_A.direction.y = 0;
                }
            } else if (Tank_B.Pos.x == Tank_A.Pos.x) {
                if (Tank_B.Pos.y > Tank_A.Pos.y) {
                    if (Tank_A.direction.x != 0 || Tank_A.direction.y != -1) {
                        Tank_A.direction.x = 0;
                        Tank_A.direction.y = 1;
                    }
                } else if (Tank_B.Pos.y < Tank_A.Pos.y) {
                    if (Tank_A.direction.x != 0 || Tank_A.direction.y != 1) {
                        Tank_A.direction.x = 0;
                        Tank_A.direction.y = -1;
                    }
                }
            } else {//如果生命值低于敌方玩家，进行逃离
                if (Tank_B.Pos.x < Tank_A.Pos.x) {
                    if (Tank_A.direction.x != -1 || Tank_A.direction.y != 0) {
                        Tank_A.direction.x = 1;
                        Tank_A.direction.y = 0;
                    } else {
                        Tank_A.turn(2);
                    }
                } else if (Tank_B.Pos.x > Tank_A.Pos.x) {
                    if (Tank_A.direction.x != 1 || Tank_A.direction.y != 0) {
                        Tank_A.direction.x = -1;
                        Tank_A.direction.y = 0;
                    } else {
                        Tank_A.turn(1);
                    }
                } else if (Tank_B.Pos.x == Tank_A.Pos.x) {
                    if (Tank_B.Pos.y > Tank_A.Pos.y) {
                        if (Tank_A.direction.x != 0 || Tank_A.direction.y != 1) {
                            Tank_A.direction.x = 0;
                            Tank_A.direction.y = -1;
                        }
                    } else if (Tank_B.Pos.y < Tank_A.Pos.y) {
                        if (Tank_A.direction.x != 0 || Tank_A.direction.y != -1) {
                            Tank_A.direction.x = 0;
                            Tank_A.direction.y = 1;
                        }
                    }
                }
            }
        }
    }else { //判断是否有子弹下回合会打中自己
        for (i = 1; i <= bull_size; i++) {
            Bullet temp = bull.front();
            bull.pop_front();
            if (temp.Pos + temp.direction + temp.direction == Tank_A.Pos + Tank_A.direction ||
                temp.Pos + temp.direction == Tank_A.Pos + Tank_A.direction) {
                judge = 1;
            }
            bull.push_back(temp);
        }
        if (judge == 1) {   //只能判断出很少情况。。
            Tank_A.turn(1);
        } else {
            if (abs(Tank_A.Pos.x - 9) >= abs(Tank_A.Pos.y - 9)) {
                if (Tank_A.Pos.x - 9 <= 0) {
                    if (Tank_A.direction.x != -1 || Tank_A.direction.y != 0) {
                        Tank_A.direction.x = 1;
                        Tank_A.direction.y = 0;
                    } else {
                        if (Tank_A.Pos.y <= 9) {
                            Tank_A.turn(1);
                        } else {
                            Tank_A.turn(2);
                        }
                    }
                } else {
                    if (Tank_A.direction.x != 1 || Tank_A.direction.y != 0) {
                        Tank_A.direction.x = -1;
                        Tank_A.direction.y = 0;
                    } else {
                        if (Tank_A.Pos.y <= 9) {
                            Tank_A.turn(2);
                        } else {
                            Tank_A.turn(1);
                        }
                    }

                }

            } else {
                if (Tank_A.Pos.y - 9 <= 0) {
                    if (Tank_A.direction.x != 0 || Tank_A.direction.y != -1) {
                        Tank_A.direction.x = 0;
                        Tank_A.direction.y = 1;
                    } else {
                        if (Tank_A.Pos.x <= 9) {
                            Tank_A.turn(2);
                        } else {
                            Tank_A.turn(1);
                        }
                    }
                } else {
                    if (Tank_A.direction.x != 0 || Tank_A.direction.y != 1) {
                        Tank_A.direction.x = 0;
                        Tank_A.direction.y = -1;
                    } else {
                        if (Tank_A.Pos.x <= 9) {
                            Tank_A.turn(1);
                        } else {
                            Tank_A.turn(2);
                        }
                    }

                }

            }

        }
    }
}





void AI_judgeB() {
    int bull_size = bull.size();
    int i;
    int judge = 0;
    if ((Tank_A.Pos.x == Tank_B.Pos.x - 1 || Tank_A.Pos.x == Tank_B.Pos.x || Tank_A.Pos.x == Tank_B.Pos.x + 1) &&
        (Tank_A.Pos.y == Tank_B.Pos.y - 1 || Tank_A.Pos.y == Tank_B.Pos.y ||
         Tank_A.Pos.y == Tank_B.Pos.y + 1)) {//判断是否在周围的9格中有玩家坦克
        if (Tank_A.life_point <= Tank_B.life_point) {//如果生命值高于或等于玩家坦克，进行追击
            if (Tank_A.Pos.x < Tank_B.Pos.x) {
                if (Tank_B.direction.x == 1 && Tank_B.direction.y == 0) {
                    Tank_B.turn(1);
                } else {
                    Tank_B.direction.x = -1;
                    Tank_B.direction.y = 0;
                }
            } else if (Tank_A.Pos.x > Tank_B.Pos.x) {
                if (Tank_B.direction.x == -1 && Tank_B.direction.y == 0) {
                    Tank_B.turn(2);
                } else {
                    Tank_B.direction.x = 1;
                    Tank_B.direction.y = 0;
                }
            } else if (Tank_A.Pos.x == Tank_B.Pos.x) {
                if (Tank_A.Pos.y > Tank_B.Pos.y) {
                    if (Tank_B.direction.x != 0 || Tank_B.direction.y != -1) {
                        Tank_B.direction.x = 0;
                        Tank_B.direction.y = 1;
                    }
                } else if (Tank_A.Pos.y < Tank_B.Pos.y) {
                    if (Tank_B.direction.x != 0 || Tank_B.direction.y != 1) {
                        Tank_B.direction.x = 0;
                        Tank_B.direction.y = -1;
                    }
                }
            } else {//如果生命值低于敌方玩家，进行逃离
                if (Tank_A.Pos.x < Tank_B.Pos.x) {
                    if (Tank_B.direction.x != -1 || Tank_B.direction.y != 0) {
                        Tank_B.direction.x = 1;
                        Tank_B.direction.y = 0;
                    } else {
                        Tank_B.turn(2);
                    }
                } else if (Tank_A.Pos.x > Tank_B.Pos.x) {
                    if (Tank_B.direction.x != 1 || Tank_B.direction.y != 0) {
                        Tank_B.direction.x = -1;
                        Tank_B.direction.y = 0;
                    } else {
                        Tank_B.turn(1);
                    }
                } else if (Tank_A.Pos.x == Tank_B.Pos.x) {
                    if (Tank_A.Pos.y > Tank_B.Pos.y) {
                        if (Tank_B.direction.x != 0 || Tank_B.direction.y != 1) {
                            Tank_B.direction.x = 0;
                            Tank_B.direction.y = -1;
                        }
                    } else if (Tank_A.Pos.y < Tank_B.Pos.y) {
                        if (Tank_B.direction.x != 0 || Tank_B.direction.y != -1) {
                            Tank_B.direction.x = 0;
                            Tank_B.direction.y = 1;
                        }
                    }
                }
            }
        }
    }else { //判断是否有子弹下回合会打中自己
        for (i = 1; i <= bull_size; i++) {
            Bullet temp = bull.front();
            bull.pop_front();
            if (temp.Pos + temp.direction + temp.direction == Tank_B.Pos + Tank_B.direction ||
                temp.Pos + temp.direction == Tank_B.Pos + Tank_B.direction) {
                judge = 1;
            }
            bull.push_back(temp);
        }
        if (judge == 1) {   //只能判断出很少情况。。
            Tank_B.turn(1);
        } else {
            if (abs(Tank_B.Pos.x - 9) >= abs(Tank_B.Pos.y - 9)) {
                if (Tank_B.Pos.x - 9 <= 0) {
                    if (Tank_B.direction.x != -1 || Tank_B.direction.y != 0) {
                        Tank_B.direction.x = 1;
                        Tank_B.direction.y = 0;
                    } else {
                        if (Tank_B.Pos.y <= 9) {
                            Tank_B.turn(1);
                        } else {
                            Tank_B.turn(2);
                        }
                    }
                } else {
                    if (Tank_B.direction.x != 1 || Tank_B.direction.y != 0) {
                        Tank_B.direction.x = -1;
                        Tank_B.direction.y = 0;
                    } else {
                        if (Tank_B.Pos.y <= 9) {
                            Tank_B.turn(2);
                        } else {
                            Tank_B.turn(1);
                        }
                    }

                }

            } else {
                if (Tank_B.Pos.y - 9 <= 0) {
                    if (Tank_B.direction.x != 0 || Tank_B.direction.y != -1) {
                        Tank_B.direction.x = 0;
                        Tank_B.direction.y = 1;
                    } else {
                        if (Tank_B.Pos.x <= 9) {
                            Tank_B.turn(2);
                        } else {
                            Tank_B.turn(1);
                        }
                    }
                } else {
                    if (Tank_B.direction.x != 0 || Tank_B.direction.y != 1) {
                        Tank_B.direction.x = 0;
                        Tank_B.direction.y = -1;
                    } else {
                        if (Tank_B.Pos.x <= 9) {
                            Tank_B.turn(1);
                        } else {
                            Tank_B.turn(2);
                        }
                    }

                }

            }

        }
    }
}




void plot_map() {

    cout << "A: " << Tank_A.life_point << ", B: " << Tank_B.life_point << ", Turn: " << turn << endl;
    char Map[31][61];
    int i, j;
    //先把分割线全部定义
    for (i = 1; i <= 31; i++) {
        for (j = 1; j <= 61; j++) {
            if (j % 2 == 0) {
                Map[i][j] = '|';
            }
        }
    }
    //再定义地图内和地图外
    for (i = 1; i <= 31; i++) {
        for (j = 1; j <= 61; j++) {
            if (j % 2 != 0) {
                if (j >= lower * 2 + 11 && j <= upper * 2 + 11 && i >= lower + 6 && i <= upper + 6) {
                    Map[i][j] = ' ';
                } else {
                    Map[i][j] = '-';
                }
            }
        }
    }
    //然后将子弹位置打印出来
    int bull_size = bull.size();
    int k;
    for (k = 1; k <= bull_size; k++) {
        Bullet temp = bull.front();
        bull.pop_front();
        for (i = 1; i < 31; i++) {
            for (j = 1; j <= 61; j++) {
                if (i == temp.Pos.y + 6 && j == temp.Pos.x * 2 + 11) {
                    Map[i][j] = '*';
                }
            }
        }
        bull.push_back(temp);
    }

    //最后赋予坦克位置
    for (i = 1; i <= 31; i++) {
        for (j = 1; j <= 61; j++) {
            if (i == Tank_A.Pos.y + 6 && j == Tank_A.Pos.x * 2 + 11) {
                Map[i][j] = 'A';
            } else if (i == Tank_B.Pos.y + 6 && j == Tank_B.Pos.x * 2 + 11) {
                Map[i][j] = 'B';
            }
        }
    }


    for (int rowone = 1; rowone <= 30; rowone++) {
        for (int columnone = 1; columnone <= 60; columnone++) {
            cout << Map[rowone][columnone];
        }
        cout << endl;
    }

    ofstream log;
    log.open("tankwar.log", ios::app);
    log << "A: " << Tank_A.life_point << ", B: " << Tank_B.life_point << ", Turn: " << turn << endl;
    for (int rowtwo = 1; rowtwo <= 30; rowtwo++) {
        for (int columntwo = 1; columntwo <= 60; columntwo++) {
            log << Map[rowtwo][columntwo];
        }
        log << endl;
    }
    log.close();
}





void help(){
    cout<<"  -h|--help print this help message"<<endl;
    cout<<"  --log-file filename write the logs in filename (default: tankwar.log)"<<endl;
    cout<<"  -m m|--mode=m play tank war in m (PVP/PVE/DEMO) mode (default: PVP)"<<endl;
    cout<<"  -p p|--initial-life=p each tank has p life points initially, p >= 1 (default: 5)"<<endl;
}


#endif //PROJECT2_LAYER2_H
