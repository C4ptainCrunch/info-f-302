
bool Solve2DRetournement(int k, int n, int m, int *X, int *Y){
    Solver s;
    s.verbosity=0;
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
        return false;
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
    return true;
}
