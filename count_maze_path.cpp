#include <iostream>
using namespace std;

int count_maze_path(int s,int e,int n){
    if(s==n-1 && e==n-1){
        return 1;
    }
    if(s>=n || e>=n){
        return 0;
    }
    // int count =0;
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         count += count_maze_path(s+i,e+j,n);
    //     }
    // }
    return count_maze_path(s+1,e,n)+count_maze_path(s,e+1,n);
}
int main(){
    cout << count_maze_path(0,0,3)<<endl;
}