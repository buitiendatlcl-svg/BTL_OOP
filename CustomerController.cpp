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
		cout << "3. Tim kiem khach hang theo Ma (hoac CCCD)" << endl;
		cout << "4. Chinh sua thong tin khach hang" << endl;
		cout << "5. Xoa khach hang" << endl;            
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
			case 3: searchCustomer(); break;
			case 4: updateCustomer(); break;
			case 5: deleteCustomer(); break;
			case 0: cout << "\n[THONG BAO]: Dang quay ve man hinh chinh ..." << endl; break;
			default: cout << "\n[LOI]: Lua chon khong hop le! Vui long nhap so nguyen tu 1 - 5!" << endl; break;
		}
	} 	while (choice != 0);
}

void CustomerController::addCustomer(){
	cout << "\n==========[THEM KHACH HANG MOI]==========" << endl;
	
	Customer cus;
	
	cus.inputFromKeyboard();
	
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
	cout << "\n==========DANH SACH KHACH HANG==========" << endl;
	
	auto list = customerRepo.getData();
	if(list.empty()){
		cout << "[THONG BAO]: Hien tai chua co khach hang nao trong danh sach" << endl;
		return;
	}
    cout << left 
         << setw(10) << "Ma KH" 
         << setw(30) << "Ho va Ten" 
         << setw(25) << "So CCCD" 
         << setw(25) << "So Dien Thoai" 
         << setw(30) << "Dia Chi" 
         << endl;
    cout << string(120, '-') << endl;	
	
	for(auto cus : list){
		cus.showToConsole();
	}
}

void CustomerController::searchCustomer(){
	cout << "\n==========TIM KIEM KHACH HANG==========" << endl;
	cout << "1. Tim kiem theo ma Khach Hang (ID)" << endl;
	cout << "2. Tim kiem theo CCCD (nationalId)" << endl;
	cout << "Chon phuong thuc tim kiem: ";
	
	int searchChoice = -1;
    string choiceStr;
    getline(cin, choiceStr);
    try {
        size_t pos;
        searchChoice = stoi(choiceStr, &pos);
        if (pos != choiceStr.size()) {
            searchChoice = -1;
        }
    } 
    catch (...) {
        searchChoice = -1;
    }
	
	if(searchChoice == 1){
		//Tim theo ma ID (Co san trong Repo)
		string cusId;
		cout << "Nhap ma khach hang can tim: ";
		cin >> cusId;
		
		Customer* cus = customerRepo.searchId(cusId);
		
		if(cus == nullptr){
			cout << "[LOI]: Khong tim thay khach hang !!!" << endl;
		}
		else{
			cout << "\n----------[KET QUA TIM KIEM]----------" << endl;	
			cout << left << setw(10) << "MaKH"
				<< setw(30) << "HovaTen"
				<< setw(25) << "SoCCCD"
				<< setw(25) << "SoDienThoai" 
				<< setw(30) << "DiaChi"
				<< endl;
				cout << string(120, '-') << endl;
				cus->showToConsole();
		}
	}
	
	else if(searchChoice == 2){
		//Tim theo ma CCCD (Quet duyet danh sach, tai vi ham getNationalId khong co trong Entity (class bo cua moi class con)
		string natId;
		cout << "Nhap so CCCD khach hang can tim: ";
		cin >> natId;
		
		auto list = customerRepo.getData();
		bool found = false; // gan found ban dau la chua tim thay 
				
		for(auto cus : list){
			// So sanh ham getNationalId() voi tung khach hang vua nhap
			if(cus.getNationalId() == natId){
				cout << "\n----------[KET QUA TIM KIEM]----------" << endl;
				cout << left << setw(10) << "MaKH"
				<< setw(30) << "HovaTen"
				<< setw(25) << "SoCCCD"
				<< setw(25) << "SoDienThoai" 
				<< setw(30) << "DiaChi"
				<< endl;
				
				cout << string(120, '-') << endl;
				cus.showToConsole(); // 
	            found = true;        // Ðánh d?u: ÐÃ TÌM TH?Y
	            break;					
			}
		}
		
		if(!found){
			cout << "[LOI]: Khong tim thay khach hang nao co CCCD " << natId << "!!!" << endl;
		}
	}
	
	else{
		cout << "\n[LOI]: Lua chon khong hop le ! Vui long nhap so nguyen tu 1 - 2 !" << endl;
	}	
}

void CustomerController::updateCustomer(){
	cout << "\n----------DANH SACH KHACH HANG HIEN TAI----------" << endl;
	cout << left << setw(10) << "MaKH"
				<< setw(30) << "HovaTen"
				<< setw(25) << "SoCCCD"
				<< setw(25) << "SoDienThoai" 
				<< setw(30) << "DiaChi"
				<< endl;
	cout << string(120, '-') << endl;
	auto list = customerRepo.getData();
	for(auto x : list){
		x.showToConsole();
	}
	
	cout << "\n==========CAP NHAT KHACH HANG==========" << endl;
	
		cout << "\nNhap ma khach hang can cap nhat: ";
		string cusId;
		getline(cin, cusId);
		
		Customer* cus = customerRepo.searchId(cusId);
		if(cus == nullptr){
			cout << "\n[LOI] Hien tai ma khach hang '" << cusId << "'khong ton tai trong danh sach !!!";
			return;
		}
		
		// Hien thi thong tin khach hang can cap nhat 
		cout << left << setw(10) << "MaKH"
					<< setw(30) << "HovaTen"
					<< setw(25) << "SoCCCD"
					<< setw(25) << "SoDienThoai" 
				<< setw(30) << "DiaChi"
				<< endl;
		cout << string(120, '-') << endl;
		for(auto& x : list){
			if(x.getId() == cusId){
				x.showToConsole();
			}
		}
	
	cout << "\n[LUU Y]: Nhan phim ENTER de bo qua neu khong muon chinh sua thong tin do" << endl;
	
	string input;
		
	// Sua ten
    cout << "+ Nhap Ho va Ten moi (Hien tai: " << cus->getName() << "): ";
    getline(cin, input);
    if (input != "") {
        cus->setName(input);
    }
    // Sua CCCD
    cout << "+ Nhap So CCCD moi (Hien tai: " << cus->getNationalId() << "): ";
    getline(cin, input);
    if (input != "") {
        cus->setNationalId(input);
    }
    // Sua sdt
    cout << "+ Nhap So dien thoai moi (Hien tai: " << cus->getPhoneNumber() << "): ";
    getline(cin, input);
    if (input != "") {
        cus->setPhoneNumber(input);
    }
    // Sua dia chi
    cout << "+ Nhap Dia chi moi (Hien tai: " << cus->getAddress() << "): ";
    getline(cin, input);
    if (input != "") {
        cus->setAddress(input);
    }
	
	customerRepo.saveToFile();
	cout << "\n[THANH CONG]: Da cap nhat va luu thong tin khach hang '" << cusId << "' vao file!" << endl;
}

void CustomerController::deleteCustomer(){
	cout << "\n----------DANH SACH KHACH HANG HIEN TAI----------" << endl;
	cout << left << setw(10) << "MaKH"
				<< setw(30) << "HovaTen"
				<< setw(25) << "SoCCCD"
				<< setw(25) << "SoDienThoai" 
				<< setw(30) << "DiaChi"
				<< endl;
	cout << string(120, '-') << endl;
	auto list1 = customerRepo.getData();
	for(auto x : list1){
		x.showToConsole();
	}
	
	cout << "\n==========XOA KHACH HANG==========" << endl;
	cout << "\nNhap ma khach hang can xoa: ";
	string cusId;
	getline(cin, cusId);
	
	Customer* cus = customerRepo.searchId(cusId);
	
	// Kiem tra xem ma KH con trong danh sach khong ?
	if(cus == nullptr){ 
		cout << "\n[LOI]: Khong tim thay ma khach hang '" << cusId <<"' trong danh sach " << endl;
		return;
	}
	
	//Kiem tra khach hang nay con hop dong khong
	contractRepo.reloadData();
	auto list2 = contractRepo.getData();
	for(auto& x : list2){
		if(x.getCustomerId() == cusId){
			cout << "\n[THONG BAO]: Hien tai khach hang '" << cusId << "' van con hop dong '" << x.getId() <<"', khong the thuc hien thao tac xoa!" << endl;
			return;
		}
	}
	
	cout << "[LUU Y]: Ban co chac chan muon xoa khach hang '" << cus->getName() << "' (" << cus->getId() << ") khong (y/n) ?";
	string choice; 
	getline(cin, choice);
	if(choice == "y" || choice == "Y"){
		if(customerRepo.remove(cusId)){
			cout << "[THANH CONG]: Da xoa khach hang co ma '" << cusId << "' trong danh sach" << endl;
			customerRepo.reloadData();
		
			cout << "\n----------DANH SACH KHACH HANG SAU KHI XOA----------" << endl;
			cout << left << setw(10) << "MaKH"
						<< setw(30) << "HovaTen"
						<< setw(25) << "SoCCCD"
						<< setw(25) << "SoDienThoai" 
						<< setw(30) << "DiaChi"
						<< endl;
			cout << string(120, '-') << endl;
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
	
	
	
	
	


					
	
