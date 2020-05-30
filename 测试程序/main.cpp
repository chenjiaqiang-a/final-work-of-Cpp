#include<iostream>
#include"matrix.h"
using namespace std;

int main(){
	Matrix<int> m(4, 4);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			m.setValue(i, j, i+j);
	
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cout<<m.getValue(i,j)<<" ";
		}
		cout<<"\n";
	}
	
	return 0;
}
