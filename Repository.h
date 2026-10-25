//ca nhom
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
template <class T>
class Repository{ //giup cho viec doc ghi du lieu nham phuc vu chuc nang CRUD
private:
	vector<T> data;
	string fileName;
public:
	Repository(string fileName){
		this->fileName = fileName; //fileName chinh la duong dan toi file.txt luu data cua doi tuong
		readFromFile();//tu dong luu vao data
	}
	
	void readFromFile(){
		ifstream ifs; // khai bao ifstream giup doc file.txt ma khong xoa hay sua
		ifs.open(fileName);
		if(!ifs.is_open())
			return;
		string line;
		while(getline(ifs, line)){
			if(line.empty())
				continue;
			T obj;
			obj.fromFileString(line);
			data.push_back(obj);
		}
		ifs.close();
	}
	
	
	void saveToFile(){
		ofstream ofs; // khai bao ofstream se lam cho file.txt bi xoa sach
		ofs.open(fileName); 
//		for(vector<T>::interator it = data.begin(); it != data.end(); it++){
//			ofs << it->toFileString() << endl;
//		}
		for(auto obj : data){
			ofs << obj.toFileString() << endl; // cap nhat toan bo object da luu o vector data va save vao file.txt
		}
		ofs.close();
	}
	
	//chuc nang Create trong CRUD
	int create(T obj){
		for(auto x : data){
			if(x.getId() == obj.getId())
				return 0;
		}
		data.push_back(obj);
		saveToFile();
		return 1;
	}
	
	//chuc nang Read 
	
	vector<T> getData(){//
		return data;  // tu data nay se xay dung mot menu cua doi tuong do de cout
	}
	
	//chuc nang Update trong CRUD
	T *searchId(string id){
		auto it = find_if(data.begin(), data.end(), [&](T obj){
			if(obj.getId() == id)
				return 1;
			else
				return 0;
		});
		if(it != data.end()){
			return &(*it); // no moi giup tro toi vung nho cua con tro can duoc sua thoi, sua nhu nao thi tung lop co cach sua rieng 
		}
		else{
			return nullptr; 
		}	
	}
	
	// sau khi lay pointer va sua thi can goi them ham saveToFile de update thong tin
	void saveChange(){
		saveToFile();
	}
	int remove(string id){
		auto it = remove_if(data.begin(), data.end(), [&](T obj){
			if(obj.getId() == id)
				return 1;
			else
				return 0;	
		});
		if(it != data.end()){
			data.erase(it, data.end());
			saveToFile();
			return 1;
		}
		else{
			return 0;
		}
	}
	
	string autoGenId(string productName){
		if(data.empty()){
			return productName + "1";
		}
	
		int maxIdNumber = 0;
		for(auto obj : data){
			string currentId = obj.getId();
	        
	        // 1. Ki?m tra mã ID có d? dài l?n hon ti?n t? (VD: "G1" dài hon "G") 
	        // và ph?i b?t d?u b?ng ti?n t? dó
	        if (currentId.length() > productName.length() && currentId.find(productName) == 0) {
			    string numStr = currentId.substr(productName.length());
	            // 2. B?c try-catch khi ép ki?u
	            try {
			        int num = stoi(numStr);
			        if(num > maxIdNumber){
				        maxIdNumber = num;
			        }
	            } catch(...) {
	                // N?u g?p mã l?i (nhu Gabc), h? th?ng s? ph?t l? và không b? crash
	            }
	        }
		}
		return productName + to_string(maxIdNumber + 1);		
	}

	void reloadData(){
		data.clear();   
		readFromFile(); 
	}	
	
};
