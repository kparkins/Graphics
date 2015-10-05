#ifndef UPDATE_DATA_H
#define UPDATE_DATA_H

#include <iostream>

class UpdateData {
    
public:
    
    UpdateData(void);
    virtual ~UpdateData(void);
    
    double m_dt;
    //Place any objects here that you want to pass to an update() call
};

#endif
