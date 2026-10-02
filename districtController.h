#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>       
#include <fstream>
#include <sstream>
#include "district.h" 
#include "Repository2.h"

using namespace std;

class districtController {
private:
    Repository<district> repo;
    map<string, vector<string>> mapTram;
    
    void docDanhSachTram();
    string chuanHoaTen(string s);
    void hienThiTieuDe();
    
    void chucNangThem();
    void chucNangXemVaTimKiem();
    void chucNangCapNhat();
    void chucNangXoa();
    
public:
    // S?a l?i sai tên Constructor t? KhuVucController thành districtController
    districtController(string fileName = "data/data_khuvuc.txt"); 
    void run();
};
