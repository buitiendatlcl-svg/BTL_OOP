#include "warrantyController.h"
#include <iomanip>
warrantyController::warrantyController()
	: warrantyRepo("data/warranty.txt"), contractRepo("data/contract.txt"), employeeRepo("data/employee.txt")
{
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

    warranty newWarranty; 
	
    cout << "\nDANH SACH HOP DONG:\n";
    //bo sung them phan in ra cac thuoc tinh hop dong cout << setw ...
    for (auto c : contractList) {
        c.showToConsole();
        cout << endl;
    }
	
	bool validContract = false;
    string chosenContract;
    
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
        
        if (contractRepo.searchId(chosenContract) != nullptr) {
            newWarranty.setContractId(chosenContract);
            validContract = true;
        } else {
            cout << "=> Ma hop dong khong ton tai. Vui long nhap lai!" << endl;
        }
    }
    
    cout << "\nDANH SACH NHAN VIEN:\n";
    cout << left << setw(8)  << "Ma NV" << "| "
         << left << setw(20) << "Ho va Ten" << "| "
         << left << setw(12) << "Ngay Sinh" << "| "
         << left << setw(12) << "SDT" << "| "
         << left << setw(20) << "Chuyen Mon" << "| "
         << left << setw(8)  << "Ma KV" << "| "
         << "Luong (VND)" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (auto emp : empList) {
        emp.showToConsole();
    }    
        
    bool validEmployee = false;
	string chosenEmployee;
    
    while (!validEmployee) {
        cout << "\nNhap ID nhan vien phu trach (nhap '0' de quay lai): "; 
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
        
        if (employeeRepo.searchId(chosenEmployee) != nullptr) {
            newWarranty.setEmployeeId(chosenEmployee);
            validEmployee = true;
        } else {
            cout << "=> Ma nhan vien khong ton tai. Vui long nhap lai!" << endl;
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
        cout << "=> Tao phieu bao hanh thanh cong! Ma phieu: " << newId << endl;
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

    // Hien thi danh sach phieu bao hanh de chon ID
    readFunction();

    // Cho nhap lai neu nhap sai ID, nhap '0' de quay lai
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
        cout << "2. Ngay tiep nhan" << endl;
        cout << "3. Noi dung su co" << endl;
        cout << "4. Trang thai xu ly" << endl;
        cout << "0. HOAN TAT VA LUU" << endl;
        cout << "Chon (0-4): ";
        
        // ngoai le nhap chu vao menu
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
                cout << "\n--- DANH SACH NHAN VIEN HIEN CO ---" << endl;
                vector<employee> employeeList = employeeRepo.getData();
                for (auto e : employeeList) {
                    cout << "Ma NV: " << e.getId() << " | Ten: " << e.getFullName() 
                         << " | Khu vuc: " << e.getAreaId() << endl;
                }
                
                while (true) {
                    cout << "Nhap ID nhan vien phu trach moi (Enter de huy): ";
                    getline(cin, newInfo);
                    if (newInfo.empty()) break;

                    for (int i = 0; i < (int)newInfo.size(); i++) {
                        if (isalpha(newInfo[i])) newInfo[i] = toupper(newInfo[i]);
                    }

                    if (employeeRepo.searchId(newInfo) != nullptr) {
                        warrantyPtr->setEmployeeId(newInfo);
                        cout << "=> Da cap nhat nhan vien phu trach!" << endl;
                        break;
                    } else {
                        cout << "=> Ma nhan vien khong ton tai. Vui long nhap lai!" << endl;
                    }
                }
                break;
            }

            case 2: {
                while (true) {
                    cout << "Nhap ngay tiep nhan moi (dd/mm/yyyy)(Enter de huy): ";
                    getline(cin, newInfo);
                    if (newInfo.empty()) break;
                    if (warrantyPtr->isValidDate(newInfo)) {
                        warrantyPtr->setReceivedDate(newInfo);
                        cout << "=> Da cap nhat ngay tiep nhan!" << endl;
                        break;
                    }
                    cout << "=> Loi! Sai dinh dang ngay thang, vui long nhap lai!" << endl;
                }
                break;
            }
            
            case 3: {
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
                        warrantyPtr->setIssueDescribe("Bao tri & keo lai day cap");
                        cout << "=> Da cap nhat noi dung su co!" << endl;
                        validIssue = true;
                    } 
					else {
                        cout << "=> Loi: Lua chon khong hop le! Vui long chon tu 1 den 4.\n";
                    }
                }
                break;
            }
            
            case 4: {
            	bool validStatus = false;
                while (!validStatus) {
                    cout << "\nChon trang thai xu ly moi:\n";
                    cout << "  1. Cho xu ly\n";
                    cout << "  2. Dang sua chua\n";
                    cout << "  3. Da hoan thanh\n";
                    cout << "  4. Da huy\n";
                    cout << "Chon (1-4, Enter de huy): ";
                    
                    getline(cin, newInfo);
                    if (newInfo.empty()) {
                    	validStatus = true;
					}

                    if (newInfo == "1") {
                        warrantyPtr->setStatus("Cho xu ly");
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
    while (true) {
        cout << "\nNhap Ma phieu BH can xoa (nhap '0' de quay lai): ";
        getline(cin, delId);
        if (delId == "0") return;

        for (int i = 0; i < (int)delId.size(); i++) {
            if (isalpha(delId[i])) delId[i] = toupper(delId[i]);
        }

        if (warrantyRepo.searchId(delId) != nullptr) {
            break;
        }
        cout << "=> Loi: Khong tim thay ma phieu " << delId << "! Vui long nhap lai." << endl;
    }

    if (warrantyRepo.remove(delId) == 1) {
        cout << "=> Da xoa phieu bao hanh thanh cong!" << endl;
    } else {
        cout << "=> Xoa that bai do loi he thong!" << endl;
    }
}

void warrantyController::run() {
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
