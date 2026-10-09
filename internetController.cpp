#include "internetController.h"
#include <cctype>

using namespace std;

internetController::internetController(){
}

void internetController::createFunction(){
	cout << "\n--- NHAP THONG TIN GOI MANG MOI ---" << endl;
	internet newInternet;
	
	string newInternetId = internetRepo.autoGenId("G");
	newInternet.setId(newInternetId);
	
	newInternet.inputFromKeyboard();
	
	if(internetRepo.create(newInternet)){
		cout << "Them moi goi mang thanh cong!" << endl;
	}
	else{
		cout << "Goi mang da ton tai!" << endl;
	}
}

void internetController::readFunction(){
	cout << "\n--- DANH SACH CAC GOI MANG ---" << endl;
	vector<internet> list = internetRepo.getData();
	
	if(list.empty()){
		cout << "Danh sach hien chua co goi mang" << endl;
	}
	else{
		for(auto x : list){
			x.showToConsole();
		}
	}
}

void internetController::updateFunction(){
	cout << "\n--- DANH SACH CAC GOI MANG ---" << endl;
	vector<internet> list = internetRepo.getData();
	if(list.empty()){
		cout << "Danh sach hien chua co goi mang" << endl;
	}
	else{
		for(auto x : list){
			x.showToConsole();
		}
		cout << "Chon ID goi mang ban muon chinh sua: ";
		string search;
		getline(cin, search);
		for(int i = 0; i < search.length(); i++){
			if(isalpha(search[i])){
				search[i] = toupper(search[i]); 
			}
		}
		auto it = internetRepo.searchId(search);
		if(it != NULL){
			cout << "\nNhap thanh phan ban muon thay doi" << endl;
			cout << "1. Ten goi mang" << endl;
			cout << "2. Toc do" << endl;
			cout << "3. Tep khach hang" << endl;
			cout << "4. Gia cuoc" << endl;
			cout << "Nhap lua chon cua ban: ";
			int option; cin >> option;
			cin.ignore();
			switch(option){
				case 1:{
					cout << "Nhap ten goi mang ban muon thay doi: ";
					string newPackageName;
					getline(cin, newPackageName);
					it->setPackageName(newPackageName);
					internetRepo.saveToFile();
					cout << "\nThay doi thanh cong!" << endl;
					break;
				}
				case 2:{
					cout << "Nhap toc do ban muon thay doi: ";
					string newSpeed;
					getline(cin, newSpeed);
					it->setSpeed(newSpeed);
					internetRepo.saveToFile();
					cout << "\nThay doi thanh cong!" << endl;
					break;
				}
				case 3:{
					cout << "Nhap tep khach hang ban muon thay doi: ";
					string newCustomerType;
					getline(cin, newCustomerType);
					it->setCustomerType(newCustomerType);
					internetRepo.saveToFile();
					cout << "\nThay doi thanh cong!" << endl;
					break;
				}
				case 4:{
					cout << "Nhap gia cuoc ban muon thay doi: ";
					double newPrice;
					cin >> newPrice; cin.ignore();
					it->setPrice(newPrice);
					internetRepo.saveToFile();
					cout << "\nThay doi thanh cong!" << endl;
					break;
				}	
			}	
		}
		else{
			cout << "Khong tim thay goi mang nao" << endl;
		}
	}
}

void internetController::deleteFunction(){
	cout << "\n--- DANH SACH CAC GOI MANG ---" << endl;
	vector<internet> list = internetRepo.getData();
	if(list.empty()){
		cout << "Danh sach hien chua co goi mang" << endl;
	}
	else{
		for(auto x : list){
			x.showToConsole();
		}
		cout << "Chon ID goi mang ban muon xoa: ";
		string search;
		getline(cin, search);
		for(int i = 0; i < search.length(); i++){
			if(isalpha(search[i])){
				search[i] = toupper(search[i]); 
			}
		}
		auto it = internetRepo.searchId(search);
		if(it != NULL){
			if(internetRepo.remove(search)){
				cout << "Xoa thanh cong!" << endl;
			}
			else{
				cout << "Xoa khong thanh cong!" << endl;
			}
		}
		else{
			cout << "Khong tim thay goi mang nao" << endl;
		}
	}
}

void internetController::run(){
	int choice;
	do{
		cout << "\n============= QUAN LY TUYEN CAP/KHU VUC =============" << endl;
		cout << "1. C - Them thong tin goi mang moi" << endl;
        cout << "2. R - Xem danh sach cac goi mang hien co" << endl;
        cout << "3. U - Thay doi cac goi mang hien co" << endl;
        cout << "4. D - Xoa goi mang hien co" << endl;
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








