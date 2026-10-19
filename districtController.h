#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>       
#include <fstream>
#include <sstream>
#include "district.h" 
#include "Repository.h"
#include "contract.h"
#include "internet.h"

using namespace std;

class districtController {
private:
    Repository<district> repo;
    Repository<internet> repoInternet;
    Repository<contract> repoHopDong;
    map<string, vector<string>> mapTram;
    
    int tinhSoKhuVuc(string maKV);
   	int tinhTongBangThong(string maKV);
    void docDanhSachTram();
    string normalizeName(string s);
    void showTitle();
    
    void createFunction();
    void readFunction();
    void updateFunction();
    void deleteFunction();
    
public:
    // S?a l?i sai tên Constructor t? KhuVucController thành districtController
    districtController(); 
    void run();
};
