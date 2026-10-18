#include <iostream>
#include <string>


// Include các file header c?a các Controller và Model tuong ?ng
#include "Repository.h"
#include "district.h"
#include "districtController.h"
#include "internet.h"
#include "internetController.h"
#include "contract.h"
#include "contractController.h"
#include "repository.h"


#include "internetController.h" 
#include "contractController.h" 
#include "districtController.h" 
#include "employeeController.h" 
#include "warrantyController.h" 


using namespace std;

int main() {

    // Kh?i t?o các d?i tu?ng Controller
    // districtController có tham s? m?c d?nh là "data/data_khuvuc.txt" nên không c?n truy?n vào
    districtController dc;
    internetController ic;
    contractController cc;

    int mainChoice;

    do {
        cout << "\n================ HE THONG QUAN LY DICH VU INTERNET ================" << endl;
        cout << "1. Quan ly Goi Internet (UC 1)" << endl;
        cout << "2. Quan ly Tuyen cap / Khu vuc (UC 5)" << endl;
        cout << "3. Quan ly Nhan vien ky thuat (UC 7)" << endl;
        cout << "4. Quan ly Hop dong thue bao (UC 2)" << endl;
        cout << "5. Quan ly Phieu bao hanh - sua chua (UC 8)" << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "===================================================================" << endl;
        cout << "Chon phan he (0-5): ";
        
        cin >> mainChoice;
        cin.ignore(); 

        switch (mainChoice) {
            case 1: {
                internetController intCtrl;
                intCtrl.run();
                break;
            }

            case 2: {
                districtController distCtrl;
                distCtrl.run();
                break;
            }

            case 3: {
                employeeController empCtrl;
                empCtrl.run();
                break;
            }

            case 4: {
                contractController conCtrl;
                conCtrl.run();
                break;
            }

            case 5: {
                warrantyController warCtrl;
                warCtrl.run();
                break;
            }

            case 0:
                cout << "\nCam on ban da su dung he thong. Tam biet!" << endl;
                break;

            default:
                cout << "=> Lua chon khong hop le, vui long nhap lai!" << endl;
        }
    } while (mainChoice != 0);

    return 0;
}
