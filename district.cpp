#include "district.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

district::district() {
    id = "";
    nameDistrict = "";
    station = "";
    maxBandWidth = 0;  
}

void district::setDistrict(string district) {
    this->nameDistrict = district;
}
string district::getDistrict() const { 
    return nameDistrict;
}

void district::setStation(string station) {
    this->station = station;
}
string district::getStation() const { 
    return station;
}

void district::setMaxBandWidth(int maxBandWidth) {
    if(maxBandWidth > 0) this->maxBandWidth = maxBandWidth;
    else cout << "=> Loi: Bang thong phai lon hon 0!\n"; // S?a l?i cú pháp cout
}
int district::getMaxBandWidth() const {
    return maxBandWidth;
}

void district::inputFromKeyboard() {
  
}

void district::showToConsole() {
    cout << left << setw(10) << id 
         << setw(25) << nameDistrict
         << setw(25) << station 
         << setw(15) << maxBandWidth << endl;	
}

string district::toFileString() {
    return id + "|" + nameDistrict + "|" + station + "|" + to_string(maxBandWidth);
}

void district::fromFileString(string &line) {
    stringstream ss(line);
    string tmp;
    
    getline(ss, id, '|');
    getline(ss, nameDistrict, '|'); 
    getline(ss, station, '|');
    getline(ss, tmp, '|');
    
    if(!tmp.empty()) maxBandWidth = stoi(tmp);
}
