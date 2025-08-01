//
//  delta_hedge.cpp
//  midproject
//
//
#include "BSM.h"
#include "delta_hedge.h"

delta_hedge::delta_hedge()
{
    vector<BSM> bsm;
    this->dh = bsm;
}
delta_hedge::delta_hedge(vector<BSM> dh)
{
    this->dh = dh;
}
delta_hedge::~delta_hedge(){}
double delta_hedge::hedge_error()
{
    vector<double> S; // stock price
    vector<double> V; // option price
    vector<double> r; // risk-free rate
    vector<double> delta; // calculate delta
    vector<double> B; // Bi =δi−1Si+Bi−1e^(ri−1*dt)−δiSi (i≥1)
    vector<double> HE; // HEi = δi−1Si + Bi−1eri−1∆t − Vi
    double dt = dh[0].get_T()/dh.size();
    for (int i=0; i<dh.size() ;i++)
    {
        S.push_back(dh[i].get_S());
        V.push_back(dh[i].BSM_price());
        r.push_back(dh[i].get_r());
        delta.push_back(dh[i].BSM_delta());
    }
    // initialize B0 B0 = V0−δ0S0
    B.push_back(V[0] - delta[0]*S[0]);
    // initialize HE0 = 0
    HE.push_back(0);
    for (int i=1; i<dh.size(); i++){
        B.push_back(delta[i-1]*S[i] + B[i-1]*exp(r[i-1]*dt) - delta[i]*S[i]);
        HE.push_back(delta[i-1]*S[i] + B[i-1]*exp(r[i-1]*dt) - V[i]);
    }
    return HE[dh.size()-1];
}
