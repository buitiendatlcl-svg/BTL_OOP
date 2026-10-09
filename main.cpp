#include <iostream>
#include <vector>
#include "customer.h"
#include "repository.h"
#include "internet.h"

using namespace std;

int main() {
	repository<internet> repo("data/internet.txt");
	
	int choice;
	do{
		cout << "\n==========Menu quan ly cac goi mang==========" << endl;
		cout << "1. Nhap thong tin goi mang moi" << endl;
		cout << "2. Xem danh sach cac goi mang hien co" << endl;
		cout << "3. Chinh sua thong tin cac goi mang hien co" << endl;
		cout << "4. Xoa goi mang hien co" << endl;
		cout << "0. Thoat chuong trinh" << endl;
		cout << "Chon chuc nang: ";
		cin >> choice;
		cin.ignore();
		switch(choice){
			case 1:{
				cout << "\n--Nhap thong tin goi mang moi--" << endl;
				internet newInternet;
				string newId = repo.autoGenId("G");
				newInternet.setId(newId);
				
				newInternet.inputFromKeyboard();
				if(repo.create(newInternet) == 1){
					cout << "Them moi thanh cong!" << endl;
				}
				else{
					cout << "Them moi that bai!" << endl;
				}
				break;
			}
			case 2:{
				cout << "\n--Danh sach cac goi mang dang hoat dong" << endl;
				vector<internet> list = repo.getData();
				if(list.empty())
					cout << "Danh sanh hien khong co goi mang nao" << endl;
				else{
					for(auto x : list){
						x.showToConsole();
					}
				}
				break;
			}
			case 3:{
				cout << "\n----Danh sach goi mang hien co----" << endl;
				vector<internet> list = repo.getData();
				for(auto x : list){
					x.showToConsole();
				}
				cout <<"\nChon Id goi mang ban muon chinh sua: ";
				string search;
				getline(cin, search);
				if(repo.searchId(search) != NULL){
					auto it = repo.searchId(search);
					it->showToConsole();
					cout << "\n---Chon thanh phan ban muon chinh sua----" << endl;
					cout << "1. Chinh sua ten" << endl;
					cout << "2. Chinh sua toc do" << endl;
					cout << "3. Chinh sua tep khach hang" << endl;
					cout << "4. Chinh sua gia cuoc(VND)" << endl;
					cout << "Nhap lua chon cua ban: ";
					int option; cin >> option;
					cin.ignore();
					switch(option){
						case 1:{
							cout << "Nhap ten moi ban muon doi: ";
							string newPackageName;
							getline(cin, newPackageName);
							it->setPackageName(newPackageName);
							cout << "Ban da chinh sua thanh cong!" << endl;
							repo.saveToFile();
							break;
						}
						case 2:{
							cout << "Nhap toc do moi ban muon doi: ";
							string newSpeed;
							getline(cin, newSpeed);
							it->setSpeed(newSpeed);
							cout << "Ban da chinh sua thanh cong!" << endl;
							repo.saveToFile();
							break;
						}
						case 3:{
							cout << "Nhap tep khach hang moi ban muon doi: ";
							string newCustomerType;
							getline(cin, newCustomerType);
							it->setCustomerType(newCustomerType);
							cout << "Ban da chinh sua thanh cong!" << endl;
							repo.saveToFile();
							break;
						}
						case 4:{
							cout << "Nhap gia cuoc moi ban muon doi: ";
							double newPrice;
							cin >> newPrice; cin.ignore();
							it->setPrice(newPrice);
							cout << "Ban da chinh sua thanh cong!" << endl;
							repo.saveToFile();
							break;
						}
					}
				}
				else
					cout << "ID khong ton tai" << endl;
				
				break;
			}
			case 4:{
				cout << "\n----Danh sach hien co----" << endl;
				vector<internet> list = repo.getData();
				for(auto x : list){
					x.showToConsole();
				}
				
				cout << "\nChon ID goi mang ban muon xoa: ";
				string removeId;
				getline(cin, removeId);
				if(repo.remove(removeId) == 1)
					cout << "Ban da xoa thanh cong!" << endl;
				else
					cout << "ID khong ton tai!" << endl;
				break;
			}
		} 
	} while(choice != 0);

    return 0;
}
