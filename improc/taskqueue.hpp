class TaskData{     //the taskdata data structure
	public:
		char* input;
		char* output;
		int func;
		
		TaskData(){
		}
		TaskData(char* input, char* output, int func){
			this->input = input;
			this->output = output;
			this->func = func;
		}
};
