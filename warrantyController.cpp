#include "warrantyController.h"

warrantyController::warrantyController()
	: warrantyRepo("data/warranty.txt"), contractRepo("data/contract.txt"), employeeRepo("data/employee.txt")
{
}

void warrantyController :: createFunction(){
	cout << "\n--- THEM PHIEU BAO HANH MOI ---" << endl;
	warranty newWarranty;
	
	cout << "DANH SACH HOP DONG: \n";
	vector <contract> contractList = contractRepo.getData();
	if (contractList.empty()){
		cout << "Hien chua co hop dong nao! Vui long tao hop dong truoc!" << endl;
		return;  //thoat toan bo ham create, quay ve menu cua nhan vien
	}
	for (auto c : contractList){
		cout << "Ma hop dong: " << c.getId() << endl;
	}
	bool validContract = false;
	string chosenContract;
	while (!validContract){
		cout << "Nhap ID hop dong can bao hanh: ";
		getline (cin, chosenContract);
		if (contractRepo.searchId(chosenContract) != nullptr){
			newWarranty.setContractId(chosenContract);
			validContract = true;
		}
		else {
			cout << "Ma hop dong khong hop le. Vui long nhap lai!" << endl;
		}
	}
	
	cout << "DANH SACH NHAN VIEN: \n";
	vector <employee> empList = employeeRepo.getData();
	if (empList.empty()){
		cout << "Hien chua co nhan vien nao ! Vui long tao nhan vien truoc !" << endl;
		return; 
	}
	for (auto e : empList){
		cout << "Ma NV: " << e.getId() << " | Ten: " << e.getFullName() << " | Khu vuc: " << e.getAreaId() << endl;
	}
		
	bool validEmployee = false;
	string chosenEmployee;
	while (!validEmployee){
		cout << "Nhap ID nhan vien phu trach: "; 
		getline (cin, chosenEmployee);
		if (employeeRepo.searchId(chosenEmployee) != nullptr){
			newWarranty.setEmployeeId(chosenEmployee);
			validEmployee = true;
		}
		else{
			cout << "Ma nhan vien khong ton tai. Vui long nhap lai!" <<endl;
		}
	}
	
	newWarranty.inputFromKeyboard();
	
	string newId = warrantyRepo.autoGenId("BH");
    newWarranty.setId(newId);

    if (warrantyRepo.create(newWarranty) == 1) {
        cout << "=> Tao phieu bao hanh thanh cong! Ma phieu: " << newId << endl;
    } else {
        cout << "=> Loi: Khong the tao phieu bao hanh." << endl;
    }	
}


void warrantyController :: readFunction (){
	cout << "\n--- DANH SACH PHIEU BAO HANH ---" << endl;
	vector <warranty> warrantyList = warrantyRepo.getData();
	if (warrantyList.empty()){
		cout << "Danh sach phieu bao hanh hien dang trong!" << endl;
	}
	else{
		for (auto w : warrantyList){
			w.showToConsole();	
	}
	}	
}	

	
void warrantyController::updateFunction() {
    cout << "\n--- SUA THONG TIN PHIEU BAO HANH ---" << endl;
    cout << "Nhap ID phieu bao hanh can sua: ";
    string searchId;
    getline(cin, searchId);
    
    warranty* warrantyPtr = warrantyRepo.searchId(searchId);
    
    if (warrantyPtr != nullptr) {
        int editChoice;
        do {
            cout << "\n--- THONG TIN HIEN TAI CUA PHIEU BAO HANH [" << warrantyPtr->getId() << "] ---" << endl;
            warrantyPtr->showToConsole();
            
            cout << "\nCHON THONG TIN CAN SUA:" << endl;
            cout << "1. Nhan vien phu trach" << endl;
            cout << "2. Noi dung su co" << endl;
            cout << "3. Trang thai xu ly" << endl;
            cout << "0. HOAN TAT VA LUU" << endl;
            cout << "Chon (0-3): ";
            
            cin >> editChoice;
            cin.ignore();
            
            string newInfo;
            switch (editChoice) {
                case 1: {
                    cout << "\n--- DANH SACH NHAN VIEN HIEN CO ---" << endl;
                    vector<employee> employeeList = employeeRepo.getData();
                    for (auto e : employeeList) {
                        cout << "Ma NV: " << e.getId() << " | Ten: " << e.getFullName() 
                             << " | Khu vuc: " << e.getAreaId() << endl;
                    }
                    
                    bool validEmployee = false;
                    while (!validEmployee) {
                        cout << "Nhap ID nhan vien phu trach moi (Enter de huy): ";
                        getline(cin, newInfo);
                        if (newInfo.empty()) {
                            validEmployee = true;
                        } else if (employeeRepo.searchId(newInfo) != nullptr) {
                            warrantyPtr->setEmployeeId(newInfo);
                            validEmployee = true;
                            cout << "=> Da cap nhat nhan vien phu trach!" << endl;
                        } else {
                            cout << "=> Ma nhan vien khong ton tai. Vui long nhap lai!" << endl;
                        }
                    }
                    break;
                }
                
                case 2: {
                    cout << "Nhap noi dung su co moi (Enter de huy): ";
                    getline(cin, newInfo);
                    if (!newInfo.empty()) {
                        warrantyPtr->setIssueDescribe(newInfo);
                        cout << "=> Da cap nhat noi dung su co!" << endl;
                    }
                    break;
                }
                
                case 3: {
                    
                    cout << "\nChon trang thai xu ly moi:\n";
                    cout << "1. Cho xu ly\n";
                    cout << "2. Dang sua chua\n";
                    cout << "3. Da hoan thanh\n";
                    cout << "4. Da huy\n";
                    cout << "Chon (1-4): ";
                    
                    int stChoice;
                    cin >> stChoice;
                    cin.ignore();

                    if (stChoice == 1) warrantyPtr->setStatus("Cho xu ly");
                    else if (stChoice == 2) warrantyPtr->setStatus("Dang sua chua");
                    else if (stChoice == 3) warrantyPtr->setStatus("Da hoan thanh");
                    else if (stChoice == 4) warrantyPtr->setStatus("Da huy");
                    else cout << "=> Lua chon khong hop le!\n";

                    if (stChoice >= 1 && stChoice <= 4) {
                        cout << "=> Da cap nhat trang thai!\n";
                    }
                    break;
                }
                
                case 0: {
                    
                    warrantyRepo.saveToFile();
                    cout << "=> DA LUU THAY DOI THANH CONG!" << endl;
                    break;
                }
                
                default: {
                    cout << "=> Lua chon khong hop le! Vui long chon tu 0 den 3." << endl;
                    break;
                }
            }
        } while (editChoice != 0); 
        
    } else {
        
        cout << "=> Khong tim thay phieu bao hanh mang ma: " << searchId << endl;
    }
}

void warrantyController::deleteFunction() {
    cout << "\n--- XOA PHIEU BAO HANH ---" << endl;
    cout << "Nhap Ma phieu BH can xoa: ";
    string delId;
    getline(cin, delId);

    if (warrantyRepo.remove(delId) == 1) {
        cout << "=> Da xoa phieu bao hanh thanh cong!" << endl;
    } else {
        cout << "=> Khong tim thay ma phieu, xoa that bai!" << endl;
    }
}

void warrantyController::menu() {
    int choice;
    do {
        cout << "\n====== QUAN LY PHIEU BAO HANH - SUA CHUA ======" << endl;
        cout << "1. Tao phieu bao hanh moi" << endl;
        cout << "2. Xem danh sach phieu bao hanh" << endl;
        cout << "3. Cap nhat tien do / thong tin phieu" << endl;
        cout << "4. Xoa phieu bao hanh" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "===============================================" << endl;
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: createFunction(); break;
            case 2: readFunction(); break;
            case 3: updateFunction(); break;
            case 4: deleteFunction(); break;
            case 0: cout << "Dang thoat khoi quan ly phieu bao hanh..." << endl; break;
            default: cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);
}































































