#include <iostream>
#include <fstream>
#include <deque>
#include<string>
#include<string.h>
#include<fstream>
#include <cstdlib>
#include "layer1.h"
#include"layer2.h"
using namespace std;

int main(int argc, char *argv[]) {
    int mode;//mode PVP=1  mode PVE=2; mode DEMO=3;
    int i;
    string file;
    Tank_A.life_point = 5;
    Tank_B.life_point = 5;
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            help();
            return 0;
        }
        if (!strcmp(argv[i], "--log-file")) {//this function should be ok to tailor the log file
            if (!argv[i + 1]) {
                file = "tankwar.log";
            } else {
                file = (argv[i + 1]);
            }
        }
        if (!strcmp(argv[i], "-p")) {
            Tank_A.life_point = atoi(argv[i + 1]);
            Tank_B.life_point = atoi(argv[i + 1]);
        }
        if (!strncmp(argv[i], "--initial-life=", 15)) {
            string s = argv[i];
            s = s.substr(15, 5);
            Tank_A.life_point = atoi(s.c_str());
            Tank_B.life_point = atoi(s.c_str());
        }


        if (!strcmp(argv[i], "-m")) {
            if (!strcmp(argv[i + 1], "PVP")) {
                mode = 1;
            } else if (!strcmp(argv[i + 1], "PVE")) {
                mode = 2;
            } else if (!strcmp(argv[i + 1], "DEMO")) {
                mode = 3;
            } else {
                help();
            }
        }
        if (!strcmp(argv[i], "--mode=PVP")) {
            mode = 1;
        }
        if (!strcmp(argv[i], "--mode=PVE")) {
            mode = 2;
        }
        if (!strcmp(argv[i], "--mode=DEMO")) {
            mode = 3;
        }
    }
    if (mode == 1) {
        cout << "You are playing PVP mode" << endl;
        cout<<"Please help set the location of two AI tanks in following format:"<<endl;
        cout<<"Player.1.posx  Player.1.posy Player.2.posx Player.2.posy Player.1.direction Player.2.direction"<<endl;
        cout<<"(direction: 0:left 1:right 2:down 3:up)"<<endl;
        cin >> Tank_A.Pos.x >> Tank_A.Pos.y >> Tank_B.Pos.x >> Tank_B.Pos.y;
        cin >> direct_A >> direct_B;
        Tank_A.initialize(direct_A);
        Tank_B.initialize(direct_B);
        plot_map();
        cout<<"input the turn for the next round:"<<endl;
        cout<<"(0:forward  1:turn left  2:turn right)"<<endl;

        while (cont == 1) {
            turn++;
            cin >> direct_A >> direct_B;

            Tank_A.turn(direct_A);
            Tank_A.move();

            Tank_B.turn(direct_B);
            Tank_B.move();

            if (turn % 3 == 1) { generate_bullet(Tank_A); }

            if (turn % 3 == 1) { generate_bullet(Tank_B); }
            judge_collisionA();
            judge_collisionB();


            judge_crash(Tank_A, Tank_B);
            if (cont == 0) {
                break;
            }


            move_bullet();
            judge_collisionA();
            judge_collisionB();

            move_bullet();
            judge_collisionA();
            judge_collisionB();


            if (turn % 16 == 0) {
                shrink();
            }

            judge_border();

            judge_life(Tank_A, Tank_B);
            if (cont == 0) {
                break;
            }
            plot_map();
            cout<<"input the turn for the next round:"<<endl;
            cout<<"(0:forward  1:turn left  2:turn right)"<<endl;
        }
    }

    if (mode == 2) {
        cout << "You are playing PVE mode" << endl;
        cout<<"Please help set the location of two tanks in following format:"<<endl;
        cout<<"AI.posx  AI.posy Player.posx Player.posy AI.direction Player.direction"<<endl;
        cout<<"(direction: 0:left 1:right 2:down 3:up)"<<endl;
        cin >> Tank_A.Pos.x >> Tank_A.Pos.y >> Tank_B.Pos.x >> Tank_B.Pos.y;
        cin >> direct_A >> direct_B;
        Tank_A.initialize(direct_A);
        Tank_B.initialize(direct_B);
        plot_map();
        cout<<"input the turn for the next round:"<<endl;
        cout<<"(0:forward  1:turn left  2:turn right)"<<endl;


        while (cont == 1) {
            turn++;
            cin >> direct_A;

            Tank_A.turn(direct_A);
            Tank_A.move();
            AI_judgeB();
            Tank_B.move();

            if (turn % 3 == 1) { generate_bullet(Tank_A); }

            if (turn % 3 == 1) { generate_bullet(Tank_B); }
            judge_collisionA();
            judge_collisionB();


            judge_crash(Tank_A, Tank_B);
            if (cont == 0) {
                break;
            }

            move_bullet();
            judge_collisionA();
            judge_collisionB();

            move_bullet();
            judge_collisionA();
            judge_collisionB();


            if (turn % 16 == 0) {
                shrink();
            }

            judge_border();

            judge_life(Tank_A, Tank_B);
            if (cont == 0) {
                break;
            }
            plot_map();
            cout<<"input the turn for the next round:"<<endl;
            cout<<"(0:forward  1:turn left  2:turn right)"<<endl;
        }
    }


    if (mode == 3) {
        cout << "Here is the DEMO mode" << endl;
        cout<<"Please help set the location of two AI tanks in following format:"<<endl;
        cout<<"AI.1.posx  AI.1.posy AI.2.posx AI.2.posy AI.1.direction AI.2.direction"<<endl;
        cout<<"(direction: 0:left 1:right 2:down 3:up)"<<endl;

        cin >> Tank_A.Pos.x >> Tank_A.Pos.y >> Tank_B.Pos.x >> Tank_B.Pos.y;
        cin >> direct_A >> direct_B;
        Tank_A.initialize(direct_A);
        Tank_B.initialize(direct_B);
        plot_map();

        while (cont == 1) {
            turn++;
            AI_judgeA();
            Tank_A.move();
            AI_judgeB();
            Tank_B.move();




            if (turn % 3 == 1) { generate_bullet(Tank_A); }

            if (turn % 3 == 1) { generate_bullet(Tank_B); }
            judge_collisionA();
            judge_collisionB();


            judge_crash(Tank_A, Tank_B);
            if (cont == 0) {
                break;
            }


            move_bullet();
            judge_collisionA();
            judge_collisionB();

            move_bullet();
            judge_collisionA();
            judge_collisionB();


            if (turn % 16 == 0) {
                shrink();
            }

            judge_border();

            judge_life(Tank_A, Tank_B);
            if (cont == 0) {
                break;
            }
            plot_map();
        }

    }
}
