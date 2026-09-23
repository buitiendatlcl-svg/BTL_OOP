#include <iostream>
#include <vector>
#include "customer.h"
#include "repository.h"

using namespace std;

int main() {
    // 1. Kh?i t?o d?i tu?ng repository qu?n lý l?p customer
    // Truy?n tên file "customer.txt" vào hàm kh?i t?o. H? th?ng s? t? d?ng d?c d? li?u t? file lên (n?u file dã t?n t?i).
    repository<customer> repo("customer.txt");
    
    int choice;
    do {
        cout << "\n=========== MENU QUAN LY KHACH HANG ===========" << endl;
        cout << "1. Nhap thong tin khach hang va luu vao file" << endl;
        cout << "2. Xem danh sach khach hang (lay tu file)" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "===============================================" << endl;
        cout << "Chon chuc nang (0-2): ";
        cin >> choice;
        cin.ignore(); // Xóa ký t? '\n' còn sót l?i trong b? d?m sau l?nh cin d? dùng getline()

        switch (choice) {
            case 1: {
                cout << "\n--- NHAP THONG TIN KHACH HANG MOI ---" << endl;
                customer newCustomer;
                
                // L?y thông tin t? ngu?i dùng thông qua bàn phím
                newCustomer.inputFromKeyboard();
	 
                
                // Hàm create s? ki?m tra trùng mã ID, d?y d?i tu?ng vào vector và t? d?ng luu xu?ng file customer.txt
                if (repo.create(newCustomer) == 1) {
                    cout << "=> Them moi va luu vao file customer.txt thanh cong!\n";
                } else {
                    cout << "=> Loi: Ma dinh danh (ID) cua khach hang nay da ton tai!\n";
                }
                break;
            }
            case 2: {
                cout << "\n--- DANH SACH KHACH HANG ---" << endl;
                // L?y danh sách (vector) các khách hàng hi?n có
                vector<customer> list = repo.getData(); 
                
                if (list.empty()) {
                    cout << "Danh sach hien dang trong!" << endl;
                } else {
                    // Duy?t qua danh sách và hi?n th? thông tin t?ng d?i tu?ng ra màn hình
                    for (auto c : list) {
                        c.showToConsole();
                    }
                }
                break;
            }
            case 0:
                cout << "Tam biet!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le, vui long nhap lai!" << endl;
        }
    } while (choice != 0);

    return 0;
}
