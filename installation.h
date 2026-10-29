//Vu Tran Tuan Minh - B24DCVT263
#pragma once
#include "Entity.h"
#include <string>
using namespace std;
class installationForm : public entity{
	private:
		string idContract;
		string idEmployee;
		string modem;
		string date;
		int status;
	public:
		installationForm();
				
		void setIdContract(string idContract);
		string getIdContract();
			
		void setIdEmployee(string idEmployee);
		string getIdEmployee();
		
		void setModem(string modem);
		string getModem();
		
		void setDate(string date);
		string getDate();
		
		void setStatus(int status);
		int getStatus();
		
		void inputFromKeyboard() override;
    	void showToConsole() override;
    	string toFileString() override;
    	void fromFileString(string &line) override;
		
};
