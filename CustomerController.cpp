#include "CustomerController.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

	CustomerController::CustomerController()
	:customerRepo("data/customer.txt"), contractRepo("data/contract.txt)"){}
	
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

void CustomerController::addCustomer(){
	cout << "\n==========DANH SACH KHACH HANG HIEN TAI=========" << endl;
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
	
	cout << "\n==========THEM KHACH HANG MOI==========" << endl;
	Customer cus;
	cus.inputFromKeyboard();
	
	if(cus.getName() == "" || cus.getNationalId() == "" || cus.getPhoneNumber() == "" || cus.getAddress() ==""){
		cout << "\n[THONG BAO]: Da huy thao tac them khach hang";
		return;
	}
	
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
    cout << "+ Nhap Ho va Ten moi (Hien tai: " << cus->getName() << ") (Nhap '0' de quay tro lai): ";
    getline(cin, input);
    if(input == "0") return;
    if (input != ""){
        cus->setName(input);
    }
    // Sua CCCD
    cout << "+ Nhap So CCCD moi (Hien tai: " << cus->getNationalId() << ") (Nhap '0' de quay tro lai): ";
    getline(cin, input);
    if(input == "0") return;
    if (input != "") {
        cus->setNationalId(input);
    }
    // Sua sdt
    cout << "+ Nhap So dien thoai moi (Hien tai: " << cus->getPhoneNumber() << ") (Nhap '0' de quay tro lai): ";
    getline(cin, input);
    if(input == "0") return;
    if (input != "") {
        cus->setPhoneNumber(input);
    }
    // Sua dia chi
    cout << "+ Nhap Dia chi moi (Hien tai: " << cus->getAddress() << ") (Nhap '0' de quay tro lai): ";
    getline(cin, input);
    if(input == "0") return;
    if (input != "") {
        cus->setAddress(input);
    }
	
	customerRepo.saveToFile();
	cout << "\n[THANH CONG]: Da cap nhat va luu thong tin khach hang '" << cusId << "' vao file!" << endl;
}

void CustomerController::deleteCustomer(){
	cout << "\n----------DANH SACH KHACH HANG HIEN TAI----------" << endl;
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
		for(auto& x : list2){
			if(x.getCustomerId() == cusId){
				cout << "\n[THONG BAO]: Hien tai khach hang '" << cusId << "' van con hop dong '" << x.getId() <<"', khong the thuc hien thao tac xoa!" << endl;
				continue;
			}
		}
		
		break;
	}
	string choice; 
	while(true){
		cout << "\n[LUU Y]: Ban co chac chan muon xoa khach hang '" << cus->getName() << "' (" << cus->getId() << ") khong (y/n) ? ";
		getline(cin, choice);
		if(choice != "y" || choice != "y" || choice != "n" || choice != "N"){
			cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
			continue;
		}
		break;
	}
	
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
		}
		else{
			cout << "\n[LOI]: Loi he thong !!!" << endl;
		}
	}
	else{
		cout << "\n[HUY THAO TAC]: Da huy lenh xoa khach hang!" << endl;
	}	
}
	
	
	
	
	


					
	
