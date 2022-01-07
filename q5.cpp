#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
int playersCount = 15;  //let the maximum number of players be 15
class Player{
	private:
	char* name;
	string type;   //attack for attacking and  defend for defending
	double points;
	bool availability;
	public:
		Player(){
			name = new char;
			points = 0;
			availability = true;
		}
		Player(char* name, string type){
			this->name = name;
			points = 0;
			this->type = type;
			availability = true;
		}
		char* getName(){
			return name;
		}
		bool isAvailable(){
			return availability;
		}
		void setPlayer(char* name, string type){
			this->name = name;
			points = 0;
			this->type = type;
			availability = true;
		}
		void disable(){
			availability = false;
		}
		string getType(){
			return type;
		}
		void addPoint(double point){
			points += point;
		}
		double getPoints(){
			return points;
		}
		void showStats(){
			cout << "Name: " << name << endl << "Type: " << type << endl << "Total Points: " << points << endl;
		}
};
class Team{
	char* teamName;
	int teamRank;
	Player* teamPlayers;
	string strategy;
	int pos;
	public:
		Team(){
			teamPlayers = new Player[3];
			pos = 0;
		}
		Team(char* name){
			teamName = name;
			teamPlayers = new Player[3];
			pos = 0;
		}
		void setTeam(char* name){
			teamName = name;
			teamPlayers = new Player[3];
			pos = 0;
		}
		void setRank(int rank){
			teamRank = rank;
		}
		void teamSelection(){
			cout << "Enter team strategy: ";
			string str;
			cin >> str;
			strategy = str;
		}
		string getStr(){
			return strategy;
		}
		void addTeamPlayer(Player &player){
			teamPlayers[pos] = player;
			pos++;
		}
		Player getPlayer(int pos){
			return teamPlayers[pos];
		}
		void showStats(){
			cout << "Team name: " << teamName << endl << "Team Rank: " << teamRank << endl;
		}
		int getRank(){
			return teamRank;
		}
		void updatePoints(bool win){
			if(win){
				for(int x = 0; x < 3; x++){
					double point = rand()%11 + 10;
					teamPlayers[x].addPoint(point);
				}
			}else{
				for(int x = 0; x < 3; x++){
					double point = rand()%6 + 5;
					teamPlayers[x].addPoint(point);
				}
			}
		}
		Player* getBest(){
			double points = teamPlayers[0].getPoints();
			Player player = teamPlayers[0];
			for(int x = 1; x < 3; x++){
				if(points < teamPlayers[x].getPoints()){
					points = teamPlayers[x].getPoints();
					player = teamPlayers[x];
				}
			}
			return &player;
		}
};
class Match{
	int Match_No;
	Team homeTeam;
	Team awayTeam;
	bool htstat, atstat;
	public:
		static int matchNum;
		Match(){
			
		}
		Match(Team& ht, Team& at){
			homeTeam = ht;
			awayTeam = at;
		}
		void setTeams(Team& ht, Team& at){
			homeTeam = ht;
			awayTeam = at;
		}
		void generateMatchStats(){
			int win = rand()%10;
			if(win > 5){
				//homeTeam wins
				htstat = true;
				atstat = false;
				
			}else{
				//awayTeam wins
				htstat = false;
				atstat = true;
			}
		}
		void bestPlayersInMatch(){
			Player* p1 = homeTeam.getBest();
			Player* p2 = awayTeam.getBest();
			cout << "Best player of home team:" << endl;
			p1->showStats();
			cout << "Best player of away team:" << endl;
			p2->showStats();
		}
		void UpdatePlayerPoints(){
			homeTeam.updatePoints(htstat);
			awayTeam.updatePoints(atstat);
		}
};
int Match::matchNum = 0;
void addPlayers(Player* players){  //adding players randomly
	char* name = "Player Name ";
	for(int x = 0; x < 15; x++){
		int hold = x+1;
		char num = hold + '0';
		name += num;
		string type;
		int ran = rand()%10;
		if(ran <= 5){
			type = "Attacking";
		}else{
			type = "Defending";
		}
		players[x].setPlayer(name, type);
	}
}
Player* returnPlayers(Player* players, char type){
	Player* getplayers = new Player;
	int pos = 0;
	for(int x = 0; x < playersCount; x++){
		if(type == 'a'){
			if(players[x].getType() == "Attacking"){
				getplayers[pos] = players[x];
				pos++;
			}
		}else if(type == 'd'){
			if(players[x].getType() == "Defending"){
				getplayers[pos] = players[x];
				pos++;
			}
		}
	}
	return getplayers;
}
void assignRanks(Team* teams){
	int arr[4] = {0,0,0,0};
	arr[0] = rand()%4 + 1;
	int done = 1;
	for(int x = 1; x <= 3; x++){
		int rank = rand()%4 + 1;
		while(1){
			bool check = true;
			for(int y = 0; y < done; y++){
				if(rank == arr[y]){
					rank = rand()%4 + 1;
					check = false;
					break;
				}
			}
			if(check){
				arr[x] = rank;
				break;
			}
		}
	}
	for(int x = 0; x < 4; x++){
		teams[x].setRank(arr[x]);
	}
}
void sortPlayers(Player* players){
	for(int x = 0; x < 12; x++){
		for(int y = 0; y < 12-x; y++){
			if(players[y].getPoints() > players[y+1].getPoints()){
				Player hold = players[y];
				players[y] = players[y+1];
				players[y+1] = hold;
			}
		}
	}
}
void sortTeams(Team* teams){
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3-x; y++){
			if(teams[y].getRank() > teams[y+1].getRank()){
				Team hold = teams[y];
				teams[y] = teams[y+1];
				teams[y+1] = hold;
			}
		}
	}
}
void printTeams(Team* team){
	for(int x = 0; x < 4; x++){
		team[x].showStats();
	}
}
void printPlayers(Player* players){
	for(int x = 0; x < playersCount; x++){
		cout << "Name: " << players[x].getName() << "Points: " << players[x].getPoints() << endl;
	}
}
void printLeaderBoard(Team* teams){
	Player* players = new Player[12];
	int pos = 0;
	for(int x = 0; x < 4; x++){
		for(int y = 0; y < 3; y++){
			players[pos] = teams[x].getPlayer(y);
			pos++;
		}
	}
	sortPlayers(players);
	printPlayers(players);
}
void printTeamRanks(Team* teams){
	sortTeams(teams);
	printTeams(teams);
}
void playerSelection(Player* players, Team* teams){
	for(int x = 0; x < 4; x++){
		int attack, defend;
		if(teams[x].getStr() == "Attacking"){
			attack = 2;
			defend = 1;
		}else if(teams[x].getStr() == "Defending"){
			attack = 1;
			defend = 2;
		}
		for(int y = 0; y < playersCount; y++){
			if(players[y].isAvailable()){
				if(players[y].getType() == "Attacking" && attack > 0){
					teams[x].addTeamPlayer(players[y]);
					attack--;
					players[y].disable();
				}else if(players[y].getType() == "Defending" && defend > 0){
					teams[x].addTeamPlayer(players[y]);
					defend--;
					players[y].disable();
				}
			}
			if(attack == 0 && defend == 0){
				break;
			}
		}
	}
}
int main(){
	srand(0);
	Player* players = new Player[playersCount];
	addPlayers(players);
	Team* teams = new Team[4];
	for(int x = 0; x < 4; x++){
		cout << "Enter team # " << x+1 << " name: ";
		char* name = new char[100];
		cin >> name;
		teams[x].setTeam(name);
		teams[x].teamSelection();
	}
	playerSelection(players, teams);
	Match* match;
	for(int x = 0; x < 4; x++){
		for(int y = 0; y < 4; y++){
			if(x != y){
				match = new Match(teams[x], teams[y]);
				match->generateMatchStats();
				match->UpdatePlayerPoints();
				match->bestPlayersInMatch();
				match = new Match(teams[x], teams[y]);
				match->generateMatchStats();
				match->UpdatePlayerPoints();
				match->bestPlayersInMatch();
			}
		}
	}
}
