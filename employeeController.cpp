#include "employeeController.h"


employeeController::employeeController() 
    : employeeRepo("data/employee.txt"), districtRepo("data/district.txt"), warrantyRepo("data/warranty.txt") {
}


void employeeController::createFunction() {
    cout << "\n--- THEM NHAN VIEN MOI ---" << endl;
    employee newEmployee;
    newEmployee.inputFromKeyboard(); 
    
    cout << "DANH SACH KHU VUC HIEN CO: \n";
    vector<district> distList = districtRepo.getData();
    if (distList.empty()){
        cout << "Chua co khu vuc nao! Vui long tao khu vuc truoc.\n";
        return; 
    }
    for (auto d : distList){
        cout << "Ma KV: " << d.getId() << " - Ten KV: " << d.getDistrict() << endl;
    }
    
    bool validDistrict = false;
    string chosenDistrict;
    while (!validDistrict){
        cout << "Nhap ma KV: ";
        getline(cin, chosenDistrict);
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
    vector<employee> list = employeeRepo.getData();
    if (list.empty()) {
        cout << "Danh sach trong!" << endl;
    } else {
        for (auto emp : list) {
            emp.showToConsole();
        }
    }
}


void employeeController::updateFunction() {
    cout << "\n--- SUA THONG TIN NHAN VIEN ---" << endl;
    cout << "Nhap ID nhan vien can sua: ";
    string searchId;
    getline(cin, searchId);

    employee* empPtr = employeeRepo.searchId(searchId);

    if (empPtr != nullptr) {
        int editChoice;
        do {
            cout << "\n--- THONG TIN HIEN TAI cua nhan vien [" << empPtr->getId() << "] ---" << endl;

            empPtr->showToConsole(); 
            
            cout << "\nCHON THONG TIN CAN SUA:" << endl;
            cout << "1. Ten nhan vien" << endl;
            cout << "2. Ngay sinh" << endl;
            cout << "3. So dien thoai" << endl;
            cout << "4. Chuyen mon" << endl;
            cout << "5. Khu vuc phu trach " << endl;
            cout << "6. Muc luong" << endl;
            cout << "0. HOAN TAT VA LUU" << endl;
            
            cin >> editChoice;
            cin.ignore(); 

            string newInfo;
            switch (editChoice) {
                case 1:
                    cout << "Nhap ten moi: ";
                    getline(cin, newInfo);
                    if (!newInfo.empty()) {
                        empPtr->setFullName(newInfo);
                        cout << "=> Da cap nhat Ten!\n";
                    }
                    break;
                
                case 2:
                    cout << "Nhap ngay thang nam sinh moi: ";
                    getline(cin, newInfo);
                    if (!newInfo.empty()) {
                        empPtr->setDateOfBirth(newInfo);
                        cout << "=> Da cap nhat Ngay sinh!\n";
                    }
                    break;
                
                case 3:
                    cout << "Nhap SDT moi: ";
                    getline(cin, newInfo);
                    if (!newInfo.empty()) {
                        empPtr->setPhoneNumber(newInfo);
                        cout << "=> Da cap nhat SDT!\n";
                    }
                    break;
                
                case 4: 
                    cout << "Nhap chuyen mon moi: ";
                    getline(cin, newInfo);
                    if (!newInfo.empty()) {
                        empPtr->setSpecialization(newInfo);
                        cout << "=> Da cap nhat Chuyen mon!\n";
                    }
                    break;

                case 5: { 
                    cout << "\nDANH SACH KHU VUC HIEN CO: \n";
                    vector<district> distList = districtRepo.getData();
                    for (auto d : distList){
                        cout << "Ma KV: " << d.getId() << " - Ten KV: " << d.getDistrict() << endl;
                    }
                    
                    bool validDistrict = false;
                    while (!validDistrict) {
                        cout << "Nhap ma KV moi (an Enter de huy thao tac sua): ";
                        getline(cin, newInfo);
                        
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
                    bool validSalary = false;
                    while (!validSalary) {
                        cout << "Nhap muc luong moi (VND/thang) (an Enter de huy thao tac sua): ";
                        getline(cin, newInfo);
                        
                        if (newInfo.empty()) {
                            validSalary = true; //huy thao tac sua luong
                        } else {
                            try {
                                double newSalary = stod(newInfo);
                                empPtr->setSalary(newSalary);
                                validSalary = true;
                                cout << "=> Da cap nhat Luong!\n";
                            } catch (...) { 
                                cout << "=> Loi: Vui long chi nhap bang so!\n";
                            }
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
    cout << "\n--- XOA NHAN VIEN ---" << endl;
    cout << "Nhap ID nhan vien can xoa: ";
    string delId;
    getline(cin, delId);
    if (employeeRepo.searchId(delId) == nullptr) {
        cout << "=> Loi: Khong tim thay nhan vien mang ma " << delId << "!" << endl;
        return;
    }

    bool isWorking = false; 
    vector<warranty> wList = warrantyRepo.getData();
    for (auto w : wList) {
  
        if (w.getEmployeeId() == delId) { 
            isWorking = true;

            cout << "=> KHONG THE XOA! Nhan vien dang phu trach Phieu bao hanh ma: " << w.getId() << endl;
        }
    }

    if (isWorking) {
        cout << "=> Vui long chuyen giao cac Phieu tren cho nhan vien khac truoc khi xoa nhan vien nay!" << endl;
        return; 
    }


    if (employeeRepo.remove(delId) == 1) {
        cout << "=> Da xoa nhan vien thanh cong!" << endl;
    } else {
        cout << "=> Xoa that bai do loi he thong!" << endl;
    }
}


void employeeController::run() {
    int choice;
    do {
        cout << "\n=========== QUAN LY NHAN VIEN ===========" << endl;
        cout << "1. Them nhan vien" << endl;
        cout << "2. Xem danh sach" << endl;
        cout << "3. Sua thong tin nhan vien" << endl;
        cout << "4. Xoa nhan vien" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "=========================================" << endl;
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

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
