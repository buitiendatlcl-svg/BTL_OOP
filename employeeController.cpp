#include "employeeController.h"
#include <iomanip>

employeeController::employeeController() 
    : employeeRepo("data/employee.txt"), districtRepo("data/data_khuvuc.txt"), warrantyRepo("data/warranty.txt")
	, installFormRepo("data/data_phieulapdat.txt"){
}

bool employeeController::isPhoneExist(string phone) {
    for (auto emp : employeeRepo.getData()) {
        if (emp.getPhoneNumber() == phone) {
            return true;
        }
    }
    return false;
}

void employeeController::createFunction() {
    cout << "\n--- THEM NHAN VIEN MOI ---" << endl;
    
    employee newEmployee;
    newEmployee.inputFromKeyboard(); 
    
	if (newEmployee.getSalary() < 0) { 
        cout << "=> Da huy thao tac them nhan vien, quay lai menu!" << endl;
        return;
    }

    string tempPhone;
    while (true) {
        cout << "Nhap sdt (10 so, bat dau bang 0)(nhap 0 de quay lai): ";
        getline(cin, tempPhone);
        
        if (tempPhone == "0") {
            cout << "=> Da huy thao tac them nhan vien, quay lai menu!" << endl;
            return;
        }
        
        if (!newEmployee.isValidPhoneNumber(tempPhone)) {
            cout << "=> Loi! Sai dinh dang (phai du 10 so va bat dau bang 0), vui long nhap lai!" << endl;
        } else if (isPhoneExist(tempPhone)) {
            cout << "=> Loi! So dien thoai nay da ton tai trong he thong, vui long nhap so khac!" << endl;
        } else {
            newEmployee.setPhoneNumber(tempPhone);
            break;
        }
    }

    districtRepo.reloadData();
    cout << "DANH SACH KHU VUC HIEN CO: \n";
    vector<district> distList = districtRepo.getData();
    if (distList.empty()){
        cout << "Chua co khu vuc nao! Vui long tao khu vuc truoc.\n";
        return; 
    }
    
    for (auto d : distList){
        cout << "Ma KV: " << d.getId() << " - Ten KV: " << d.getDistrict() << " - Ten Tram: " << d.getStation() << endl;
    }
    
    bool validDistrict = false;
    string chosenDistrict;
    while (!validDistrict){
        cout << "Nhap ma KV (nhap 0 de quay lai): ";
        getline(cin, chosenDistrict);
        
        if (chosenDistrict == "0") { 
        	cout << "=> Da huy thao tac them nhan vien, quay lai menu!" << endl;
        	return;
		}
        
        for (int i = 0; i < (int)chosenDistrict.size(); i++){
        	if (isalpha(chosenDistrict[i])){
        		chosenDistrict[i] = toupper(chosenDistrict[i]);
			}
		}
        
        if (districtRepo.searchId(chosenDistrict) != nullptr){
            newEmployee.setAreaId(chosenDistrict);
            validDistrict = true;
        } else {
            cout << "Ma KV khong ton tai! Vui long nhap lai!\n";
        }
    }
    string newId = employeeRepo.autoGenId("NV"); 
    newEmployee.setId(newId);

    if (employeeRepo.create(newEmployee) == 1) {
        cout << "=> Them thanh cong! Ma nhan vien: " << newId << endl;
    } else {
        cout << "=> Loi: Khong the them nhan vien." << endl;
    }
}


void employeeController::readFunction() {
    cout << "\n--- DANH SACH NHAN VIEN ---" << endl;
    districtRepo.reloadData();
    vector<employee> list = employeeRepo.getData();
    if (list.empty()) {
        cout << "Danh sach trong!" << endl;
    } else {
        cout << left << setw(8)  << "Ma NV" << "| "
             << left << setw(20) << "Ho va Ten" << "| "
             << left << setw(12) << "Ngay Sinh" << "| "
             << left << setw(12) << "SDT" << "| "
             << left << setw(20) << "Chuyen Mon" << "| "
             << left << setw(8)  << "Ma KV" << "| "
             << left << setw(15) << "Ten KV" << "| "
             << left << setw(15) << "Ten Tram" << "| "
             << left << setw(8)  << "Cap Bac" << "| "
             << "Luong (VND)" << endl;
        cout << string(144, '-') << endl;
        for (auto emp : list) {
            district* d = districtRepo.searchId(emp.getAreaId());
            if (d != nullptr) {
                emp.showToConsole(d->getDistrict(), d->getStation());
            } else {
                emp.showToConsole("Chua ro", "Chua ro");
            }
        }
    }
}

void employeeController::updateFunction() {
	if (employeeRepo.getData().empty()){
		cout <<"Danh sach nhan vien hien dang trong. Vui long them nhan vien truoc khi sua!";
		return;
	}
	
	readFunction();
	
    string searchId;
    employee* empPtr = nullptr;
    while (true) {
        cout << "\nNhap ID nhan vien can sua (nhap '0' de quay lai): ";
        getline(cin, searchId);
        for (int i = 0; i < (int)searchId.size(); i++){
        	if (isalpha(searchId[i])){
        		searchId[i] = toupper(searchId[i]);
			}
		}
        if (searchId == "0") return;

        empPtr = employeeRepo.searchId(searchId);
        if (empPtr != nullptr) {
            break;
        }
        cout << "=> Khong tim thay nhan vien mang ma: " << searchId << ". Vui long nhap lai!" << endl;
    }

    if (empPtr != nullptr) {
        int editChoice = -1;
        do {
            cout << "\n--- THONG TIN HIEN TAI cua nhan vien [" << empPtr->getId() << "] ---" << endl;

            district* curDist = districtRepo.searchId(empPtr->getAreaId());
            if (curDist != nullptr) {
                empPtr->showToConsole(curDist->getDistrict(), curDist->getStation());
            } else {
                empPtr->showToConsole("Chua ro", "Chua ro");
            }
            
            cout << "\nCHON THONG TIN CAN SUA:" << endl;
            cout << "1. Ten nhan vien" << endl;
            cout << "2. Ngay sinh" << endl;
            cout << "3. So dien thoai" << endl;
            cout << "4. Chuyen mon" << endl;
            cout << "5. Khu vuc phu trach" << endl;
            cout << "6. Cap bac (Tu dong tinh lai luong)" << endl;
            cout << "0. HOAN TAT VA LUU" << endl;
            cout << "Chon (0-6): ";
            
            string choiceStr;
			getline (cin, choiceStr);
			try{
			size_t pos;
			editChoice = stoi(choiceStr, &pos);
			if (pos != choiceStr.size()) editChoice = -1;
			} catch(...){
			editChoice = -1;
			}

            string newInfo;
            switch (editChoice) {
                case 1: {
                    while (true) {
                        cout << "Nhap ho ten moi (Enter de giu nguyen): ";
                        getline(cin, newInfo);
                        if (newInfo.empty()) break;
                        if (empPtr->isValidName(newInfo)) {
                            empPtr->setFullName(newInfo); 
                            cout << "=> Da cap nhat ho ten!\n";
                            break;
                        }
                        cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
                    }
                    break;
                }
                
                case 2: {
                    while (true) {
                        cout << "Nhap ngay sinh moi dd/mm/yyyy (Enter de giu nguyen): ";
                        getline(cin, newInfo);
                        if (newInfo.empty()) break;
                        if (empPtr->isValidDate(newInfo)) {
                            empPtr->setDateOfBirth(newInfo);
                            cout << "=> Da cap nhat ngay sinh!\n";
                            break;
                        }
                        cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
                    }
                    break;
                }
                
                case 3: {
                    while (true) {
                        cout << "Nhap SDT moi (Enter de giu nguyen): ";
                        getline(cin, newInfo);
                        if (newInfo.empty()) break;
                        if (!empPtr->isValidPhoneNumber(newInfo)) {
                            cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
                        } else if (newInfo != empPtr->getPhoneNumber() && isPhoneExist(newInfo)) {
                            cout << "=> Loi! So dien thoai nay da ton tai, vui long nhap so khac!" << endl;
                        } else {
                            empPtr->setPhoneNumber(newInfo);
                            cout << "=> Da cap nhat SDT!\n";
                            break;
                        }
                    }
                    break;
                }
                
                case 4: {
                    while (true) {
                        cout << "\nChon chuyen mon moi :\n";
                        cout << "  1. Ky thuat thiet bi\n";
                        cout << "  2. Quan ly truc cap\n";
                        cout << "  3. Quan tri mang\n";
                        cout << "Chon (1-3, Enter de huy): ";
                        
                        getline(cin, newInfo);

                        if (newInfo.empty()) {
                            break;
                        }
                        
                        if (newInfo == "1") {
                            empPtr->setSpecialization("Ky thuat thiet bi");
                            cout << "=> Da cap nhat chuyen mon!" << endl;
                            break;
                        } else if (newInfo == "2") {
                            empPtr->setSpecialization("Quan ly truc cap");
                            cout << "=> Da cap nhat chuyen mon!" << endl;
                            break;
                        } else if (newInfo == "3") {
                            empPtr->setSpecialization("Quan tri mang");
                            cout << "=> Da cap nhat chuyen mon!" << endl;
                            break;
                        } else {
                            cout << "=> Loi: Lua chon khong hop le! Vui long chon tu 1 den 3.\n";
                        }
                    }
                    break;
                }
                
                case 5: { 
                    cout << "\nDANH SACH KHU VUC HIEN CO: \n";
                    vector<district> distList = districtRepo.getData();
                    for (auto d : distList){
                        cout << "Ma KV: " << d.getId() << " - Ten KV: " << d.getDistrict() << " - Ten Tram: " << d.getStation() << endl;
                    }
                    
                    bool validDistrict = false;
                    while (!validDistrict) {
                        cout << "Nhap ma KV moi (an Enter de huy thao tac sua): ";
                        getline(cin, newInfo);
                        
						for (int i = 0; i < (int)newInfo.size(); i++){
                        	if (isalpha(newInfo[i])){
                        		newInfo[i] = toupper(newInfo[i]);
							}
						}
                        
                        if (newInfo.empty()) {
                            validDistrict = true; // huy thao tac sua khu vuc
                        } else if (districtRepo.searchId(newInfo) != nullptr) {
                            empPtr->setAreaId(newInfo);
                            validDistrict = true;
                            cout << "=> Da cap nhat Khu vuc!\n";
                        } else {
                            cout << "Ma KV khong ton tai! Vui long nhap lai!\n";
                        } 
                    }
                    break;
                }
                
                case 6: { 
                    while (true) {
                        cout << "\nChon cap bac moi (Luong co ban: 8,000,000 VND):\n";
                        cout << "  1. Bac 1 (He so 1.0 ->  8,000,000 VND)\n";
                        cout << "  2. Bac 2 (He so 1.4 -> 11,200,000 VND)\n";
                        cout << "  3. Bac 3 (He so 1.8 -> 14,400,000 VND)\n";
                        cout << "Chon (1-3, an Enter de giu nguyen): ";
                        getline(cin, newInfo);
                        
                        if (newInfo.empty()) break;

                        if (newInfo == "1") {
                            empPtr->setLevel(1);
                            cout << "=> Da cap nhat sang Bac 1! Muc luong moi: " << fixed << setprecision(0) << empPtr->getSalary() << " VND\n";
                            break;
                        } else if (newInfo == "2") {
                            empPtr->setLevel(2);
                            cout << "=> Da cap nhat sang Bac 2! Muc luong moi: " << fixed << setprecision(0) << empPtr->getSalary() << " VND\n";
                            break;
                        } else if (newInfo == "3") {
                            empPtr->setLevel(3);
                            cout << "=> Da cap nhat sang Bac 3! Muc luong moi: " << fixed << setprecision(0) << empPtr->getSalary() << " VND\n";
                            break;
                        } else {
                            cout << "=> Loi: Lua chon khong hop le! Vui long chon tu 1 den 3.\n";
                        }
                    }
                    break;
                }

                case 0:
                    employeeRepo.saveToFile();
                    cout << "=> CAP NHAT VA LUU THANH CONG!" << endl;
                    break;
                
                default:
                    cout << "Lua chon khong hop le, vui long chon lai!" << endl;
            }
        } while (editChoice != 0); 
        
    } else {
        cout << "=> Khong tim thay nhan vien mang ma: " << searchId << endl;
    }
}


void employeeController::deleteFunction() {
	if (employeeRepo.getData().empty()) {
		cout << "Danh sach nhan vien hien dang trong!" << endl;
		return;
	}

	readFunction();
	
    cout << "\n--- XOA NHAN VIEN ---" << endl;
    string delId;
    while (true) {
        cout << "\nNhap ID nhan vien can xoa (nhap '0' de quay lai): ";
        getline(cin, delId);
        
        for (int i = 0; i < (int)delId.size(); i++){
        	if (isalpha(delId[i])){
        		delId[i] = toupper(delId[i]);
			}
		}
		
        if (delId == "0") return;

        if (employeeRepo.searchId(delId) != nullptr) {
            break;
        }
        cout << "=> Loi: Khong tim thay nhan vien mang ma " << delId << "! Vui long nhap lai." << endl;
    }

    bool isWorking = false; 
    vector<warranty> wList = warrantyRepo.getData();
    for (auto w : wList) {
        if (w.getEmployeeId() == delId && w.getStatus() != "Da hoan thanh" && w.getStatus() != "Da huy") { 
            isWorking = true;
            cout << "=> KHONG THE XOA! Nhan vien dang phu trach Phieu bao hanh ma: " << w.getId() << endl;
        }
    }
    
    bool isInstalling = false;
    vector<installationForm> formList = installFormRepo.getData();
    for (auto i : formList){
    	if (i.getIdEmployee() == delId && i.getStatus() != 1 && i.getStatus() != -1 ){
    		isInstalling = true;
    		cout << "=> KHONG THE XOA! Nhan vien dang phu trach Phieu lap dat ma: " << i.getId() << endl;
		}
	}

    if (isWorking || isInstalling) { 
        cout << "=> Vui long chuyen giao hoac hoan tat cac Phieu tren truoc khi xoa nhan vien nay!" << endl;
        return; 
    }


    if (employeeRepo.remove(delId) == 1) {
        cout << "=> Da xoa nhan vien thanh cong!" << endl;
    } else {
        cout << "=> Xoa that bai do loi he thong!" << endl;
    }
}


void employeeController::run() {
	warrantyRepo.reloadData();
    districtRepo.reloadData();
    employeeRepo.reloadData();
    installFormRepo.reloadData();

    int choice = -1;
    do {
        cout << "\n=========== QUAN LY NHAN VIEN ===========" << endl;
        cout << "1. Them nhan vien" << endl;
        cout << "2. Xem danh sach" << endl;
        cout << "3. Sua thong tin nhan vien" << endl;
        cout << "4. Xoa nhan vien" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "=========================================" << endl;
        cout << "Chon chuc nang: ";
        
		string choiceStr;
		getline (cin, choiceStr);
		try{
			size_t pos;
			choice = stoi(choiceStr, &pos);
			if (pos != choiceStr.size()) choice = -1;
		} catch(...){
			choice = -1;
		}

        switch (choice) {
            case 1: createFunction(); break;
            case 2: readFunction(); break;
            case 3: updateFunction(); break;
            case 4: deleteFunction(); break;
            case 0: cout << "Dang thoat khoi quan ly nhan vien..." << endl; break;
            default: cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);
}
