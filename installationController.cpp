#include "installationController.h"
using namespace std;
// check lai ai xem co sai code ko

installationController::installationController() : 
		repoPhieuLapDat("data/data_phieulapdat.txt"),
		repoHopDong("data/contract.txt"),
		repoNhanVien("data/employee.txt"),
		repoInternet("data/internet.txt"),
		repoKhuVuc("data/data_khuvuc.txt")
		{
			docDanhSachModem();
		}
string installationController::chuanHoaTen(string s){//chuan hoa ten de lay trong file modem luu dang CA NHAN|modem...
	for(auto &c : s) c=toupper(c);
	return s;
}
bool installationController::chuanHoaNgay(string date){
	//check dinh dang dd/mm/yyyy
	if (date.size() != 10 || date[2] != '/' || date[5] != '/') return false;
	for (int i = 0; i < date.size(); i++){
		if (i == 2 || i == 5) continue; // neu la dau "/" thi bo qua
		if (!isdigit(date[i])) return false;
	}
	
	int d = stoi(date.substr(0, 2)); 
	int m = stoi(date.substr(3, 2));
	int y = stoi(date.substr(6, 4));
	
	if ( d < 1 || m < 1 || m > 12 || y < 1900 || y < 2025 ) return false;
	
	int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonth[2] = 29; // nam nhuan
    }
    return d <= daysInMonth[m]; // so sanh ngay nhap & ngay toi da cua thang do, neu dung tra ve true	
}

bool installationController::checkDay(string ngay1, string ngay2) {
    int d1 = stoi(ngay1.substr(0, 2)), m1 = stoi(ngay1.substr(3, 2)), y1 = stoi(ngay1.substr(6, 4));
    int d2 = stoi(ngay2.substr(0, 2)), m2 = stoi(ngay2.substr(3, 2)), y2 = stoi(ngay2.substr(6, 4));
    if (y1 != y2) return y1 > y2;
    if (m1 != m2) return m1 > m2;
    return d1 >= d2;
}
void installationController::showToConsoleNew(installationForm& ph) {
    string tenHienThi = ph.getIdEmployee();
        tenHienThi += "(Da nghi viec)"; 
		string trangThai;// vi chi luu state la cac so  0 1 2 nen cho vao switch bat cac trang thai in ra
	    	switch(ph.getStatus()){
	        case 1:  trangThai = "Hoan thanh"; break;
	        case -1:  trangThai= "Huy bo";break;
	        default: trangThai = "Khong xac dinh"; break;
			}
    cout << left << setw(18) << ph.getId() 
         << setw(15) << ph.getIdContract() 
         << setw(25) << tenHienThi 
         << setw(25) << ph.getModem() 
         << setw(20) << ph.getDate() 
         << setw(15) << trangThai << endl;
}

void installationController::docDanhSachModem(){//doc danh sach modem luu map key-value
	mapModem.clear();
	ifstream file("data/data_modem.txt");//doc file txt
	if(!file.is_open()) return;
	
	string line;
	while(getline(file,line)){
		if(line.empty()) continue;
		stringstream ss(line);
		string loaiKhachHang,modem;
		
		getline(ss,loaiKhachHang,'|');
		loaiKhachHang=chuanHoaTen(loaiKhachHang);
		
		vector<string> dsModem;
		while(getline(ss,modem,'|')){
			if(!modem.empty()) dsModem.push_back(modem);
		}
		mapModem[loaiKhachHang]=dsModem;
		
		
	}
	file.close();
}
	void installationController:: showTitle(){
		cout << left << setw(18) << "Ma phieu lap dat" 
          <<"| " << setw(15) << "Ma hop dong" 
          <<"| " << setw(25) << "Ma nhan vien ky thuat" 
          <<"| " << setw(25) << "Loai modem" 
          <<"| " << setw(20) << "Ngay lap dat" 
          <<"| " << setw(15) << "Trang thai" << endl;
    cout << string(125, '-') << endl;
	}
	
	void installationController::capNhatNgayHen(installationForm* phieu) {
   cout << "\n--- CAP NHAT NGAY HEN ---\n";
    cout << "Ngay hen hien tai: " << phieu->getDate() << "\n";
    repoHopDong.reloadData();
    contract* hd = repoHopDong.searchId(phieu->getIdContract());
    string ngayKy = (hd != nullptr) ? hd->getSignDate() : "01/01/2000";

    while(true){
        cout << "Nhap ngay hen moi (VD: 25/10/2026) [Bo trong giu nguyen]: ";
        string ngayMoi;
        getline(cin, ngayMoi);
        
        if(ngayMoi.empty()){
            cout << "=> Khong co thay doi nao duoc luu." << endl;
            break;
        } 
        
        if(!chuanHoaNgay(ngayMoi)){
            cout<<"=> [LOI] Vui long nhap ngay thang hop le!\n";
        }
        else if (checkDay(ngayMoi, ngayKy) == false) {
            cout<<"=> [LOI] Ngay hen khong duoc nho hon ngay ky HD (" << ngayKy << ")!\n";
        }
        else {
            phieu->setDate(ngayMoi);
            cout << "=> Tinh trang: Da cap nhat ngay hen tren he thong tam thoi.\n";
            break;
        }
    }
}
string tinhNgayHetHan(string ngayKy, int kiHanThang) {
    int d = stoi(ngayKy.substr(0, 2));
    int m = stoi(ngayKy.substr(3, 2));
    int y = stoi(ngayKy.substr(6, 4));
    m += kiHanThang;
    while (m > 12) {
        m -= 12;
        y++;
    }
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonth[2] = 29; // Nam nhu?n
    }
    if (d > daysInMonth[m]) {
        d = daysInMonth[m];
    }
    string kq = "";
    
    if (d < 10) kq += "0";
    kq += to_string(d) + "/";
    
    if (m < 10) kq += "0";
    kq += to_string(m) + "/";
    
    kq += to_string(y);
    
    return kq;
}
  void installationController::capNhatTrangThai(installationForm* phieu) {
    cout << "\n--- CAP NHAT TRANG THAI ---\n";
    if (phieu->getStatus() == 1 || phieu->getStatus() == -1) {
        cout << "=> [TU CHOI]: Phieu nay da chot so (Hoan thanh / Huy bo). Khong the thay doi trang thai!\n";
        return; 
    }
    
    cout << "Trang thai hien tai: " << phieu->getStatus() << "\n";
    cout << "Cac trang thai: [0: Cho xu ly | 1: Hoan thanh | -1: Huy bo]\n";
    
    while (true) {
        cout << "Nhap trang thai moi [Bo trong giu nguyen]: ";
        string trangThaiMoi;
        getline(cin, trangThaiMoi);
        if (trangThaiMoi.empty()) {
            cout << "=> Khong co thay doi nao duoc luu.\n";
            break;
        }
        
        try {
            size_t pos;
            int tt = stoi(trangThaiMoi, &pos);
            if (pos != trangThaiMoi.length()) throw runtime_error("Loi ky tu la");
            if (tt == -1 || tt == 0 || tt == 1) {
                phieu->setStatus(tt); 
                if (tt == 1) {
                    repoHopDong.reloadData();
                    repoKhuVuc.reloadData();
                    contract* hd = repoHopDong.searchId(phieu->getIdContract());
                    
                    if (hd != nullptr) {
                        hd->setStatus(1); 
                        
                        int kiHan = hd->getTerm(); 
                        string ngayHetHan = tinhNgayHetHan(phieu->getDate(), kiHan);
                        hd->setExpiryDate(ngayHetHan); 
                        
                        cout << "=> He thong tu dong KICH HOAT Hop Dong: " << hd->getId() << "\n";
                        cout << "=> Tu dong tinh Ngay Het Han Hop Dong: " << ngayHetHan << "\n";

                        district* tram = repoKhuVuc.searchId(hd->getAreaId());
                        if (tram != nullptr) {
                            int inUse = 0;
                            vector<contract> dsHD = repoHopDong.getData();
                            for (auto& c : dsHD) {
                                if (c.getAreaId() == tram->getId() && c.getStatus() == 1) {
                                    internet* goi = repoInternet.searchId(c.getPackageId());
                                    if (goi != nullptr) inUse += goi->getSpeed();
                                }
                            }
                            
                            if (inUse >= tram->getMaxBandWidth()) {
                                tram->setStatus(1); 
                                cout << "=> [CANH BAO]: Khu vuc " << tram->getDistrict()<<"Tram "<< tram->getStation() << " da vuot tai!\n";
                            }
                            
                            repoKhuVuc.saveChange(); 
                        }
                        
                        repoHopDong.saveChange(); 
                    }
                } 
                else if (tt == -1) {
                    cout << "=> Phieu lap dat da chuyen sang trang thai Huy (-1).\n";
                }
                repoPhieuLapDat.saveChange();
                cout << "=> [THANH CONG]: Da luu trang thai truc tiep xuong file!\n";
                break; 
                
            } else { 
                cout << "=> [LOI]: So khong hop le. Vui long chi nhap -1, 0 hoac 1!\n";
            }
        } catch (...) {
            cout << "=> [LOI]: Vui long chi nhap so (-1, 0 hoac 1)!\n";
        }
    } 
}
	

	void installationController::capNhatModem(installationForm* phieu) {
		docDanhSachModem();
	    cout << "\n--- CAP NHAT MODEM ---\n";
	    cout << "Modem hien tai: " << phieu->getModem() << "\n";
	      repoHopDong.reloadData();
	    contract* hd = repoHopDong.searchId(phieu->getIdContract());
	    if (hd) {
	        string maGoi = hd->getPackageId();
	        internet* goi = repoInternet.searchId(maGoi);
	        if (goi) {
	            string loaiKH = chuanHoaTen(goi->getCustomerType());
	            if (mapModem.find(loaiKH) == mapModem.end() || mapModem[loaiKH].empty()) {
	    cout << "=> [LOI DATA]: He thong chua co Modem cho loai khach: " << loaiKH << "\n";
	    return; // Thoát ra kh?i hàm c?p nh?t
	}
	            vector<string> dsModem = mapModem[loaiKH];
	            
	            cout << "Danh sach Modem phu hop:\n";
	            for (int i = 0; i < dsModem.size(); i++) {
	                cout << i + 1 << "." << dsModem[i] << "\n";
	            }
	            while(true){
	            cout << "Chon Modem thay the (1-" << dsModem.size() << ") [Bo trong de giu nguyen]: ";
	            string choose;
	            getline(cin,choose);
	            if(choose.empty()){
	            	cout<< "=> Khong co thay doi nao duoc luu." << endl;
	            	break;
				}
	            try{
	            	size_t pos;
                    int in = stoi(choose, &pos);
                    
                    // Ch?n ngu?i dùng nh?p s? kèm ch? (VD: "2abc")
                    if (pos != choose.length()) {
                        throw runtime_error("Loi ky tu la");
                    }
	            	if (in >= 1 && in <= dsModem.size()) {
	                phieu->setModem(dsModem[in - 1]);
	                cout << "=> Tinh trang: Da thay doi Modem thanh cong.\n";
	                break;
	            }
	            else  cout<< "=> Vui long chi nhap cac so trong khoang (1-" 
				<<dsModem.size()<<")"<< endl;
				}
	            catch(...){
	            	cout<<"[LOI] Vui long chi nhap so nguyen !\n";
				}
				}
	        }
	    }
	}
//chuc nang them
void installationController::createFunction(){
	docDanhSachModem();
	repoHopDong.reloadData();
	vector<contract> dsHD=repoHopDong.getData();
	vector<installationForm> dsPhieu=repoPhieuLapDat.getData();
	string maHD;
	string maNV;
	string ngayHen;
	string loaiModem;
	cout << "\n----THEM MOI PHIEU LAP DAT----" << endl;
	cout << "\n* DANH SACH HOP DONG DANG CHO THI CONG:\n";
		cout << left << setw(15) << "Ma hop dong"
		 	 << "| " << setw(15) << "Ma khach hang"
		 	 << "| " << setw(10) << "Ma goi"
			 << "| " << setw(12) << "Ma khu vuc" 
			 << "| " << setw(12) << "Ngay ky" 
			 << "| " << setw(10) << "Ky han"
			 << "| " << setw(15) << "Ngay het han"
			 << "| " << setw(16) << "Trang thai" << endl;
		cout << string(120, '-') << endl;
	int dem=0;
	for(auto& hd : dsHD){//tra ma hop dong trung voi ma hd da có trong phieu lap dat
		bool check=false;
		for(auto& ph: dsPhieu){
			if(ph.getIdContract()==hd.getId()){
				check=true;
				break;
			}
		}
		if(check==false){
			hd.showToConsole();
			dem++;
		}
	}
	if(dem==0){
		cout << "(Hien khong co hop dong nao can lap dat moi!)";
		return;
	}
	
	cout << "\n" << string(40, '-') << "\n";
	
	while(true){
		cout << "-> Nhap Ma Hop Dong can lap dat(hoac '0' de thoat): ";
		getline(cin,maHD);
		maHD=chuanHoaTen(maHD);
		if(maHD=="0"){
			cout<<"Da thoat chuc nang them phieu !\n";
			return;
		}
		contract* timThay=repoHopDong.searchId(maHD);
		if(timThay !=nullptr){//kiem tra trung 
			bool kiemtra=false;
			for(auto& ph: dsPhieu){
				if(ph.getIdContract()==maHD){
					kiemtra=true;
					break;
				}
			}
			if(kiemtra) cout<<"=> [LOI]: Hop dong '" << maHD << "'da duoc lap phieu. Vui long chon ma khac o tren!\n";
			else{
			break;//dung vong lap khi dã chon ma hd dung
			} 
		}
		else cout<<"=> [LOI]: Khong tim thay Ma Hop Dong trong he thong!\n";
	}
	//nhan vien lap dat 
	contract* check=repoHopDong.searchId(maHD);
	string k=check->getAreaId();
	district* timKiem=repoKhuVuc.searchId(k);
	cout << "\n* DANH SACH NHAN VIEN QUAN LY "<<k<<" DANG CO TRONG HE THONG:\n";
 cout << left << setw(8)  << "Ma NV" << "| "
             << left << setw(20) << "Ho va Ten" << "| "
             << left << setw(12) << "Ngay Sinh" << "| "
             << left << setw(12) << "SDT" << "| "
             << left << setw(20) << "Chuyen Mon" << "| "
             << left << setw(8)  << "Ma KV" << "| "
             << left << setw(15) << "Ten KV" << "| "
             << left << setw(15) << "Ten Tram" << "| "
             << left << setw(8)  << "Cap Bac" << "| "
             << "Luong (VND)" << endl;
        cout << string(144, '-') << endl;
		repoNhanVien.reloadData();
		vector<employee> dsNV=repoNhanVien.getData();
		bool kt=false;
	for(auto& nv : dsNV){
		if(nv.getAreaId()==k){
		kt=true;
		nv.showToConsole(timKiem->getDistrict(),timKiem->getStation());
	}}
	cout << "\n" << string(40, '-') << "\n";
	if(!kt){
		cout<<"=>Chua co nhan vien nao quan ly o khu vuc nay\n";
		return;
	}
	
	
	while(true){
	cout << "-> Nhap Ma Nhan Vien phu trach(hoac '0' de thoat): ";
	getline(cin,maNV);
	maNV=chuanHoaTen(maNV);
	if(maNV=="0"){
		cout<<"Da thoat chuc nang them phieu !\n";
		return;
	}
	employee* timThay=repoNhanVien.searchId(maNV);
	if(timThay==nullptr){
		cout<<"=> [LOI]: Khong tim thay Ma Nhan Vien trong he thong! Moi nhap lai !\n";
	}
	else if(timThay->getAreaId()!=k){
		cout << "=> [LOI]: Nhan vien " << maNV << " khong quan ly khu vuc " << k << "! Moi chon lai!\n";
	}
	else{
	
		break;
	}}
	cout << "\n* DANH SACH Loai Modem Phu Hop Voi Ma Hop Dong:\n";
	repoHopDong.reloadData();
	repoInternet.reloadData();
	string loaiKH,maGoi;
	contract* tim=repoHopDong.searchId(maHD);
	maGoi=tim->getPackageId();
	internet* timLoaiKH=repoInternet.searchId(maGoi);
	if (timLoaiKH == nullptr) {
        cout << "=> [LOI DATA]: Khong tim thay thong tin Goi Internet '" << maGoi << "'!\n";
        return;
    }
    
	loaiKH=timLoaiKH->getCustomerType();
	loaiKH=chuanHoaTen(loaiKH);
	if (mapModem.find(loaiKH) == mapModem.end() || mapModem[loaiKH].empty()) {
    cout << "=> [LOI DATA]: He thong chua co Modem cho loai khach: " << loaiKH << "\n";
    return; 
}
	
    
	vector<string> dsModem=mapModem[loaiKH];
	
	for(int i=0;i<dsModem.size();i++){
		
		cout<<i+1<<". "<<dsModem[i]<<"\n";
	}
	cout << "\n" << string(40, '-') << "\n";

	string input;
	while(true){
		cout << "Moi chon loai Modem (1-" << dsModem.size() << ") ";
		cout<<"hoac '0' de thoat chuc nang them phieu :";
	
		getline(cin,input);
		try{
		size_t pos;
                    int in = stoi(input, &pos);
                    if (pos !=input.length()) {
                        throw runtime_error("Loi ky tu la");
                    }
            if(in==0){
            	cout<<"Da thoat chuc nang them phieu !\n";
            	return;
			}
			if (in >= 1 && in <= dsModem.size()) {
            loaiModem=dsModem[stoi(input)-1];
			break;
    		
        }
		 	else {
           cout << "=> Lua chon sai. Vui long chon lai!\n";
		}
	}catch(...){
		cout << "=> [LOI] Vui long chi nhap so!\n";
	}}
	
	string ngayKyHopDong=tim->getSignDate();
	while(true){
	cout << "-> Nhap ngay hen lap dat (VD: 20/10/2026) hoac('0' de thoat): ";
	getline(cin, ngayHen);
	 	if(ngayHen=="0"){
			cout<<"Da thoat chuc nang them phieu !\n";
			return;
		}
	if(!chuanHoaNgay(ngayHen)){
		cout<<"[LOI] Vui long nhap ngay thang hop le (VD: 20/10/2026) !\n";
	}
	else if(checkDay(ngayHen, ngayKyHopDong) == false) 
	cout<<"[LOI] Ngay hen ("<< ngayHen <<") khong duoc dien ra TRUOC ngay ky HÐ ("<< ngayKyHopDong <<")!\n";
	else break; // Vu?t qua m?i rào ch?n
 }
	//sinh mã tu don
	int maxId=0;
	for(auto& ph : dsPhieu){
		string cur=ph.getId();
		if(cur.length() > 3){
			try{
				int soHienTai=stoi(cur.substr(3));//cat bo PLD
				if( soHienTai>maxId) maxId=soHienTai;
				
				
			}catch(...){}
			
		}
	}
	string max;
	if(maxId<9){
		 max="0"+to_string(maxId+1);
	}
	else{
		max=to_string(maxId+1);
	}
	string maPhieuMoi=string("PLD")+max;
	installationForm phieuMoi;
	phieuMoi.setId(maPhieuMoi);
	phieuMoi.setIdContract(maHD);
	phieuMoi.setIdEmployee(maNV);
	phieuMoi.setModem(loaiModem);
	phieuMoi.setDate(ngayHen);
	phieuMoi.setStatus(0);// them 1 phieu thi phai dang trong trang thai cho xu ly
	
	if(repoPhieuLapDat.create(phieuMoi)){
		cout << "\n=> [THANH CONG] Da tao Phieu Lap Dat ! He thong tu cap ma " <<maPhieuMoi<<"!\n";
	}}
void installationController::readFunction() {
	repoNhanVien.reloadData();
    cout << "\n--- DANH SACH PHIEU LAP DAT ---" << endl;
    vector<installationForm> ds = repoPhieuLapDat.getData();
    
    if (ds.empty()) {
        cout << "=> Danh sach hien dang trong!" << endl;
        return;
    } 
    
    // In danh sách
    showTitle();
    for (auto& ph : ds) {
    employee* nv = repoNhanVien.searchId(ph.getIdEmployee());
    if (nv == nullptr) {
       showToConsoleNew(ph);
    }
    else{
        ph.showToConsole();
    }}
    
    while (true) {
        cout << "\nNhap Ma Phieu Lap Dat de xem chi tiet (hoac '0' de thoat): ";
        string ma;
        getline(cin, ma);
        ma=chuanHoaTen(ma);
        if (ma == "0") {
            cout << "=> Da thoat chuc nang xem chi tiet.\n";
            break; 
        }
        
        installationForm* timThay = repoPhieuLapDat.searchId(ma);
        
        if(timThay) {
        	employee* nv = repoNhanVien.searchId(timThay->getIdEmployee());
        	if (nv == nullptr) {
        		showToConsoleNew(*timThay);}
        	else{
            cout << "\n--- CHI TIET MA " << ma << " ---" << endl;
            showTitle();
            timThay->showToConsole();
        }} 
		else {
          
            cout << "=> [LOI]: Khong tim thay Phieu Lap Dat co ma: " << ma << endl;
        }
    }
}
void installationController::updateFunction(){
	cout << "\n--- CAP NHAT THONG TIN PHIEU LAP DAT ---" << endl;
	cout << "--- DANH SACH CAC PHIEU LAP DAT DANG CO TRONG HE THONG---"<<endl;
	vector<installationForm> dsPLD=repoPhieuLapDat.getData();
	 if (dsPLD.empty()) {
        cout << "=> Danh sach hien dang trong!" << endl;
        return;
    } 
	showTitle();
    for (auto& ph : dsPLD) {
        ph.showToConsole();
    }
	
    
        string chon;
   	
    while(true){
	cout << "Nhap ma PLD can cap nhat(hoac '0' de thoat): ";
    string ma;
    getline(cin, ma);
    ma=chuanHoaTen(ma);
    if (ma == "0") {
    cout << "=> Da thoat chuc nang cap nhat.\n";
    return; 
	}
    installationForm* timThay=repoPhieuLapDat.searchId(ma);
    if (timThay == nullptr) {
    cout << "=> [LOI]: Khong tim thay Phieu Lap Dat co ma: " << ma << " Moi nhap lai !"<<"\n";
	}
	
	else{
		if(timThay->getStatus()==1){
			cout<<"Phieu lap dat da hoan thanh vui long ko sua thong tin !\n";
			continue;
		}
		else{
		while(true){
        cout << "\n--- THONG TIN PHIEU HIEN TAI ---\n";
        showTitle();
        timThay->showToConsole();
        cout << "\nCHON THONG TIN CAN CAP NHAT:\n";
        cout << "0. Thoat va luu thay doi\n ";
        cout << "1. Cap nhat loai modem\n ";
        cout << "2. Cap nhat ngay hen\n ";
        cout << "3. Cap nhat trang thai phieu\n ";
        cout << "Chon: ";
        getline(cin,chon);
        try{
		int choice=stoi(chon);
        switch(choice){
        	case 1: 
                capNhatModem(timThay); 
                break;
            case 2: 
                capNhatNgayHen(timThay); 
                break;
            case 3: 
                capNhatTrangThai(timThay);
				if (timThay->getStatus() == 1 || timThay->getStatus() == -1) {
                    cout << "=> Phieu da chot so, he thong tu dong thoat khoi man hinh cap nhat.\n";
                    return; 
                } 
                break;
            case 0: 
               
                repoPhieuLapDat.saveChange(); 
                cout << "=> [THANH CONG]: Da luu toan bo thay doi vao he thong!\n";
                return;
            default: 
                cout << "=> Sai lua chon!\n"; 
                break;
        }
    }catch(...){
    	cout<<"[LOI] Vui long chi nhap so\n";
	}}}
}}}
    void installationController::deleteFunction(){
    	cout << "\n--- DANH SACH PHIEU LAP DAT HIEN CO TRONG HE THONG ---" << endl;
    	vector<installationForm> ds=repoPhieuLapDat.getData();
    	if (ds.empty()) {
        cout << "=> (Danh sach hien dang trong. Khong co du lieu de xoa!)\n";
        return;
    }
    	showTitle();
    	for(auto& ph : ds){
    		ph.showToConsole();
		}
		while(true){
		cout<<"Hay chon ma phieu lap dat can xoa (hoac '0' de thoat) : ";
		string ma;
		getline(cin,ma);
		ma=chuanHoaTen(ma);
		if(ma=="0"){///1
			 cout << "=> Da thoat chuc nang xoa.\n";
            break; 
		}
		///ma khac 0
		installationForm* timThay=repoPhieuLapDat.searchId(ma);
		if(timThay==nullptr){
			 cout << "=> [LOI]: Khong tim thay Phieu Lap Dat co ma: " << ma <<". Vui long chon lai!\n";
		}
		else {
			if(timThay->getStatus()==1){
				showTitle();
                timThay->showToConsole();
                cout << "\n=> [TU CHOI XOA]: Khong the xoa phieu da hoan thanh !\n";
			}
			else{
			cout << "\n--- CHI TIET MA " << ma << " ---" << endl;
            showTitle();
            timThay->showToConsole();
            
            string xacNhan;
           
            while(true){
            	cout << "\nBan co chac chan muon xoa phieu nay? (y/n): ";
            getline(cin, xacNhan);
            
            if (xacNhan == "y" || xacNhan == "Y") {
                    if (repoPhieuLapDat.remove(ma)) {
                        cout << "=> Da xoa an toan Phieu Lap Dat: " << ma << endl;
                        break;
                    }
                } 
				else if(xacNhan == "n" || xacNhan == "N") {
                    cout << "=> Da huy xoa.\n";
                    break;
                }
                else{
                	cout<<"[LOI] Vui long chi nhap 'y','Y','n' hoac 'N' !\n";
				} 
            }
		}
		}
	}}
void installationController::run(){
		int choice=-1;
	do{
		cout << "\n============= QUAN LY PHIEU LAP DAT =============" << endl;
		cout << "1. C - Them thong tin phieu lap dat moi" << endl;
        cout << "2. R - Xem danh sach cac phieu lap dat hien co" << endl;
        cout << "3. U - Thay doi cac phieu lap dat hien co" << endl;
        cout << "4. D - Xoa phieu lap dat hien co" << endl;
        cout << "0. Thoat chuong trinh quan ly phieu lap dat" << endl;
        cout << "Nhap lua chon cua ban: ";
       	string chon;
       	getline(cin,chon);
       	try{	
		   	size_t pos;
	    	choice=stoi(chon,&pos);
	    	if(pos!=chon.length()) choice=-1;
        }catch(...){
        	choice=-1;
		}
        switch(choice){
        	case 1: createFunction(); break;
        	case 2: readFunction(); break;
        	case 3: updateFunction(); break;
        	case 4: deleteFunction(); break;
        	case 0: break;
		}
	} while(choice != 0);
}
