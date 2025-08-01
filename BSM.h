//
//  BSM.h
//  midproject
//
//

#ifndef BSM_h
#define BSM_h
#include <vector>
#include <math.h>
#include <string>

using namespace std;

class BSM{
private:
    string flag;
    double K;
    double S;
    double r;
    double d;
    double T;
    double sigma;
public:
    BSM();
    BSM(string flag, double K, double S, double r, double d, double T, double sigma);
    BSM(string flag, double K, double S, double r, double d, double T);
    ~BSM();
    double get_S();
    double get_r();
    double get_T();
    double N(const double &x);
    double BSM_price();
    double BSM_delta();
    double BSM_iv(double mktprice); //binary search for implied_volatility
    
};
#endif /* BSM_h */
