#include <iostream>
#include <cmath>

#include "Solver.hpp"

using namespace std;

void solveQ1(int k, int n, int m, int *X, int *Y, Solver &s){
    int mu[k][n][m];
    for(int h=0; h<k; h++){
        vec<Lit> solution_exists;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                mu[h][i][j] = s.newVar();
            }
        }
        for(int i=0; i<=n-X[h]; i++){
            for(int j=0; j<=m-Y[h]; j++){
                solution_exists.push(Lit(mu[h][i][j]));
            }
        }
        for(int i=n-X[h]+1; i<n; i++){
            for(int j=m-Y[h]+1; j<m; j++){
                s.addUnit(~Lit(mu[h][i][j]));
            }
        }
        s.addClause(solution_exists);
    }

    for(int h=0; h<k; h++){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                for(int h2=0; h2<k && h2!=h; h2++){
                    for(int i2=i;i2<n && i2<i+X[h]; i2++){
                        for(int j2=j;j2<m && j2<j+Y[h]; j2++){
                            s.addBinary(~Lit(mu[h][i][j]), ~Lit(mu[h2][i2][j2]));
                        }
                    }
                }
            }
        }
    }

    s.solve();
    cout << s.okay() << endl;
    for(int h =0; h<k; h++){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(s.model[mu[h][i][j]] == l_True){
                    cout << h + 1 <<" "<<i<<" "<<j<<endl;
                }
            }
        }
    }   
}

int main(){
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
    solveQ1(k, n, m, X,Y, s);
}
