#include "districtController.h"
//quan ly cac tram mang va khu vuc qua file text(tu them cac tram va khu vuv)
//moi 1 tram gan lien voi khu vuc co ma duy nhat ví du hanoi-hoan kiem kv01, ha noi-dong da kv02
//moi tram se có bang thong toi da
///1 tram se kiem soat nhieu nguoi và chi thay doi duoc bang thong toi da
//neu muon xoa
using namespace std;

districtController::districtController(string fileName) : repo(fileName) {
    docDanhSachTram();
}

string districtController::chuanHoaTen(string s) {
    for(char &c : s) c = toupper(c);
    
    
   
    return s;
    
}

// S?a l?i void string thành void
void districtController::docDanhSachTram() {
    ifstream file("data/data_tram.txt");
    if(!file.is_open()) return;
    
    string line ;
    while(getline(file, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string tenTinh, tenTram;
        
        getline(ss, tenTinh, '|');
        tenTinh = chuanHoaTen(tenTinh);
        
        vector<string> dsTram;
        while(getline(ss, tenTram, '|')) {
            if(!tenTram.empty()) dsTram.push_back(tenTram);
        }
        mapTram[tenTinh] = dsTram;
    }
    file.close();
}

void districtController::hienThiTieuDe() {
    cout << left << setw(10) << "Ma KV" 
         << setw(25) << "Ten Tinh/Thanh" 
         << setw(25) << "Tram Quan Ly" 
         << setw(15) << "Bang Thong" << endl;
    cout << string(75, '-') << endl;
}

void districtController::chucNangThem() {
    cout << "\n--- THEM MOI KHU VUC / TUYEN CAP ---" << endl;
    if (mapTram.empty()) {
        cout << "=> LOI: He thong chua co du lieu Tram. Vui long kiem tra lai file data_tram.txt!\n";
        return;
    }
    
    string tinhNhap, tramNhap;
    bool check = false;
    do {
        cout << "Nhap ten Tinh/Thanh pho (VD: Ha Noi): ";
        getline(cin, tinhNhap);
        tinhNhap = chuanHoaTen(tinhNhap);
        
        if(mapTram.find(tinhNhap) != mapTram.end()) {
            check = true;
        } else {
            cout << "=> LOI: Tinh/Thanh pho nay khong co hoac go sai!\n";
            cout << "=> Goi y cac Tinh ho tro: ";
            for (auto& pair : mapTram) cout << pair.first << ", ";
            cout << "\n\n";
        }
    } while(!check); 
    
    vector<string> dsTramCuaTinh = mapTram[tinhNhap];
    int chonTram;
    do {
        cout << "\n--- Danh sach Tram tai " << tinhNhap << " ---\n";
        for(size_t i = 0; i < dsTramCuaTinh.size(); i++) {
            cout << i + 1 << ". " << dsTramCuaTinh[i] << "\n";
        }
        
        cout << "Moi chon Tram phu trach (1-" << dsTramCuaTinh.size() << "): ";
        cin >> chonTram;
        cin.ignore();
        
        if (chonTram < 1 || chonTram > dsTramCuaTinh.size()) {
            cout << "=> Lua chon sai. Vui long chon lai!\n";
        }
    } while (chonTram < 1 || chonTram > dsTramCuaTinh.size());

    tramNhap = dsTramCuaTinh[chonTram - 1];
    cout << "=> Da chon: " << tramNhap << " (" << tinhNhap << ")\n";
    
    vector<district> dsHienTai = repo.getData();
    bool daTonTai = false;
    int maxId = 0;
    
    for(auto& kv : dsHienTai) {
        // S?a l?i di?u ki?n so sánh tr?m qu?n lý b? tr?ng hàm
        if(kv.getDistrict() == tinhNhap && kv.getStation() == tramNhap) {
            cout << "=> LOI TU CHOI: Ha tang tai " << tramNhap << " da ton tai voi ma " << kv.getId() << "!\n";
            daTonTai = true;
            break;
        }
        if(kv.getId().length() > 2) {
            int soHienTai = stoi(kv.getId().substr(2));
            if(soHienTai > maxId) maxId = soHienTai;
        }
    }
    
    if(!daTonTai) {
        // S?a l?i hoàn thi?n thu?t toán sinh chu?i ID
        string ma = string("KV")+ (maxId + 1 < 10 ? "0" :"") + to_string(maxId + 1);
        int bangThong;
        
        cout << "Nhap bang thong toi da cua tram (Mbps): ";
        cin >> bangThong;
        cin.ignore();
        
        district kvMoi;
        kvMoi.setId(ma);
        kvMoi.setDistrict(tinhNhap);
        kvMoi.setStation(tramNhap);
        kvMoi.setMaxBandWidth(bangThong); 
        
        if (repo.create(kvMoi)) {
            cout << "=> Them thanh cong! He thong da tu cap ma: " << ma << endl;
        }
    }
}

void districtController::chucNangXemVaTimKiem() {
    cout << "\n--- DANH SACH KHU VUC QUAN LY ---" << endl;
    vector<district> ds = repo.getData();
    if(ds.empty()) {
        cout << "=> Danh sach hien dang trong!" << endl;
    } else {
        hienThiTieuDe();
        for(auto &kv : ds) kv.showToConsole();
    }
    
    cout << "\nNhap Ma KV de xem chi tiet (hoac '0' de thoat): ";
    string ma;
    getline(cin, ma);
    if(ma != "0") {
        district* timThay = repo.searchId(ma);
        if(timThay) {
            cout << "\n--- CHI TIET MA " << ma << " ---" << endl;
            hienThiTieuDe();
            timThay->showToConsole();
        } else {
            cout << "=> Khong tim thay ma: " << ma << endl;
        }
    }
}

void districtController::chucNangCapNhat() {
    cout << "\n--- CAP NHAT THONG TIN KHU VUC ---" << endl;
    cout << "Nhap ma KV can cap nhat: ";
    string ma;
    getline(cin, ma);
    district* timThay = repo.searchId(ma);
    
    if(timThay) {
        hienThiTieuDe(); // S?a l?i thi?u ch?m ph?y
        timThay->showToConsole();
        string input;
        cout << "\nSua bang thong (" << timThay->getMaxBandWidth() << ") [Bo trong giu nguyen]: ";
        getline(cin, input);
        if(!input.empty()) {
            timThay->setMaxBandWidth(stoi(input));
            repo.saveChange();
            cout << "=> Da cap nhat bang thong thanh cong!" << endl;
        } else {
            cout << "=> Khong co thay doi nao duoc luu." << endl;
        }
    } else {
        cout << "=> Khong tim thay!" << endl;
    } 
}

void districtController::chucNangXoa() {
    cout << "\n--- XOA KHU VUC ---" << endl;
    cout << "Nhap ma KV can xoa: ";
    string ma;
    getline(cin, ma);
    district* timThay = repo.searchId(ma);
    
    if(timThay) {
        hienThiTieuDe();
        timThay->showToConsole();
        cout << "\nBan co chac chan xoa? (y/n): ";
        char xacNhan; 
        cin >> xacNhan; 
        cin.ignore();
        
        if (xacNhan == 'y' || xacNhan == 'Y') {
            if (repo.remove(ma)) cout << "=> Da xoa an toan!" << endl;
        } else { 
            cout << "=> Da huy xoa." << endl; // S?a l?i dóng ngo?c nh?n tùy ti?n
        }
    } else {
        cout << "=> Khong tim thay!" << endl;
    }
}

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
            case 1: chucNangThem(); break;
            case 2: chucNangXemVaTimKiem(); break;
            case 3: chucNangCapNhat(); break;
            case 4: chucNangXoa(); break;
            case 0: break;
            default: cout << "=> Sai lua chon!" << endl; break;
        }
    } while (chon != 0);
}
