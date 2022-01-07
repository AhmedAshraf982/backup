#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

int getPivotPos(int part, int arr[], int size){
	if(part == 1){
		return size/2 + 1;
	}else if(part == 2){
		return 0;
	}else if(part == 3){
		return rand()%size;
	}else if(part == 4){
		return 0;
	}
}
int quicksort(int* arr,int low,int high)
{
    if(low>=high)
        return 0;

    int mid=(low+high)/2;
    int pivot=arr[mid];
    int i=low,j=high;
    int temp;
    while(i<j)
    {
        if(arr[i]>=pivot && arr[j]<=pivot)
        {
            temp=arr[j];
            arr[j]=arr[i];
            arr[i]=temp;
            i++;
            j--;
        }
        else
        {
            i++;
        }
    }
    quicksort(arr,low,mid-1);
    quicksort(arr,mid+1,high);
}
int partitionMedian(int arr[], int low, int high) {

  int pivot = arr[low + ((high - low) / 2)];
  while (low != high) {
    if (arr[low] < pivot)
      low++;
    else
      swap(arr[low], arr[high--]);
  }
  return high;
}
int partitionRandom(int arr[], int low, int high){
	int part = 4;
	int pos = low;
	int pivot = arr[pos];
    int i = (low - 1);
 	
    for (int j = low; j <= high- 1; j++){
        if (arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
	swap(&arr[i + 1], &arr[pos]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high){
    if (low < high){
        int pi = partitionRandom(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size){
    for (int i=0; i < size; i++)
        cout << arr[i] << endl;
}

int main(){
	srand(0);
	int size = 100;
    int arr[size];
    for(int x = 0; x < size; x++){
    	arr[x] = rand() % 1000;    //0 - 1000
	}
	int* tempArr = arr;
    quicksort(arr, 0, size-1);
    cout << "Sorted array: " << endl;
    printArray(arr, size);
    return 0;
}
