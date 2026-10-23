#include "internetController.h"
#include <cctype>
#include <iomanip>
using namespace std;

internetController::internetController(){
}

void internetController::createFunction(){
	internetRepo.reloadData();
	vector<internet> list = internetRepo.getData();
	cout << "\n--- NHAP THONG TIN GOI MANG MOI ---" << endl;
	internet newInternet;
	
	string newInternetId = internetRepo.autoGenId("G");
	newInternet.setId(newInternetId);
	
	newInternet.inputFromKeyboard(list);
	
	if(newInternet.getId() == ""){
		cout << "Quay lai menu!" << endl;
		return;
	}
	
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
		cout << left << setw(8)  << "Ma Goi" 
		     << "| " << setw(20) << "Ten Goi Mang" 
		     << "| " << setw(15) << "Toc Do (Mbps)" 
		     << "| " << setw(20) << "Tep Khach Hang" 
		     << "| " << "Gia Cuoc (VND)" << endl;
		    
		cout << string(85, '-') << endl;
		    
		for(auto x : list){
			x.showToConsole();
		}
	}
}

void internetController::updateFunction(){
	while(true){
		cout << "\n--- DANH SACH CAC GOI MANG ---" << endl;
		vector<internet> list = internetRepo.getData();
		if(list.empty()){
			cout << "Danh sach hien chua co goi mang" << endl;
		}
		else{
			cout << left << setw(8)  << "Ma Goi" 
			     << "| " << setw(20) << "Ten Goi Mang" 
			     << "| " << setw(15) << "Toc Do (Mbps)" 
			     << "| " << setw(20) << "Tep Khach Hang" 
			     << "| " << "Gia Cuoc (VND)" << endl;
			    
			cout << string(85, '-') << endl;
			for(auto x : list){
				x.showToConsole();
			}
			cout << "Chon ID goi mang ban muon chinh sua (nhap 0 de quay lai): ";
			string search;
			getline(cin, search);
			if(search == "0") break;
			for(int i = 0; i < search.length(); i++){
				if(isalpha(search[i])){
					search[i] = toupper(search[i]); 
				}
			}
			auto it = internetRepo.searchId(search);
			if(it != NULL){
				contractRepo.reloadData();
				bool isRented = false;
				vector<contract> contractList = contractRepo.getData();
				for(auto c : contractList){
					if(c.getPackageId() == search){
						isRented = true;
						break;
					}
				}
				int option = -1;
				do{
					if(isRented){
						cout << "(!) Goi mang nay da duoc khach hang thue." << endl;
						cout << "(!) He thong chi cho phep sua Ten va Tep khach hang de bao toan lich su doanh thu." << endl;
					}
					cout << "Nhap thanh phan ban muon thay doi:" << endl;
					cout << "1. Ten goi mang" << endl;
					if (isRented) 
						cout << "2. Toc do (Khoa)" << endl;
					else 
						cout << "2. Toc do" << endl;
					cout << "3. Tep khach hang" << endl;
					if(isRented) 
						cout << "4. Gia cuoc (Khoa)" << endl;
					else
						cout << "4. Gia cuoc" << endl;
					cout << "0. Quay lai chon ID" << endl;
					cout << "Nhap lua chon cua ban: ";
					string optionStr;
					getline(cin, optionStr);
					try{
						size_t pos;
						option = stoi(optionStr, &pos);
						if(pos != optionStr.size()){
							option = -1;
						}
					}catch(...){
						option = -1;
					}
					switch(option){
						case 1:{
							cout << "Nhap ten goi mang ban muon thay doi (nhap 0 de quay lai): ";
							string newPackageName;
							getline(cin, newPackageName);
							if(newPackageName == "0"){
								cout << "Quay lai lua chon chinh sua!" << endl;
								break;
							}
							it->setPackageName(newPackageName);
							internetRepo.saveToFile();
							cout << "\nThay doi thanh cong!" << endl;
							break;
						}
						case 2:{
							if(isRented){
								cout << "[LOI] Goi mang dang co hop dong hoat dong. Khong the sua toc do!" << endl;
								break;
							}
							cout << "Nhap toc do ban muon thay doi (nhap 0 de quay lai): ";
							int newSpeed;
							bool check = false;
							while(true){
								string newSpeedStr;
								getline(cin, newSpeedStr);
								if(newSpeedStr == "0"){
									check = true;
									break;
								}
								try{
									size_t pos;
									newSpeed = stoi(newSpeedStr, &pos);
									if(newSpeed < 0 || pos != newSpeedStr.size()){
										cout << "[Loi] Vui long nhap lai!" << endl;
										cout << "Nhap toc do ban muon thay doi (nhap 0 de quay lai): ";
									}
									else 
										break;
								}catch(...){
									cout << "[Loi] Vui long nhap lai!" << endl;
									cout << "Nhap toc do ban muon thay doi (nhap 0 de quay lai): ";
								}
							}
							if(check){
								cout << "Quay lai lua chon chinh sua!" << endl;
								break;
							}
							it->setSpeed(newSpeed);
							internetRepo.saveToFile();
							cout << "\nThay doi thanh cong!" << endl;
							break;
						}
						case 3:{
							int option = -1;
							
							while(true){
								cout << "Cac loai tep khach hang:" << endl;
								cout << "1.Ca nhan" << endl;
								cout << "2.Gia dinh" << endl;
								cout << "3.Doanh nghiep" << endl;
								cout << "0.Quay lai" << endl;
								cout << "Nhap tep khach hang ban muon thay doi: ";
								string optionStr;
								getline(cin, optionStr);
								if(optionStr == "0"){
									cout << "Quay lai lua chon chinh sua!" << endl;
									break;
								}
								try{
									size_t pos;
									option = stoi(optionStr, &pos);
									if(optionStr.size() != pos || option < 0){
										option = -1;
									}
								}catch(...){
									option = -1;
								}
								bool check = false;
								switch(option){
									case 1:{
										it->setCustomerType("Ca nhan");
										internetRepo.saveToFile();
										check = true;
										break;
									}
									case 2:{
										it->setCustomerType("Gia dinh");
										internetRepo.saveToFile();
										check = true;
										break;
									}
									case 3:{
										it->setCustomerType("Doanh nghiep");
										internetRepo.saveToFile();
										check = true;
										break;
									}
									default:{
										cout << "Vui long nhap lai!" << endl;
										check = false;
										break;
									}		
								}
								if(check){
									cout << "Thay doi thanh cong!" << endl;
									break;
								}
						 	}
							break;
						}
						case 4:{
							if (isRented) {
								cout << "[LOI] Goi mang dang co hop dong hoat dong. Neu muon doi gia, vui long tao goi mang moi!" << endl;
								break;
							}
							double newPrice;
							bool check = false;
							while(true){
								cout << "Nhap gia cuoc ban muon thay doi (nhap 0 de quay lai): ";
								string newPriceStr;
								getline(cin, newPriceStr);
								if(newPriceStr == "0"){
									cout << "Quay lai lua chon chinh sua!" << endl;
									check = true;
									break;
								}
								try{
									size_t pos;
									newPrice = stod(newPriceStr, &pos);
									if(pos != newPriceStr.size() || newPrice < 0){
										cout << "[Loi] Vui long nhap lai!" << endl;
										cout << "Nhap gia cuoc ban muon thay doi (nhap 0 de quay lai): ";
									}
									else
										break;
								}catch(...){
									cout << "[Loi] Vui long nhap lai!" << endl;
									cout << "Nhap gia cuoc ban muon thay doi (nhap 0 de quay lai): ";
								}
								if(check){
									cout << "Quay lai lua chon chinh sua!" << endl;
									break;
								}
							}
							it->setPrice(newPrice);
							internetRepo.saveToFile();
							cout << "\nThay doi thanh cong!" << endl;
							break;
						}
						default:
							
							break;	
					}
				}while(option != 0);		
			}
			else{
				cout << "Khong tim thay goi mang nao!" << endl;
			}
		}
	}
}

void internetController::deleteFunction(){
	contractRepo.reloadData();
	cout << "\n--- DANH SACH CAC GOI MANG ---" << endl;
	vector<internet> list = internetRepo.getData();
	if(list.empty()){
		cout << "Danh sach hien chua co goi mang" << endl;
	}
	else{
		cout << left << setw(8)  << "Ma Goi" 
			     << "| " << setw(20) << "Ten Goi Mang" 
			     << "| " << setw(15) << "Toc Do (Mbps)" 
			     << "| " << setw(20) << "Tep Khach Hang" 
			     << "| " << "Gia Cuoc (VND)" << endl;	    
		cout << string(85, '-') << endl;
		
		for(auto x : list){
			x.showToConsole();
		}
		
		cout << "Chon ID goi mang ban muon xoa (nhap 0 de quay lai): ";
		string search;
		getline(cin, search);
		if(search == "0") return;
		for(int i = 0; i < search.length(); i++){
			if(isalpha(search[i])){
				search[i] = toupper(search[i]); 
			}
		}
		auto it = internetRepo.searchId(search);
		if(it != NULL){
			vector<contract> list = contractRepo.getData();
			for(auto x : list){
				if(x.getPackageId() == search){
					cout << "Goi internet hien tai dang trong danh sach hop dong" << endl;
					return;
 				}
			}
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
	int choice = -1;
	do{
		cout << "\n============= QUAN LY CAC GOI MANG =============" << endl;
		cout << "1. C - Them thong tin goi mang moi" << endl;
        cout << "2. R - Xem danh sach cac goi mang hien co" << endl;
        cout << "3. U - Thay doi cac goi mang hien co" << endl;
        cout << "4. D - Xoa goi mang hien co" << endl;
        cout << "0. Thoat chuong trinh quan ly goi mang" << endl;
        cout << "Nhap lua chon cua ban: ";
        
        string choiceStr;
        getline(cin, choiceStr);
        try{
        	size_t pos;
        	choice = stoi(choiceStr, &pos);
        	if(pos != choiceStr.size())
        		choice = -1;
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








