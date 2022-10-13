#include <iostream>
using namespace std;

int count_ones(int n){
    int count =0;
    while(n){
        n=n & n-1;
        count ++;
    }
        return count;
}

int main(){
    cout << "enter the no: ";
    int n;
    cin >> n;
    cout << count_ones(n)<<endl;
}