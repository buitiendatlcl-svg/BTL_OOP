#pragma once
#include "Entity.h"
#include <string>
//vu tran tuan minh
using namespace std;

class district : public entity {
private :
    string nameDistrict;
    string station;
    int maxBandWidth;
    int status;
public:
    district();
    void setDistrict(string district);
    string getDistrict() const;
    
    void setStation(string station);
    string getStation() const;
    
    void setMaxBandWidth(int maxBandWidth);
    int getMaxBandWidth() const;
    
    void setStatus(int status);
    int getStatus() const;
    
    void inputFromKeyboard() override;
    void showToConsole() override;
    string toFileString() override;
    void fromFileString(string &line) override;
};
