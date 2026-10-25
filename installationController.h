//vu tran tuan minh
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
		string chuanHoaTen(string s);//chuan hoa e dang viet hoa het de doc file txt
		bool chuanHoaNgay(string s);//chuan hoa ngay dang dd/mm/yyyy
		bool checkDay(string ngay1, string ngay2);//kiem tra ngay ki hop dong và ngày hen lap phieu
		void showToConsoleNew(installationForm& ph);//hien danh sách pld neu nhan vien da nghi viec 
		void showTitle();//hien tieu de
		void capNhatModem(installationForm* phieu);//cap nhat modem chuyen vao con tro tim theo id search
		void capNhatNgayHen(installationForm* phieu);//cap nhat trang thai chuyen vao con tro tim theo id search neu trang thai la 1 haowcj -1 thi ko 
		//khong duoc sua nua,moi khi lap phieu trnag thai se là 0
		void capNhatTrangThai(installationForm* phieu);//cap nhat ngay hen chuyen vao con tro tim theo id
		string congNgayHen(string ngayKy,int kiHanThang);//tinh toan de cong ngay het han set cho hop dong
	    void createFunction();//chuc nang C
	    void readFunction();//chuc nang R
	    void updateFunction();//chuc nang u
	    void deleteFunction();//chuc nang D
    
    public:
    	installationController();//ham tao
    	void run();//ham chay
};
