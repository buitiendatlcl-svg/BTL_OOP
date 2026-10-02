#pragma once 
#include <string>
using namespace std;

class entity {
protected:
    string id;
public:
    virtual ~entity() {} // B? sung hàm h?y ?o d? tránh rò r? b? nh?
    
    void setId(string id) {
        this->id = id;
    }
    
    string getId() const {
        return id;
    }
    
    virtual void inputFromKeyboard() = 0; 
    virtual void showToConsole() = 0; 
    virtual string toFileString() = 0; 
    virtual void fromFileString(string &line) = 0; 
};
