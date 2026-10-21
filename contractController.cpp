#include "contractController.h"
#include <cctype>
#include <iomanip>
using namespace std;

contractController::contractController(){
	Repository<Customer> customerRepo{"data/customer.txt"};
	Repository<internet> internetRepo{"data/internet.txt"};
	Repository<district> districtRepo{"data/data_khuvuc.txt"};
}

void contractController::createFunction(){
	cout << "\n--- DANH SACH KHACH HANG HIEN CO ---" << endl;
	vector<Customer> listCustomer = customerRepo.getData();
	if(listCustomer.empty()){
		cout << "Hien khong co khach hang nao!" << endl;
	}	
	else{
		for(auto x : listCustomer){
			x.showToConsole();
		}
	}
	
	cout << "Chon ID khach hang ban muon them vao hop dong: ";
	string idCustomer;
	getline(cin, idCustomer);
	
	for(int i = 0; i < idCustomer.length(); i++){
		if(isalpha(idCustomer[i])){
			idCustomer[i] = toupper(idCustomer[i]); 
		}
	}
	
	contract newContract;
	auto itCustomer = customerRepo.searchId(idCustomer);
	if(itCustomer != NULL){
		newContract.setCustomerId(idCustomer);
	}
	else{
		cout << "Khong tim thay ID khach hang" << endl;
	}
	
	cout << "\n--- DANH SACH CAC GOI MANG HIEN CO ---" << endl;
	vector<internet> listInternet = internetRepo.getData();
	if(listInternet.empty()){
		cout << "Hien khong co goi mang nao!" << endl;
	}	
	else{
		for(auto x : listInternet){
			x.showToConsole();
		}
	}
	cout << "Chon ID goi mang ban muon them vao hop dong: ";
	string idInternet;
	getline(cin, idInternet);
	
	for(int i = 0; i < idInternet.length(); i++){
		if(isalpha(idInternet[i])){
			idInternet[i] = toupper(idInternet[i]); 
		}
	}
	
	auto itInternet = internetRepo.searchId(idInternet);
	if(itInternet != NULL){
		newContract.setPackageId(idInternet);
	}
	else{
		cout << "Khong tim thay ID goi mang" << endl;
	}
	
	cout << "\n--- DANH SACH CAC KHU VUC HIEN CO ---" << endl;
	vector<district> listDistrict = districtRepo.getData();
	if(listDistrict.empty()){
		cout << "Hien khong co khu vuc nao!" << endl;
	}	
	else{
		for(auto x : listDistrict){
			x.showToConsole();
		}
	}
	cout << "Chon ID khu vuc ban muon them vao hop dong: ";
	string idDistrict;
	getline(cin, idDistrict);
	
	for(int i = 0; i < idDistrict.length(); i++){
		if(isalpha(idDistrict[i])){
			idDistrict[i] = toupper(idDistrict[i]); 
		}
	}
	
	auto itDistrict = districtRepo.searchId(idDistrict);
	if(itDistrict != NULL){
		newContract.setAreaId(idDistrict);
	}
	else{
		cout << "Khong tim thay ID khu vuc" << endl;
	}
	
	string newContractId = contractRepo.autoGenId("HD");
	newContract.setId(newContractId);
	
	newContract.inputFromKeyboard();
	if(contractRepo.create(newContract)){
		cout << "Them moi hop dong thanh cong!" << endl;
	}
	else{
		cout << "Them moi hop dong that bai!" << endl;
	}
}

void contractController::readFunction(){
	cout << "\n--- DANH SACH HOP DONG HIEN CO ---" << endl;
	vector<contract> listContract = contractRepo.getData();
	if(listContract.empty()){
		cout << "Danh sach chua co hop dong nao" << endl;
	}
	else{
		cout << left << setw(20) << "Ma hop dong"
		 	 << "| " << setw(15) << "Ma khach hang"
		 	 << "| " << setw(15) << "Ma goi"
			 << "| " << setw(15) << "Ma khu vuc" 
			 << "| " << setw(15) << "Ngay ky" << endl;
		cout << string(85, '-') << endl;
		
		for(auto x : listContract){
			x.showToConsole();
		}
	}
}

void contractController::updateFunction(){
	readFunction();
	cout << "Chon ID hop dong ban muon chinh sua: ";
	string search;
	getline(cin, search);
	for(int i = 0; i < search.length(); i++){
		if(isalpha(search[i])){
			search[i] = toupper(search[i]); 
		}
	}
	auto itContract = contractRepo.searchId(search);
	if(itContract != NULL){
		cout << "\nNhap thanh phan ban muon thay doi" << endl;
		cout << "1. Ngay ky hop dong" << endl;
		cout << "0. Quay lai" << endl;
		cout << "Nhap lua chon cua ban: ";
		int option; cin >> option;
		cin.ignore();
		switch(option){
			case 1: {
				cout << "Nhap ngay ky hop dong thay doi: ";
				string newSignDate;
				getline(cin, newSignDate);
				itContract->setSignDate(newSignDate);
				contractRepo.saveToFile();
				break;
			}
		}
	}
	else{
		cout << "Khong tim thay hop dong nao" << endl;
	}
}

void contractController::deleteFunction(){
	
}

void contractController::run(){
	int choice = -1;
	do{
		cout << "\n============= QUAN LY HOP DONG =============" << endl;
		cout << "1. C - Them thong tin hop dong moi" << endl;
        cout << "2. R - Xem danh sach cac hop dong hien co" << endl;
        cout << "3. U - Thay doi cac hop dong hien co" << endl;
        cout << "4. D - Xoa hop dong hien co" << endl;
        cout << "0. Thoat chuong trinh quan ly goi mang" << endl;
        cout << "Nhap lua chon cua ban: ";
        string choiceStr;
        getline(cin, choiceStr);
        try{
        	size_t pos;
        	choice = stoi(choiceStr, &pos);
        	if(pos != choiceStr.size() || choice < 0){
        		choice = -1;
			}
		}catch(...){
			choice = -1;
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

