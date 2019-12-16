//Olu Owolabi
//CSCE 4110
//Assignment2

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int maxSubArraySum(int arr[], int size)
{
int max = 0, maxEnd = 0; //to store the max sum in the array
for (int i = 0; i < size; i++){
    maxEnd = maxEnd + arr[i];
    if (maxEnd < 0){
        maxEnd = 0;
    }
    else if (max < maxEnd){
        max = maxEnd;
    }
}
return max;
}


int main() {

    srand(time(NULL));
    const int len = 1000;   //lenght of the array to be generated randomly
    int* arr_large = new int[len]; //pass the lenght into the array
    for (int i = 0; i < len; i++) {
        arr_large[i] = rand();      //generate the array randomly
    }
    //loop to print the array large array generated randomly
   /*for(int i=0; i< len; i++){
        cout<< arr_large[i]<< " ";
   }*/
    int kk = maxSubArraySum(arr_large, len);
    cout << "\nSum of consecutive: " << kk <<"\n";  //display the sum of the consecutive numbers 


    // example of how to use already determined array
   /* int arr[] = {2,-5,3,4,0,-1,5,8,-9,1,-2,0};
    int num = sizeof(arr) / sizeof(arr[0]);

     int kk = maxSubArraySum(arr, num);
     cout << "linear: " << kk <<"\n";*/
}

