#include<iostream>
#include<vector>
#include<stdlib.h>
#include<fstream>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
using namespace std;
void gotoxy (int x, int y){  //function to print anywhere on console with respect to the given x and y coordinates
    COORD coordinates;     // coordinates is declared as COORD
    coordinates.X = x;     // defining x-axis
    coordinates.Y = y;     //defining  y-axis
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);       
}
class Interface{   //interface for customer class
	protected:
	    string name;
	    string number;
	    bool is_regular;
	    
	public:
		virtual string getName() = 0;
		virtual bool isRegular() = 0;
		virtual void setRegular() = 0;
		virtual string getContact() = 0;
};
class Customer: public Interface{   //concrete customer class
	public:
		Customer(){  //default constructor
			is_regular = false;
		}
		Customer(string name, string number, bool isRegular){  //parameterized constructor
			this->name = name;
			this->number = number;
			this->is_regular = is_regular;
		}
		string getName(){  //to get the name
			return name;
		}
		bool isRegular(){  //to check if the customer is regular one or not
			return is_regular;
		}
		void setRegular(){  //to set the customer as regular
			is_regular = true;
		}
		string getContact(){  //to get the contact number of the customer
			return number;
		}
};
class Product{   //the class to hold all the available products in the mart
	vector<string> products;   //to hold the names of the products
	vector<float> rates;  //to hold the rates of the products
	private:
		loadProducts(){  //loads the product name and rate from a file names as "products.txt"
			fstream file;
			file.open("products.txt", ios::in);
			string item;
			float rate;
			while(!file.eof()){
				file >> item;
				file >> rate;
				products.push_back(item);
				rates.push_back(rate);
			}
		}
	public:
		Product(){   //default constructor
			loadProducts();   //loading the products to get set
		}
		bool isValid(string item){   //to check if an item is available in the list of product
			for(int x = 0; x < products.size(); x++){
				if(products[x] == item){
					return true;
				}
			}
			return false;
		}
		float getRate(string item){  // to get the rate of given product
			for(int x = 0; x < products.size(); x++){
				if(products[x] == item){
					return rates[x];
				}
			}
		}
};
class List{  //the list or cart that the customer has, to hold the products
	Product products;  //getting all the products
	vector<string> list;  //to hold the names of the products the customer has bought
	vector<float> rates;  //to hold the rates of the products bought by the customer
	vector<int> quantities;   //to hold the quantities of each item bought by the customer
	float bill;  //the current bill
	private:
		int alreadyInList(string item){   //to check if the bought item is already present in the cart
			for(int x = 0; x < list.size(); x++){
				if(list[x] == item){
					return x;
				}
			}
			return -1;
		}
	public:
		List(){   //default constructor
			bill = 0;  //initially, the bill is zero
		}
		void addItem(string item){  //adding an item to the cart
			if(!products.isValid(item)){  //checks if the item is valid or available
				cout << "The item entered is either invalid or unavailable!" << endl; 
				cout << "Press any key to continue." << endl;
				getch();
				return;
			}
			cout << "Enter quantity: ";  //getting the quantity of that item
			int quantity;
			cin >> quantity;
			float rate;
			int x = alreadyInList(item);
			rate = quantity*products.getRate(item);
			if(x != -1){  //already present in the list
				rates[x] += rate;  //if already present, then we add the rate to the already present rate
				quantities[x] += quantity;
			}else{
				list.push_back(item);  //else, we push it as a new one
			    rates.push_back(rate);
			    quantities.push_back(quantity);
			}
			bill += rate;
		    cout << "Item added." << endl;
		}
		void show(){  //showing the items available in the cart
			system("cls");
			gotoxy(70, 14);
			cout << "Current Bill: $" << bill;
			gotoxy(0, 0);
			cout << "Billing System for ABC Store:\n\n";
			if(list.size()){
				for(int x = 0; x < list.size(); x++){
				    cout << x+1 << ". Item: " << list[x] << ", Quantity: " << quantities[x] << ", " << "Price: " << rates[x] << endl;
			    }
			}else{
				cout << "List is currently empty!";
			}
			cout << "\n\nPress any key to continue!";
			getch();
		}
		void deleteItem(string item){  //delete an item from the cart
				int x = alreadyInList(item);
			    if(x != -1){
				    cout << "Enter quantity to be removed: ";
			        int quantity;
			        cin >> quantity;
			        if(quantities[x] < quantity){
			        	cout << "Quantity of the item to be removed cannot be greater than the quantity of that item currently present!\n\nPress any key to get back!" << endl;
			    	    getch();
				        return;
			        }
			        float rate = quantity*products.getRate(item);
			        rates[x] -= rate;
			        if(rates[x] == 0){
			        	list.erase(list.begin() + x);
			        	quantities.erase(quantities.begin() + x);
			        	rates.erase(rates.begin() + x);
					}
			        bill -= rate;
			        quantities[x] -= quantity;
		            cout << "Item removed.\n\nPress any key to get back!" << endl;
		            getch();
			    }else{
				    cout << "Please enter a valid item!\n\nPress any key to continue!" << endl;
				    getch();
			    }
		}
		void finalize(Customer customer){  //finalize the bill
			system("cls");
			cout << "Billing System for ABC Store:\n\n";
			cout << "Customer: " << customer.getName() << "\t\tContact Number: " << customer.getContact() << endl << endl;
			if(list.size()){
				cout << "Items in the cart:" << endl << endl;
				for(int x = 0; x < list.size(); x++){
				    cout << x+1 << ". Item: " << list[x] << ", Quantity: " << quantities[x] << ", " << "Price: " << rates[x] << endl;
			    }
			    if(customer.isRegular()){
				    cout << "You saved \'$" << bill*0.2 << "\' as you are our regular customer!" << endl;
				    cout << "Final Bill: $" << bill*0.8 << endl; 
			    }
			}else{
				cout << "List is currently empty!";
			}
			cout << "\n\nPress any key to get back to the main page!";
			getch();
		}
		float getBill(){  //to get the bill made so far
	    	return bill;
	    }
	    void showSide(){   //to show the items in the cart and bill in the side of the screen while purchasing
	    	system("cls");
	    	gotoxy(70, 14);
			cout << "Current Bill: $" << bill;
	    	gotoxy(70, 16);
	    	if(list.size()){
	    		cout << "Items in cart:";
		    	for(int x = 0; x < list.size(); x++){
				    gotoxy(70, 17+x);
				    cout << x+1 << ". " << list[x] << ", " << quantities[x] << ", $" << rates[x];
			    }
			}else{
				cout << "Items in cart will be shown here!";
			}
			gotoxy(0, 0);
		}
};
class Menu{  //main menu of billing
	Customer* customer;
	List* list;
	private:
		bool validateNumber(string num){  //validating the contact number
		    try{  //handling the exception of digets to be lesser than 11
		    	if(num.length() != 11){
                    throw 1;
			    }else{
			    	return num.find_first_not_of("0123456789") == std::string::npos;
				}
			}catch(int ex){
				return false;
			}
		}
	public:
		Menu(){   //default constructor
			
		}
		void show(){  //to show the main menu
			addCustomerDetails();
			list = new List();
			while(1){
				system("cls");
				list->showSide();
				cout << "Billing System for ABC Store:\n\n";
				cout << "Customer: " << customer->getName() << endl << endl;
			    cout << "Enter Option number:\n1. Press '1' to add an item in the cart.\n2. Press '2' to delete an item from the cart.\n3. Press '3' to show the list.\n4. Press '4' to finalize the bill.\n5. Press any other key to force shut down the billing entry and exit to main page.";
		     	int option;
		     	cin >> option;
		     	switch(option){
		     		case 1:   //adds item to the cart
		     			{   
		     			    cout << "Enter Item Name: ";
		     		    	string item;
						    cin >> item;
						    list->addItem(item);
		     				break;
						}
					case 2:  //deletes an item from the cart
						{
							if(list->getBill() > 0){
								cout << "Enter Item Name: ";
		     		        	string item;
						        cin >> item;
							    list->deleteItem(item);
							}else{
				                cout << "List is currently empty!";
		    	                cout << "\n\nPress any key to continue!";
			                    getch();
							}
							break;
						}
					case 3:  //shows the cart items
						{
							list->show();
							break;
						}
					case 4:  //finalizes the bill
						{
							list->finalize(*customer);
							if(list->getBill() > 0){
								delete list;
						        delete customer;
						        show();
							}
							break;
						}
					default:   //quit the billing process for that particular customer
						cout << "Force quitting the application!\nReturning to the main page...";
						delete list;
						delete customer;
						sleep(2);
						show();
				}
			}
		}
		void addCustomerDetails(){   //to set the details of the customer
			string name, number;
			bool isRegular = false;
			system("cls");
			cout << "Billing System for IJK Store:\n\n";
			cout << "Enter Customer Name: ";
			cin >> name;
			cout << "\nEnter Contact Number: ";
			cin >> number;
			while(!validateNumber(number)){
				system("cls");
				cout << "Billing System for ABC Store:\n\n";
				cout << "Enter Name: " << name << endl << "Contact number should be 11 digits long without characters! " << endl << "\nEnter Contact Number: ";
				cin >> number;
			}
			cout << "\nIs the customer regular? (y/n): ";
			char ch;
			cin >> ch;
			if(ch == 'y' || ch == 'Y'){
				isRegular = true;
			}
			customer = new Customer(name, number, isRegular);
			cout << "\n\nRedirecting to the billing page...";
			sleep(1);
		}
};

//driver's code
int main(){
	Menu menu;  //show the main menu
	menu.show();
}
