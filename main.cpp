#include <iostream>
#include <vector>
#include <string>

// Include các file header c?a các Controller và Model tuong ?ng
#include "Repository.h"
#include "district.h"
#include "districtController.h"
#include "internet.h"
#include "internetController.h"
#include "contract.h"
#include "contractController.h"

using namespace std;

int main() {
    // Kh?i t?o các d?i tu?ng Controller
    // districtController có tham s? m?c d?nh là "data/data_khuvuc.txt" nên không c?n truy?n vào
    districtController dc("data/data_khuvuc.txt");
    internetController ic;
    contractController cc;

    int choice;
    do {
        cout << "\n=================================================" << endl;
        cout << "   CHUONG TRINH QUAN LY DICH VU INTERNET FTTH    " << endl;
        cout << "=================================================" << endl;
        cout << "1. Quan ly Tuyen cap / Khu vuc" << endl;
        cout << "2. Quan ly Goi mang" << endl;
        cout << "3. Quan ly Hop dong thue bao" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "=================================================" << endl;
        cout << "Nhap lua chon cua ban: ";
        
        // Ki?m tra xem ngu?i dùng nh?p có dúng d?nh d?ng s? không d? tránh treo/l?p vô h?n
        if (!(cin >> choice)) {
            cout << "=> LOI: Vui long nhap so nguyen!" << endl;
            cin.clear(); // Xoá c? l?i c?a cin
            cin.ignore(10000, '\n'); // Lo?i b? các ký t? th?a trong b? d?m
            choice = -1; // Ð?t giá tr? m?c d?nh d? ti?p t?c vòng l?p
            continue;
        }
        cin.ignore(); // Xoá ký t? '\n' còn sót l?i trong b? d?m

        // Ði?u hu?ng t?i các use case tuong ?ng d?a vào menu dánh s?
        switch(choice) {
            case 1:
                dc.run(); // G?i use case qu?n lý khu v?c / tuy?n cáp
                break;
            case 2:
                ic.run(); // G?i use case qu?n lý gói m?ng
                break;
            case 3:
                cc.run(); // G?i use case qu?n lý h?p d?ng
                break;
            case 0:
                cout << "=> Da thoat chuong trinh quan ly. Tam biet!" << endl;
                break;
            default:
                cout << "=> LOI: Lua chon khong hop le, vui long chon lai!" << endl;
                break;
        }
    } while(choice != 0);

    return 0;
}
