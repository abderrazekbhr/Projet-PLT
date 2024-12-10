#include<iostream>
using namespace std;

class NotFoundCardException: public exception
{
private:
    string message;
public:
    NotFoundCardException(string message){
        this->message = message;   
    }
    void what(){
        //cout << message << endl;
    }
};
