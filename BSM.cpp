//
//  BSM.cpp
//  midproject
//
//
#include <math.h>
#include <iostream>
#include "BSM.h"
using namespace std;

BSM::BSM()
{
    this->flag = 'c';
    this->K = 0.0;
    this->S = 0.0;
    this->r = 0.0;
    this->d = 0.0;
    this->T = 0.0;
    this->sigma = 0.0;
}
BSM::BSM(string flag, double K, double S, double r, double d, double T, double sigma)
{
    this->flag = flag;
    this->K = K;
    this->S = S;
    this->r = r;
    this->d = d;
    this->T = T;
    this->sigma = sigma;
}
BSM::BSM(string flag, double K, double S, double r, double d, double T)
{
    this->flag = flag;
    this->K = K;
    this->S = S;
    this->r = r;
    this->d = d;
    this->T = T;
}
BSM::~BSM(){}
double BSM::get_S(){return this->S;}
double BSM::get_r(){return this->r;}
double BSM::get_T(){return this->T;}
double BSM::N(const double &x)
{
    return 0.5 * erfc(-x * M_SQRT1_2);
}
double BSM::BSM_price()
{
    double BS_price;
    double d1 = (log(S/K)+(r-d+0.5*sigma*sigma)*T)/(sigma*sqrt(T));
    double d2 = d1 - sigma*sqrt(T);
    if (flag == "c" or flag == "C")
    {
        BS_price = (S*exp(-d*T)*N(d1)) - (K*exp(-r*T)* N(d2));
//        cout << "===> Black scholes call price: " << BS_price << endl;
    }
    else if (flag == "p" or flag == "P")
    {
        BS_price = (K*exp(-r*T)*N(-d2)) - (S*exp(-d*T)*N(-d1));
//        cout << "===> Black scholes put price: " << BS_price << endl;
    }
    else
    {
        cout << "wrong input! use c or C, p or P" <<endl;
        return 0;
    }
    return BS_price;
}
double BSM::BSM_delta()
{
    double BS_delta;
    double d1 = ((log(S/K)+(r-d+0.5*sigma*sigma)*T))/(sigma*sqrt(T));
    if (flag == "c" or flag == "C")
    {
        BS_delta = N(d1);
//        cout << "===> Black scholes delta: " <<d1 << " " << BS_delta << endl;
    }
    else if (flag == "p" or flag == "P")
    {
        BS_delta = N(d1)-1;
//        cout << "===> Black scholes delta: " << delta << endl;
    }
    else
    {
        cout << "wrong input! use c or C, p or P" <<endl;
        return 0;
    }
    return BS_delta;
}
double BSM::BSM_iv(double mktprice)
{
    double low = 0.0;
    double high = 1.0;
    double iv = 0.5;
    do {
        double iv_price = BSM(flag, K, S, r, d, T, iv).BSM_price();
//        cout << "IV " <<iv <<endl;
//        cout << "flag " <<flag<< " " << K<< " " <<S<< " " <<r<<" " <<d<<" " <<T<< " " << iv <<endl;
        if (mktprice - iv_price < 0.0){high = iv;}
        else {low = iv;}
//        cout << "*******" << high << " " << iv << " " << low <<endl;
//        cout << "IV " <<iv << " " << iv_price << " " << mktprice <<endl;
//        cout << "low:" << low_price << " iv:" << iv_price << " mkt:" << mktprice << " high:" <<high_price<<endl;
        iv = 0.5*(low + high);
    } while(high - low > 0.0001);
    return iv;
}
//double BSM::BSM_iv(double mktprice)
//{
//    vector<double> price;
//    vector<double> vol;
//    vector<double> vega;
//    vol.push_back(0.3);
////    cout << "market price" << marketPrice << endl;
//    double K = this->K;
//    double T = this->T;
//    double r = this->r;
//    double S = this->S;
//    string flag = this->flag;
//    double d= this->d;
////    cout << K <<","<< T <<","<< r <<","<< S <<","<< pc<<","<<d<< endl;
//
//    int i = 0;
//    do{
//        i++;
//        double vol_0 = vol[i-1];
//        BSM bs(flag, K, S, r, d, T, vol_0);
//        long double d1 = ((log(S/K)+(r-d+0.5*sigma*sigma)*T))/(sigma*sqrt(T)); //normal distribution factor
//        vega.push_back(S*N(d1)*sqrt(T));
//        price.push_back(bs.BSM_price());
//        double v = vol[i-1] - (price[i-1] - mktprice)/vega[i-1];
//        vol.push_back(v);
////        cout << bs.BSM_price() << " * " <<mktprice <<endl;
////        cout << bs.calculateVega() << endl;
////        cout << bs.calculateValue() << endl;
////        cout << "vol" << v << endl;
////        cout << i << endl;
//
//    } while(abs(vol[i]-vol[i-1]) >= 0.0001 && i<= 100);
//    return vol[i];
//}

