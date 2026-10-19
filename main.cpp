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

#include "installation.h"



#include "internetController.h" 
#include "contractController.h" 
#include "districtController.h" 
#include "employeeController.h" 
#include "warrantyController.h" 
#include "installationController.h"


using namespace std;

int main() {

    // Kh?i t?o các d?i tu?ng Controller
    // districtController có tham s? m?c d?nh là "data/data_khuvuc.txt" nên không c?n truy?n vào
    districtController dc;
    internetController ic;
    contractController cc;
    installationController inc;
    employeeController ec;
    warrantyController wc;

    int mainChoice;

    do {
        cout << "\n================ HE THONG QUAN LY DICH VU INTERNET ================" << endl;
        cout << "1. Quan ly Goi Internet" << endl;
        cout << "2. Quan ly Tuyen cap / Khu vuc" << endl;
        cout << "3. Quan ly Nhan vien ky thuat" << endl;
        cout << "4. Quan ly Hop dong thue bao" << endl;
        cout << "5. Quan ly Phieu bao hanh - sua chua" << endl;
        cout << "6. Quan ly Phieu lap dat" << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "===================================================================" << endl;
        cout << "Chon phan he (0-5): ";
        
        cin >> mainChoice;
        cin.ignore(); 

        switch (mainChoice) {
            case 1: {
                ic.run();
                break;
            }

            case 2: {
                dc.run();
                break;
            }

            case 3: {
                ec.run();
                break;
            }

            case 4: {
                cc.run();
                break;
            }

            case 5: {
                wc.run();
                break;
            }
            
			case 6:{
				inc.run();
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
