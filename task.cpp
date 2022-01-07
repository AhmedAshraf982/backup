#include<iostream>
#define NULLPTR 0
using namespace std;
class Team{
	int wins;
	int losses;
	string name;
	Team* next;
	public:
		Team(){	
			next = NULLPTR;
		}
		Team(int wins, int losses, string name){
			this->wins = wins;
			this->losses = losses;
			this->name = name;
			next = NULLPTR;
		}
		int getWins(){
			return wins;
		}
		int getLosses(){
			return losses;
		}
		void setNext(Team* node){
			next = node;
		}
		Team* getNext(){
			return next;
		}
		string getName(){
			return name;
		}
};

class PQ{
	Team* head1;
	Team* head2;
	public:
		PQ(){
			head1 = NULLPTR;
			head2 = NULLPTR;	
		}
		bool isEmpty1(){
			if(head1 == NULLPTR)
				return true;
			return false;
		}
		bool isEmpty2(){
			if(head2 == NULLPTR)
				return true;
			return false;
		}
		void insert(Team& node){
			bool inserted = false;
			if(isEmpty1()){
				head1 = new Team(node);
				inserted = true;
			}
			Team* prev = NULLPTR;
			if(!inserted){
				for(Team* start = head1; start != NULLPTR; start = start->getNext()){
				if(node.getWins() >= start->getWins()){
					if(start == head1){
						Team* team = new Team(node);
						team->setNext(head1);
						head1 = team;
						inserted = true;
						break;
					}
					else{	
						Team* team = new Team(node);
						prev->setNext(team);
						team->setNext(start);
						inserted = true;
						break;
					}
				}
				prev = start;
				}
				if(!inserted){
					Team* team = new Team(node);
					prev->setNext(team);
				}
			}
			if(isEmpty2()){
				head2 = new Team(node);
				return;
			}
			prev = NULLPTR;
			for(Team* start = head2; start != NULLPTR; start = start->getNext()){
				if(node.getLosses() <= start->getLosses()){
					if(start == head2){
						Team* team = new Team(node);
						team->setNext(head2);
						head2 = team;
						return;
					}
					else{	
						Team* team = new Team(node);
						prev->setNext(team);
						team->setNext(start);
						return;
					}
				}
				prev = start;
			}
			Team* team = new Team(node);
			prev->setNext(team);
		}
		void displayWins(){
			for(Team* team = head1; team != NULLPTR; team = team->getNext()){
				cout << team->getName() << " " << team->getWins() << endl;
			}
		}
		void displayLosses(){
			for(Team* team = head2; team != NULLPTR; team = team->getNext()){
				cout << team->getName() << " " << team->getLosses() << endl;
			}
		}
		void removeWins(){
			if(!isEmpty1()){
				Team* hold = head1;
				head1 = head1->getNext();
				delete hold;
			}
		}
		void removeLosses(){
			if(!isEmpty2()){
				Team* hold = head2;
				head2 = head2->getNext();
				delete hold;
			}
		}
		void showWins(){
			if(!isEmpty1()){
				cout << head1->getName() << endl;
			}
		}
		void showLosses(){
			if(!isEmpty2()){
				cout << head2->getName() << endl;
			}
		}
		void execute(){
			string command;
			cin >> command;
			if(command == "i"){
				int wins, losses;
				string name;
				cin >> wins >> losses >> name;
				Team team(wins, losses, name);
				insert(team);
			}else if(command == "pw"){
				showWins();
			}else if(command == "rw"){
				removeWins();
			}else if(command == "pl"){
				showLosses();
			}else if(command == "rl"){
				removeLosses();
			}else if(command == "x"){
				exit(0);
			}
		}
};
int main(){
	PQ pq;
	cout << "Keep entering commands. To stop, press enter 'x'." << endl;
	while(1) pq.execute();
}
