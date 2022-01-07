#include<vector>
#include "improc.cpp"
#include "taskqueue.hpp"
using namespace std;

class TaskQueue{   //the taskqueue datas structure, using vectors
	vector<string> ids;
	vector<TaskData> tasks;
	
	string getFileName(char* input){
		string fileName;
		int x = strlen(input) - 5;
		while(input[x]!= '/'){
			fileName.push_back(input[x]);
			x--;
		}
		string hold;
		for(int x = fileName.length() - 1; x >= 0; x--){
			hold.push_back(fileName[x]);
		}
		return hold;
	}
	string stringify(char* something){
		string hold;
		for(int x = 0; x < strlen(something); x++){
			hold.push_back(something[x]);
		}
		return hold;
	}
	char* characterify(string anything){
		char* hold = new char;
		int x;
		for(x = 0; x < anything.length(); x++){
			hold[x] = anything[x];
		}
		hold[x] = '\0';
		return hold;
	}
	public:
		TaskQueue(){
		}
		void add_task(string id, TaskData task){
			ids.push_back(id);
			tasks.push_back(task);
		}
		void execute_all(){
			for(int x = 0; x < ids.size(); x++){
				char* input_filepath = tasks[x].input;
				char* output_filepath = tasks[x].output;
				string fileName = getFileName(input_filepath);
				fileName += "_";
				fileName += ids[x];
				fileName += ".bmp";
				string output_ = stringify(output_filepath);
				output_ += fileName;
				output_filepath = new char;
				output_filepath = characterify(output_);
				int mode = tasks[x].func;
				BITMAPINFO* bitmap_info = NULL;
				Image<byte>* image = load_bitmap(input_filepath, &bitmap_info);
				image->setBmpInfo(bitmap_info);
				image = transform(image, mode);
				save_bitmap(output_filepath, image);
			}
		}
		vector<TaskData> get_all_tasks(){
			return tasks;
		}
		~TaskQueue(){
			ids.clear();
			tasks.clear();
		}
};
