#include<iostream>
#include<vector>
#include<unistd.h>
#include<conio.h>
#define MAX 10  //maximum number of types of a particular food iterm

using namespace std;

class Food{  //interface
	protected:
		int num_types;
		string types[MAX];
		vector<vector<float> > rates;
	public:
	    virtual void showTypes(){
	    	for(int x = 0; x < num_types; x++){
	    		cout << x+1 << ". " << types[x] << endl;
			}
		}
		virtual float getRate(int x, int y){
			return rates[x][y];
		}
		virtual int getNumTypes(){
			return num_types;
		}
};
class Burger: public Food{
	vector<vector<string> > sub_types;
	public:
		Burger(){
			num_types = 3;
			types[0] = "Beef Burger";
			types[1] = "Chicken Burger";
			types[2] = "Lamb Burger";
			vector<string> sub_type;
			sub_type.push_back("Beef Regular");
			sub_type.push_back("Beef Large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			sub_type.push_back("Chicken Regular");
			sub_type.push_back("Chicken Large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			sub_type.push_back("Lamb Regular");
			sub_type.push_back("Lamb Large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			vector<float> rate;
			rate.push_back(3.5);
			rate.push_back(4.5);
			rates.push_back(rate);
			rate.clear();
			rate.push_back(3);
			rate.push_back(4);
			rates.push_back(rate);
			rate.clear();
			rate.push_back(4);
			rate.push_back(5);
			rates.push_back(rate);
		}
		void showSubTypes(int pos){
			for(int x = 0; x < sub_types[pos-1].size(); x++){
				cout << x+1 << " . " << sub_types[pos-1][x] << ", $" << rates[pos-1][x] << endl;
			}
		}
		string getItem(int x, int y){
			return sub_types[x][y];
		}
};
class Pizza: public Food{
	vector<vector<string> > sub_types;
	public:
		Pizza(){
			num_types = 2;
			types[0] = "Chicken BBQ";
			types[1] = "Chicken Peri Peri";
			vector<string> sub_type;
			sub_type.push_back("Chicken BBQ regular");
			sub_type.push_back("Chicken BBQ large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			sub_type.push_back("Peri Peri regular");
			sub_type.push_back("Peri Peri large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			vector<float> rate;
			rate.push_back(19.9);
			rate.push_back(29.9);
			rates.push_back(rate);
			rate.clear();
			rate.push_back(19.9);
			rate.push_back(29.9);
			rates.push_back(rate);
		}
		void showSubTypes(int pos){
			for(int x = 0; x < sub_types[pos-1].size(); x++){
				cout << x+1 << " . " << sub_types[pos-1][x] << ", $" << rates[pos-1][x] << endl;
			}
		}
		string getItem(int x, int y){
			return sub_types[x][y];
		}
};
class Sandwich: public Food{
	vector<vector<string> > sub_types;
	public:
		Sandwich(){
			num_types = 2;
			vector<string> sub_type;
			sub_type.push_back("Crispy Chicken regular");
			sub_type.push_back("Crispy Chicken large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			sub_type.push_back("Tuna regular");
			sub_type.push_back("Tuna large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			types[0] = "Crispy Chicken";
			types[1] = "Tuna Sandwich";
			vector<float> rate;
			rate.push_back(3);
			rate.push_back(5);
			rates.push_back(rate);
			rate.clear();
			rate.push_back(4);
			rate.push_back(6);
			rates.push_back(rate);
		}
		void showSubTypes(int pos){
			for(int x = 0; x < sub_types[pos-1].size(); x++){
				cout << x+1 << " . " << sub_types[pos-1][x] << ", $" << rates[pos-1][x] << endl;
			}
		}
		string getItem(int x, int y){
			return sub_types[x][y];
		}
};
class Roll: public Food{
	vector<vector<string> > sub_types;
	public:
		Roll(){
			num_types = 2;
			vector<string> sub_type;
			sub_type.push_back("Chicken Mayo regular");
			sub_type.push_back("Chicken Mayo large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			sub_type.push_back("Beef Peperoni regular");
			sub_type.push_back("Beef Peperoni large");
			sub_types.push_back(sub_type);
			sub_type.clear();
			types[0] = "Chicken Mayo Roll";
			types[1] = "Beef Peperoni Roll";
			vector<float> rate;
			rate.push_back(3);
			rate.push_back(4);
			rates.push_back(rate);
			rate.clear();
			rate.push_back(3.5);
			rate.push_back(4.5);
			rates.push_back(rate);
		}
		void showSubTypes(int pos){
			for(int x = 0; x < sub_types[pos-1].size(); x++){
				cout << x+1 << " . " << sub_types[pos-1][x] << ", $" << rates[pos-1][x] << endl;
			}
		}
		string getItem(int x, int y){
			return sub_types[x][y];
		}
};
class Rice: public Food{
	public:
		Rice(){
			num_types = 3;
			types[0] = "Butter Chicken Rice";
			types[1] = "Sweet and Sour Rice";
			types[2] = "Chicken Rice";
			vector<float> rate;
			rate.push_back(5);
			rates.push_back(rate);
			rates.push_back(rate);
			rates.push_back(rate);
		}
		void showTypes(){
			for(int x = 0; x < num_types; x++){
	    		cout << x+1 << " . " << types[x] << ", $" << rates[x][0] << endl;
			}
		}
		string getItem(int x){
			return types[x];
		}
};
class Person{
	string name;
	string num;
	string address;
	public:
		Person(){
			
		}
		Person(string name, string num, string address){
			this->name = name;
			this->num = num;
			this->address = address;
		}
		string getName(){
			return name;
		}
		string getNum(){
			return num;
		}
		string getAddress(){
			return address;
		}
};
class Menu{
	Burger* burgers;
	Pizza* pizzas;
	Sandwich* sandwiches;
	Roll* rolls;
	Rice* rice;
	Person* person;
	float bill;
	vector<string> items;
	vector<float> prices;
	
	private:
		void showList(){
			system("cls");
			try{
				if(items.size() == 0){
					throw 1;
				}
				for(int x = 0; x < items.size(); x++){
			    	cout << x+1 << ". Item: " << items[x] << ", Rate: $" << prices[x] << endl;
			    }
				cout << "\nYour current bill is: " << bill << endl;
			}catch(int ex){
				cout << "No items added to the list so far!" << endl;
			}
			cout << "\nPress any key to get back to the menu page!";
	      	getch();
	    	show();
	 	}
		void submitOrder(){
			system("cls");
			try{
				if(items.size() == 0){
					throw 1;
				}
			    cout << "\nYour Total Bill is \'$" << bill  << "\'." << endl<< "Your Order Will be delivered in 40 Minutes!";
			    cout << "\nThank you For Ordering From Z Food Corner!\n";
			    exit(0);
			}catch(int ex){
				cout << "No items added to the list so far!" << endl;
				cout << "\nPress any key to get back to the menu page!";
	      	    getch();
	    	    show();
			}
		}
		void orderPlaced(string item){
	    	cout << "\n\nThe item \'" << item << "\' has been entered in the list of your order!" << endl;
	    	cout << "\nYour current bill is: " << bill << endl;
		    cout << "\nPress any key to get back to the menu page!";
		    getch();
		    show();
	    }
	public:
		
	Menu(){
		bill = 0;
	}
	void welcomePage(){
		string name, num, address;
		system("cls");
		cout << "\t\t\t----------Z Food Corner-----------\n\n";	
		cout << "\n\n To proceed to menu, please provide the following information." << endl;			
		cout << "\n Your Name: ";
		fflush(stdin);										
		getline(cin, name);														
		cout << "\n Your Phone number: ";	
		fflush(stdin);								
		getline(cin, num);												
		cout << "\n Your Address: ";	
		fflush(stdin);								
		getline(cin, address);
		person = new Person(name, num, address);
		cout << "\n\n Proceeding in a moment!";
		sleep(1);
	}
	void show(){
		int option1;
		system("cls");
		cout << "Hello " << person->getName() << "!" << "\n\n What would you like to order?\n\n";
		cout << "\t\t\t\t--------Menu--------\n\n";
		cout << " 1. Pizzas." << endl;
		cout << " 2. Burgers." << endl;
		cout << " 3. Sandwich." << endl;
		cout << " 4. Rolls." << endl;
		cout << " 5. Rice." << endl << endl;
		cout << " 6. Help on ordering." << endl;
		cout << " 7. Feedbacks." << endl;
		cout << " 8. Context." << endl;	
		cout << " 9. Show the list of items selected." << endl;
		cout << " 10. Submit the order." << endl;
		cout << " 11. Any other key to exit." << endl;
		cout << "\n Please Enter an option number: ";							
		cin >> option1;
		switch(option1){
			case 1:
				{
					pizzas = new Pizza();
					cout << "  Select flavor by entering option number:\n";
					pizzas->showTypes();
					int option2;
					cin >> option2;
					if(option2 > pizzas->getNumTypes()){
						cout << "Invaid Option!" << endl;
					}else{
						pizzas->showSubTypes(option2);
						cout << "   Select the size by entering the option number:\n";
						int option3;
						cin >> option3;
					    cout << "  Enter quantity: ";
					    int quantity;
					    cin >> quantity;
					    float rate = (quantity*pizzas->getRate(option2-1, option3-1));;
					    bill += rate;
					    string item = pizzas->getItem(option2-1, option3-1);
					    items.push_back(item);
					    prices.push_back(rate);
					    orderPlaced(item);
					}
					break;
				}
			case 2:
				{
					burgers = new Burger();
					cout << "  Select flavor by entering option number:\n";
					burgers->showTypes();
					int option2;
					cin >> option2;
					if(option2 > burgers->getNumTypes()){
						cout << "Invaid Option!" << endl;
					}else{
						burgers->showSubTypes(option2);
						cout << "   Select the size by entering the option number:\n";
						int option3;
						cin >> option3;
					    cout << "  Enter quantity: ";
					    int quantity;
					    cin >> quantity;
					    float rate = (quantity*burgers->getRate(option2-1, option3-1));
					    bill += rate;
					    string item = burgers->getItem(option2-1, option3-1);
					    items.push_back(item);
					    prices.push_back(rate);
					    orderPlaced(item);
					}
					break;
				}
			case 3:
				{
					sandwiches = new Sandwich();
					cout << "  Select flavor by entering option number:\n";
					sandwiches->showTypes();
					int option2;
					cin >> option2;
					if(option2 > sandwiches->getNumTypes()){
						cout << "Invaid Option!" << endl;
					}else{
						sandwiches->showSubTypes(option2);
						cout << "   Select the size by entering the option number:\n";
						int option3;
						cin >> option3;
					    cout << "  Enter quantity: ";
					    int quantity;
					    cin >> quantity;
					    float rate = (quantity*sandwiches->getRate(option2-1, option3-1));
					    bill += rate;
					    string item = sandwiches->getItem(option2-1, option3-1);
					    items.push_back(item);
					    prices.push_back(rate);
					    orderPlaced(item);
					}
					break;
				}
			case 4:
			    {
			    	rolls = new Roll();
					cout << "  Select flavor by entering option number:\n";
					rolls->showTypes();
					int option2;
					cin >> option2;
					if(option2 > rolls->getNumTypes()){
						cout << "Invaid Option!" << endl;
					}else{
						rolls->showSubTypes(option2);
						cout << "   Select the size by entering the option number:\n";
						int option3;
						cin >> option3;
					    cout << "  Enter quantity: ";
					    int quantity;
					    cin >> quantity;
					    float rate = (quantity*rolls->getRate(option2-1, option3-1));
					    bill += rate;
					    string item = rolls->getItem(option2-1, option3-1);
					    items.push_back(item);
					    prices.push_back(rate);
					    orderPlaced(item);
					}
				    break;
			    }
			case 5:
				{
					rice = new Rice();
					cout << "  Enter option number:\n";
					rice->showTypes();
					int option2;
					cin >> option2;
					cout << "  Enter quantity: ";
					int quantity;
					cin >> quantity;
					float rate = (quantity*rice->getRate(option2-1, 0));
					bill += rate;
					string item = rice->getItem(option2-1);
					items.push_back(item);
					prices.push_back(rate);
					orderPlaced(item);
					break;
				}
			case 6:
				{
					system("CLS");
					cout << "\t\t\t\t--------Ways to order--------\n\n";
					cout << "1) The name, phone number and address should be accurate.\n";
					cout << "2) First, select the category of any food item, e.g. burgers then select the sub-category, e.g. chicken burger, then the size, e.g. regular, and finally, the quantity, e.g. 5.\n";
					cout << "3) If you want to order other food you can go back to the menu part and make another order.\n";
					cout << "4) The estimated time of delivery will be shown when you are done ordering the foods.\n";
					cout << "5) Payment can be made through online or you can give the delivery guy.\n\n";
					cout << "Press any key to get back to the main page.";
					getch();
					welcomePage();
					show();
					break;
				}
			case 7:
				{
					system("CLS");
					cout << "\t\t\t\t--------Feedbacks--------\n\n";
					cout << "To give us a feedbacks kindly click this email ZFoodCorner@gmail.com. Thank for ordering in our restaurant.\n";
					cout << "Press any key to get back to the main page.";
					getch();
					welcomePage();
					show();
					break;
				}
			case 8:
				{
					system("CLS");
			        cout << "\t\t\t\t--------Context--------\n\n";
					cout << " Do contact us if you have further question, +673 8776655 or +673 8778989.\n";
					cout << " Follow our instagram page @Zfoodrestaurant.\n";
					cout << " Our facebook page @Zfood_restaurant.\n";
					cout << "Press any key to get back to the main page.";
					getch();
					welcomePage();
					show();
					break;
				}
			case 9:
				{
					showList();
					break;
				}
			case 10:
				{
					submitOrder();
					break;
				}
			default:
				cout << "Thanks for visiting us!";
				exit(0);
		}
	}
};
int main(){
	Menu menu;
	menu.welcomePage();
	menu.show();
}
