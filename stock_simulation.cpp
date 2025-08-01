//
//  stock_simulation.cpp
//  midproject
//
//

#include "stock_simulation.h"
#include <random>
using namespace std;
std::mt19937 generator(12345);
std::normal_distribution<double> normal(/*mean=*/0.0, /*stddev=*/1.0);

stock_simulation::stock_simulation()
{
    this->S0 = 0.0;
    this->miu = 0.0;
    this->sigma = 0.0;
    this->r = 0.0;
    this->n = 0.0;
    this->T = 0.0;
}
stock_simulation::stock_simulation(double S0, double miu, double sigma, double r, double n, double T)
{
    this->S0 = S0;
    this->miu = miu;
    this->sigma = sigma;
    this->r = r;
    this->n = n;
    this->T = T;
}
stock_simulation::~stock_simulation(){}
vector<double> stock_simulation::calculate()
{
    for (int i=0; i<n; i++)
    {
        Z.push_back(normal(generator));
    }
    stock.push_back(S0);
    double dt = T/n;
    for (int i=1; i<=n; i++)
    {
        stock.push_back(stock[i-1] + stock[i-1]*miu*dt + sigma*stock[i-1]*sqrt(dt)*Z[i-1]);
    }
    return stock;
}

