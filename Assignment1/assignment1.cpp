//Name: Olu Owolabi
//Course: CSCE 4110
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void random_quicksort(long long *array, long long first, long long last);  //function to perfrom the quicksort algorithm
int random_partition(long long *array, long long first, long long last);   //function to partition the array
void swap(long long array[], long long i, long long j);                    //function to swap
void radixSort(long long *array, long long n);

int main(void)
{
   clock_t start, end;     //to store the time it takes to run the program
   long size = 1000000;     //to store the length array of size 1 million
   long long *array;
   long long first =1000000000000000000;  //for 20 didigts
   long long last = 100;
   array = new long long [size];    //store the length of the array
   srand(time(NULL));
   for (int i = 0; i < size; i++)
   {
      //first + rand() % (last-first+1);
      array[i] = first +(rand() % (last-first+1)) ; //generate a randow 1 milliom 20 digits
   }
   cout << endl;
   start = clock(); //start the clock
   random_quicksort(array, first,last);   //perfrom the quick sort array
   end = clock();    //stop the clock
   cout << "Sorted array: \n";
   for (int i = 0; i < size; i++)
      cout << array[i] << "\n";   // print out the sorted array
   cout << endl;
   cout << "Total time: For Quick Sort " << (end - start)/((double) CLOCKS_PER_SEC) << " seconds" << endl;
   delete [] array;

   start = clock();
   radixSort(array, size);
   end = clock();

   for (int i = 0; i < size; i++)
      cout << array[i] << "\n";   // print out the sorted array
   cout << endl;
   cout << "Total time: For Radix Sort " << (end - start)/((double) CLOCKS_PER_SEC) << " seconds" << endl;

   return -1;





}
//The function to perfrom the quick sort algorithm
void random_quicksort(long long *array, long long first, long long last)
{
   long long q;
   if (first < last)
   {
      // Separately sort elements before  
      // partition and after partition  
      q = random_partition(array, first, last);
      random_quicksort(array, first, q-1);
      random_quicksort(array, q+1, last);
   }
}
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array*/
int random_partition(long long *array, long long first, long long last)
{
   long long pivot_loc;
   srand(time(0));
   pivot_loc = first + rand() % (last-first+1);
   long long pivot = array[pivot_loc];
   swap(array, pivot_loc, last);
   pivot_loc = last;
   long long i = first - 1;
   for(int j = first; j <= last-1; j++)
   {
      if(array[j] <= pivot)
      {
         i++;
         swap(array, i, j);
      }
   }
   swap(array, i+1, pivot_loc);
   return i+1;
}
//The function to swap the array
void swap(long long *array, long long i, long long j)
{
   long long temp;
   temp = array[i];
   array[i] = array[j];
   array[j] = temp;
}

void radixSort(long long *array, long long arraySize){
  
    if( array == NULL | arraySize == 0 )
        return;
   int i;
    long long *bucket = new long long[arraySize];
    long long maxVal = 0;
    long long digitPosition = 1;
    for ( i = 0; i < arraySize; i++)
    {
        if ( array[i] > maxVal )                        // get the largest value in the array (will need for digits)
            maxVal = array[i];
    }
    
    while ( maxVal / digitPosition > 0 )
    {                                                       // loop for the number of digits in maxVal
        
                                                            // To keep the order, start from back side
        for(i = arraySize - 1; i >= 0; i--)
            bucket[  array[i] / digitPosition % 1000000 ] = array[i];    // put elements into buckets
                                                            // rearrange the original array using elements in the bucket
        for(i = 0; i < arraySize; i++)
            array[i] = bucket[i];
                                                            // move up by one digit
        digitPosition *= 1000000;
    }
    
    delete[] bucket;
    bucket = NULL;

}