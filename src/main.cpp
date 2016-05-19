#include <iostream>
#include <cmath>

#include "Solver.hpp"

inline int max(int x, int y){
    return (x > y) ? x : y;
}

using namespace std;

void Solve2D(int k, int n, int m, int *X, int *Y){
    Solver s;
    int mu[k][n][m][2];
    for(int i=0; i<k; i++){
        for(int x=0; x<n; x++){
            for(int y=0; y<m; y++){
                mu[i][x][y][0] = s.newVar();
                mu[i][x][y][1] = s.newVar();
            }
        }
    }

    for(int i=0; i<k; i++){
        vec<Lit> solution_exists;
        for(int x0=0; x0<=n-X[i]; x0++){
            for(int y0=0; y0<=m-Y[i]; y0++){
                solution_exists.push(Lit(mu[i][x0][y0][0]));
                for(int x1=0; x1<n; x1++){
                    for(int y1=0; y1<m; y1++){
                        if(x0<=x1 && x1<(x0+X[i]) && y0 <= y1 && y1<(y0+Y[i])){
                            s.addBinary(~Lit(mu[i][x0][y0][0]), Lit(mu[i][x1][y1][1]));
                        }
                    }
                }
            }
        }
        s.addClause(solution_exists);
    }

    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            if(i == j)
                continue;
            for(int x=0; x<n; x++){
                for(int y=0; y<m; y++){
                    s.addBinary(~Lit(mu[i][x][y][1]), ~Lit(mu[j][x][y][1]));
                }
            }
        }
    }

    if(!s.solve() || !s.okay()){
        cout << 0 << endl;
        exit(42);
    }
    cerr << s.okay() << endl;
    if(s.okay()){
        for(int i =0; i<k; i++){
            for(int x=0; x<n; x++){
                for(int y=0; y<m; y++){
                    if(s.model[mu[i][x][y][0]] == l_True){
                        cout << ""<< i + 1 <<" "<<x<<" "<<y<<endl;
                    }
                }
            }
        }
    }
}

void Solve2DRetournement(int k, int n, int m, int *X, int *Y){
    Solver s;
    int mu[k][n][m][2];
    int R[k];
    for(int i=0; i<k; i++){
        for(int x=0; x<n; x++){
            for(int y=0; y<m; y++){
                mu[i][x][y][0] = s.newVar();
                mu[i][x][y][1] = s.newVar();
            }
        }
        R[i] = s.newVar();
    }

    for(int i=0; i<k; i++){
        vec<Lit> solution_exists;
        for(int x0=0; x0<n; x0++){
            for(int y0=0; y0<m; y0++){
                if(x0<=n-X[i] && y0<=m-Y[i]){
                    for(int x1=0; x1<n; x1++){
                        for(int y1=0; y1<m; y1++){
                            if(x0<=x1 && x1<(x0+X[i]) && y0 <= y1 && y1<(y0+Y[i])){
                                s.addTernary(~Lit(mu[i][x0][y0][0]), Lit(R[i]), Lit(mu[i][x1][y1][1]));
                            }
                        }
                    }
                } else {
                    s.addBinary(~Lit(mu[i][x0][y0][0]), Lit(R[i]));
                }
                if(x0<=n-Y[i] && y0<=m-X[i]){
                    for(int x1=0; x1<n; x1++){
                        for(int y1=0; y1<m; y1++){
                            if(x0<=x1 && x1<(x0+Y[i]) && y0 <= y1 && y1<(y0+X[i])){
                                s.addTernary(~Lit(mu[i][x0][y0][0]), ~Lit(R[i]), Lit(mu[i][x1][y1][1]));
                            }
                        }
                    }
                } else {
                    s.addBinary(~Lit(mu[i][x0][y0][0]), ~Lit(R[i]));
                }
                if((x0<=n-Y[i] && y0<=m-X[i])||(x0<=n-X[i] && y0<=m-Y[i])){
                    solution_exists.push(Lit(mu[i][x0][y0][0]));
                }
            }
        }
        s.addClause(solution_exists);
    }

    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            if(i == j)
                continue;
            for(int x=0; x<n; x++){
                for(int y=0; y<m; y++){
                    s.addBinary(~Lit(mu[i][x][y][1]), ~Lit(mu[j][x][y][1]));
                }
            }
        }
    }

    if(!s.solve() || !s.okay()){
        cout << 0 << endl;
        exit(42);
    }
    cerr << s.okay() << endl;
    if(s.okay()){
        for(int i =0; i<k; i++){
            for(int x=0; x<n; x++){
                for(int y=0; y<m; y++){
                    if(s.model[mu[i][x][y][0]] == l_True){
                        cout << ""<< i + 1 <<" "<<x<<" "<<y <<" "<<(s.model[R[i]]==l_True)<<endl;
                    }
                }
            }
        }
    }
}

void solve3D(int k, int n, int m, int o, int *X, int *Y, int *Z, bool flottant=false){
    Solver s;
    int mu[k][n][m][o][2];
    for(int i=0; i<k; i++){
        for(int x=0; x<n; x++){
            for(int y=0; y<m; y++){
                for(int z=0; z<o; z++){
                    mu[i][x][y][z][0] = s.newVar();
                    mu[i][x][y][z][1] = s.newVar();
                }
            }
        }
    }

    for(int i=0; i<k; i++){
        vec<Lit> solution_exists;
        for(int x0=0; x0<n; x0++){
            for(int y0=0; y0<m; y0++){
                for(int z0=0; z0<o; z0++){
                    solution_exists.push(Lit(mu[i][x0][y0][z0][0]));
                    if(x0<=m-X[i] && y0<=m-Y[i] && z0<=o-Z[i]){
                        for(int x1=0; x1<n; x1++){
                            for(int y1=0; y1<m; y1++){
                                for(int z1=0; z1<o; z1++){
                                    if(x0<=x1 && x1<(x0+X[i])
                                            && y0 <= y1 && y1<(y0+Y[i])
                                            && z0 <= z1 && z1<(z0+Z[i])){
                                        s.addBinary(~Lit(mu[i][x0][y0][z0][0]), Lit(mu[i][x1][y1][z1][1]));
                                    }
                                    if(x0!=x1 && y0!=y1 && z0!=z1){
                                        s.addBinary(~Lit(mu[i][x0][y0][z0][0]), ~Lit(mu[i][x1][y1][z1][0]));
                                    }
                                }
                            }

                        }
                    }else{
                        s.addUnit(~Lit(mu[i][x0][y0][z0][0]));
                    }
                }
            }
        }
        s.addClause(solution_exists);
    }

    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            if(i == j)
                continue;
            for(int x=0; x<n; x++){
                for(int y=0; y<m; y++){
                    for(int z=0; z<o; z++){
                        s.addBinary(~Lit(mu[i][x][y][z][1]), ~Lit(mu[j][x][y][z][1]));
                    }
                }
            }
        }
    }

    if(flottant){
        for(int x=0; x<n; x++){
            for(int y=0; y<m; y++){
                for(int z=1; z<o; z++){
                    for(int i=0; i<k; i++){
                        vec<Lit> nonFloating;
                        nonFloating.push(~Lit(mu[i][x][y][z][1]));
                        for(int j=0; j<k; j++){
                            nonFloating.push(Lit(mu[j][x][y][z-1][1]));
                        }
                        s.addClause(nonFloating);
                    }
                }
            }
        }
        for(int x=0; x<n; x++){
            for(int y=0; y<m; y++){
                for(int z=0; z<o; z++){
                    for(int i=0; i<k; i++){
                        vec<Lit> reverseImpl;
                        reverseImpl.push(~Lit(mu[i][x][y][z][1]));
                        for(int x1=x; x1>=0 && x1>x-X[i]; x1--){
                            for(int y1=y; y1>=0 && y1>y-Y[i]; y1--){
                                for(int z1=z; z1>=0 && z1>z-Z[i]; z1--){
                                    reverseImpl.push(Lit(mu[i][x1][y1][z1][0]));
                                }
                            }
                        }
                        s.addClause(reverseImpl);
                    }
                }
            }
        }
    }

    if(!s.solve() || !s.okay()){
        cout << 0 << endl;
        exit(42);
    }
    cerr << s.okay() << endl;
    if(s.okay()){
        for(int i =0; i<k; i++){
            for(int x=0; x<n; x++){
                for(int y=0; y<m; y++){
                    for(int z=0; z<o; z++){
                        if(s.model[mu[i][x][y][z][0]] == l_True){
                            cout << i + 1 <<" "<< x<<" "<<y<<" "<<z<<" "<<endl;
                        }
                    }
                }
            }
        }
    }
}

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
            }
            else if (argv[1][1] == 'f'){
                mode = 'f';
        }
    }
    }

    if(mode == '2'){
        cout << "| Solving in base mode" << endl;
        Solver s;
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

        Solve2D(k, n, m, X,Y);
    } else if(mode == 'r'){
        cout << "| Solving in swap mode" << endl;
        Solver s;
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
        Solve2DRetournement(k, n, m, X,Y);
    } else if (mode == '3' || mode == 'f') {
        bool floating = false;
        if(mode == 'f')
            floating = true;
        cout << "| Solving in 3D mode" << endl;
        int k = 4;
        int m = 3;
        int n = 3;
        int o = 3;
        int X2[] = {1,2,2,1};
        int Y2[] = {3,2,1,2};
        int Z2[] = {3,2,2,1};
        solve3D(k, n, m, o, X2, Y2, Z2, floating);
    }
}
