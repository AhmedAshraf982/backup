#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#define MAX_SIZE 500000
int num = MAX_SIZE;
int array[MAX_SIZE];
int num_of_threads = 10;
void insertionSort(void* arg){  //ascending order

    int size =  (int*) arg;
    int chunk_size = num / num_of_threads;
    size *= chunk_size;
	int x, y;
	for(x = size; x < size+chunk_size-1; x++){
		int key = array[x+1];
		y = x;
		while(key < array[y] && y >= size){
			array[y+1] = array[y];
			y--;
		}
		array[y+1] = key;
	}
}
void makeArray(){
	int x;
	for(x = 0; x < num; x++){
		array[x] = rand()%num;
	}
}

int main(){
	srand(NULL);
	int x, y;
	makeArray();
	pthread_t threads[num_of_threads];
	for(x = 0; x < num_of_threads; x++){
		pthread_create(&threads[x],NULL,insertionSort,(void*) x);
		pthread_join(&threads[x],NULL);
	}
	int pointers[num_of_threads];
	int chunk_size = num / num_of_threads;
	for(x = 0; x < num_of_threads; x++){
		pointers[x] = x*chunk_size;
	}
	int sorted_array[num];
	for(x = 0; x < num; x++){  //merge
	    int y;
	    int min, index;
	    for(y = 0; y < num_of_threads; y++){
	    	if(pointers[y] < (y+1)*chunk_size){
	    		min = array[pointers[y]];
	    		index = y;
	    		break;
			}
		}
	    for(y = index+1; y < num_of_threads; y++){
	    	if(array[pointers[y]] < min){
	    		min = array[pointers[y]];
	    		index = y;
			}
		}
		sorted_array[x] = min;
		pointers[index]++;
	}
}
