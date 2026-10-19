#include "InvoiceController.h"

using namespace std;

	InvoiceController::InvoiceController()
	:invoiceRepo("data/invoice.txt"), contractRepo("data/contract.txt"){}
	
	//Ham hien thi MenuHoaDon
	void InvoiceController::run(){
		int choice;
		do{
			cout << "\n==========QUAN LY HOA DON CUOC==========" << endl;
			cout << "1. Lap hoa don cuoc moi" << endl;
			cout << "2. Hien thi danh sach toan bo hoa don" << endl;
			cout << "3. Tim kiem hoa don theo ma hop dong" << endl;
			cout << "4. Cap nhat trang thai thanh toan " << endl;
			cout << "5. Xoa hoa don" << endl;
			cout << "0. Quay lai Menu chinh" << endl;
			cout << "--------------------------------------------------------" << endl;			
			cout << "Lua chon cua ban: ";
			
  		// Kiem tra nhap chu thay cho nhap so
        if (!(cin >> choice)) { //Kiem tra ham Cin co nhap datatype cua choice khong ?
            cout << "\n[LOI]: Lua chon khong hop le! Vui long chi nhap so (0-4)." << endl;
            cin.clear();            // 1. Xóa c? l?i c?a cin
            cin.ignore(1000, '\n'); // 2. V?t b? chu?i ký t? rác (nhu KH002) ra kh?i b? d?m
            choice = -1;            // 3. Ð?t giá tr? khác 0 d? không b? thoát nh?m
            continue;               // 4. Quay l?i d?u vòng l?p hi?n l?i menu
        }	
        cin.ignore(1000, '\n');		
			
			switch (choice){
				case 1: addInvoice(); break;
				case 2: displayAllInvoices(); break;
				case 3: searchInvoiceByContract(); break;
				case 4: updatePaymentStatus(); break;
				case 5: deleteInvoiceByContractId(); break;
				case 0: cout << "Dang quay lai Menu chinh ..." << endl; break;
				default: cout << "Lua chon khong hop le! Vui long quay lai." << endl; break;
			}
		}
		while (choice != 0);
	}

void InvoiceController::addInvoice(){
	cout << "\n==========LAP HOA DON CUOC MOI==========" << endl;
	string contractId;
	cout << "Nhap ma hop dong can lap hoa don: ";
	getline(cin, contractId);
	
	// BU?C 1: Kiem tra id hop dong
	
	contract* hd = contractRepo.searchId(contractId);
	if(hd == nullptr){
		cout << "\n[THONG BAO]: Ma hop dong " << contractId << " khong ton tai trong he thong. "
			<< "Vui long kiem tra lai contract.txt!" << endl;
		return;
	}
	//Buoc 2 : Tao doi tuong Invoice
	
	cout << "\n[XAC NHAN]: Hop dong hop le! Tien hanh nhap thong tin cuoc ..." << endl;
	Invoice inv;
	inv.setContractId(contractId);
	inv.inputFromKeyboard();
	
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
         << setw(20) << "Cuoc Goi" 
         << setw(20) << "Chiet Khau" 
         << setw(20) << "Phu Phi" 
         << setw(20) << "Trang Thai" 
         << endl;
    cout << string(140, '-') << endl;

    for (auto obj : list) {
        obj.showToConsole(); 
    }
}

void InvoiceController::searchInvoiceByContract(){
    cout << "\n==========TIM KIEM HOA DON THEO MA HOP DONG==========" << endl;
    string contractId;
    cout << "Nhap ma hop dong can tim: ";
    getline(cin, contractId);
    
    auto list = invoiceRepo.getData();
    bool found = false;
    
    cout << "\n" << left 
         << setw(30) << "Ma Hoa Don" 
         << setw(20) << "Ma Hop Dong" 
         << setw(20) << "Thang/Nam" 
         << setw(20) << "Cuoc Goi" 
         << setw(20) << "Chiet Khau" 
         << setw(20) << "Phu Phi" 
         << setw(20) << "Trang Thai" 
         << endl;
    cout << string(140, '-') << endl;

    for (auto inv : list) {
        if (inv.getContractId() == contractId) {
            inv.showToConsole(); // Neu lop Invoice dung hienThi() thi doi thanh inv.hienThi();
            found = true;
        }
    }
    
    if (!found) {
        cout << "\n[THONG BAO]: Khong tim thay hoa don nao cho ma hop dong '" << contractId << "'!" << endl;
    }
}


void InvoiceController::updatePaymentStatus(){
	cout << "\n==========CAP NHAT TRANG THAI THANH TOAN==========" << endl;
	string invId;
	cout << "Nhap ma hoa don can thanh toan: ";
	getline(cin, invId);
	
	//B1: TIm hoa don, tra ve pointer 
	Invoice* inv = invoiceRepo.searchId(invId);
	
	if(inv == nullptr){
		cout << "\n[ERROR] Khong tim thay hoa don " << invId << "!" << endl;
		return;
	}
	
	//B2: Kiem tra trang thai hien tai
	cout << "Trang thai hien tai: " << inv->getPaymentStatus() << endl;
	if(inv->getPaymentStatus() == "Paid"){
		cout << "\n[THONG BAO] Hoa don nay da duoc thanh toan tu truoc roi!" << endl;
		return;
	}
	
	//B3: Xac nhan va cap nhat 
	cout << "Chuyen trang thai thanh 'Paid' (Y/N)? ";
	char confirm;
	cin >> confirm;
	cin.ignore();
	
	if(confirm == 'y' || confirm == 'Y'){
		inv->setPaymentStatus("Paid");
		invoiceRepo.saveToFile();
		cout << "\n[THANH CONG]: Da cap nhat trang thai hoa don '" << invId << "' sang 'Paid'!" << endl;
	}
	else{
		cout << "Da huy thao tac." << endl;
	}
}

void InvoiceController::deleteInvoiceByContractId(){
	cout << "\n========== XOA HOA DON THEO MA HOP DONG ==========" << endl;
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
         << setw(20) << "Cuoc Goi" 
         << setw(20) << "Chiet Khau" 
         << setw(20) << "Phu Phi" 
         << setw(20) << "Trang Thai" 
         << endl;
    cout << string(140, '-') << endl;

    for (auto& obj : list) {
        obj.showToConsole(); 
    }
    
    cout << "\nNhap ma hop dong de xoa toan bo hoa don chua hop dong do: ";
	string conId;
    getline(cin, conId);
    contractRepo.reloadData();
    contract* con = contractRepo.searchId(conId); 
    
    //Kiem tra xem hop dong con han khong ? 
    if(con != nullptr){
    		cout << "[THONG BAO]: Hop dong '" << conId << "' hien tai van con han! Khong the thuc hien thao tac xoa hoa don" << endl;
    		return;
		}
	
	//Kiem tra xem hop dong nay da co hoa don chua 
	auto list1 = invoiceRepo.getData();
	int check = 0;
	for(auto& x : list1){
		if(x.getContractId() == conId){
			check = 1;
			break;
		}
	}
	if(check == 0){
		cout << "[THONG BAO]: Hop dong '" << conId << "' hien tai van chua co hoa don trong danh sach !" << endl;
		return;
	}
	//Hien thi cac hoa don chua ma HD conId
	cout << "\n---------- DANH SACH HOA DON CUA HOP DONG '" << conId << "' ----------" << endl;
	cout << left 
	         << setw(30) << "Ma Hoa Don" 
	         << setw(20) << "Ma Hop Dong" 
	         << setw(20) << "Thang/Nam" 
	         << setw(20) << "Cuoc Goi" 
	         << setw(20) << "Chiet Khau" 
	         << setw(20) << "Phu Phi" 
	         << setw(20) << "Trang Thai" 
	         << endl;
	    cout << string(140, '-') << endl;
	for(auto& x : list1){
		if(x.getContractId() == conId){
			x.showToConsole();
		}
	}
	
	cout << "\n[LUU Y]: Ban co chac chan muon xoa cac hoa don tren khong (y/n) ? ";
	string choice;
	getline(cin, choice);
	
	//Thao tac xoa hop dong
	if(choice == "y" || choice == "Y"){
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
	         << setw(20) << "Cuoc Goi" 
	         << setw(20) << "Chiet Khau" 
	         << setw(20) << "Phu Phi" 
	         << setw(20) << "Trang Thai" 
	         << endl;
	    cout << string(140, '-') << endl;

	    for (auto obj : list3) {
	        obj.showToConsole(); 
	    }
	}
	else{
		cout << "\n[HUY THAO TAC]: Huy thao tac xoa hoa don thanh cong" << endl;
	}
}





