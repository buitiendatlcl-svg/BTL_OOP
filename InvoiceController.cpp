#include "InvoiceController.h"

using namespace std;

	InvoiceController::InvoiceController()
	:invoiceRepo("data/invoice.txt"), contractRepo("data/contract.txt"), internetRepo("data/internet.txt"){}
	
	//Ham hien thi MenuHoaDon
	void InvoiceController::run(){
		int choice = -1;
		do{
			cout << "\n==========QUAN LY HOA DON CUOC==========" << endl;
			cout << "1. Lap hoa don cuoc moi" << endl;
			cout << "2. Hien thi danh sach toan bo hoa don" << endl;
			cout << "3. Cap nhat trang thai thanh toan " << endl;
			cout << "4. Xoa hoa don" << endl;
			cout << "0. Quay lai Menu chinh" << endl;
			cout << "--------------------------------------------------------" << endl;			
			cout << "Lua chon cua ban: ";
			
  		// Kiem tra nhap chu thay cho nhap so
        string richChoice;
        getline(cin, richChoice);
        
		try{
			size_t pos;
			choice = stoi(richChoice, &pos);
			if(pos != richChoice.size()){
				choice = -1;
			}
		}
		catch(...){
			choice = -1;
		}
			switch (choice){
				case 1: addInvoice(); break;
				case 2: displayAllInvoices(); break;
				case 3: updatePaymentStatus(); break;
				case 4: deleteInvoiceByContractId(); break;
				case 0: cout << "Dang quay lai Menu chinh ..." << endl; break;
				default: cout << "Lua chon khong hop le! Vui long quay lai." << endl; break;
			}
		}
		while (choice != 0);
	}

void InvoiceController::addInvoice(){
    contractRepo.reloadData();
    internetRepo.reloadData();	
	
	cout << "\n========== DANH SACH HOP DONG HIEN TAI ==========" << endl;
    auto list = contractRepo.getData(); 
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hop dong nao trong he thong!" << endl;
	}

    for (auto obj : list) {
        obj.showToConsole(); 
    }
    
    
	cout << "\n==========LAP HOA DON CUOC MOI==========" << endl;
	
	string contractId;
	contract* hd =nullptr;
	
	//KIEM TRA HOP DONG VA NHAP DUNG
	while(true){
		cout << "\nNhap ma hop dong can lap hoa don (Nhap '0' de quay tro lai): ";
		getline(cin, contractId);
		
		//Kiem tra nhap 0
		if(contractId == "0"){
			cout << "\n[THONG BAO]: Quay tro lai thanh thanh cong !" << endl;
			return;
		}
		
		//Chuan hoa
		for(char&c : contractId){
			c = toupper(c);
		}
	
		//Kiem tra id hop dong
		hd = contractRepo.searchId(contractId);
		if(hd == nullptr){
			cout << "\n[THONG BAO]: Ma hop dong " << contractId << " khong ton tai trong he thong. "
				<< "Vui long kiem tra lai contract.txt!" << endl;
			continue;
		}
		// tuc la ma HD ton tai trong he thong thi thoat vong lap
		break; 
	}	
	
	//Kiem tra xem goi mang nay con ton tai o trong danh sach Internet khong ? 
	internet* in = internetRepo.searchId(hd->getPackageId());
    if(in == nullptr){
        cout << "\n[LOI HE THONG]: Khong tim thay goi mang cua hop dong nay!" << endl;
        return;
    }
    
    cout << "\n[XAC NHAN]: Hop dong hop le! Tien hanh nhap thong tin cuoc ..." << endl;
    Invoice inv;
	inv.setContractId(contractId);
	inv.setPackageFee(in->getPrice());
	
	inv.inputFromKeyboard();
	
	if(inv.getBillingMonth() == 0 || inv.getBillingYear() == 0 || inv.getDiscount() == -1 || inv.getSurcharge() == -1 || inv.getPaymentStatus() == ""){  
		cout << "\n[THONG BAO]: Quay lai Menu thanh cong !" << endl;
		return;
	}
	
	//Buoc 3: Kiem tra khoa chinh 
	if(invoiceRepo.create(inv) == 1){
		cout << "\n[THANH CONG]: Da tao va luu hoa don '" << inv.getId() << "' vao phai invoices.txt!" << endl;
	}	
	else{
		cout << " \n[LOI TRUNG KHOA CHINH]: Hoa don '" << inv.getId() << "' da ton tai trong thang nay" << endl;
		cout << "\n--> Hop dong '" << contractId << "' da duoc lap hoa don cho Thang " 
             << inv.getBillingMonth() << "/" << inv.getBillingYear() << " roi!" << endl;
    }	
}
    
    
void InvoiceController::displayAllInvoices() {
    cout << "\n========== DANH SACH HOA DON CUOC ==========" << endl;
    

    auto list = invoiceRepo.getData(); 
    
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }

    cout << left 
         << setw(30) << "Ma Hoa Don" 
         << setw(20) << "Ma Hop Dong" 
         << setw(20) << "Thang/Nam" 
         << setw(15) << "Cuoc Goi" 
         << setw(15) << "Chiet Khau" 
         << setw(15) << "Phu Phi" 
         << setw(15) << "Tong so tien"
         << setw(15) << "Trang Thai" 
         << endl;
    cout << string(140, '-') << endl;

    for (auto obj : list) {
        obj.showToConsole(); 
    }
}

void InvoiceController::updatePaymentStatus(){
	cout << "\n========== DANH SACH HOA DON CUOC HIEN TAI ==========" << endl;
    
    auto list = invoiceRepo.getData(); 
    
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }

    cout << left 
         << setw(30) << "Ma Hoa Don" 
         << setw(20) << "Ma Hop Dong" 
         << setw(20) << "Thang/Nam" 
         << setw(15) << "Cuoc Goi" 
         << setw(15) << "Chiet Khau" 
         << setw(15) << "Phu Phi" 
         << setw(15) << "Tong so tien"
         << setw(15) << "Trang Thai" 
         << endl;
    cout << string(140, '-') << endl;

    for (auto obj : list) {
        obj.showToConsole(); 
    }
    
	cout << "\n==========CAP NHAT TRANG THAI THANH TOAN==========" << endl;
	string invId;
	Invoice* inv = nullptr;
	
	while(true){
		cout << "\nNhap ma hoa don can thanh toan (Nhap '0' de quay lai): ";
		getline(cin, invId);
		
		if(invId == "0"){
			cout << "\n[THONG BAO]: Quay lai Menu thanh cong !" << endl;
			return;
		}
	
		for(char& c : invId){
			c = toupper(c);
		}	
		
		inv = invoiceRepo.searchId(invId);
		if(inv == nullptr){
			cout << "\n[ERROR] Khong tim thay hoa don '" << invId << "'. Vui long nhap lai" << endl;
			continue;
		}
		break;
	}
	
	//B2: Kiem tra trang thai hien tai
	cout << "Trang thai hien tai: " << inv->getPaymentStatus() << endl;
	if(inv->getPaymentStatus() == "Paid"){
		cout << "\n[THONG BAO] Hoa don nay da duoc thanh toan tu truoc roi!" << endl;
		return;
	}
	
	//B3: Xac nhan va cap nhat 
	
	string confirm;
	while(true){
		cout << "\nChuyen trang thai thanh 'Paid' (Y/N)? ";
		getline(cin, confirm);
		if(confirm != "y" || confirm != "Y" || confirm != "n"|| confirm != "N"){
			cout << "\n[THONG BAO]: Vui long nhap lai !";
			continue;
		}
		break;
	}
	
	if(confirm == "y" || confirm == "Y"){
		inv->setPaymentStatus("Paid");
		invoiceRepo.saveToFile();
		cout << "\n[THANH CONG]: Da cap nhat trang thai hoa don '" << invId << "' sang 'Paid'!" << endl;
	}
	else{
		cout << "\nDa huy thao tac." << endl;
	}
}

void InvoiceController::deleteInvoiceByContractId(){
	cout << "\n---------- DANH SACH HOA DON CUOC HIEN TAI ----------" << endl;
    auto list = invoiceRepo.getData(); 
	 
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }

    cout << left 
         << setw(30) << "Ma Hoa Don" 
         << setw(20) << "Ma Hop Dong" 
         << setw(20) << "Thang/Nam" 
         << setw(15) << "Cuoc Goi" 
         << setw(15) << "Chiet Khau" 
         << setw(15) << "Phu Phi" 
         << setw(15) << "Tong so tien"
         << setw(15) << "Trang Thai" 
         << endl;
    cout << string(145, '-') << endl;

    for (auto& obj : list) {
        obj.showToConsole(); 
    }
    	
	cout << "\n========== XOA HOA DON THEO MA HOP DONG ==========" << endl;
	string conId;
    contractRepo.reloadData();
    contract* con = contractRepo.searchId(conId); 
    auto list1 = invoiceRepo.getData();
    
    while(true){
    	cout << "\nNhap ma hop dong de xoa toan bo hoa don chua hop dong do (Nhap '0' de quay lai): ";
    	getline(cin, conId);
    	
    	//Quay lai 
    	if(conId == "0"){
			cout << "\n[THONG BAO]: Quay lai Menu thanh cong !" << endl;
    		return;
		}
		//chuan hoa kh --> KH
		for(char& c : conId){
			c = toupper(c);
		}
 		
 		//Kiem tra trong danh sach hoa don co chua hop dong 'conId' khong
		int check = 0;
		for(auto& x : list1){
			if(x.getContractId() == conId){
				check = 1;
				break;
			}
		}
		
		if(check == 1){
			cout << "\n[XAC NHAN]: Hop dong hop le" << endl;
		 	break; //Xac nhan hop dong co hoa don, thoat vong lap while(true)
		 }
		else{
			cout << "\n[THONG BAO]: Hop dong '" << conId << "' chua co hoa don nao trong danh sach !" << endl;
			cout << "\nVui long nhap lai !" << endl;
			continue;
		}
	}
	
	
	//Hien thi cac hoa don chua ma HD conId
	cout << "\n---------- DANH SACH HOA DON CUA HOP DONG '" << conId << "' ----------" << endl;
	cout << left 
         << setw(30) << "Ma Hoa Don" 
         << setw(20) << "Ma Hop Dong" 
         << setw(20) << "Thang/Nam" 
         << setw(15) << "Cuoc Goi" 
         << setw(15) << "Chiet Khau" 
         << setw(15) << "Phu Phi" 
         << setw(15) << "Tong so tien"
         << setw(15) << "Trang Thai" 
         << endl;
    cout << string(145, '-') << endl;
	for(auto& x : list1){
		if(x.getContractId() == conId){
			x.showToConsole();
		}
	}
	
	string confirm;
	while(true){
		cout << "\nBan co chac chan xoa cac hoa don nay khong (Y/N)? ";
		getline(cin, confirm);
		if(confirm == "y" || confirm == "Y" || confirm == "n" || confirm == "N"){
			if(confirm == "y" || confirm == "Y"){
				for(auto& x : list1){
					if(x.getContractId() == conId){
						if(invoiceRepo.remove(x.getId())){
							continue;
						}
					}
				}
				cout << "\n[THANH CONG]: Da xoa cac hoa don co ma hop dong '" << conId <<"' thanh cong" << endl;
				cout << "\n---------- CAP NHAT DANH SACH HOA DON SAU KHI XOA HOP DONG '" << conId << "' ----------" << endl;
				invoiceRepo.reloadData();
				auto list3 = invoiceRepo.getData();
			 
			    cout << left 
		         << setw(30) << "Ma Hoa Don" 
		         << setw(20) << "Ma Hop Dong" 
		         << setw(20) << "Thang/Nam" 
		         << setw(15) << "Cuoc Goi" 
		         << setw(15) << "Chiet Khau" 
		         << setw(15) << "Phu Phi" 
		         << setw(15) << "Tong so tien"
		         << setw(15) << "Trang Thai" 
		         << endl;
		    	cout << string(145, '-') << endl;
		
			    for (auto obj : list3) {
			        obj.showToConsole(); 
			    }
			    break;
			}
			//Neu chon n hoac N
			else{
				cout << "\n[HUY THAO TAC]: Huy thao tac xoa hoa don thanh cong" << endl;
				break;
			}
		}
		
		else{
			cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
			continue;
		}
	}	
}





