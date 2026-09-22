#pragma once
#include <string>
using namespace std;

class entity{
protected:
	string id;
public:
	void setId(string id){
		this->id = id;
	}
	string getId(){
		return id;
	}
	virtual void inputFromKeyboard() = 0; // ham de lay du lieu data tu keyboard
	
	virtual void showToConsole() = 0; // ham de show data cua doi tuong ra man hinh
	
	virtual string toFileString() = 0; // ham dung de chuyen data thanh string va luu vao file
	
	virtual void fromFileString(string &line) = 0; // doc chuoi string trong file va gan cac gia tri vao thuoc tinh tuong ung cua doi tuong 
	
};


