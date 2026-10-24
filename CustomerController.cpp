#include "CustomerController.h"
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

	CustomerController::CustomerController()
	:customerRepo("data/customer.txt"), contractRepo("data/contract.txt "){}

// 1. Kiem tra trung CCCD
bool CustomerController::isNationalIdDuplicate(string cccd, string excludeId) {
    for (auto cus : customerRepo.getData()) {
        // Neu ma khac voi nguoi dang sua VA cccd bi trung -> bao trung (true)
        if (cus.getId() != excludeId && cus.getNationalId() == cccd) {
            return true;
        }
    }
    return false; // Duyet het danh sach ma khong thay ai trung -> hop le (false)
}

// 2. Kiem tra trung So Dien Thoai
bool CustomerController::isPhoneNumberDuplicate(string sdt, string excludeId) {
    for (auto cus : customerRepo.getData()) {
        // Neu ma khac voi nguoi dang sua VA sdt bi trung -> bao trung (true)
        if (cus.getId() != excludeId && cus.getPhoneNumber() == sdt) {
            return true;
        }
    }
    return false; // Khong bi trung
}

void CustomerController::addCustomer(){
	cout << "\n==========THEM KHACH HANG MOI==========" << endl;
	Customer cus;
	cus.inputFromKeyboard();
	
	// Kiem tra trung CCCD
	while (isNationalIdDuplicate(cus.getNationalId())) {
	    cout << "\n[LOI]: So CCCD '" << cus.getNationalId() << "' da ton tai! Vui long nhap lai (hoac nhap '0' de huy): ";
	    string cccdMoi;
	    getline(cin, cccdMoi);
	    if (cccdMoi == "0") return;
	    if (cus.isValidNationalId(cccdMoi)) {
	        cus.setNationalId(cccdMoi);
	    }
	}

	// Kiem tra trung SDT
	while (isPhoneNumberDuplicate(cus.getPhoneNumber())) {
	    cout << "\n[LOI]: So dien thoai '" << cus.getPhoneNumber() << "' da ton tai! Vui long nhap lai (hoac nhap '0' de huy): ";
	    string sdtMoi;
	    getline(cin, sdtMoi);
	    if (sdtMoi == "0") return;
	    if (cus.isValidPhoneNumber(sdtMoi)) {
	        cus.setPhoneNumber(sdtMoi);
	    }
	}	
	
		// CHON DIA CHI TRUC TIEP TAI DAY:
	cout << "\n--- CHON DIA CHI KHACH HANG ---" << endl;
	string diaChi = selectAddress();
	if (diaChi == "") {
		cout << "\n[THONG BAO]: Da huy thao tac vi chua chon dia chi!";
		return;
	}
	cus.setAddress(diaChi); // gan dia chi vao khach hang
	
	
	// Tu dong sinh ma khach hang voi tien to "KH" (vi du: KH37, KH38, ...)
	string newId = customerRepo.autoGenId("KH");
	cus.setId(newId);
	
	if(customerRepo.create(cus) == 1){
		cout << "\n[THANH CONG]: Da them khach hang '" << cus.getName() 
		<< "' (Ma: " << cus.getId() << ") vao he thong!" << endl;
	}
	else{
		cout << "\n[LOI TRUNG KHOA CHINH]: Ma khach hang '" << cus.getId() << "' DA TON TAI TRONG HE THONG!!!" << endl;
		cout << "\n--->Vui long su dung ma khach hang khac ! <---" << endl;
	}
}

void CustomerController::displayAllCustomer(){
	cout << "\n==========DANH SACH KHACH HANG ==========" << endl;
	
	auto list = customerRepo.getData();
	if(list.empty()){
		cout << "\n[THONG BAO]: Hien tai chua co khach hang nao trong danh sach" << endl;
		return;
	}
    cout << left 
         << setw(10) << "Ma KH" 
         << setw(25) << "Ho va Ten" 
         << setw(20) << "So CCCD" 
         << setw(20) << "So Dien Thoai" 
         << setw(20) << "Dia Chi" 
         << endl;
    cout << string(95, '-') << endl;	
	
	for(auto cus : list){
		cus.showToConsole();
	}
}

void CustomerController::updateCustomer(){
	auto list = customerRepo.getData();
	if (list.empty()) {
		cout << "\n[THONG BAO]: Hien tai chua co khach hang nao trong danh sach de cap nhat!" << endl;
		return;
	}
	
	cout << "\n----------DANH SACH KHACH HANG HIEN TAI----------" << endl;
	cout << left 
         << setw(10) << "Ma KH" 
         << setw(25) << "Ho va Ten" 
         << setw(20) << "So CCCD" 
         << setw(20) << "So Dien Thoai" 
         << setw(20) << "Dia Chi" 
         << endl;
    cout << string(95, '-') << endl;
	for(auto x : list){
		x.showToConsole();
	}
	
	cout << "\n==========CAP NHAT KHACH HANG==========" << endl;
		
	string cusId;
	Customer* cus = nullptr;
	
	while(true){
		cout << "\nNhap ma khach hang can cap nhat (Nhap '0' de quay lai): ";
		getline(cin, cusId);
		
		//Chuc nang quay lai banh cach nhap 0
		if(cusId == "0"){
			cout << "\n[THONG BAO]: Quay lai Menu thanh cong !" << endl;
			return;
		}
		
		//chuan hoa "kh" --> "KH"
		for(char &c : cusId){ // c bat buoc phai co tham chieu de cusId co the thay doi gia tri theo C
			c = toupper(c);
		}
		
		//Kiem tra xem ma khach hang nay con ton tai khong, neu ton tai thi thoat vong lap
		cus = customerRepo.searchId(cusId);
		if(cus != nullptr){
			break;
		}
		
		//Neu khong ton tai thi bao loi
		cout << "\n[LOI] Hien tai ma khach hang '" << cusId << "'khong ton tai trong danh sach ! Vui long nhap lai !" << endl;
	}
		
		cout << "\n---------THONG TIN CUA KHACH HANG '" << cusId << "' TRONG DANH SACH----------" << endl;
		// Hien thi thong tin khach hang can cap nhat 
		cout << left 
         << setw(10) << "Ma KH" 
         << setw(25) << "Ho va Ten" 
         << setw(20) << "So CCCD" 
         << setw(20) << "So Dien Thoai" 
         << setw(20) << "Dia Chi" 
         << endl;
    	cout << string(95, '-') << endl;
		for(auto& x : list){
			if(x.getId() == cusId){
				x.showToConsole();
			}
		}
	
	cout << "\n[LUU Y]: Nhan phim ENTER de bo qua neu khong muon chinh sua thong tin do" << endl;
	
	string input;
		
	// Sua ten
	while(true){
	    cout << "\n+ Nhap Ho va Ten moi (Hien tai: " << cus->getName() << ") (Nhap '0' de quay tro lai): ";
	    getline(cin, input);
	    if(input == "") break;
	    if(input == "0") return;
	    if(cus->isValidName(input)){
	        cus->setName(input);
	        break;
	    }
	    cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
	}
	
     // 2. Sua So CCCD
    while(true){    
        cout << "+ Nhap So CCCD moi (Hien tai: " << cus->getNationalId() << ") (Nhap '0' de quay lai): ";
        getline(cin, input);
        if(input == "") break; // Nhan Enter de bo qua (giu nguyen)
        if(input == "0") return;
        
        if (cus->isValidNationalId(input)){
            // Neu nguoi dung nhap lai dung CCCD hien tai cua chinh ho thi bo qua
            if(input == cus->getNationalId()){
                break;
            }
            // Kiem tra xem da co khach hang khac dang ky so nay chua
            if (isNationalIdDuplicate(input, cus->getId())) {
                cout << "\n[LOI]: So CCCD nay da duoc khach hang khac dang ky! Vui long nhap so khac!" << endl;
                continue; // continue nam trong while nen hoan toan hop le
            }
            cus->setNationalId(input);
            break;
        }
        cout << "\n[THONG BAO]: So CCCD khong hop le (phai du 12 chu so va bat dau bang '0')! Vui long nhap lai!" << endl;
    }
    
    // 3. Sua So dien thoai
    while(true){
        cout << "+ Nhap So dien thoai moi (Hien tai: " << cus->getPhoneNumber() << ") (Nhap '0' de quay lai): ";
        getline(cin, input);
        if(input == "") break; // Nhan Enter de bo qua (giu nguyen)
        if(input == "0") return;
        
        if (cus->isValidPhoneNumber(input)) {
            // Neu nguoi dung nhap lai dung SDT hien tai cua chinh ho thi bo qua
            if(input == cus->getPhoneNumber()){
                break;
            }
            // Kiem tra xem da co khach hang khac dang ky so nay chua
            if (isPhoneNumberDuplicate(input, cus->getId())) {
                cout << "\n[LOI]: So dien thoai nay da duoc khach hang khac dang ky! Vui long nhap so khac!" << endl;
                continue; // continue nam trong while nen hoan toan hop le
            }
            cus->setPhoneNumber(input);
            break;
        }
        cout << "\n[THONG BAO]: So dien thoai khong hop le (phai du 10 so va bat dau bang '0')! Vui long nhap lai!" << endl;
    }
    
    // Sua dia chi
    cout << "+ Nhap Dia chi moi (Hien tai: " << cus->getAddress() << ") (Nhap '0' de quay tro lai): ";
    getline(cin, input);
    if(input == "0") return;
    if (input != ""){
        cus->setAddress(input);
    }
	
	customerRepo.saveToFile();
	cout << "\n[THANH CONG]: Da cap nhat va luu thong tin khach hang '" << cusId << "' vao file!" << endl;
}

void CustomerController::deleteCustomer(){
	cout << "\n----------DANH SACH KHACH HANG HIEN TAI1----------" << endl;
	cout << left 
         << setw(10) << "Ma KH" 
         << setw(25) << "Ho va Ten" 
         << setw(20) << "So CCCD" 
         << setw(20) << "So Dien Thoai" 
         << setw(20) << "Dia Chi" 
         << endl;
    cout << string(95, '-') << endl;
	auto list1 = customerRepo.getData();
	for(auto x : list1){
		x.showToConsole();
	}
	
	cout << "\n==========XOA KHACH HANG==========" << endl;
	
	string cusId;
	Customer* cus = nullptr;
	
	while(true){
		cout << "\nNhap ma khach hang can xoa (Nhap '0' de quay lai): ";
		getline(cin, cusId);
		
		//Nhap 0 thi quay lai
		if(cusId == "0"){
			cout << "\n[THONG BAO]: Quay lai Menu thanh cong !" << endl;
			return;
		}
		
		//Chuyen kh thanh KH
		for(char &c : cusId){ // c bat buoc phai co tham chieu de cusId co the thay doi gia tri theo C
				c = toupper(c);
		}
		
		cus = customerRepo.searchId(cusId);	
		// Kiem tra xem ma KH con trong danh sach KH khong ?
		if(cus == nullptr){ 
			cout << "\n[LOI]: Khong tim thay ma khach hang '" << cusId <<"' trong danh sach. Vui long nhap lai ! " << endl;
			continue;
		}
		//Kiem tra khach hang nay con hop dong khong
		contractRepo.reloadData();
		auto list2 = contractRepo.getData();
		int check = 0;
		for(auto& x : list2){
			if(x.getCustomerId() == cusId){
				cout << "\n[THONG BAO]: Hien tai khach hang '" << cusId << "' van con hop dong '" << x.getId() <<"', khong the thuc hien thao tac xoa!" << endl;
				check = 1;
				break;
			}
		}
		if(check==1) continue;
		else{
			break;
		}
}
	
	string choice; 
	while(true){
		cout << "\n[LUU Y]: Ban co chac chan muon xoa khach hang '" << cus->getName() << "' (" << cus->getId() << ") khong (y/n) ? ";
		getline(cin, choice);
		
		if(choice == "y" || choice == "Y" || choice == "n" || choice == "N"){
			if(choice == "y" || choice == "Y"){
				if(customerRepo.remove(cusId)){
					cout << "[THANH CONG]: Da xoa khach hang co ma '" << cusId << "' trong danh sach" << endl;
					customerRepo.reloadData();
				
					cout << "\n----------DANH SACH KHACH HANG SAU KHI XOA----------" << endl;
					cout << left 
				         << setw(10) << "Ma KH" 
				         << setw(25) << "Ho va Ten" 
				         << setw(20) << "So CCCD" 
				         << setw(20) << "So Dien Thoai" 
				         << setw(20) << "Dia Chi" 
				         << endl;
				    cout << string(95, '-') << endl;
					auto list3 = customerRepo.getData();
					for(auto x : list3){
						x.showToConsole();
					}
					break;			
				}
				else{
					cout << "\n[LOI]: Loi he thong !!!" << endl;
					break;
				}
			}
			else{
				cout << "\n[HUY THAO TAC]: Da huy lenh xoa khach hang!" << endl;
				break;
			}
		}
		else{
			cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
			continue;
		}	
	}
}

void CustomerController::run(){
	int choice = -1;
	do{
		cout << "\n==========QUAN LY KHACH HANG==========" << endl;
		cout << "1. Them khach hang moi" << endl;
		cout << "2. Hien thi toan bo khach hang" << endl;
		cout << "3. Chinh sua thong tin khach hang" << endl;
		cout << "4. Xoa khach hang" << endl;            
		cout << "0. Quay lai Menu chinh" << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << "Lua chon: ";
		
        string choiceStr;
        getline(cin, choiceStr);
        
        try {
            size_t pos;
            choice = stoi(choiceStr, &pos);
            // Kiem tra neu nguoi dung nhap lan lon chu va so (vi du: 1abc)
            if (pos != choiceStr.size()) {
                choice = -1;
            }
        } 
        catch (...) {
            // Bat moi ngoai le (nhap chu, enter trong, so qua lon)
            choice = -1;
        }

		switch (choice) {
			case 1: addCustomer(); break;
			case 2: displayAllCustomer(); break;
			case 3: updateCustomer(); break;
			case 4: deleteCustomer(); break;
			case 0: cout << "\n[THONG BAO]: Dang quay ve man hinh chinh ..." << endl; break;
			default: cout << "\n[LOI]: Lua chon khong hop le! Vui long nhap so nguyen tu 0 - 4!" << endl; break;
		}
	} 	while (choice != 0);
}



// ham tinh doc file data_tram.txt, loc bo trung lap va luu vao bo nho RAM
vector<string> CustomerController::getListProvinces() {
    // bien static luu danh sach trong RAM, cac lan goi sau khong can doc lai file
    static vector<string> cachedProvinces;

    // neu RAM da co du lieu thi tra ve luon, tranh doc lai file
    if (!cachedProvinces.empty()) {
        return cachedProvinces;
    }

    cachedProvinces.clear();
    set<string> uniqueProvinces; // set tu dong loc cac tinh trung lap va sap xep A-Z

    ifstream file("data/data_tram.txt");
    if (!file.is_open()) {
        cout << "[LOI]: Khong the mo file data/data_tram.txt!" << endl;
        return cachedProvinces;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string tenTinh;

        // lay ten tinh truoc dau '|'
        if (getline(ss, tenTinh, '|')) {
            // cat bo khoang trang thua o dau chuoi
            while (!tenTinh.empty() && isspace((unsigned char)tenTinh.front())) {
                tenTinh.erase(tenTinh.begin());
            }
            // cat bo khoang trang thua o cuoi chuoi
            while (!tenTinh.empty() && isspace((unsigned char)tenTinh.back())) {
                tenTinh.pop_back();
            }

            // nhet vao set, neu tinh da co roi set se tu dong bo qua
            if (!tenTinh.empty()) {
                uniqueProvinces.insert(tenTinh);
            }
        }
    }
    file.close();

    // do du lieu tu set sang vector cachedProvinces
    for (const string& tinh : uniqueProvinces) {
        cachedProvinces.push_back(tinh);
    }

    return cachedProvinces;
}

// ham hien thi danh sach tinh thanh va cho nguoi dung nhap dia chi
string CustomerController::selectAddress() {
    // goi ham tinh de lay du lieu tu RAM
    vector<string> dsTinh = getListProvinces();

    if (dsTinh.empty()) {
        cout << "[CANH BAO]: Danh sach tinh trong, vui long tu nhap dia chi: ";
        string dc;
        getline(cin, dc);
        return dc;
    }

    // in ra man hinh danh sach tinh theo 3 cot
    cout << "\n================= DANH SACH TINH / THANH PHO =================" << endl;
    for (size_t i = 0; i < dsTinh.size(); ++i) {
        string muc = to_string(i + 1) + ". " + dsTinh[i];
        cout << left << setw(26) << muc;
        if ((i + 1) % 3 == 0) cout << endl; // cu 3 tinh thi xuong dong
    }
    if (dsTinh.size() % 3 != 0) cout << endl;
    cout << "0. Huy bo / Khong chon" << endl;
    cout << string(62, '-') << endl;

    // nguoi dung nhap so de chon tinh
    int chon = -1;
    while (true) {
        cout << "Moi chon Tinh/Thanh pho (1 - " << dsTinh.size() << ") hoac nhap '0' de bo qua: ";
        string input;
        getline(cin, input);
        try {
            size_t pos;
            chon = stoi(input, &pos);
            if (pos == input.size() && chon >= 0 && chon <= (int)dsTinh.size()) {
                break;
            }
        } catch (...) {}
        cout << "[LOI]: Vui long nhap so hop le tu 0 den " << dsTinh.size() << "!" << endl;
    }

    if (chon == 0) return ""; // nguoi dung huy

    string tinhDaChon = dsTinh[chon - 1];
    cout << "=> Ban da chon: " << tinhDaChon << endl;

    // cho phep nhap them so nha ten duong
    cout << "Nhap so nha / ten duong (hoac nhan Enter de chi lay ten Tinh): ";
    string chiTiet;
    getline(cin, chiTiet);

    if (chiTiet.empty()) {
        return tinhDaChon;
    }
    return chiTiet + ", " + tinhDaChon;
}
	
	
	
	


					
	
