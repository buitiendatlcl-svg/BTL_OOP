#include "InvoiceController.h"
#include <sstream>
using namespace std;

	InvoiceController::InvoiceController()
	: invoiceRepo("data/invoice.txt"), 
	  contractRepo("data/contract.txt"), 
	  internetRepo("data/internet.txt"),
	  installationRepo("data/data_phieulapdat.txt") {}
	  
	// 1. Phuong thuc lay hoa don thang gan nhat cua mot hop dong
	Invoice* InvoiceController::getLastInvoice(string contractId) {
		invoiceRepo.reloadData();
		string maxInvId = "";
		int maxCycle = -1;
		for (auto& inv : invoiceRepo.getData()) {
			if (inv.getContractId() == contractId) {
				int cycle = inv.getBillingYear() * 12 + inv.getBillingMonth();
				if (cycle > maxCycle) {
					maxCycle = cycle;
					maxInvId = inv.getId();
				}
			}
		}
		if (!maxInvId.empty()) {
			return invoiceRepo.searchId(maxInvId);
		}
		return nullptr;
}
// 2. Phuong thuc kiem tra chu ky cuoc nam trong khoang [A <= x <= B]
bool InvoiceController::isWithinContractPeriod(string contractId, int month, int year) {
	contractRepo.reloadData();
	installationRepo.reloadData();
	contract* hd = contractRepo.searchId(contractId);
	if (hd == nullptr) return false;
	// Tim phieu lap dat hoan thanh (state = 2) de lay moc A (ngay lap dat xong)
	string installDate = "";
	for (auto& pld : installationRepo.getData()) {
		if (pld.getIdContract() == contractId && pld.getStatus() == 2) {
			installDate = pld.getDate();
			break;
		}
	}
	if (installDate.empty()) return false;
	int dA = 0, mA = 0, yA = 0;
	stringstream ssA(installDate);
	char c1, c2;
	if (!(ssA >> dA >> c1 >> mA >> c2 >> yA)) {
		return false;
	}
	int valA = yA * 12 + mA; // Moc A (thang bat dau tinh cuoc)
	// Lay moc B (ngay het han hop dong)
	string expDate = hd->getExpiryDate();
	int valB = 0;
	if (expDate != "none" && !expDate.empty()) {
		int dB = 0, mB = 0, yB = 0;
		stringstream ssB(expDate);
		if (ssB >> dB >> c1 >> mB >> c2 >> yB) {
			valB = yB * 12 + mB;
		}
	}
	// Neu hop dong expiryDate la "none", tinh theo ky han (term)
	if (valB == 0) {
		int term = hd->getTerm();
		if (term > 0) {
			valB = valA + term;
		} else {
			valB = valA + 120; // 10 nam neu khong gioi han
		}
	}
	int valX = year * 12 + month; // Chu ky cuoc x can kiem tra
	return (valX >= valA && valX <= valB);
}
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
    } else {
        	cout << left << setw(15) << "Ma hop dong"
		 	 << "| " << setw(15) << "Ma khach hang"
		 	 << "| " << setw(10) << "Ma goi"
			 << "| " << setw(12) << "Ma khu vuc" 
			 << "| " << setw(12) << "Ngay ky" 
			 << "| " << setw(10) << "Ky han"
			 << "| " << setw(15) << "Ngay het han"
			 << "| " << setw(16) << "Trang thai"
			 << "| " << "Ghi chu" << endl;
		cout << string(140, '-') << endl;
        for (auto obj : list) {
            obj.showToConsole(); 
        }
    }
    
    
	cout << "\n==========LAP HOA DON CUOC MOI==========" << endl;
	
	string contractId;
	contract* hd = nullptr;
	
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
	
	// RANG BUOC 2 (RANG BUOC NGHIEM THU): Chi xuat hoa don neu da co phieu lap dat state = 2 (Hoan thanh)
	bool daNghiemThu = false;
	for (auto& pld : installationRepo.getData()) {
		if (pld.getIdContract() == contractId && pld.getStatus() == 1) {
			daNghiemThu = true;
			break;
		}
	}
	if (!daNghiemThu) {
		cout << "\n[TU CHOI XUAT HOA DON]: Hop dong '" << contractId 
		     << "' chua co Phieu lap dat o trang thai 'Hoan thanh'!" << endl;
		cout << "=> He thong chi xuat hoa don sau khi da nghiem thu lap dat thanh cong." << endl;
		return;
	}
	// RANG BUOC 1 (RANG BUOC CHAN LAP): 
	// Neu hoa don gan nhat co trang thai Unpaid hoac Overdue VA hop dong o trang thai Khong hoat dong (status = 2) -> Tu choi xuat hoa don
	Invoice* lastInv = getLastInvoice(contractId);
	if (lastInv != nullptr) {
		bool noCu = (lastInv->getPaymentStatus() == "Unpaid" || lastInv->getPaymentStatus() == "Overdue");
		bool hopDongKhoa = (hd->getStatus() == 2); // 2 la "Khong hoat dong"
		if (noCu && hopDongKhoa) {
			cout << "\n[TU CHOI XUAT HOA DON]: Hop dong '" << contractId << "' dang 'Khong hoat dong'" << endl;
			cout << "va hoa don ky gan nhat (" << lastInv->getBillingMonth() << "/" << lastInv->getBillingYear() 
			     << ") dang '" << lastInv->getPaymentStatus() << "' (chua thanh toan)!" << endl;
			cout << "=> Tu choi xuat hoa don moi. Vui long thanh toan no cu hoac mo khoa hop dong." << endl;
			return;
		}
	}
	// RANG BUOC 3 (TU DONG TINH PHU PHI):
	// Neu hoa don thang truoc Unpaid/Overdue nhung hop dong van Hoat dong (status = 1) -> Tu dong don no vao surcharge
	double noThangTruoc = 0.0;
	if (lastInv != nullptr && (lastInv->getPaymentStatus() == "Unpaid" || lastInv->getPaymentStatus() == "Overdue") && hd->getStatus() == 1) {
		noThangTruoc = lastInv->getTotalAmount();
		cout << "\n[CANH BAO NO CU]: Hoa don ky truoc (" << lastInv->getBillingMonth() << "/" << lastInv->getBillingYear() 
		     << ") chua thanh toan (So tien: " << fixed << setprecision(0) << noThangTruoc << " VND)." << endl;
		cout << "=> He thong se tu dong don so tien no cu nay vao phu phi (surcharge) cua hoa don ky nay." << endl;
	}
	// Kiem tra goi mang cua hop dong
	internet* in = internetRepo.searchId(hd->getPackageId());
    if(in == nullptr){
        cout << "\n[LOI HE THONG]: Khong tim thay goi mang cua hop dong nay!" << endl;
        return;
    }
    
    cout << "\n[XAC NHAN]: Hop dong du dieu kien xuat hoa don! Tien hanh nhap thong tin cuoc ..." << endl;
    Invoice inv;
	inv.setContractId(contractId);
	inv.setPackageFee(in->getPrice());
	
	inv.inputFromKeyboard();
	
	if(inv.getBillingMonth() == 0 || inv.getBillingYear() == 0 || inv.getDiscount() == -1 || inv.getSurcharge() == -1){  
		cout << "\n[THONG BAO]: Da huy thao tac lap hoa don!" << endl;
		return;
	}
	// KIEM TRA CHU KY CUOC: A <= x <= B
	if (!isWithinContractPeriod(contractId, inv.getBillingMonth(), inv.getBillingYear())) {
		cout << "\n[LOI CHU KY CUOC]: Chu ky cuoc Thang " << inv.getBillingMonth() << "/" << inv.getBillingYear() 
		     << " khong nam trong thoi gian hieu luc cua hop dong (tu ngay nghiem thu den ngay het han hop dong)!" << endl;
		return;
	}
	// Tu dong don no cu vao phu phi
	if (noThangTruoc > 0) {
		inv.setSurcharge(inv.getSurcharge() + noThangTruoc);
		inv.calculateTotalAmount();
		cout << "\n=> Phu phi sau khi don no cu: " << fixed << setprecision(0) << inv.getSurcharge() << " VND" << endl;
		cout << "=> Tong tien hoa don ky nay: " << fixed << setprecision(0) << inv.getTotalAmount() << " VND" << endl;
	}
	
	// Kiem tra trung hoa don ky nay
	if(invoiceRepo.create(inv) == 1){
		cout << "\n[THANH CONG]: Da tao va luu hoa don '" << inv.getId() << "' vao he thong!" << endl;
	}	
	else{
		cout << "\n[LOI TRUNG KHOA CHINH]: Hoa don '" << inv.getId() << "' da ton tai!" << endl;
		cout << "--> Hop dong '" << contractId << "' da duoc lap hoa don cho Thang " 
             << inv.getBillingMonth() << "/" << inv.getBillingYear() << " roi!" << endl;
    }	
}
    
    
void InvoiceController::displayAllInvoices() {
    cout << "\n============================================ DANH SACH HOA DON CUOC ============================================" << endl;
    invoiceRepo.reloadData();
    auto list = invoiceRepo.getData(); 
    
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }
	
    cout << left 
         << setw(21) << "Ma Hoa Don" 
         << "| " << setw(7)  << "Ma HD" 
         << "| " << setw(9)  << "Ky Cuoc" 
         << "| " << setw(11) << "Cuoc Goi" 
         << "| " << setw(11) << "Chiet Khau" 
         << "| " << setw(10) << "Phu Phi" 
         << "| " << setw(12) << "Tong Tien"
         << "| " << setw(10) << "Trang Thai" 
         << "| " << setw(12) << "Ngay Lap"
         << "| " << setw(12) << "Han Tra"
         << "| " << setw(12) << "Ngay TT"
         << endl;
    cout << string(150, '-') << endl;
    for (auto obj : list) {
        obj.showToConsole(); 
    }
}

void InvoiceController::updatePaymentStatus(){
	invoiceRepo.reloadData();
	auto list = invoiceRepo.getData(); 
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }
	displayAllInvoices();
	cout << "\n========== CAP NHAT TRANG THAI THANH TOAN ==========" << endl;
	string invId;
	Invoice* inv = nullptr;
	while(true){
		cout << "\nNhap ma hoa don can cap nhat (Nhap '0' de quay lai): ";
		getline(cin, invId);
		if(invId == "0") return;
		for(char& c : invId){
			c = toupper(static_cast<unsigned char>(c));
		}
		inv = invoiceRepo.searchId(invId);
		if(inv == nullptr){
			cout << "[LOI]: Khong tim thay hoa don '" << invId << "'! Vui long nhap lai!" << endl;
			continue;
		}
		break;
	}
	cout << "\nThong tin hoa don hien tai:" << endl;
	cout << "+ Trang thai: " << inv->getPaymentStatus() << endl;
	cout << "+ Tong tien:  " << fixed << setprecision(0) << inv->getTotalAmount() << " VND" << endl;
	cout << "+ Han nop:    " << inv->getDueDate() << endl;
	cout << "\n[CHON TRANG THAI THANH TOAN MOI]:" << endl;
	cout << "1. Paid (Da thanh toan)" << endl;
	cout << "2. Overdue (Qua han thanh toan)" << endl;
	cout << "3. Unpaid (Chua thanh toan)" << endl;
	cout << "0. Huy thao tac" << endl;
	cout << "Nhap lua chon: ";
	string opt;
	getline(cin, opt);
	if (opt == "1") {
		inv->setPaymentStatus("Paid");
		
		cout << "Nhap ngay thanh toan thuc te (dd/mm/yyyy) [Nhan Enter lay mac dinh hom nay]: ";
		string payDate;
		getline(cin, payDate);
		if (payDate.empty()) {
			payDate = inv->getDueDate();
		}
		inv->setPaymentDate(payDate);
		invoiceRepo.saveToFile();
		cout << "\n[THANH CONG]: Da cap nhat hoa don '" << invId << "' sang trang thai 'Paid'!" << endl;
	}
	else if (opt == "2") {
		inv->setPaymentStatus("Overdue");
		inv->setPaymentDate("none");
		invoiceRepo.saveToFile();
		cout << "\n[THANH CONG]: Da cap nhat hoa don '" << invId << "' sang trang thai 'Overdue' (Qua han)!" << endl;
	}
	else if (opt == "3") {
		inv->setPaymentStatus("Unpaid");
		inv->setPaymentDate("none");
		invoiceRepo.saveToFile();
		cout << "\n[THANH CONG]: Da cap nhat hoa don '" << invId << "' sang trang thai 'Unpaid'!" << endl;
	}
	else {
		cout << "\n[THONG BAO]: Da huy thao tac cap nhat!" << endl;
	}
}

void InvoiceController::deleteInvoiceByContractId(){
	invoiceRepo.reloadData();
    auto list = invoiceRepo.getData(); 
    if (list.empty()) {
        cout << "\n[THONG BAO]: Chua co hoa don nao trong he thong!" << endl;
        return;
    }
	displayAllInvoices();
	cout << "\n========== XOA HOA DON THEO MA HOP DONG ==========" << endl;
	string conId;
    
    while(true){
    	cout << "\nNhap ma hop dong de xoa hoa don (Nhap '0' de quay lai): ";
    	getline(cin, conId);
    	if(conId == "0") return;
		for(char& c : conId){
			c = toupper(static_cast<unsigned char>(c));
		}
 		
		bool tonTai = false;
		for(auto& x : list){
			if(x.getContractId() == conId){
				tonTai = true;
				break;
			}
		}
		
		if(tonTai){
		 	break;
		} else {
			cout << "\n[THONG BAO]: Hop dong '" << conId << "' khong co hoa don nao! Vui long nhap lai!" << endl;
		}
	}
	
	cout << "\nBan co chac chan muon xoa cac hoa don da thanh toan (Paid) cua hop dong '" << conId << "' khong (y/n)? ";
	string confirm;
	getline(cin, confirm);
	if(confirm == "y" || confirm == "Y"){
		int count = 0;
		for(auto& x : list){
			if(x.getContractId() == conId && x.getPaymentStatus() == "Paid"){
				invoiceRepo.remove(x.getId());
				count++;
			}
		}
		if (count > 0) {
			cout << "\n[THANH CONG]: Da xoa " << count << " hoa don da thanh toan cua hop dong '" << conId << "'!" << endl;
		} else {
			cout << "\n[THONG BAO]: Khong co hoa don nao o trang thai 'Paid' de xoa (chi duoc xoa hoa don da thanh toan)!" << endl;
		}
	} else {
		cout << "\n[HUY THAO TAC]: Da huy thao tac xoa hoa don!" << endl;
	}
}





