//vu tran tuan minh
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
    
    int tinhSoKhuVuc(string maKV);//tinh so hop dong o trang thai hoat dong neu lon hon 1 thi ko cho xoa
   	int tinhTongBangThong(string maKV);//tinh bang thong cua cac hop dong lay ma kh,lay ma goi, lay toc do tinh tong
    void docDanhSachTram();//doc file txt dung dinh dang
    string normalizeName(string s);//chuan hoa ten dang viet hoa het de chuan file txt
    void showTitle();//hien thi tieu de
    //crud
    void createFunction();
    void readFunction();
    void updateFunction();
    void deleteFunction();
    
public:
    districtController(); 
    void run();
};
