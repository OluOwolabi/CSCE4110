#include <iostream>

using namespace std;
int box(int n){
	int count = 0;
	for(int i = 1;i*i<=n;i++){ 
		if(i*i<=n){ 
		count++; 
		}
	}
	return count; 
}
int main()
{
	cout<<"Enter the number of boxes\n";
	int n;
	cin>>n;
	cout<<"open boxes are : "<<box(n)<<"\n";


	return 0;
}