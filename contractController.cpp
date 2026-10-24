#include "contractController.h"
#include <cctype>
#include <iomanip>
using namespace std;

contractController::contractController(){
	Repository<Customer> customerRepo{"data/customer.txt"};
	Repository<internet> internetRepo{"data/internet.txt"};
	Repository<district> districtRepo{"data/data_khuvuc.txt"};
	Repository<installationForm> installationRepo{"data/data_phieulapdat.txt"};
	Repository<warranty> warrantyRepo{"data/warranty.txt"};
	Repository<Invoice> invoiceRepo{"data/invoice.txt"};
}

void contractController::createFunction(){
	installationRepo.reloadData();
	warrantyRepo.reloadData();
	invoiceRepo.reloadData();
	vector<Customer> listCustomer = customerRepo.getData();
	if(listCustomer.empty()){
		cout << "Hien khong co khach hang nao!" << endl;
	}	
	else{
		cout << "\n--- DANH SACH KHACH HANG HIEN CO ---" << endl;
		cout << left 
         << setw(10) << "Ma KH" 
         << setw(25) << "Ho va Ten" 
         << setw(20) << "So CCCD" 
         << setw(20) << "So Dien Thoai" 
         << setw(20) << "Dia Chi" 
         << endl;
    	cout << string(95, '-') << endl;
    	
		for(auto x : listCustomer){
			x.showToConsole();
		}
	}
	
	contract newContract;
	
	bool check1 = false;
	while(true){
		cout << "Chon ID khach hang ban muon them vao hop dong(nhan '0' de quay lai): ";
		string idCustomer;
		getline(cin, idCustomer);
		if(idCustomer == "0"){
			check1 = true;
			break;
		}
		
		for(int i = 0; i < idCustomer.length(); i++){
			if(isalpha(idCustomer[i])){
				idCustomer[i] = toupper(idCustomer[i]); 
			}
		}
		
		auto itCustomer = customerRepo.searchId(idCustomer);
		if(itCustomer != NULL){
			newContract.setCustomerId(idCustomer);
			break;
		}
		else{
			cout << "Khong tim thay ID khach hang" << endl;
			continue;
		}
	}
	if(check1) return;
	
	cout << "\n--- DANH SACH CAC GOI MANG HIEN CO ---" << endl;
	vector<internet> listInternet = internetRepo.getData();
	if(listInternet.empty()){
		cout << "Hien khong co goi mang nao!" << endl;
	}	
	else{
		cout << left << setw(8)  << "Ma Goi" 
			     << "| " << setw(20) << "Ten Goi Mang" 
			     << "| " << setw(15) << "Toc Do (Mbps)" 
			     << "| " << setw(20) << "Tep Khach Hang" 
			     << "| " << "Gia Cuoc (VND)" << endl;
		cout << string(85, '-') << endl;
		
		for(auto x : listInternet){
			x.showToConsole();
		}
	}
	
	bool check2 = false;
	while(true){
		cout << "Chon ID goi mang ban muon them vao hop dong(nhan '0' de quay lai): ";
		string idInternet;
		getline(cin, idInternet);
		if(idInternet == "0"){
			check2 = true;
			break;
		}
		
		for(int i = 0; i < idInternet.length(); i++){
			if(isalpha(idInternet[i])){
				idInternet[i] = toupper(idInternet[i]); 
			}
		}
		
		auto itInternet = internetRepo.searchId(idInternet);
		if(itInternet != NULL){
			newContract.setPackageId(idInternet);
			break;
		}
		else{
			cout << "Khong tim thay ID goi mang" << endl;
			continue;
		}
	}
	if(check2) return;
	
	cout << "\n--- DANH SACH CAC KHU VUC HIEN CO ---" << endl;
	vector<district> listDistrict = districtRepo.getData();
	if(listDistrict.empty()){
		cout << "Hien khong co khu vuc nao!" << endl;
	}	
	else{
		cout << left << setw(10) << "Ma KV" 
         	 << setw(25) << "Ten Tinh/Thanh" 
         	 << setw(25) << "Tram Quan Ly" 
         	 << setw(15) << "Bang Thong" << endl;
    	cout << string(75, '-') << endl;
    	
		for(auto x : listDistrict){
			x.showToConsole();
		}
	}
	
	bool check3 = false;
	while(true){
		cout << "Chon ID khu vuc ban muon them vao hop dong(nhan '0' de quay lai): ";
		string idDistrict;
		getline(cin, idDistrict);
		if(idDistrict == "0"){
			check3 = true;
			break;
		}
		
		for(int i = 0; i < idDistrict.length(); i++){
			if(isalpha(idDistrict[i])){
				idDistrict[i] = toupper(idDistrict[i]); 
			}
		}
		
		auto itDistrict = districtRepo.searchId(idDistrict);
		if(itDistrict != NULL){
			newContract.setAreaId(idDistrict);
			break;
		}
		else{
			cout << "Khong tim thay ID khu vuc" << endl;
			continue;
		}
	}
	if(check3) return;
	
	string newContractId = contractRepo.autoGenId("HD");
	newContract.setId(newContractId);
	
	cout << "Nhap ngay ky hop dong(dd/mm/yyyy)(nhap '0' de quay lai): ";
	string date;
	getline(cin, date);
	if(date == "0") return;
	else
		newContract.setSignDate(date);
		
	int termValue;
	while(true){
		cout << "Nhap ky han hop dong (thang) (nhap '0' de quay lai): ";
		string termStr;
		getline(cin, termStr);
		if(termStr == "0") return;
		try{
			size_t pos;
			termValue = stoi(termStr, &pos);
			if(pos != termStr.size() || termValue <= 0){
				cout << "[Loi] Vui long nhap so nguyen duong!" << endl;
			} else {
				break;
			}
		}catch(...){
			cout << "[Loi] Vui long nhap lai!" << endl;
		}
	}
	newContract.setTerm(termValue);
	newContract.setStatus(2);
	newContract.setExpiryDate("none");
	
	if(contractRepo.create(newContract)){
		cout << "Them moi hop dong thanh cong!" << endl;
	}
	else{
		cout << "Them moi hop dong that bai!" << endl;
	}
}

void contractController::readFunction(){
	
	vector<contract> listContract = contractRepo.getData();
	if(listContract.empty()){
		cout << "Danh sach chua co hop dong nao" << endl;
	}
	else{
		cout << "\n--- DANH SACH HOP DONG HIEN CO ---" << endl;
		
		cout << left << setw(15) << "Ma hop dong"
		 	 << "| " << setw(15) << "Ma khach hang"
		 	 << "| " << setw(10) << "Ma goi"
			 << "| " << setw(12) << "Ma khu vuc" 
			 << "| " << setw(12) << "Ngay ky" 
			 << "| " << setw(10) << "Ky han"
			 << "| " << setw(15) << "Ngay het han"
			 << "| " << setw(16) << "Trang thai" << endl;
		cout << string(120, '-') << endl;
		
		for(auto x : listContract){
			x.showToConsole();
		}
	}
}

void contractController::updateFunction(){
	installationRepo.reloadData();
	warrantyRepo.reloadData();
	invoiceRepo.reloadData();
	readFunction();
	bool check = false;
	while(true){
		cout << "Chon ID hop dong ban muon chinh sua(nhap '0' de quay lai): ";
		string search;
		getline(cin, search);
		if(search == "0"){
			check = true;
			break;
		}
		for(int i = 0; i < search.length(); i++){
			if(isalpha(search[i])){
				search[i] = toupper(search[i]); 
			}
		}
		auto itContract = contractRepo.searchId(search);
		int option = -1;
		if(itContract != NULL){
			do{
				cout << "\nNhap thanh phan ban muon thay doi" << endl;
				cout << "1. Ngay ky hop dong" << endl;
				cout << "0. Quay lai" << endl;
				cout << "Nhap lua chon cua ban: ";
				string optionStr;
				getline(cin, optionStr);
				try{
					size_t pos;
					option = stoi(optionStr, &pos);
					if(pos != optionStr.size() || option < 0)
						option = -1;
				}catch(...){
					option = -1;
				}
				switch(option){
					case 1: {
						cout << "Nhap ngay ky hop dong thay doi(nhap '0' de quay lai): ";
						string newSignDate;
						getline(cin, newSignDate);
						if(newSignDate == "0"){
							option = -1;
							break;
						}
						itContract->setSignDate(newSignDate);
						contractRepo.saveToFile();
						break;
					}
					default:{
						break;
					}
				}
			}while(option != 0);
		}
		else{
			cout << "Khong tim thay hop dong nao" << endl;
			continue;
		}
	}
	if(check) return;	
}

void contractController::deleteFunction(){
	readFunction();
	bool check = false;
	while(true){
		cout << "Lua chon ID hop dong can xoa(nhap '0' de quay lai): ";
		string search;
		getline(cin, search);
		if(search == "0"){
			check = true;
			break;
		}
		for(int i = 0; i < search.length(); i++){
			if(isalpha(search[i])){
				search[i] = toupper(search[i]); 
			}
		}
		auto itContract = contractRepo.searchId(search);
		bool ok = false;
		if(itContract != NULL){
			installationRepo.reloadData();
			warrantyRepo.reloadData();
			invoiceRepo.reloadData();
			vector<installationForm> listInstallation = installationRepo.getData();
			for(auto x : listInstallation){
				if(x.getIdContract() == search){
					cout << "Hop dong dang co trong danh sach phieu lap dat" << endl;
					ok = true;
					break;
				}
			}
			
			
			vector<warranty> listWarranty = warrantyRepo.getData();
			for(auto x : listWarranty){
				if(x.getContractId() == search){
					cout << "Hop dong dang co trong danh sach phieu bao hanh" << endl;
					ok = true;
					break;
				}
			}
			
			
			vector<Invoice> listInvoice = invoiceRepo.getData();
			for(auto x : listInvoice){
				if(x.getContractId() == search){
					cout << "Hop dong dang co trong danh sach hoa don" << endl;
					ok = true;
					break;
				}
			}
			if(!ok){
				if(contractRepo.remove(search)){
					cout << "Xoa hop dong thanh cong!" << endl;
					break;
				}
			}
			else{
				continue;
			}
		}
		else{
			cout << "Khong tim thay hop dong nao" << endl;
			continue;
		}
	}
	if(check) return;
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

