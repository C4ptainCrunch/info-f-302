int lepetitrobert(int k, int X[], int Y[]){
    bool success;

    int aire = 0;
    for (int i = 0; i < k; ++i)
    {
        aire += X[i] * Y[i];
    }
    int h = sqrt(aire);

    std::stringstream buffer;
    std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());

    do {
        cerr << "Trying with a size of " << h << endl;
        success = Solve2D(k, h, h, X,Y);
        cerr << "\b" << (success ? "Solvable" : "Insolvable") << endl;
        h = h * 2;
    } while(!success);
    int min = h/4;
    int max = h/2;

    cerr << "Lower bound : " << min << " Upper bound: "  << max << endl;

    do {
        int step = (max - min) / 2;
        int test = min + step;
        cerr << "Trying with a size of " << test << endl;
        if(Solve2D(k, test, test, X,Y)){
            cerr << "Solvable" << endl;
            max = test;
        } else {
            min = test;
            cerr << "Insolvable" << endl;
        }
    } while(min != max - 1);

    // std::string text = buffer.str();
    std::cout.rdbuf(old);

    cerr << "Minimal size is " << max << endl;
    cout << max << endl;
    return max;
}
