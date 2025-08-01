//
//  main.cpp
//  midproject
//
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "BSM.h"
#include "delta_hedge.h"
#include "stock_simulation.h"
#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "unit_test.h"
using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

double time_to_maturity(date d0, date d1) {
    double ndays = (d1-d0).days() + 1;
    double nwkends = 2*((ndays+d0.day_of_week())/7); // 2*Saturdays
    if( d0.day_of_week() == boost::date_time::Sunday ) {nwkends++;}
    if( d1.day_of_week() == boost::date_time::Saturday ) {nwkends--;}
    return (ndays - nwkends - 1)/252;
}

int main(){
    unit_test();
    //******************************* Q1. test delta_hedge using BSM *******************************//
    //************* 1.1(a) simulate the price series: St-stock price path *************//
    vector<vector<double>> St; //size = 1000*100
    for (int i=0; i<1000; i++)
    {
    //* constructor: stock_simulation(double S0, double miu, double sigma, double r, double n, double T)
        stock_simulation sample(100,0.05,0.24,0.025,100,0.4);
        St.push_back(sample.calculate());
    }
    //************* 1.1(b) export 100 lines stock_path csv and plot *************//
    ofstream stock_path("/Users/wangyijia/Desktop/gatech 21fall/ISYE6767/homework/midproject/data/stock_path.csv");
    stock_path << "Stock_Path" << endl;
    //(double S0, double miu, double sigma, double r, double n, double T)
    for (int i=0; i<100; i++)
    {
        for (int j=0; j<=100; j++)
        {
            stock_path << St[i][j] << ",";
        }
        stock_path << endl;
    }
    //************* 1.2 option path: bs-option price *************//
    vector<delta_hedge> dh;
    vector<vector<double>> call_price;
    for (int i=0; i<1000; i++)
    {
        vector<BSM> BSM1;
        vector<double> BSM1_price;
        for(int j=0; j<St[i].size(); j++)
        {
            double t = 0.4-0.4*j/(St[i].size()-1);
            double S = St[i][j];
    //* constructor: BSM(string flag, double K, double S, double r, double d, double T, double sigma)
            BSM tmp = BSM("c",105,S,0.025,0,t,0.24);
            BSM1.push_back(tmp);
            BSM1_price.push_back(tmp.BSM_price());
        }
        call_price.push_back(BSM1_price);
        dh.push_back(BSM1);
    }
    for (int i=0; i<100; i++)
    {
        cout << " simulation time: " << i << ", stock price: " << St[0][i] <<  ", call option price: "  << call_price[0][i] << endl;
    }
    //************* 1.2(b) export 100 lines option_path csv and plot *************//
    ofstream option_path("/Users/wangyijia/Desktop/gatech 21fall/ISYE6767/homework/midproject/data/option_path.csv");
    option_path << "Option_Path" << endl;
    //(double S0, double miu, double sigma, double r, double n, double T)
    for (int i=0; i<100; i++)
    {
        for (int j=0; j<=100; j++)
        {
            option_path << call_price[i][j] << ",";
        }
        option_path << endl;
    }
    //************* 1.3(a) construct the delta-hedging portfolios *************//
    vector<double> hedging_error;
    for (int i=0; i<dh.size(); i++)
    {
        hedging_error.push_back(dh[i].hedge_error());
    }
    //************* 1.3(b) export 1000 hedging_errors.csv and plot *************//
    ofstream  HE("/Users/wangyijia/Desktop/gatech 21fall/ISYE6767/homework/midproject/data/hedging_error.csv");
    HE << "Hedging_Error" << endl;
    for(int i=0; i<=1000; i++)
    {
        HE << hedging_error[i] << endl;
    }
    //******************************* Q2. real market data *******************************//
    //************* 2(a). calculate total wealth *************//
    //* read interest.csv *//
    vector<date> interest_date;
    vector<double> interest_rate;
    ifstream interest("/Users/wangyijia/Desktop/gatech 21fall/ISYE6767/homework/midproject/data/interest.csv");
    if (interest.fail()) {cout<<"Open interest.csv fail!"<<endl; exit(0);}
    int i = 0;
    string line;
    string field;
    cout << "import interest.csv" << endl;
    while(getline(interest, line))
    {
        if (i >= 1) // exclude header
        {
            istringstream sin(line);
            getline(sin, field, ',');
            interest_date.push_back(from_simple_string(field));
            getline(sin,field);
            interest_rate.push_back(stod(field)/100);
        }
        i++;
    }
    cout << "read interest.csv completed! " << endl;
    interest.close();
    //* read stock sec_GOOG.csv *//
    vector<date> stock_date;
    vector<double> stock_price;
    ifstream stock("/Users/wangyijia/Desktop/gatech 21fall/ISYE6767/homework/midproject/data/sec_GOOG.csv");
    if (stock.fail()) {cout<<"Open sec_GOOG.csv fail!"<<endl; exit(0);}
    i = 0;
    cout << "import sec_GOOG.csv" << endl;
    while(getline(stock, line))
    {
        if (i >= 1) // exclude header
        {
            istringstream sin(line);
            getline(sin, field, ',');
            stock_date.push_back(from_simple_string(field));
            getline(sin,field);
            stock_price.push_back(stod(field));
        }
        i++;
    }
    cout << "read sec_GOOG.csv completed! " << endl;
    stock.close();
    //* read option op_GOOG.csv *//
    vector<date> option_date;
    vector<date> option_exdate;
    vector<string> option_flag;
    vector<double> option_K;
    vector<double> option_mktprice;
    string bid;
    string ask;
    ifstream option("/Users/wangyijia/Desktop/gatech 21fall/ISYE6767/homework/midproject/data/op_GOOG.csv");
    if (option.fail()) {cout<<"Open op_GOOG.csv fail!"<<endl; exit(0);}
    i = 0;
    cout << "import op_GOOG.csv" << endl;
    while(getline(option, line))
    {
        if (i >= 1) // exclude header
        {
            istringstream sin(line);
            getline(sin, field, ',');
            option_date.push_back(from_simple_string(field));
            getline(sin, field, ',');
            option_exdate.push_back(from_simple_string(field));
            getline(sin, field, ',');
            option_flag.push_back(field);
            getline(sin, field, ',');
            option_K.push_back(stod(field));
            getline(sin, bid, ',');
            getline(sin, ask);
            option_mktprice.push_back(0.5*stod(bid)+0.5*stod(ask));
        }
        i++;
    }
    cout << "read sec_GOOG.csv completed! " << endl;
    option.close();
    //************* 2(b). export result.csv containing stock price, option price, implied volatility, delta, hedging error, PNL, PNL with hedge *************//
//$$$$$$$$$$$$$$$$$$$$$   initialization $$$$$$$$$$$$$$$$$$$$$//
    date t0 = from_simple_string("2011-07-05"); // set as given example
    date tn = from_simple_string("2011-07-29"); // set as given example
    date T = from_simple_string("2011-09-17"); // set as given example
    string flag = "C"; // here set as call option
    double K = 500;
//$$$$$$$$$$$$$$$$$$$$$   initialization $$$$$$$$$$$$$$$$$$$$$//
//$$$$$$$$$$$$$$$$$$$$$   user input $$$$$$$$$$$$$$$$$$$$$//
//    string time0;
//    cout << "Please input the start time(t0) eg. 2011-07-05 : " ;
//    cin >> time0;
//    date t0 = from_simple_string(time0);
//    string timen;
//    cout << "Please input the end time(tn) eg. 2011-07-29 : " ;
//    cin >> timen;
//    date tn = from_simple_string(timen);
//    string maturity;
//    cout << "Please input the expiration date(T) eg. 2011-09-17 : " ;
//    cin >> maturity;
//    date T = from_simple_string(maturity);
//    string flag;
//    cout << "Please input the flag of option eg. call-c/C put-p/P : " ;
//    cin >> flag;
//    double K;
//    cout << "Please input strike price: " ;
//    cin >> K;
//$$$$$$$$$$$$$$$$$$$$$   user input $$$$$$$$$$$$$$$$$$$$$//
    int start = 0;
    int end = 0;
    for (int i=0; i<interest_date.size(); i++)
    {
        if (interest_date[i] == t0) {start=i;}
        if (interest_date[i] == tn) {end=i;}
    }
    int n = end-start+1;
    vector<date> _date;
    vector<double> _S; // stock price
    vector<double> _V; // option price
    vector<double> _iv; // implied volatility
    vector<double> _delta; // delta
    vector<double> _HE; // hedging error
    vector<double> _PNL; // PNL
    vector<BSM> all_option; // used to calculate hedging error
    for (int i=0; i<n; i++)
    {
        _date.push_back(interest_date[i+start]);
        _S.push_back(stock_price[i+start]);
        for (int j=0; j<option_date.size(); j++)
        {
            if(option_date[j] == _date[i] && option_flag[j] == flag && option_exdate[j] == T && option_K[j] == K)
            {
                _V.push_back(option_mktprice[j]);
                break;
            }
        }
        double t = time_to_maturity(interest_date[i+start],T);
//        cout << i << " " << t <<endl;
        BSM option1("C", K, _S[i], interest_rate[i+start], 0, t);
        _iv.push_back(option1.BSM_iv(_V[i]));
        BSM option2("C", K, _S[i], interest_rate[i+start], 0, t, _iv[i]);
        _delta.push_back(option2.BSM_delta());
        all_option.push_back(BSM("C", K, _S[i], interest_rate[i+start], 0, t, _iv[i]));
        _HE.push_back(delta_hedge(all_option).hedge_error());
        _PNL.push_back(_V[0]-_V[i]);
    }
    ofstream result ("/Users/wangyijia/Desktop/gatech 21fall/ISYE6767/homework/midproject/data/result.csv");
    cout << "export result.csv" << endl;
    result <<"Initial: " << "t0-" << t0 << ", tn-"<< tn << ", maturity date-" << T << ", option type-" << flag << ", K-" << K << endl;
    result<<"date"<<","<<"S"<<","<<"V"<<","<<"Implied_volatility"<<","<<"delta"<<","<<" HE"<<","<<"PNL"<<","<<"PNL(with_hedge)"<<","<<"total_wealth"<<endl;
    for (int i = 0; i<n; i++)
    {
        result << _date[i] << "," << _S[i] << "," << _V[i] << "," << _iv[i] << "," << _delta[i] << "," << _HE[i] << "," << _PNL[i] << "," << _HE[i] << "," << _PNL[i] <<endl;
    }
    cout << "export result.csv completed!" << endl;
    return 0;
}
