#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <map>       
#include <fstream>
#include <sstream> 
#include "Repository.h"
#include "contract.h"
#include "employee.h"//sua sau
#include "internet.h"
#include "installation.h"
#include "district.h"
using namespace std;

class installationController{
	private:
		Repository<installationForm> repoPhieuLapDat;
		Repository<contract> repoHopDong;
		Repository<employee> repoNhanVien;
		Repository<internet> repoInternet;
		Repository<district> repoKhuVuc;
		map<string,vector<string>> mapModem;
		
		void docDanhSachModem();
		string chuanHoaTen(string s);
		bool chuanHoaNgay(string s);
		bool checkDay(string ngay1, string ngay2);
		void showToConsoleNew(installationForm& ph);
		void showTitle();
		void capNhatModem(installationForm* phieu);
		void capNhatNgayHen(installationForm* phieu);
		void capNhatTrangThai(installationForm* phieu);
		string congNgayHen(string ngayKy,int kiHanThang);
	    void createFunction();
	    void readFunction();
	    void updateFunction();
	    void deleteFunction();
    
    public:
    	installationController();
    	void run();
};
