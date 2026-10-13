#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>       
#include <fstream>
#include <sstream>
#include "district.h" 
#include "repository.h"
#include "contract.h"
#include "internet.h"

using namespace std;
//memay canasoduhaodhawo
class districtController {
private:
    repository<district> repo;
    repository<internet> repoInternet;
    repository<contract> repoHopDong;
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
    districtController(string fileName = "data/data_khuvuc.txt"); 
    void run();
};
