//#include "installation.h"
//#include<sstream>
//#include<iostream>
//#include<iomanip>
//using namespace std;
//
//installationForm::installationForm(){
//		 id="";
//		 idContract="";
//		 idEmployee="";
//		 modem="";
//		 date="";
//		 state=0;
//}
//
//	
//				
//		void installationForm :: setIdContract(string idContract){
//			this->idContract=idContract;
//		}
//		string installationForm :: getIdContract(){
//			return idContract;
//		}
//			
//		void installationForm :: setIdEmplyee(string idEmployee){
//			this->idEmployee=idEmployee;
//		}
//		string installationForm :: getIdEmployee(){
//			return idEmployee;
//		}
//		
//		void installationForm :: setModem(string modem){
//			this->modem=modem;
//		}
//		string installationForm:: getModem(){
//			return modem;
//		}
//		
//		void installationForm :: setDate(string date){
//			this->date=date;
//		}
//		string installationForm:: getDate(){
//			return date;
//		}
//		
//		void installationForm :: setState(int state){
//			this->state=state
//		}
//		int installationForm:: getState(){
//			return state;
//		}
//		void installationForm::inputFromKeyboard(){
//			
//		}
//    	void installationForm::showToConsole(){
//    		string trangThai;// vi chi luu state la cac so  0 1 2 nen cho vao switch bat cac trang thai in ra
//	    	switch(state){
//	    	case 0:  trangThai = "Cho xu ly"; break;
//	        case 1:  trangThai = "Dang thi cong"; break;
//	        case 2:  trangThai = "Hoan thanh"; break;
//	        case -1  trangThai= "Huy bo";break;
//	        default: trangThai = "Khong xac dinh"; break;
//			}
//			cout << left << setw(12) << id
//	         << setw(12) << idContract
//	         << setw(12) << idEmployee
//	         << setw(30) << modem
//	         << setw(15) << date
//	         << setw(15) << trangThai << endl;
//    		
//    		
//		}
//    	string installationForm:: toFileString(){
//    		return id + "|" +idContract+ "|" +modem+ "|" +date+ "|" +to_string(state);
//    		
//		}
//    	void installationForm::fromFileString(string &line){
//    		stringstream ss(line);
//    		string tmp;
//    		getline(ss,id,'|');
//    		getline(ss,idContract,'|');
//    		getline(ss,idTechnician,'|');
//    		getline(ss,modem,'|');
//    		getline(ss,date,'|');
//    		getline(ss,tmp,'|');
//    		if(!tmp.empty()) state=stoi(tmp);
//    		
//    		
//		}
//		
//		

