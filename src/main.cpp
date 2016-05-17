#include <iostream>
#include <cmath>

#include "Solver.hpp"

inline int max(int x, int y){
    return (x > y) ? x : y;
}

using namespace std;

void solve2D(int k, int n, int m, int *X, int *Y, Solver &s){
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
                for(int h2=0; h2<k; h2++){
                    if(h == h2)
                        continue;
                    for(int i2=max(i-X[h2], 0);i2<n && i2<i+X[h]; i2++){
                        for(int j2=max(j-Y[h2], 0);j2<m && j2<j+Y[h]; j2++){
                            s.addBinary(~Lit(mu[h][i][j]), ~Lit(mu[h2][i2][j2]));
                            if(h2 == 24 && h == 27){
                                if(i == 4 && j == 11){
                                    cout << "i2: " << i2 << " j2: " << j2 << endl;
                                }
                            }
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
void solve3D(int k, int n, int m, int p, int *X, int *Y, int *Z, Solver &s){
    int mu[k][n][m][p];
    for(int h=0; h<k; h++){
        vec<Lit> solution_exists;
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                for(int g=0; g<p; g++)
                    mu[h][i][j][g] = s.newVar();

        for(int i=0; i<=n-X[h]; i++)
            for(int j=0; j<=m-Y[h]; j++)
                for(int g=0; g<=p-Z[h]; g++)
                    solution_exists.push(Lit(mu[h][i][j][g]));

        for(int i=n-X[h]+1; i<n; i++)
            for(int j=m-Y[h]+1; j<m; j++)
                for(int g=p-Z[h]+1; g<p; g++)
                    s.addUnit(~Lit(mu[h][i][j][g]));
        s.addClause(solution_exists);
    }

    for(int h=0; h<k; h++)
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                for(int g=0; g<p; g++)
                    for(int h2=0; h2<k && h2!=h; h2++)
                        for(int i2=i;i2<n && i2<i+X[h]; i2++)
                            for(int j2=j;j2<m && j2<j+Y[h]; j2++)
                                for(int g2=g;g2<p && g2<g+Z[h]; g2++)
                                    s.addBinary(~Lit(mu[h][i][j][g]), ~Lit(mu[h2][i2][j2][g2]));

    s.solve();
    cout << s.okay() << endl;
    for(int h =0; h<k; h++)
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                for(int g=0; g<p; g++)
                    if(s.model[mu[h][i][j][g]] == l_True)
                        cout << h + 1 <<" "<<i<<" "<<j << " " << g <<endl;
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
    solve2D(k, n, m, X,Y, s);
    //k =4;
    //m = 3;
    //n=3;
    //int p = 3;
    //int X[] = {1,2,2,1};
    //int Y[] = {3,2,1,2};
    //int Z[] = {3,2,2,1};
    //solve3D(k, n, m, p, X, Y, Z, s);
}
