 #include "districtController.h"

//quan ly cac tram mang va khu vuc qua file text(tu them cac tram va khu vuv)
//moi 1 tram gan lien voi khu vuc co ma duy nhat ví du hanoi-hoan kiem kv01, ha noi-dong da kv02
//moi tram se có bang thong toi da
///1 tram se kiem soat nhieu nguoi và chi thay doi duoc bang thong toi da
//neu muon xoa
using namespace std;

districtController::districtController() : 
	repo("data/data_khuvuc.txt"),repoInternet("data/internet.txt"),repoHopDong("data/contract.txt")
{
    docDanhSachTram();
}

string districtController::normalizeName(string s) {
    for(char &c : s) c = toupper(c);
    
    
   
    return s;
    
}

// S?a l?i void string thành void
void districtController::docDanhSachTram() {
	mapTram.clear();
    ifstream file("data/data_tram.txt");
    if(!file.is_open()) return;
    
    string line ;
    while(getline(file, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string tenTinh, tenTram;
        
        getline(ss, tenTinh, '|');
        tenTinh = normalizeName(tenTinh);
        
        vector<string> dsTram;
        while(getline(ss, tenTram, '|')) {
            if(!tenTram.empty()) dsTram.push_back(tenTram);
        }
        mapTram[tenTinh] = dsTram;
    }
    file.close();
}

void districtController::showTitle() {
    cout << left << setw(10) << "Ma KV" 
         << setw(25) << "Ten Tinh/Thanh" 
         << setw(25) << "Tram Quan Ly" 
         << setw(15) << "Bang Thong" << endl;
    cout << string(75, '-') << endl;
}
int districtController::tinhTongBangThong(string maKV){//ham tinh tong bang thon trong 1 khu vuc trong hop dong
	repoHopDong.reloadData();
	repoInternet.reloadData();
	int tong=0;
	vector<contract> dsHopDong=repoHopDong.getData();//doc hop dong
	for(auto& hd : dsHopDong ){
		if(hd.getAreaId()==maKV){//lay ma khuvuc cua hop dong
			string maGoi=hd.getPackageId();//lay ma internet
			internet* timThay=repoInternet.searchId(maGoi);//tim kiem id cua internet
			if(timThay!=nullptr){
				tong+=timThay->getSpeed();
			}
		}
	}
	return tong;
}
int districtController::tinhSoKhuVuc(string maKV){//tinh toan co bao nhieu khu vuc trong hop dong
repoHopDong.reloadData();
	repoInternet.reloadData();
	int tong=0;
	vector<contract> dsHopDong=repoHopDong.getData();
	for(auto& hd: dsHopDong){
		if(hd.getAreaId()==maKV){
			tong++;
		}
	}
	return tong;
}

void districtController::createFunction() {
docDanhSachTram();
    cout << "\n--- THEM MOI KHU VUC / TUYEN CAP ---" << endl;
    if (mapTram.empty()) {
        cout << "=> LOI: He thong chua co du lieu Tram. Vui long kiem tra lai file data_tram.txt!\n";
        return;
    }
    vector<district> dsHienTai = repo.getData();
    
    string tinhNhap, tramNhap;
    while (true) {
        bool tinhHopLe = false;
        do {
            cout << "\nNhap ten Tinh/Thanh pho (VD: Ha Noi) hoac nhap '0' de thoat: ";
            getline(cin, tinhNhap);
            
            if (tinhNhap == "0") {
                cout << "=> Da thoat chuc nang Them moi.\n";
                return; // Thoát h?n hàm create
            }
            tinhNhap = normalizeName(tinhNhap);
            if(mapTram.find(tinhNhap) != mapTram.end()) {
                tinhHopLe = true;
            } else {
                cout << "=> LOI: Tinh/Thanh pho nay khong co hoac go sai!\n";
                cout << "=> Goi y cac Tinh ho tro: ";
                for (auto& pair : mapTram) cout << pair.first << ", ";
                cout << "\n";
            }
        } while(!tinhHopLe); 

        vector<string> dsTramCuaTinh = mapTram[tinhNhap];
        int chon;
        while(true) {
            cout << "\n--- Danh sach Tram tai " << tinhNhap << " ---\n";
            for(int i = 0; i < dsTramCuaTinh.size(); i++) {
                cout << i + 1 << ". " << dsTramCuaTinh[i] << "\n";
            }
            cout << "0. Huy bo (Chon lai Tinh/Thanh pho)\n";
            
            cout << "Moi chon Tram phu trach (0-" << dsTramCuaTinh.size() << "): ";
            string chonTram;
            getline(cin, chonTram);
            
            try {
                chon = stoi(chonTram);
                if (chon == 0) {
                    break; 
                }
                if (chon < 1 || chon > dsTramCuaTinh.size()) {
                    cout << "=> Lua chon sai. Vui long chon lai!\n";
                } else {
                    break; // Phá vòng l?p Tr?m d? di ti?p xu?ng ki?m tra trùng
                }
            } catch(...) {
                cout<<"[LOI] Vui long chi nhap so!\n";
            }
        }
        
        if (chon == 0) continue; //quay ve chon tinh 
        tramNhap = dsTramCuaTinh[chon - 1];
        cout << "=> Da chon: " << tramNhap << " (" << tinhNhap << ")\n";
        
        bool daTonTai = false;
        for(auto& kv : dsHienTai) {
            if(kv.getDistrict() == tinhNhap && kv.getStation() == tramNhap) {
                daTonTai = true;
                cout << "\n=> [LOI TU CHOI]: Ha tang tai '" << tramNhap << "' da ton tai voi ma '" << kv.getId() << "'!\n";
                cout << "=> Vui long chon Khu vuc hoac Tram khac!\n";
                break; 
            }
        }
        
        if (!daTonTai) {
            break; 
        }
    }
      
    int maxId = 0;
    for(auto& kv : dsHienTai) {
        if(kv.getId().length() > 2) {
            try {
                int soHienTai = stoi(kv.getId().substr(2));
                if(soHienTai > maxId) maxId = soHienTai;
            } catch(...) {} 
        }
    }
    
    string max;
    if(maxId <= 8) {
        max = "0" + to_string(maxId + 1);
    } else {
        max = to_string(maxId + 1);
    }
    
    district kvMoi;
    string ma = string("KV") + max;
    string bangThong;
    
   while(true){
        cout << "\nNhap bang thong toi da cua tram " << tramNhap << " (Mbps) hoac '0' de huy: ";
        try {   
            getline(cin, bangThong);
            
            size_t pos; 
            int kq = stoi(bangThong, &pos);
            
            if (pos != bangThong.length()) {
                throw runtime_error("Chuoi co chua chu cai hoac ky tu la"); 
            }
            
            if (kq == 0) {
                cout << "=> Da huy tao khu vuc moi.\n";
                return;
            }
            if (kq < 0) {
                cout << "=> Vui long chi nhap so lon hon 0!\n";
            } else {
                kvMoi.setMaxBandWidth(kq);
                break;
            }
        } catch(...) {
            cout << "=> [LOI] Vui long chi nhap so nguyen hop le (khong dính chu cai hay ky tu la)!\n";
        }
    }
    kvMoi.setId(ma);
    kvMoi.setDistrict(tinhNhap);
    kvMoi.setStation(tramNhap);

    if (repo.create(kvMoi)) {
        cout << "=> Them thanh cong! He thong da tu cap ma: " << ma << endl;
    }}
void districtController::readFunction() {
    cout << "\n--- DANH SACH KHU VUC QUAN LY ---" << endl;
    vector<district> ds = repo.getData();
    if(ds.empty()) {
        cout << "=> Danh sach hien dang trong!" << endl;
    } else {
        showTitle();
        for(auto &kv : ds) kv.showToConsole();
    }
    while(true){
    cout << "\nNhap Ma KV de xem chi tiet (hoac '0' de thoat): ";
    string ma;
    getline(cin, ma);
    ma=normalizeName(ma);
    if(ma=="0"){
    	cout << "=> Da thoat chuc nang xem chi tiet.\n";
        break; 
	}
        district* timThay = repo.searchId(ma);
        if(timThay) {
            cout << "\n--- CHI TIET MA " << ma << " ---" << endl;
            showTitle();
            timThay->showToConsole();
            int inUse=tinhTongBangThong(ma);//tinh toan bang thong theo khu vuc
            int maxBand=timThay->getMaxBandWidth();
            int remain=maxBand-inUse;//so sanh voi mã bang thong cap
            cout << "\n--- TINH TRANG BANG THONG ---" << endl;
            cout << "Tong bang thong tram: " << maxBand << " Mbps\n";
		    cout << "Da cap cho khach hang: " << inUse << " Mbps\n";
		    cout << "Bang thong con trong: " << remain << " Mbps\n";
		    if(remain<=0){
		    	cout << "=> CANH BAO: Tram dang bi qua tai! Can cap nhat lai bang thong\n";
			}
			else cout<< "=> THONG BAO: Bang thong cua tram o muc an toan !\n";
        }
		 else {
            cout << "=> [LOI]: Khong tim thay ma khu vuc: " << ma << endl;
        }
    }
}

void districtController::updateFunction() {
    cout << "\n--- CAP NHAT THONG TIN KHU VUC ---" << endl;
    cout << "\n--- DANH SACH DANG CO TRONG HE THONG ---" << endl;
    vector<district> ds=repo.getData();
    showTitle();
    for(auto& kv :ds){
    	kv.showToConsole();
	}
	district* timThay = nullptr;
    while (true) {
        cout << "Nhap ma KV can cap nhat (hoac '0' de thoat): ";
        string ma;
        getline(cin, ma);
        ma=normalizeName(ma);
        if (ma == "0") {
            cout << "=> Da thoat chuc nang cap nhat." << endl;
            return;
        }
        
        timThay = repo.searchId(ma);
        
        if (timThay == nullptr) {
            cout << "=> [LOI] Khong tim thay khu vuc mang ma: " << ma << "! Vui long nhap lai.\n";
        } else {
            break; 
        }
    }
     while(true){
 		cout<<"Thong tin khu vuc hien tai:\n";
        showTitle(); // S?a l?i thi?u ch?m ph?y
        timThay->showToConsole();
        string input;
       
        cout << "\nSua bang thong (" << timThay->getMaxBandWidth() << ") [Bo trong giu nguyen]: ";
        getline(cin, input);
          if(input.empty()) {
            cout << "=> Khong co thay doi nao duoc luu." << endl;
            break;
        }
		try{
        int chon=stoi(input);
        if (chon <= 0) {
            cout << "=> [LOI] Vui long chi nhap so lon hon 0!\n";
			}
			else {
            timThay->setMaxBandWidth(chon);
            repo.saveToFile();
            cout << "=> Da cap nhat bang thong thanh cong!" << endl;
            break;
        }
       
    }
	catch(...){
	 cout<<"[LOI] Vui long chi nhap so !\n";}}
	
}

void districtController::deleteFunction() {
    cout << "\n--- XOA KHU VUC ---" << endl;
    cout << "\n--- DANH SACH KHU VUC HIEN CO TRONG HE THONG ---" << endl;
    showTitle();
    vector<district>ds=repo.getData(); 
    for(auto& kv : ds){
    	kv.showToConsole();
	}
    while(true){
    cout << "Nhap ma KV can xoa (Hoac nhap '0' de thoat chuc nang): ";
    string ma;
    getline(cin, ma);
    ma=normalizeName(ma);
    if(ma=="0"){
    	cout<<"=> Da thoat chuc nang xoa.\n";
    	break;
	}
    district* timThay = repo.searchId(ma);
    
    if(timThay) {
    	int inContract=tinhSoKhuVuc(ma);
    	if (inContract==0){
        showTitle();
        timThay->showToConsole();
        string chot;
        while(true){
        cout << "\nBan co chac chan xoa? (y/n): ";
        getline(cin,chot);
        if (chot == "y" || chot == "Y") {
            if (repo.remove(ma)) cout << "=> Da xoa khu vuc voi ma :"<< ma << endl;
            break;
        } 
		
		else if(chot=="n"||chot=="N") { 
            cout << "=> Da huy xoa." << endl; // S?a l?i dóng ngo?c nh?n tùy ti?n
            break;
        }
        else cout<<"[LOI] Lua chon khong hop le ! vui long chi nhap 'y','Y','n','N'\n";
    }
}
		else{
			showTitle();
			timThay->showToConsole();
			cout<< "\nBan khong the xoa vi dang ton tai "<<inContract<<" hop dong o khu vuc nay!\n";
			cout<<"Vui long nhap lai!";
		}
}
	 else {
        cout << "=> Khong tim thay ma khu vuc: " <<ma<<".Vui long chon lai!\n"<< endl;
    }
}}

void districtController::run() {
    int chon;
    do {
        cout << "\n============= QUAN LY TUYEN CAP/KHU VUC =============" << endl;
        cout << "1. C - Them moi Khu vuc (Tu dong cap ma)" << endl;
        cout << "2. R - Xem danh sach & Chi tiet" << endl;
        cout << "3. U - Cap nhat Khu vuc" << endl;
        cout << "4. D - Xoa Khu vuc (Kiem tra an toan)" << endl;
        cout << "0. Thoat module" << endl;
        cout << "Chon: "; 
        cin >> chon; 
        cin.ignore(); 
        
        switch (chon) {
            case 1: createFunction(); break;
            case 2: readFunction(); break;
            case 3: updateFunction(); break;
            case 4: deleteFunction(); break;
            case 0: break;
            default: cout << "=> Sai lua chon!" << endl; break;
        }
    } while (chon != 0);
}
