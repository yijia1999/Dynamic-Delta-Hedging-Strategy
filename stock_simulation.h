//
//  stock_simulation.h
//  midproject
//
//

#ifndef stock_simulation_h
#define stock_simulation_h
#include <vector>
using namespace std;

class stock_simulation {
private:
    double S0;
    double miu;
    double sigma;
    double r;
    double n;
    double T;
    vector<double> Z;
    vector<double> stock;
public:
    stock_simulation();
    stock_simulation(double S0, double miu, double sigma, double r, double n, double T);
    ~stock_simulation();
    vector<double> calculate();
};

#endif /* stock_simulation_h */
