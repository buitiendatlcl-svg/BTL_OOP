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
using namespace std;

class installationController{
	private:
		Repository<installationForm> repoPhieuLapDat;
		Repository<contract> repoHopDong;
		Repository<employee> repoNhanVien;
		Repository<internet> repoInternet;
		map<string,vector<string>> mapModem;
		
		void docDanhSachModem();
		string chuanHoaTen(string s);
		string chuanHoaNgay(string s);
		void showTitle();
		void capNhatModem(installationForm* phieu);
		void capNhatNgayHen(installationForm* phieu);
		void capNhatTrangThai(installationForm* phieu);
		 
	    void createFunction();
	    void readFunction();
	    void updateFunction();
	    void deleteFunction();
    
    public:
    	installationController();
    	void run();
};
