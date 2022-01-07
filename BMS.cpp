#include<iostream>  
#include<fstream>    
#include<cctype>      
#include<iomanip>  
#include<string.h>
#include<unistd.h>
using namespace std; 

class Customer_interface{  //an interface for customer class
	protected:
	int account_number;
    char name[100];	
    char type;
    int amount_deposited;
    float loan;
    public:
    	virtual void create_Acc(int account_number, char name[100], char type, int amount_deposited) = 0;
    	virtual void show_Acc() const = 0;
    	virtual void modify() = 0;
    	virtual void adep(int x) = 0;
    	virtual void draw(int x) = 0;
    	virtual void report() const = 0;
    	virtual int retano() const = 0;
    	virtual int retbal() const = 0;
    	virtual char qtype() const = 0;
};
class Customer: public Customer_interface{  //inheriting the interface of customer 
    
    public:
    	Customer(){
    		account_number = -1;  //not logged in, any other value means that the user is logged in
    		loan = 0;  //innitially, loan is 0
		}
    void create_Acc(int account_number, char name[100], char type, int amount_deposited)  //setter function
	{
		this->account_number = account_number;
		strcpy(this->name, name);
		this->type = type;
		this->amount_deposited = amount_deposited;
	}
	char* getName(){  
		return name;
	}
	void show_Acc() const
	{
	    cout<<"\n\tAccount Number : "<< account_number;
	    cout<<"\n\tAccount Holder Name : ";
	    cout<<name;
	    cout<<"\n\tType of Account : "<<type;
	    cout<<"\n\tBalance amount : "<<amount_deposited;
	}
	void updateLoan(float loan){
		this->loan += loan;
	}
	int getLoan(){
		return loan;
	}
	void modify(){
	    cout<<"\n\tAccount Number : "<<account_number;
	    cout<<"\n\tModify Account Holder Name : ";
	    cin.ignore();
	    cin.getline(name,100);
	    cout<<"\n\tModify Type of Account : ";
	    cin>>type;
	    cout<<"\n\tModify Balance amount : ";
	    cin>>amount_deposited;
	}
	 void reset(){
	 	account_number = -1;
	 }
	void adep(int x)
	{
	    amount_deposited+=x;
	}
	   
	void draw(int x)
	{
	    amount_deposited-=x;
	}
	   
	void report() const
	{
	    cout<<account_number<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<amount_deposited<<endl << setw(10) << loan; 
	}
	   
	int retano() const
	{
	    return account_number;
	}
	
	int retbal() const
	{
	    return amount_deposited;
	}
	
	char qtype() const
	{
	    return type;
	}
};

class Record{  //a class that handles filing
	public:
	void delete_all_records(){
		remove("info.csv");
	}
	Customer& getCustomer(int acc_num){  //returns the matched customer record with respect to the given account number
		Customer customer;
	    ifstream x;
	    x.open("info.csv",ios::binary);
	    if(!x)
	    {
	        cout<<"File could not be opened!! Press any Key to exit...";
	        return customer;
	    }
	    cout<<"\nBALANCE DETAILS\n";
	
	        while(x.read(reinterpret_cast<char *> (&customer), sizeof(Customer)))
	    {
	        if(customer.retano()==acc_num)
	        {
	            return customer;
	        }
	    }
	    x.close();
	    return customer;
	}
	
	void addLoan(int acc_num, int loan, float interest){  //adds loan in the given customer account with interest
		bool found=false;
	    Customer customer;
	    fstream x;
	    x.open("info.csv", ios::binary|ios::in|ios::out);
	    if(!x)
	    {
	        cout<<"File could not be open !! Press any Key...";
	        return;
	    }
	    while(!x.eof() && found==false)
	    {
	        x.read(reinterpret_cast<char *> (&customer), sizeof(Customer));
	        if(customer.retano()==acc_num)
	        {
	        	customer.updateLoan(loan+loan*float((interest/100)));
	            int pos=(-1)*static_cast<int>(sizeof(customer));
	            x.seekp(pos,ios::cur);
	            x.write(reinterpret_cast<char *> (&customer), sizeof(Customer));
	            cout<<"\n\n\t Record Updated";
	            return;
	            found=true;
	           }
	         }
	    x.close();
	    if(found==false)
	        cout<<"\n\n Record Not Found ";
	}
	
	void payLoan(int acc_num, int loan){  //subtracts loan from the customer account
		bool found=false;
	    Customer customer;
	    fstream x;
	    x.open("info.csv", ios::binary|ios::in|ios::out);
	    if(!x)
	    {
	        cout<<"File could not be open !! Press any Key...";
	        return;
	    }
	    while(!x.eof() && found==false)
	    {
	        x.read(reinterpret_cast<char *> (&customer), sizeof(Customer));
	        if(customer.retano()==acc_num)
	        {
	                int bal=customer.retbal()-loan;
	                if((bal<500 && customer.qtype()=='S') || (bal<1000 && customer.qtype()=='C'))
	                    cout<<"Insufficience balance";
	                else
	                    customer.updateLoan(-1*loan);
	            int pos=(-1)*static_cast<int>(sizeof(customer));
	            x.seekp(pos,ios::cur);
	            x.write(reinterpret_cast<char *> (&customer), sizeof(Customer));
	            cout<<"\n\n\t Record Updated";
	            return;
	            found=true;
	           }
	         }
	    x.close();
	    if(found==false)
	        cout<<"\n\n Record Not Found ";
	}
	
	bool checkUser(int acc_num){  //checks if the user exists in file
		Customer customer;
	    bool flag=false;
	    ifstream x;
	    x.open("info.csv",ios::binary);
	    if(!x)
	    {
	        cout<<"File could not be opened!! Press any Key to exit...";
	        return false;
	    }
	    cout<<"\nBALANCE DETAILS\n";
	
	        while(x.read(reinterpret_cast<char *> (&customer), sizeof(Customer)))
	    {
	        if(customer.retano()==acc_num)
	        {
	            flag=true;
	        }
	    }
	    x.close();
	    return flag;
	}
	void write_Acc(Customer customer)
	{
	    ofstream x;
	    x.open("info.csv",ios::binary|ios::app);
	    x.write(reinterpret_cast<char *> (&customer), sizeof(Customer));
	    x.close();
	}
	void display_sp(int n)      //function to retrive a record from file stored
	{
	    Customer customer;
	    bool flag=false;
	    ifstream x;
	    x.open("info.csv",ios::binary);
	    if(!x)
	    {
	        cout<<"File could not be opened!! Press any Key to exit...";
	        return;
	    }
	    cout<<"\nBALANCE DETAILS\n";
	
	        while(x.read(reinterpret_cast<char *> (&customer), sizeof(Customer)))
	    {
	        if(customer.retano()==n)
	        {
	            customer.show_Acc();
	            flag=true;
	        }
	    }
	    x.close();
	    if(flag==false)
	        cout<<"\n\nAccount number does not exist";
	}
//function to modify record of an Account which is stored in file

	void modify_Acc(int n)
	{
	    bool found=false;
	    Customer customer;
	    fstream x;
	    x.open("info.csv",ios::binary|ios::in|ios::out);
	    if(!x)
	    {
	        cout<<"File could not be open !! Press any Key...";
	        return;
	    }
	    while(!x.eof() && found==false)
	    {
	        x.read(reinterpret_cast<char *> (&customer), sizeof(Customer));
	        if(customer.retano()==n)
	        {
	            customer.show_Acc();
	            cout<<"\n\nEnter The New Details of Account"<<endl;
	            customer.modify();
	            int pos=(-1)*static_cast<int>(sizeof(Customer));
	            x.seekp(pos,ios::cur);
	            x.write(reinterpret_cast<char *> (&customer), sizeof(Customer));
	            cout<<"\n\n\t Record Updated";
	            found=true;
	          }
	    }
	    x.close();
	    if(found==false)
	        cout<<"\n\n Record Not Found ";
	}

//function to delete a record from file
	void delete_Acc(int n)
	{
	    Customer customer;
	    ifstream x;
	    ofstream y;
	    x.open("info.csv",ios::binary);
	    if(!x)
	    {
	        cout<<"File could not be open !! Press any Key...";
	        return;
	    }
	    y.open("Temp.csv",ios::binary);
	    x.seekg(0,ios::beg);
	    while(x.read(reinterpret_cast<char *> (&customer), sizeof(Customer)))
	    {
	        if(customer.retano()!=n)
	        {
	            y.write(reinterpret_cast<char *> (&customer), sizeof(Customer));
	        }
	    }
	    x.close();
	    y.close();
	    remove("info.csv");
	    rename("Temp.csv","info.csv");
	    cout<<"\n\n\tRecord Deleted ..";
	}// function to display Customerount details from the stored file
	void display_all()
	{
	    Customer customer;
	    ifstream x;
	    x.open("info.csv",ios::binary);
	    if(!x)
	    {
	        cout<<"File could not be open !! Press any Key...";
	        return;
	    }
	    cout<<"\n\n\t\tCustomerOUNT HOLDER LIST\n\n";
	    cout<<"==========================================================================\n";
	    cout<<"A/c no.      NAME           Type         Balance      Loan(with interests)\n";
	    cout<<"==========================================================================\n";
	    while(x.read(reinterpret_cast<char *> (&customer), sizeof(Customer)))
	    {
	        customer.report();
	    }
	    x.close();
	}
	// function to withdraw amount from the Customer account
	void dep_withdraw(int n, int amt, int option)
	{
	    bool found=false;
	    Customer customer;
	    fstream x;
	    x.open("info.csv", ios::binary|ios::in|ios::out);
	    if(!x)
	    {
	        cout<<"File could not be open !! Press any Key...";
	        return;
	    }
	    while(!x.eof() && found==false)
	    {
	        x.read(reinterpret_cast<char *> (&customer), sizeof(Customer));
	        if(customer.retano()==n)
	        {
	            if(option==1)
	            {
	                customer.adep(amt);
	            }
	            if(option==2)
	            {
	                int bal=customer.retbal()-amt;
	                if((bal<500 && customer.qtype()=='S') || (bal<1000 && customer.qtype()=='C'))
	                    cout<<"Insufficience balance";
	                else
	                    customer.draw(amt);
	            }
	            int pos=(-1)*static_cast<int>(sizeof(customer));
	            x.seekp(pos,ios::cur);
	            x.write(reinterpret_cast<char *> (&customer), sizeof(Customer));
	            cout<<"\n\n\t Record Updated";
	            found=true;
	           }
	         }
	    x.close();
	    if(found==false)
	        cout<<"\n\n Record Not Found ";
	}
};

class Admin_interface{  //an interface for admin clas
	protected:
		Record record;
    	float interest_rate;
    public:
    	virtual void delete_account(int num) = 0;
    	virtual void set_interest_rate(float rate) = 0;
    	virtual float getRate() = 0;
};

class Admin: public Admin_interface{  //actual admin class
	public:
		Admin(){
			interest_rate = 5;	
		}
		void delete_account(int num){
			Customer customer;
		    ifstream x;
		    ofstream y;
		    x.open("info.csv",ios::binary);
		    if(!x)
		    {
		        cout<<"File could not be open !! Press any Key...";
		        return;
		    }
		    y.open("Temp.csv",ios::binary);
		    x.seekg(0,ios::beg);
		    while(x.read(reinterpret_cast<char *> (&customer), sizeof(Customer)))
		    {
		        if(customer.retano()!=num)
		        {
		            y.write(reinterpret_cast<char *> (&customer), sizeof(Customer));
		        }
		    }
		    x.close();
		    y.close();
		    remove("info.csv");
		    rename("Temp.csv","info.csv");
		    cout<<"\n\n\tRecord Deleted ..";
		}
		
		void set_interest_rate(float rate){
			this->interest_rate = rate;
		}

		float getRate(){
			return interest_rate;
		}
};
class Menu{  //Menu class that shows the menus to the user
	Customer customer;  //stores a session for a customer
	Admin admin;  //storesmsession for an admin
	Record record;
	public:
		// Function To write the Account data to .csv file
		//The Entry/Welcome Screen
		void intro()
		{
		    cout<<"\n\n\n\tWelcome To BANK MANAGEMENT SYSTEM";
		    cout<<"\n\nA C++ Project by Priyanshu Mishra for Object Oriented Programming";
		    //Note: All the data of the new Account entered will be stored in the disk
		    cout<<"\nPress Enter To Continue........";
		    cin.get();
		}
		void mode(){  //admin or customer mode
			int num;
			system("cls");
			cout<<"\n\n\n\tACTION MENU";
			cout << "\n\n\t1. Login as Customer.\n\n\t2. Login as Admin.";
			cout<<"\n\n\tSelect Your Option (1-2) ";
			cin >> num;
			while(1){
				show(num);
			}
		}
		
		void show(int num){  //entire menu
			char ch;
			if(num == 1){
				int num_;
				if(customer.retano() == -1){
					system("cls");
					cout << "\n\n\tCustomer Menu:";
					cout<<"\n\n\n\tACTION MENU";
					cout << "\n\n\t1. Make a new Account.\n\n\t2. Already a user.";
					cout<<"\n\n\tSelect Your Option (1-2) ";
					cin >> num_;
				}
				if(num_ == 1){
					int ano, dep;
		        	char name[100];
		        	char type;
		        	system("cls");
		        	cout << "\n\n\tCustomer Menu:";
				    cout<<"\n\n\tEnter The Account Number :";
				    cin>>ano;
				    cout<<"\n\n\tEnter, Name of The Account Holder : ";
				    cin.ignore();
				    cin.getline(name,100);
				    cout<<"\n\tEnter Type of Account(C/S) : ";
				    cin>>type;
				    cout<<"\n\n\tEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
				    cin>>dep;     //We have set the minimum initial amount for savings be 500 & for current be 1000
				    cout<<"\n\n\n\tCongrats Account Has Been Created..";
				    customer.create_Acc(ano, name, type, dep);  //making the account
		            record.write_Acc(customer);  //writing that account to file
		            customer.reset();
				}else if(num_ == 2){
					int acc_num = customer.retano();
					if(acc_num == -1){
						system("cls");
						cout << "\n\n\tCustomer Menu:";
						cout<<"\n\n\n\tACTION MENU";
						cout << "\n\n\tEnter Account Number: ";
						cin >> acc_num;
					}
					if(record.checkUser(acc_num)){
						customer = record.getCustomer(acc_num);
						system("cls");
						cout << "\n\n\tCustomer Menu:";
						cout << "\n\n\tLogged In as: " << customer.getName() << "\n\tAccount No.: " << customer.retano() << "\n\tType of Account: " << customer.qtype() << "\n\tBalance: " << customer.retbal() << "\n\tLoan: " << customer.getLoan(); 
						cout<<"\n\n\n\tACTION MENU";
				        cout<<"\n\n\t1. DEPOSIT";
				        cout<<"\n\n\t2. WITHDRAW";
				        cout<<"\n\n\t3. BALANCE ENQUIRY";
				        cout<<"\n\n\t4. CLOSE AN ACCOUNT";
				        cout<<"\n\n\t5. MODIFY AN ACCOUNT";
				        cout << "\n\n\t6. Check loan rates.";
				        cout << "\n\n\t7. Request a loan.";
				        cout << "\n\n\t8. Pay back loan(if any).";
				        cout<<"\n\n\t9. EXIT";
				        cout<<"\n\n\tSelect Your Option (1-9) ";
				        int option;
				        cin >> option;
				        switch(option){
				        	case 1:{
					            cout<<"\n\n\tTO DEPOSIT AMOUNT: ";
				                cout<<"\n\n\tEnter The amount to be deposited: ";
				                int amt;
				                cin>>amt;
					            record.dep_withdraw(customer.retano(), amt, 1);
					            customer.adep(amt);
					            cout << "\n\n\tUpdated Balance: " << customer.retbal();
								break;
							}
							case 2:{
					            cout<<"\n\n\tTO WITHDRAW AMOUNT: ";
				                cout<<"\n\n\tEnter The amount to be withdrawn: ";
				                int amt;
				                cin>>amt;
					            record.dep_withdraw(customer.retano(), amt, 2);
					            customer.draw(amt);
					            cout << "\n\n\tUpdated Balance: " << customer.retbal();
								break;
							}
							case 3:{
	           					record.display_sp(customer.retano());
								break;
							}
							case 4:{
	          				    record.delete_Acc(customer.retano());
								break;
							}
							case 5:{
	            				record.modify_Acc(customer.retano());
								break;
							}
							case 6:{
								cout << "\n\n\tCurrent Loan Rate: " << admin.getRate() << "%";
								break;
							}
							case 7:{
								cout << "\n\n\tEnter amount of loan to request: ";
								float loan;
								cin >> loan;
								cout << "\n\n\tRequest accepted for loan.\nAmount \'" << loan << "\' has been added in your account.";
								record.dep_withdraw(customer.retano(), loan, 1);
								record.addLoan(customer.retano(), loan, admin.getRate());
								break;
							}
							case 8:{
								if(customer.getLoan() == 0){
									cout << "\n\n\tYou have not requested for any loan so far!";
									break;
								}
								cout << "\n\n\tEnter amount to pay back: ";
								float loan;
								cin >> loan;
								if(loan > customer.retbal()){
									cout << "\n\n\tInsufficient balance!";
								}else{
									record.payLoan(customer.retano(), loan);
									record.dep_withdraw(customer.retano(), loan, 2);
						            customer.draw(loan);
						            cout << "\n\n\tUpdated Balance: " << customer.retbal();
								}
								break;
							}
							case 9:{
								cout << "\n\n\tExiting the application...";
								mode();
								sleep(2);
								break;
							}
							default: {
								cout << "\n\n\tInvalid option number!";
							}
						}
					}else{
						cout << "\n\n\tUser not found!";
					}
				}
			}else if(num == 2){
				system("cls");
				cout << "\n\n\tAdmin Menu:";
				cout<<"\n\n\n\tACTION MENU";
				cout<<"\n\n\t1. Display all Accounts.";
				cout << "\n\n\t2. Update a particular account.";
		        cout<<"\n\n\t3. Delete an Account.";
		        cout<<"\n\n\t4. Delete all Accounts.";
		        cout<<"\n\n\t5. Set Loan Rate.";
		        cout<<"\n\n\t6. Get Loan Rate.";
		        cout<<"\n\n\t7. EXIT";
		        cout<<"\n\n\tSelect Your Option (1-6) ";
		        int option;
		        cin >> option;
		        switch(option){
		        	case 3:{
		        		cout << "\n\n\tEnter Account number to delete: ";
		        		int num;
		        		cin >> num;
		        		record.delete_Acc(num);
						break;
					}
					case 4:{
						record.delete_all_records();
						break;
					}
					case 5:{
						cout << "\n\n\tEnter new Loan Rate: ";
						float rate;
						cin >> rate;
						admin.set_interest_rate(rate);
						cout << "\n\n\tLoan rate updated!";
						break;
					}
					case 1:{
						record.display_all();
						break;
					}
					case 6:{
						cout << "\n\n\tCurrent loan rate: " << admin.getRate() << "%";
						break;
					}
					case 2:{
						cout << "\n\n\tEnter Account number to update: ";
						int acc_num;
						cin >> acc_num;
						record.modify_Acc(acc_num);
						break;
					}
					case 7:{
						mode();
						break;
					}
				}
			}
	        cin.ignore();
	        cin.get();
		}
};

int main()
{
	Menu menu;  //making the menu
	menu.intro();  //intro page
	menu.mode();  //menu
    return 0;
}

