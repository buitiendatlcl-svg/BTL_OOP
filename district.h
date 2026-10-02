#pragma once
#include "Entity2.h"
#include <string>

using namespace std;

class district : public entity {
private :
    string nameDistrict;
    string station;
    int maxBandWidth;
public:
    district();
    
    // Setter và Getter dã s?a ki?u tr? v? thành string
    void setDistrict(string district);
    string getDistrict() const;
    
    void setStation(string station);
    string getStation() const;
    
    void setMaxBandWidth(int maxBandWidth);
    int getMaxBandWidth() const;
    
    // Ghi dè t? entity
    void inputFromKeyboard() override;
    void showToConsole() override;
    string toFileString() override;
    void fromFileString(string &line) override;
};
