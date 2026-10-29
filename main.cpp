//ca nhom
#include <iostream>
#include <string>

// Include c?c file header c?a c?c Controller v? Model tuong ?ng
#include "Repository.h"
#include "district.h"
#include "districtController.h"
#include "internet.h"
#include "internetController.h"
#include "contract.h"
#include "contractController.h"
#include "repository.h"
#include "installation.h"
#include "Customer.h"
#include "Invoice.h"


#include "internetController.h" 
#include "contractController.h" 
#include "districtController.h" 
#include "employeeController.h" 
#include "warrantyController.h" 
#include "installationController.h"
#include "InvoiceController.h"
#include "CustomerController.h"



using namespace std;

int main() { // dieu khien va goi ham run cua cac controller

    districtController dc;
    internetController ic;
    contractController cc;
    installationController inc;
    employeeController ec;
    warrantyController wc;
    CustomerController cuc;
    InvoiceController invc;

    int mainChoice = -1;

    do {
        cout << "\n================ HE THONG QUAN LY DICH VU INTERNET ================" << endl;
        cout << "1. Quan ly Goi Internet" << endl;
        cout << "2. Quan ly Tuyen cap / Khu vuc" << endl;
        cout << "3. Quan ly Nhan vien ky thuat" << endl;
        cout << "4. Quan ly Hop dong thue bao" << endl;
        cout << "5. Quan ly Phieu bao hanh - sua chua" << endl;
        cout << "6. Quan ly Phieu lap dat" << endl;
        cout << "7. Quan ly Khach hang" << endl;
        cout << "8. Quan ly Hoa don cuoc" << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "===================================================================" << endl;
        cout << "Chon phan he (0-8): ";
        
        string mainChoiceStr;
        getline(cin, mainChoiceStr);
        try{
        	size_t pos;
        	mainChoice = stoi(mainChoiceStr, &pos);
        	if(pos != mainChoiceStr.size() || mainChoice < 0)
        		mainChoice = -1;
		}catch(...){
			mainChoice = -1;
		}

        switch (mainChoice) {
            case 1: {
                ic.run(); // goi den ham run cua internetController
                break;
            }

            case 2: {
                dc.run(); // goi den ham run cua districtController
                break;
            }

            case 3: {
                ec.run(); // goi den ham run cua employeeController
                break;
            }

            case 4: {
                cc.run(); // goi den ham run cua contractController
                break;
            }

            case 5: {
                wc.run(); // goi den ham run cua warrantyController
                break;
            }
            
			case 6:{
				inc.run(); // goi den ham run cua installationController
				break;
			}
			case 7:{
				cuc.run(); // goi den ham run cua customerController
				break;
			}
			case 8:{
				invc.run(); // goi den ham run cua invoiceController
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
