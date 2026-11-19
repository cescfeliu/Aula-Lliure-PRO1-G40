#include <iostream> 
using namespace std;

void girar(){

    string a;

    if(cin >> a){
        girar();
        cout << a << endl;
    }

}

int main(){

    girar();
    return 0;

}