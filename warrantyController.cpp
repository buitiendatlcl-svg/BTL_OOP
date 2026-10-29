//Tran Hoang Hai - MSV: B24DCVT123
#include "warrantyController.h"
#include <iomanip>

warrantyController::warrantyController()
	: warrantyRepo("data/warranty.txt"), contractRepo("data/contract.txt"), employeeRepo("data/employee.txt")
	, installFormRepo("data/data_phieulapdat.txt"), districtRepo("data/data_khuvuc.txt")
{
}

// tim pld tuong ung voi hop dong 
installationForm* warrantyController::getInstallFormByContractId(string contractId) {
	vector<installationForm> formList = installFormRepo.getData();
	for (int i = 0; i < (int)formList.size(); i++) {

		if (formList[i].getIdContract() == contractId) {
			return installFormRepo.searchId(formList[i].getId());
		}
	}
	return nullptr;
}

void warrantyController::createFunction() {
    cout << "\n--- THEM PHIEU BAO HANH MOI ---" << endl;
    
    vector<contract> contractList = contractRepo.getData();
    if (contractList.empty()) {
        cout << "Hien chua co hop dong nao! Vui long tao hop dong truoc!" << endl;
        return;
    }

    vector<employee> empList = employeeRepo.getData();
    if (empList.empty()) {
        cout << "Hien chua co nhan vien nao! Vui long tao nhan vien truoc!" << endl;
        return; 
    }

    if (installFormRepo.getData().empty()) {
        cout << "Hien chua co phieu lap dat nao trong he thong! Khong the tao phieu bao hanh!" << endl;
        return;
    }

    warranty newWarranty; 

    cout << "DANH SACH HOP DONG HIEN CO: \n";
    cout << left << setw(15) << "Ma hop dong"
		 	 << "| " << setw(15) << "Ma khach hang"
		 	 << "| " << setw(10) << "Ma goi"
			 << "| " << setw(12) << "Ma khu vuc" 
			 << "| " << setw(12) << "Ngay ky" 
			 << "| " << setw(10) << "Ky han"
			 << "| " << setw(15) << "Ngay het han"
			 << "| " << setw(16) << "Trang thai"
			 << "| " << "Ghi chu" << endl;
		cout << string(135, '-') << endl;
    for (auto c : contractList) {
        c.showToConsole();
    }

    string chosenCustomer;
    vector<contract> customerContracts;
    while (true) {
        cout << "\nNhap ID khach hang can bao hanh (nhap '0' de quay lai): ";
        getline(cin, chosenCustomer);

        if (chosenCustomer == "0") {
            cout << "=> Da huy thao tac them phieu bao hanh, quay lai menu!" << endl;
            return;
        }

        for (int i = 0; i < (int)chosenCustomer.size(); i++) {
            if (isalpha(chosenCustomer[i])) {
                chosenCustomer[i] = toupper(chosenCustomer[i]);
            }
        }

        customerContracts.clear();
        for (auto c : contractList) {
            if (c.getCustomerId() == chosenCustomer) {
                customerContracts.push_back(c);
            }
        }

        if (!customerContracts.empty()) {
            break;
        }
        cout << "=> Khach hang [" << chosenCustomer << "] khong ton tai hoac chua co hop dong nao! Vui long nhap lai!" << endl;
    }

    //hien thi danh sach hd, phieu ld va trang thai pld
    cout << "\nDANH SACH HOP DONG CUA KHACH HANG [" << chosenCustomer << "]:\n";
    for (auto c : customerContracts) {
        installationForm* insPtr = getInstallFormByContractId(c.getId());
        string contractStatusStr = (c.getStatus() == 1) ? "Dang hoat dong" : "Khong hoat dong";
        
        cout << "  + Ma HD: " << left << setw(8) << c.getId()
             << " | Trang thai HD: " << left << setw(16) << contractStatusStr;
        if (insPtr != nullptr) {
            cout << " | Phieu lap dat: " << insPtr->getId() 
                 << " (Ngay lap dat: " << insPtr->getDate() << ")" << endl;
        } else {
            cout << " | [Chua co Phieu lap dat]" << endl;
        }
    }
	
	bool validContract = false;
    string chosenContract;
    string installDate = "";
    string contractAreaId = ""; // luu ma kv cua hd duoc chon
    
	while (!validContract) {
        cout << "\nNhap ID hop dong can bao hanh (nhap '0' de quay lai): ";
        getline(cin, chosenContract);
        
        if (chosenContract == "0") {
        	cout << "=> Da huy thao tac them phieu bao hanh, quay lai menu!" << endl;
			return;
		}
        
        for (int i = 0; i < (int)chosenContract.size(); i++) {
            if (isalpha(chosenContract[i])) {
                chosenContract[i] = toupper(chosenContract[i]);
            }
        }
        
        //kiem tra hop dong co thuoc ve khach hang dang chon khong
        contract* selectedContractPtr = nullptr;
        for (int i = 0; i < (int)customerContracts.size(); i++) {
            if (customerContracts[i].getId() == chosenContract) {
                selectedContractPtr = &customerContracts[i];
                break;
            }
        }

        if (selectedContractPtr == nullptr) {
            cout << "=> Ma hop dong khong thuoc ve khach hang [" << chosenCustomer << "]. Vui long nhap lai!" << endl;
            continue;
        }

        //kiem tra trang thai hd
        if (selectedContractPtr->getStatus() != 1) {
            cout << "=> KHONG THE THEM! Hop dong [" << chosenContract << "] hien KHONG HOAT DONG!" << endl;
            cout << "=> Chi duoc tao phieu bao hanh cho hop dong dang hoat dong. Vui long chon hop dong khac hoac nhap '0' de quay lai." << endl;
            continue;
        }

        //tim pld cua hd de lay ngay lap dat
        installationForm* insPtr = getInstallFormByContractId(chosenContract);
        if (insPtr == nullptr) {
            cout << "=> KHONG THE THEM! Hop dong [" << chosenContract << "] chua co Phieu lap dat!" << endl;
            cout << "=> Vui long chon hop dong khac hoac nhap '0' de quay lai." << endl;
            continue;
        }

        contractAreaId = selectedContractPtr->getAreaId(); 
        installDate = insPtr->getDate(); 
        newWarranty.setContractId(chosenContract);
        validContract = true;

        cout << "=> Da chon Hop dong [" << chosenContract << "] (Khu vuc: " << contractAreaId 
             << ") - Ngay lap dat: " << installDate << endl;
    }
    
    //tim nhan vien thuoc khu vuc hd
    vector<employee> areaEmployees;
    for (auto emp : empList) {
        if (emp.getAreaId() == contractAreaId) {
            areaEmployees.push_back(emp);
        }
    }

    if (areaEmployees.empty()) {
        cout << "=> KHONG THE THEM! Khu vuc [" << contractAreaId << "] cua hop dong nay hien chua co nhan vien ky thuat nao phu trach!" << endl;
        cout << "=> Vui long bo sung nhan vien cho khu vuc [" << contractAreaId << "] truoc!" << endl;
        return;
    }

    cout << "\nDANH SACH NHAN VIEN PHU TRACH KHU VUC [" << contractAreaId << "]:\n";
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
    for (auto emp : areaEmployees) {
        district* d = districtRepo.searchId(emp.getAreaId());
        if (d != nullptr) {
            emp.showToConsole(d->getDistrict(), d->getStation());
        } else {
            emp.showToConsole("Chua ro", "Chua ro");
        }
    }    
        
    bool validEmployee = false;
	string chosenEmployee;
    
    while (!validEmployee) {
        cout << "\nNhap ID nhan vien phu trach thuoc khu vuc [" << contractAreaId << "] (nhap '0' de quay lai): "; 
        getline(cin, chosenEmployee);
        
        if (chosenEmployee == "0") {
        	cout << "=> Da huy thao tac them phieu bao hanh, quay lai menu!" << endl;
			return;
		}

        for (int i = 0; i < (int)chosenEmployee.size(); i++) {
            if (isalpha(chosenEmployee[i])) {
                chosenEmployee[i] = toupper(chosenEmployee[i]);
            }
        }
        
        employee* empPtr = employeeRepo.searchId(chosenEmployee);
        if (empPtr == nullptr) {
            cout << "=> Ma nhan vien khong ton tai. Vui long nhap lai!" << endl;
        } else if (empPtr->getAreaId() != contractAreaId) {
            cout << "=> Loi! Nhan vien [" << chosenEmployee << "] thuoc khu vuc [" << empPtr->getAreaId() 
                 << "], khong phu trach khu vuc [" << contractAreaId << "] cua hop dong nay! Vui long chon lai." << endl;
        } else {
            newWarranty.setEmployeeId(chosenEmployee);
            validEmployee = true;
        }
    }

    //ngay tiep nhan
    string tempDate;
    while (true) {
        cout << "Nhap ngay tiep nhan (dd/mm/yyyy, sau ngay lap dat " << installDate << " toi da 2 nam) (nhap 0 de quay lai): ";
        getline(cin, tempDate);

        if (tempDate == "0") {
            cout << "=> Da huy thao tac them phieu bao hanh, quay lai menu!" << endl;
            return;
        }

        if (!newWarranty.isValidDate(tempDate)) {
            cout << "=> Loi! Sai dinh dang ngay thang, vui long nhap lai!" << endl;
        } else if (!newWarranty.isWithinTwoYears(installDate, tempDate)) {
            cout << "=> Loi! Ngay tiep nhan phai tu ngay lap dat (" << installDate << ") va trong han 2 nam bao hanh!" << endl;
        } else {
            newWarranty.setReceivedDate(tempDate);
            break;
        }
    }
    
    newWarranty.inputFromKeyboard();
    
    if (newWarranty.getStatus().empty()){
    	cout << "=> Da huy thao tac them phieu bao hanh, quay lai menu!" << endl;
		return;
	}
    
    string newId = warrantyRepo.autoGenId("BH");
    newWarranty.setId(newId);

    if (warrantyRepo.create(newWarranty) == 1) {
        cout << "=> Tao phieu bao hanh thanh cong! Ma phieu: " << newId << " (Trang thai: " << newWarranty.getStatus() << ")" << endl;
    } else {
        cout << "=> Loi: Khong the tao phieu bao hanh." << endl;
    }    
}


void warrantyController::readFunction() {
    cout << "\n--- DANH SACH PHIEU BAO HANH ---" << endl;
    vector<warranty> warrantyList = warrantyRepo.getData();
    if (warrantyList.empty()) {
        cout << "Danh sach phieu bao hanh hien dang trong!" << endl;
    } else {
        cout << left << setw(8)  << "Ma BH" << "| "
             << left << setw(10) << "Ma HD" << "| "
             << left << setw(10) << "Ma NV" << "| "
             << left << setw(12) << "Ngay Nhan" << "| "
             << left << setw(28) << "Noi Dung Su Co" << "| "
             << "Trang Thai" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        for (auto w : warrantyList) {
            w.showToConsole();    
        }
    }    
}

	
void warrantyController::updateFunction() {
    cout << "\n--- SUA THONG TIN PHIEU BAO HANH ---" << endl;
    if (warrantyRepo.getData().empty()) {
        cout << "Danh sach trong, khong co du lieu de sua!" << endl;
        return;
    }

    readFunction();

    string searchId;
    warranty* warrantyPtr = nullptr;
    while (true) {
        cout << "\nNhap ID phieu bao hanh can sua (nhap '0' de quay lai): ";
        getline(cin, searchId);
        if (searchId == "0") return;

        for (int i = 0; i < (int)searchId.size(); i++) {
            if (isalpha(searchId[i])) searchId[i] = toupper(searchId[i]);
        }

        warrantyPtr = warrantyRepo.searchId(searchId);
        if (warrantyPtr != nullptr) {
            break;
        }
        cout << "=> Khong tim thay phieu bao hanh mang ma: " << searchId << ". Vui long nhap lai!" << endl;
    }
    
    int editChoice = -1;
    do {
        cout << "\n--- THONG TIN HIEN TAI CUA PHIEU BAO HANH [" << warrantyPtr->getId() << "] ---" << endl;
        warrantyPtr->showToConsole();
        
        cout << "\nCHON THONG TIN CAN SUA:" << endl;
        cout << "1. Nhan vien phu trach" << endl;
        cout << "2. Noi dung su co" << endl;
        cout << "3. Trang thai xu ly" << endl;
        cout << "0. HOAN TAT VA LUU" << endl;
        cout << "Chon (0-3): ";
        
        string choiceStr;
        getline(cin, choiceStr);
        try {
            size_t pos;
            editChoice = stoi(choiceStr, &pos);
            if (pos != choiceStr.size()) editChoice = -1;
        } catch (...) {
            editChoice = -1;
        }
        
        string newInfo;
        switch (editChoice) {
            case 1: {
                // Tim Hop dong cua Phieu bao hanh nay de lay Ma Khu Vuc
                contract* cPtr = contractRepo.searchId(warrantyPtr->getContractId());
                if (cPtr == nullptr) {
                    cout << "=> Loi: Khong tim thay thong tin hop dong goc cua phieu bao hanh nay!" << endl;
                    break;
                }

                // LUU Y: Doi getAreaId() neu trong contract.h dat la getDistrictId() hoac getIdDistrict()
                string contractAreaId = cPtr->getAreaId();

                // Loc danh sach nhan vien cung khu vuc voi hop dong
                vector<employee> employeeList = employeeRepo.getData();
                vector<employee> areaEmployees;
                for (auto emp : employeeList) {
                    if (emp.getAreaId() == contractAreaId) {
                        areaEmployees.push_back(emp);
                    }
                }

                if (areaEmployees.empty()) {
                    cout << "=> Khu vuc [" << contractAreaId << "] hien khong co nhan vien nao de thay the!" << endl;
                    break;
                }

                cout << "\nDANH SACH NHAN VIEN CUNG KHU VUC [" << contractAreaId << "] VOI HOP DONG:\n";
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
    		    for (auto emp : areaEmployees) {
                    district* d = districtRepo.searchId(emp.getAreaId());
                    if (d != nullptr) {
                        emp.showToConsole(d->getDistrict(), d->getStation());
                    } else {
                        emp.showToConsole("Chua ro", "Chua ro");
                    }
   			    }    
                
                while (true) {
                    cout << "Nhap ID nhan vien phu trach moi thuoc khu vuc [" << contractAreaId << "] (Enter de huy): ";
                    getline(cin, newInfo);
                    if (newInfo.empty()) break;

                    for (int i = 0; i < (int)newInfo.size(); i++) {
                        if (isalpha(newInfo[i])) newInfo[i] = toupper(newInfo[i]);
                    }

                    employee* empPtr = employeeRepo.searchId(newInfo);
                    if (empPtr == nullptr) {
                        cout << "=> Ma nhan vien khong ton tai. Vui long nhap lai!" << endl;
                    } else if (empPtr->getAreaId() != contractAreaId) {
                        cout << "=> Loi! Nhan vien [" << newInfo << "] thuoc khu vuc [" << empPtr->getAreaId() 
                             << "], khong cung khu vuc [" << contractAreaId << "] voi hop dong! Vui long chon lai." << endl;
                    } else {
                        warrantyPtr->setEmployeeId(newInfo);
                        cout << "=> Da cap nhat nhan vien phu trach!" << endl;
                        break;
                    }
                }
                break;
            }
            
            case 2: {
            	bool validIssue = false;
                while (!validIssue) {
                    cout << "\nChon noi dung su co moi:\n";
                    cout << "  1. Mat ket noi Internet\n";
                    cout << "  2. Mang cham, chap chon\n";
                    cout << "  3. Loi thiet bi Modem/Wifi\n";
                    cout << "  4. Van de khac\n";
                    cout << "Chon (1-4, Enter de huy): ";
                    
                    getline(cin, newInfo);
                    if (newInfo.empty()) break;

                    if (newInfo == "1") {
                        warrantyPtr->setIssueDescribe("Mat ket noi Internet");
                        cout << "=> Da cap nhat noi dung su co!" << endl;
                        validIssue = true;
                    }
					else if (newInfo == "2") {
                        warrantyPtr->setIssueDescribe("Mang cham, chap chon");
                        cout << "=> Da cap nhat noi dung su co!" << endl;
                        validIssue = true;
                    } 
					else if (newInfo == "3") {
                        warrantyPtr->setIssueDescribe("Loi thiet bi Modem/Wifi");
                        cout << "=> Da cap nhat noi dung su co!" << endl;
                        validIssue = true;
                    } 
					else if (newInfo == "4") {
                        warrantyPtr->setIssueDescribe("Van de khac");
                        cout << "=> Da cap nhat noi dung su co!" << endl;
                        validIssue = true;
                    } 
					else {
                        cout << "=> Loi: Lua chon khong hop le! Vui long chon tu 1 den 4.\n";
                    }
                }
                break;
            }
            
            case 3: {
            	bool validStatus = false;
                while (!validStatus) {
                    cout << "\nChon trang thai xu ly moi:\n";
                    cout << "  1. Cho xac nhan\n";
                    cout << "  2. Dang sua chua\n";
                    cout << "  3. Da hoan thanh\n";
                    cout << "  4. Da huy\n";
                    cout << "Chon (1-4, Enter de huy): ";
                    
                    getline(cin, newInfo);
                    if (newInfo.empty()) {
                    	validStatus = true;
                    	break;
					}

                    if (newInfo == "1") {
                        warrantyPtr->setStatus("Cho xac nhan");
                        cout << "=> Da cap nhat trang thai!\n";
                        validStatus = true;
                    } 
					else if (newInfo == "2") {
                        warrantyPtr->setStatus("Dang sua chua");
                        cout << "=> Da cap nhat trang thai!\n";
                        validStatus = true;
                    } 
					else if (newInfo == "3") {
                        warrantyPtr->setStatus("Da hoan thanh");
                        cout << "=> Da cap nhat trang thai!\n";
                        validStatus = true;
                    } 
					else if (newInfo == "4") {
                        warrantyPtr->setStatus("Da huy");
                        cout << "=> Da cap nhat trang thai!\n";
                        validStatus = true;
                    } 
					else {
                        cout << "=> Lua chon khong hop le! Vui long chon tu 1 den 4.\n";
                    }
                }
                break;
            }
            
            case 0: {
                warrantyRepo.saveToFile();
                cout << "=> DA LUU THAY DOI THANH CONG!" << endl;
                break;
            }
            
            default: {
                cout << "=> Lua chon khong hop le! Vui long chon tu 0 den 4." << endl;
                break;
            }
        }
    } while (editChoice != 0); 
}

void warrantyController::deleteFunction() {
    cout << "\n--- XOA PHIEU BAO HANH ---" << endl;
    if (warrantyRepo.getData().empty()) {
        cout << "Danh sach trong, khong co du lieu de xoa!" << endl;
        return;
    }

    readFunction();

    string delId;
    warranty* wPtr = nullptr;
    while (true) {
        cout << "\nNhap Ma phieu BH can xoa (nhap '0' de quay lai): ";
        getline(cin, delId);
        if (delId == "0") return;

        for (int i = 0; i < (int)delId.size(); i++) {
            if (isalpha(delId[i])) delId[i] = toupper(delId[i]);
        }

        wPtr = warrantyRepo.searchId(delId);
        if (wPtr != nullptr) {
            break;
        }
        cout << "=> Loi: Khong tim thay ma phieu " << delId << "! Vui long nhap lai." << endl;
    }

    if (wPtr->getStatus() != "Da hoan thanh" && wPtr->getStatus() != "Da huy") {
        cout << "=> KHONG THE XOA! Phieu bao hanh [" << delId << "] dang o trang thai: " << wPtr->getStatus() << endl;
        cout << "=> Chi duoc phep xoa phieu khi trang thai la 'Da hoan thanh' hoac 'Da huy'!" << endl;
        return;
    }

    if (warrantyRepo.remove(delId) == 1) {
        cout << "=> Da xoa phieu bao hanh thanh cong!" << endl;
    } else {
        cout << "=> Xoa that bai do loi he thong!" << endl;
    }
}

void warrantyController::run() {
	warrantyRepo.reloadData();
    contractRepo.reloadData();
    employeeRepo.reloadData();
    installFormRepo.reloadData();
    districtRepo.reloadData();
    
    int choice = -1;
    do {
        cout << "\n====== QUAN LY PHIEU BAO HANH - SUA CHUA ======" << endl;
        cout << "1. Tao phieu bao hanh moi" << endl;
        cout << "2. Xem danh sach phieu bao hanh" << endl;
        cout << "3. Cap nhat tien do / thong tin phieu" << endl;
        cout << "4. Xoa phieu bao hanh" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "===============================================" << endl;
        cout << "Chon chuc nang: ";
        
        string choiceStr;
        getline(cin, choiceStr);
        try {
            size_t pos;
            choice = stoi(choiceStr, &pos);
            if (pos != choiceStr.size()) choice = -1;
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
            case 1: createFunction(); break;
            case 2: readFunction(); break;
            case 3: updateFunction(); break;
            case 4: deleteFunction(); break;
            case 0: cout << "Dang thoat khoi quan ly phieu bao hanh..." << endl; break;
            default: cout << "=> Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);
}
