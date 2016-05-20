
bool Solve2D(int k, int n, int m, int *X, int *Y, int p=0){
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
                            // gama(i, x0, y0) -> beta(i, x1, y1) un départ implique un block
                            s.addBinary(~Lit(mu[i][x0][y0][0]), Lit(mu[i][x1][y1][1]));
                        }
                    }
                }

            }
        }
        s.addClause(solution_exists);
    }

    if(p>0){
        for(int i=0; i<k; i++){
            for(int x0=0; x0<n; x0++){
                for(int y0=0; y0<m; y0++){
                    for(int x1=0; x1<n; x1++){
                        for(int y1=0; y1<m; y1++){
                            // beta(i, x0, y0) -> V(gama(i, x1, y1)) chaque block doit avoir un départ
                            vec<Lit> reverseImpl;
                            reverseImpl.push(~Lit(mu[i][x0][y0][1]));
                            for(int x1=x0; x1>=0 && x1>x0-X[i]; x1--){
                                for(int y1=y0; y1>=0 && y1>y0-Y[i]; y1--){
                                    reverseImpl.push(Lit(mu[i][x1][y1][0]));
                                }
                            }
                            s.addClause(reverseImpl);
                            if(x0 == x1 && y0==y1)
                                continue;
                            // Chaque rectanlge avoir son départ placé qu'une seule fois
                            s.addBinary(~Lit(mu[i][x0][y0][0]), ~Lit(mu[i][x1][y1][0]));
                        }
                    }
                }
            }
        }
    }

    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            if(i == j)
                continue;
            for(int x=0; x<n; x++){
                for(int y=0; y<m; y++){
                    // beta(i, x, y) -> ~beta(j, x, y) on  ne peut avoir q'un seul block en x,y
                    s.addBinary(~Lit(mu[i][x][y][1]), ~Lit(mu[j][x][y][1]));
                }
            }
        }
    }

    if(p>0 && p<=(m+n)*2){
        vector<tuple<int, int, int>> borders((m+n)*2);
        for(int x=0; x<n; x++){
            borders[x] = make_tuple(x, x,0);
            borders[n+x] = make_tuple(n+x, x,m-1);
        }
        for(int y=0; y<m; y++){
            cerr << "y: "<< y << endl;
            borders[2*n+y] = make_tuple(2*n+y, 0,y);
            borders[2*n+m+y] = make_tuple(2*n+m+y, n-1,y);
        }
        int c = borders.size()- p + 1;
        do{
            vec<Lit> b;
            for(int w=0; w<c; w++){
                for(int i=0; i<k; i++){
                    b.push(Lit(mu[i][get<1>(borders[w])][get<2>(borders[w])][1]));
                }
            }
            s.addClause(b);
        } while(next_combination(borders.begin(), borders.begin() + c, borders.end()));
    }

    if(!s.solve() || !s.okay()){
        return false;
    }
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
    return true;
}
