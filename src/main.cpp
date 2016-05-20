#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <list>
#include <tuple>
#include <numeric>
#include <sstream>

#include "Solver.hpp"

#include "utils.cpp"

using namespace std;

#include "solve/2D.cpp"
#include "solve/swap.cpp"
#include "solve/3D.cpp"
#include "solve/robert.cpp"

int main(int argc, char *argv[]){
    char mode = '2';
    if(argc > 1){
        if(argv[1][0] == '-') {
            if(argv[1][1] == '2'){
                mode = '2';
            } else if (argv[1][1] == '3'){
                mode = '3';
            } else if (argv[1][1] == 'r'){
                mode = 'r';
            } else if (argv[1][1] == 'f'){
                mode = 'f';
            } else if (argv[1][1] == 'b'){
                if(argc < 3){
                    cerr << "You need a second argument for the border mode" << endl;
                    exit(-1);
                }
                mode = 'b';
            } else if (argv[1][1] == 's'){
                mode = 's';
            } else if (argv[1][1] == 'n'){
                if(argc < 3){
                    cerr << "You need a second argument for the super square mode(tm)" << endl;
                    exit(-1);
                }
                mode = 'n';
            }
        }
    }

    bool success = false;

    if(mode == '2' || mode == 'b'){
        cerr << "Solving in base mode" << endl;
        int k;
        int m;
        int n;
        cin >> k >> m >> n;
        int X[k];
        int Y[k];
        for(int i =0; i<k; i++){
            int a;
            cin >> a >> X[i] >> Y[i];
        }
        int min_border = 0;
        if (mode == 'b'){
            min_border = atoi(argv[2]);
            cerr << "With minimum border lenght = " << min_border << endl;
        }
        success = Solve2D(k, n, m, X,Y, min_border);
    } else if(mode == 'r'){
        cerr << "Solving in swap mode" << endl;
        int k;
        int m;
        int n;
        cin >> k >> m >> n;
        int X[k];
        int Y[k];
        for(int i =0; i<k; i++){
            int a;
            cin >> a >> X[i] >> Y[i];
        }
        success =Solve2DRetournement(k, n, m, X,Y);
    } else if (mode == '3' || mode == 'f') {
        bool floating = false;
        if(mode == 'f')
            floating = true;
        cerr << "Solving in 3D mode" << endl;
        int k = 4;
        int m = 3;
        int n = 3;
        int o = 3;
        int X2[] = {1,2,2,1};
        int Y2[] = {3,2,1,2};
        int Z2[] = {3,2,2,1};
        success = solve3D(k, n, m, o, X2, Y2, Z2, floating);
    } else if(mode == 's'){
        cerr << "Solving in smallest square mode" << endl;
        int k;
        int m;
        int n;
        cin >> k >> m >> n;
        int X[k];
        int Y[k];
        for(int i =0; i<k; i++){
            int a;
            cin >> a >> X[i] >> Y[i];
        }
        lepetitrobert(k, X, Y);
        success = true;

    } else if(mode == 'n'){
        cerr << "Solving in super square mode(tm)" << endl;
        int k = atoi(argv[2]);
        int X[k];
        int Y[k];
        for(int i =0; i<k; i++){
            X[i] = i+1;
            Y[i] = i+1;
        }
        lepetitrobert(k, X, Y);
        success = true;
    }

    if(!success){
        cout << 0 << endl;
        exit(42);
    }
}
