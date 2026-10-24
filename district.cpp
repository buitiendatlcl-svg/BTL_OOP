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
    status = 0;
}

void district::setStatus(int status) {
    this->status = status;
}
int district::getStatus() const {
    return status;
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
   string trangThai;
   switch(status){
	    	case 0:  trangThai = "On Dinh"; break;
	        case 1:  trangThai = "Canh Bao"; break;
	        default: trangThai = "Khong xac dinh"; break;
			}
			
    cout << left << setw(10) << id 
         << "| " << setw(20) << nameDistrict
         << "| " << setw(20) << station 
         << "| " << setw(15) << maxBandWidth 
         << "| " << setw(15) << trangThai << endl;
}

string district::toFileString() {
    return id + "|" + nameDistrict + "|" + station + "|" + to_string(maxBandWidth) + "|" + to_string(status);
}

void district::fromFileString(string &line) {
    stringstream ss(line);
    string tmp;
    
    getline(ss, id, '|');
    getline(ss, nameDistrict, '|'); 
    getline(ss, station, '|');
    getline(ss, tmp, '|');
    if(!tmp.empty()) maxBandWidth = stoi(tmp);
    getline(ss, tmp, '|');
    if(!tmp.empty()) status = stoi(tmp);
}
