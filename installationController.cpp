#include "installationController.h"
using namespace std;
// check lai ai xem co sai code ko

installationController::installationController(string fileName) : 
		repoPhieuLapDat(fileName),
		repoHopDong("data/contract.txt"),
		repoNhanVien("data/employee.txt"),
		repoInternet("data/internet.txt")
		{
			docDanhSachModem();
		}
string installationController::chuanHoaTen(string s){//chuan hoa ten de lay trong file modem luu dang CA NHAN|modem...
	for(auto &c : s) c=toupper(c);
	return s;
}
string installationController::chuanHoaNgay(string s){//Chuan hoa ngay sinh dang dd/mm/yyyy
	if(s[1]=='/') s="0"+s;
	if(s[4]=='/') s.insert(3,"0");
	return s;
}
void installationController::docDanhSachModem(){//doc danh sach modem luu map key-value
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
		cout << left << setw(12) << "Ma phieu lap dat"
	         << setw(12) << "Ma hop dong"
	         << setw(12) << "Ma nhan vien ky thuat"
	         << setw(30) << "Loai modem"
	         << setw(15) << "Ngay lap dat"
	         << setw(15) << "Trang thai" << endl;
	        cout << string(96, '-') << endl;
	}
	
	void installationController::capNhatNgayHen(installationForm* phieu) {
    cout << "\n--- CAP NHAT NGAY HEN ---\n";
    cout << "Ngay hen hien tai: " << phieu->getDate() << "\n";
    cout << "Nhap ngay hen moi (VD: 25/10/2026) [Bo trong giu nguyen]: ";
    
    string ngayMoi;
    getline(cin, ngayMoi);
    ngayMoi=chuanHoaNgay(ngayMoi);
    if (!ngayMoi.empty()) {
        phieu->setDate(ngayMoi);
        cout << "=> Tinh trang: Da cap nhat ngay hen tren he thong tam thoi.\n";
    }
    else cout <<  "=> Khong co thay doi nao duoc luu." << endl;
}

void installationController::capNhatTrangThai(installationForm* phieu) {
    cout << "\n--- CAP NHAT TRANG THAI ---\n";
    cout << "Trang thai hien tai: " << phieu->getState() << "\n";
    cout << "Cac trang thai: [0: Cho xu ly | 1: Dang thi cong | 2: Hoan thanh | -1: Huy bo]\n";
    while(true){
	cout << "Nhap trang thai moi [Bo trong giu nguyen]: ";
    string trangThaiMoi;
    getline(cin, trangThaiMoi);
	if(trangThaiMoi.empty()) {
    cout << "=> Khong co thay doi nao duoc luu.\n";
    break;
}
    //try catch de bat ng dung nhap int so chu khong phai string linh tinh
    try {
        int tt = stoi(trangThaiMoi);
        if (tt == -1 || tt == 0 || tt == 1 || tt == 2) {
                phieu->setState(tt);
                cout << "=> Tinh trang: Da cap nhat trang thai tren he thong tam thoi.\n";
				break;
				}
        else {
                cout << "=> [LOI]: So khong hop le. Vui long chi nhap -1, 0, 1 hoac 2!\n";
    }} catch (...) {
        cout << "=> [LOI]: Vui long chi nhap so (0, 1, 2, hoac -1)!\n";
    }
} 
}

void installationController::capNhatModem(installationForm* phieu) {
    cout << "\n--- CAP NHAT MODEM ---\n";
    cout << "Modem hien tai: " << phieu->getModem() << "\n";
      repoHopDong.reloadData();
    contract* hd = repoHopDong.searchId(phieu->getIdContract());
    if (hd) {
        string maGoi = hd->getInternetId();
        internet* goi = repoInternet.searchId(maGoi);
        if (goi) {
            string loaiKH = chuanHoaTen(goi->getCustomerType());
            if (mapModem.find(loaiKH) == mapModem.end() || mapModem[loaiKH].empty()) {
    cout << "=> [LOI DATA]: He thong chua co Modem cho loai khach: " << loaiKH << "\n";
    return; // Thoát ra kh?i hàm c?p nh?t
}
            vector<string> dsModem = mapModem[loaiKH];
            
            cout << "Danh sach Modem phu hop:\n";
            for (size_t i = 0; i < dsModem.size(); i++) {
                cout << i + 1 << ". " << dsModem[i] << "\n";
            }
            string chon;
            
            cout << "Chon Modem thay the (1-" << dsModem.size() << ") hoac '0' de huy: ";
            int chon;
            cin >> chon;
            cin.ignore();
            
            if (chon >= 1 && chon <= dsModem.size()) {
                phieu->setModem(dsModem[chon - 1]);
                cout << "=> Tinh trang: Da thay doi Modem thanh cong.\n";
            }
            else  cout<< "=> Khong co thay doi nao duoc luu." << endl;
        }
    }
}
//chuc nang them
void installationController::createFunction(){
	cout << "\n----THEM MOI PHIEU LAP DAT----" << endl;
	repoHopDong.reloadData();
	vector<contract> dsHD=repoHopDong.getData();
	vector<installationForm> dsPhieu=repoPhieuLapDat.getData();
	cout << "\n* DANH SACH HOP DONG DANG CHO THI CONG:\n  ";
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
			cout<<	hd.getId()<<"\n";
			dem++;
		}
	}
	if(dem==0){
		cout << "(Hien khong co hop dong nao can lap dat moi!)";
		return;
	}
	
	cout << "\n" << string(40, '-') << "\n";
	string maHD;
	while(true){
		cout << "-> Nhap Ma Hop Dong can lap dat: ";
		getline(cin,maHD);
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
			else break;//dung vong lap khi dã chon ma hd dung
		}
		else cout<<"=> [LOI]: Khong tim thay Ma Hop Dong trong he thong!\n";
	}
	//nhan vien lap dat 
	contract* check=repoHopDong.searchId(maHD);
	string k=check->getAreaId();
	cout << "\n* DANH SACH MA NHAN VIEN QUAN LY"<<k<<"DANG CO TRONG HE THONG:\n  ";
		repoNhanVien.reloadData();
		vector<employee> dsNV=repoNhanVien.getData();
		bool kt=false;
	for(auto& nv : dsNV){
		if(nv.getAreaId()==k){
			kt=true;
		cout<<nv.getId()<<" - "<<nv.getFullName()<<"\n";
	}
	cout << "\n" << string(40, '-') << "\n";
	if(!kt){
		cout<<"=>Chua co nhan vien nao quan ly o khu vuc nay\n";
		return;
	}
	
	string maNV;
	while(true){
	cout << "-> Nhap Ma Nhan Vien phu trach: ";
	getline(cin,maNV);
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
	cout << "\n* DANH SACH Loai Modem Phu Hop Voi Ma Hop Dong:\n  ";
	repoHopDong.reloadData();
	repoInternet.reloadData();
	string loaiKH,loaiModem,maGoi;
	contract* tim=repoHopDong.searchId(maHD);
	maGoi=tim->getInternetId();
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
	int chon;
	
	while(true){
		cout << "Moi chon loai Modem (1-" << dsModem.size() << "): ";
		string input;
		getline(cin,input);
		try{
			
			chon=stoi(input);
			if (chon < 1 || chon > dsModem.size()) {
            cout << "=> Lua chon sai. Vui long chon lai!\n";
        }
		 	else {
            break;
		}
	}catch(...){
		cout << "=> [LOI] Vui long chi nhap so!\n";
	}}
	
	loaiModem=dsModem[chon-1];
	
	string ngayHen;
cout << "-> Nhap ngay hen lap dat (VD: 20/10/2026): ";
getline(cin, ngayHen); 
ngayHen = chuanHoaNgay(ngayHen);
	//sinh mã tu dong
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
	phieuMoi.setState(0);// them 1 phieu thi phai dang trong trang thai cho xu ly
	
	if(repoPhieuLapDat.create(phieuMoi)){
		cout << "\n=> [THANH CONG] Da tao Phieu Lap Dat!\n";
		
	}}
void installationController::readFunction() {
    cout << "\n--- DANH SACH PHIEU LAP DAT ---" << endl;
    vector<installationForm> ds = repoPhieuLapDat.getData();
    
    if (ds.empty()) {
        cout << "=> Danh sach hien dang trong!" << endl;
        return;
    } 
    
    // In danh sách
    showTitle();
    for (auto& ph : ds) {
        ph.showToConsole();
    }
    
    while (true) {
        cout << "\nNhap Ma Phieu Lap Dat de xem chi tiet (hoac '0' de thoat): ";
        string ma;
        getline(cin, ma);
        
        if (ma == "0") {
            cout << "=> Da thoat chuc nang xem chi tiet.\n";
            break; 
        }
        
        installationForm* timThay = repoPhieuLapDat.searchId(ma);
        
        if(timThay) {
            cout << "\n--- CHI TIET MA " << ma << " ---" << endl;
            showTitle();
            timThay->showToConsole();
        } 
		else {
          
            cout << "=> [LOI]: Khong tim thay Phieu Lap Dat co ma: " << ma << endl;
        }
    }
}
void installationController::updateFunction(){
	cout << "\n--- CAP NHAT THONG TIN PHIEU LAP DAT ---" << endl;
	cout << "--- DANH SACH CAC PHIEU LAP DAT DANG CO TRONG HE THONG---"<<endl;
	vector<installationForm> dsPLD=repoPhieuLapDat.getData();
	showTitle();
    for (auto& ph : dsPLD) {
        ph.showToConsole();
    }
	cout << "Nhap ma PLD can cap nhat(hoac '0' de thoat): ";
    string ma;
    getline(cin, ma);
    if (ma == "0") {
    cout << "=> Da thoat chuc nang cap nhat.\n";
    return; 
}
    installationForm* timThay=repoPhieuLapDat.searchId(ma);
    if (timThay == nullptr) {
        cout << "=> [LOI]: Khong tim thay Phieu Lap Dat co ma: " << ma << "\n";
        return;     
		}
        string chon;
   	
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
	} }
}
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
			if(timThay->getState()==1||timThay->getState()==2){
				showTitle();
                timThay->showToConsole();
                cout << "\n=> [TU CHOI XOA]: Khong the xoa phieu dang thi cong hoac da hoan thanh !\n";
			}
			else{
			cout << "\n--- CHI TIET MA " << ma << " ---" << endl;
            showTitle();
            timThay->showToConsole();
            cout << "\nBan co chac chan muon xoa phieu nay? (y/n): ";
            string xacNhan;
            getline(cin, xacNhan);
            if (xacNhan == "y" || xacNhan == "Y") {
                    if (repoPhieuLapDat.remove(ma)) {
                        cout << "=> Da xoa an toan Phieu Lap Dat: " << ma << endl;
                    }
                } 
				else {
                    cout << "=> Da huy xoa.\n";
                }
                break; 
            }
		}
		}
	}
void installationController::run(){
		int choice;
	do{
		cout << "\n============= QUAN LY HOP DONG =============" << endl;
		cout << "1. C - Them thong tin hop dong moi" << endl;
        cout << "2. R - Xem danh sach cac hop dong hien co" << endl;
        cout << "3. U - Thay doi cac hop dong hien co" << endl;
        cout << "4. D - Xoa hop dong hien co" << endl;
        cout << "0. Thoat chuong trinh quan ly goi mang" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> choice; cin.ignore();
        switch(choice){
        	case 1: createFunction(); break;
        	case 2: readFunction(); break;
        	case 3: updateFunction(); break;
        	case 4: deleteFunction(); break;
        	case 0: break;
		}
	} while(choice != 0);
}
