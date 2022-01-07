#include<iostream>
#include "taskqueue.cpp"

//the code which uses the imporc library and performs both types of filters i.e. the average masking and inverted pixels for better understanding
int main(){
	TaskQueue tasks;
	char* input = "C:/Users/Hp/Desktop/improc/imgs/lena_512.bmp";   //path of the image
	char* output = "C:/Users/Hp/Desktop/improc/imgs/";   //path of the directory only
	TaskData* task = new TaskData(input, output, 1);   //for inverting pixels
	string id = "abc";   //id is to be set manually as required
	tasks.add_task(id, *task);
	input = "C:/Users/Hp/Desktop/improc/imgs/lena_128.bmp";
	output = "C:/Users/Hp/Desktop/improc/imgs/";
	id = "def";
	task = new TaskData(input, output, 2);   //for average masking filter
	tasks.add_task(id, *task);
	tasks.execute_all();  	//after the execution, two output images should be in the imgs directory!
}
