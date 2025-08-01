//
//  delta_hedge.h
//  midproject
//
//  Created by 王艺嘉 on 10/16/21.
//

#ifndef delta_hedge_h
#define delta_hedge_h
#include "BSM.h"
#include <vector>
using namespace std;

class delta_hedge{
private:
    vector<BSM> dh;
public:
    delta_hedge();
    delta_hedge(vector<BSM> dh);
    ~delta_hedge();
    double hedge_error();
};
#endif /* delta_hedge_h */
