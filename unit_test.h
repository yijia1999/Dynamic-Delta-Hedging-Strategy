//
//  unit_test.h
//  midproject
//
//

#ifndef unit_test_h
#define unit_test_h
#include <iostream>
#include <fstream>
#include <sstream>
#include "BSM.h"
#include "delta_hedge.h"
#include "stock_simulation.h"
#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;
void test_BSM_price()
{
    //* constructor: BSM(string flag, double K, double S, double r, double d, double T, double sigma)
    BSM bs1("C",100,105,0.02,0,2,0.05);
    double price = bs1.BSM_price();
    assert(abs(9.2760 - price) < 0.001);
    cout << "BSM class call price function passed! " <<endl;
    BSM bs2("P",100,95,0.02,0,2,0.05);
    price = bs2.BSM_price();
    assert(abs(3.2683- price) < 0.001);
    cout << "BSM class put price function passed! " <<endl;
}
void test_BSM_delta()
{
    //* constructor: BSM(string flag, double K, double S, double r, double d, double T, double sigma)
    BSM bs1("C",100,105,0.02,0,2,0.05);
    double delta = bs1.BSM_delta();
    assert(abs(0.9017 - delta) < 0.001);
    cout << "BSM class call delta function passed! " <<endl;
    BSM bs2("P",100,95,0.02,0,2,0.05);
    delta = bs2.BSM_delta();
    assert(abs(-0.5495 - delta) < 0.001);
    cout << "BSM class put delta function passed! " <<endl;
}
void test_BSM_iv()
{
    //* constructor: BSM(string flag, double K, double S, double r, double d, double T, double sigma)
    BSM bs1("C",100,105,0.02,0,2);
    double iv = bs1.BSM_iv(10);
    assert(abs(0.071971 - iv) < 0.001);
    cout << "BSM class call delta function passed! " <<endl;
    BSM bs2("P",100,95,0.02,0,2);
    iv = bs2.BSM_iv(5);
    assert(abs(0.082413- iv) < 0.001);
    cout << "BSM class put delta function passed! " <<endl;

}
void unit_test()
{
    test_BSM_price();
    test_BSM_delta();
    test_BSM_iv();
}

#endif /* unit_test_h */
