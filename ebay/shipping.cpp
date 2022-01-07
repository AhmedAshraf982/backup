#include<iostream>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
using namespace std;
class interface{    //the interface for the basic calculator class
	protected:  //all the attributes that are required for shipment
	float sold_price;
	float shipping_charged;
	float item_cost;
	float shipping_cost;
	long num_of_orders;
	string seller_level;
	string payment_processing;
	bool overseas;
	bool shipping_in_sales_tax;
	float promoted_ad_rate;
	float donated_to_charity;
	string item_category;
	
	public:
		virtual void calculate() = 0;  //pure virtual funtion
		virtual float getProfit() = 0;  //pure virtual funtion
		virtual float getSalesTax() = 0;  //pure virtual funtion
		virtual float getFee() = 0;  //pure virtual funtion
};
class Calculator: public interface{   //concrete class to inherit the interface for its implementation
//the output attributes
	float profit;
	float sales_tax;
	float fee;
	float cut_off;
	float sales_tax_rate;
	public:
		Calculator(){
		}
		Calculator(float sold_price, float shipping_charged, float item_cost, float shipping_cost,    //the parametereized constructor
		long num_of_orders, string seller_level, string payment_processing, bool overseas,
		 bool shipping_in_sales_tax, float promoted_ad_rate, float donated_to_charity, string item_category){
			this->sold_price = sold_price;
	        this->shipping_charged = shipping_charged;
			this->item_cost = item_cost;
			this->shipping_cost = shipping_cost;
			this->num_of_orders = num_of_orders;
			this->seller_level = seller_level;
			this->payment_processing = payment_processing;
			this->overseas = overseas;
			this->shipping_in_sales_tax = shipping_in_sales_tax;
			this->promoted_ad_rate = promoted_ad_rate;
			this->donated_to_charity = donated_to_charity;
			this->item_category = item_category; 
			this->profit = 0;
			this->fee = 0;
			this->sales_tax = 0;
			this->cut_off = 0.2;  //%20 earning
			this->sales_tax_rate = 0.04;  //4% sales tax rate
		}
		void calculate(){  //the function to calcuate results
			fee = sold_price*cut_off;
			profit = sold_price - num_of_orders*item_cost - shipping_cost - donated_to_charity - fee;
			sales_tax = num_of_orders*item_cost*sales_tax_rate;
		}
		
		//getter functions
		float getProfit(){
			return profit;
		}
		float getSalesTax(){
			return sales_tax;
		}
		float getFee(){
			return fee;
		}
		float getSoldPrice(){
			return sold_price;
		}
		float getShippingCharged(){
			return shipping_charged;
		}
		float getItemCost(){
			return item_cost;
		}
		float getShippingCost(){
			return shipping_cost;
		}
		long getNumOfOrders(){
			return num_of_orders;
		}
		string getSellerLevel(){
			return seller_level;
		}
		string getPaymentProcesing(){
			return payment_processing;
		}
		bool getOverseas(){
			return overseas;
		}
		bool getShippingInSalesTax(){
			return shipping_in_sales_tax;			
		}
		float getPromotedAdRate(){
			return promoted_ad_rate;
		}
		float getCharity(){
			return donated_to_charity;
		}
		string getItemCategory(){
			return item_category;
		}
};
class Filing{  //class to handle file streaming
	fstream file;
	
	private:
		void stringify(char* arr, string& data){
			string hold;
			for(int x = 0; x < strlen(arr); x++){
				hold.push_back(arr[x]);
			}
			data = hold;
		}
	public:
		void write(float sold_price, float shipping_charged, float item_cost, float shipping_cost, long num_of_orders, string seller_level, string payment_processing, bool overseas,
			bool shipping_in_sales_tax, float promoted_ad_rate, float donated_to_charity, string item_category, float profit, float sales_tax, float fee){  //write to the file
			try{
				bool flag = false;
				file.open("file.txt", ios::in);
				if(file.is_open()){
					flag = true;
				}
				file.close();
				file.open("file.txt", ios::app);
				if(!file.is_open()){
					throw 1;
				}
				if(flag){
					file << endl;  //Not the first time
				}
				time_t now = time(0);
   				char* dt = ctime(&now);
   				string date;
   				stringify(dt, date);
   				string overseas_ = "No", shipping_in_sales_tax_ = "No";
   				if(overseas){
   					overseas_ = "Yes";
				}
				if(shipping_in_sales_tax){
					shipping_in_sales_tax_ = "Yes";
				}
				file << date << sold_price << endl << shipping_charged << endl << item_cost << endl << shipping_cost << endl << num_of_orders << endl << seller_level << endl
				<< payment_processing << endl << overseas_ << endl << shipping_in_sales_tax_ << endl << promoted_ad_rate << endl << donated_to_charity << endl << item_category << endl
				<< profit << endl << sales_tax << endl << fee;
				file.close();
				cout << "Data has been recorded to the file!" << endl;
			}
			catch(int exp){
				cout << "Failed to access the file!" << endl;
			}
			
		}
		void read(){  //read from the file
			try{
				file.open("file.txt", ios::in);
				if(!file.is_open()){
					throw 1;
				}
				int pos = 1;
				string sold_price;
				string shipping_charged;
				string item_cost;
				string shipping_cost;
				string num_of_orders;
				string seller_level;
				string payment_processing;
				string overseas;
				string shipping_in_sales_tax;
				string promoted_ad_rate;
				string donated_to_charity;
				string item_category;
				string profit;
				string sales_tax;
				string fee;
				string date;
				while(!file.eof()){
					getline(file, date);
					getline(file, sold_price);
					getline(file, shipping_charged);
					getline(file, item_cost);
					getline(file, shipping_cost);
					getline(file, num_of_orders);
					getline(file, seller_level);
					getline(file, payment_processing);
					getline(file, overseas);
					getline(file, shipping_in_sales_tax);
					getline(file, promoted_ad_rate);
					getline(file, donated_to_charity);
					getline(file, item_category);
					getline(file, profit);
					getline(file, sales_tax);
					getline(file, fee);
			
					cout << "Record# " << pos << ":" << endl << "Sold Price: " << sold_price << endl << "Shipping Charged: " << shipping_charged << endl  << "Item Cost: " << item_cost << endl << "Shipping Cost: " 
					<< shipping_cost << endl << "Number of Orders: " << num_of_orders << endl << "Seller Level: " << seller_level << endl << "Payment Processing: " << payment_processing 
					<< endl << "Overseas: " << overseas << endl << "Shipping Included: " << shipping_in_sales_tax << endl << "Promoted Ad Rate: " << promoted_ad_rate << endl <<
					"Donated to Charity(%): " << donated_to_charity << endl << "Item Category: " << item_category << endl << "Profit($): " << profit << endl << "Sales Tax($): " << 
					sales_tax << endl << "Fee($): " << fee << endl << "Date and Time: " << date << endl << endl;
					pos++;
					date.clear();
					}
				file.close();
			}
			catch(int exp){
				cout << "Failed to access the file or the file does not exist!" << endl;
			}
		}
};
class Menu{  //driver class to test run the calculator
	Calculator* calculator;  //class association
	Filing filing;
	
	private:
		void calculateFee(){
			float sold_price;
			float shipping_charged;
			float item_cost;
			float shipping_cost;
			long num_of_orders;
			string seller_level;
			string payment_processing;
			bool overseas;
			bool shipping_in_sales_tax;
			float promoted_ad_rate;
			float donated_to_charity;
			string item_category;
			cout << "Enter Sold Price($): ";
			cin >> sold_price;
			cout << "Enter Shipping Charged($): ";
			cin >> shipping_charged;
			cout << "Enter Item Cost($): ";
			cin >> item_cost;
			cout << "Enter Shipping Cost($): ";
			cin >> shipping_cost;
			cout << "Enter Number of Orders: ";
			cin >> num_of_orders;
			cout << "Enter Seller Level(top, above, below): ";
			fflush(stdin);
			getline(cin, seller_level);
			cout << "Enter Payment Processing(PayPal, Ebay): ";
			fflush(stdin);
			getline(cin, payment_processing);
			cout << "Is this an overseas sale? (y/n): ";
			char ch;
			cin >> ch;
			if(ch == 'y' || 'Y'){
				overseas = true;
			}else{
				overseas = false;
			}
			cout << "Is Shipping included in Sales Tax? (y/n): ";
			cin >> ch;
			if(ch == 'y' || ch == 'Y'){
				shipping_in_sales_tax = true;
			}else{
				shipping_in_sales_tax = false;
			}
			cout << "Enter Promoted Ad Rate(%): ";
			cin >> promoted_ad_rate;
			cout << "Enter Donation to Charity(%): ";
			cin >> donated_to_charity;
			cout << "Enter Item Category(Electronics, Art, Clothes, etc): ";
			fflush(stdin);
			getline(cin, item_category);
			calculator = new Calculator(sold_price, shipping_charged, item_cost, shipping_cost, num_of_orders, seller_level, payment_processing,
			overseas, shipping_in_sales_tax, promoted_ad_rate, donated_to_charity, item_category);
			calculator->calculate();
			filing.write(sold_price, shipping_charged, item_cost, shipping_cost, num_of_orders, seller_level, payment_processing,
			overseas, shipping_in_sales_tax, promoted_ad_rate, donated_to_charity, item_category, calculator->getProfit(), calculator->getSalesTax(), calculator->getFee());
		}
	public:
		Menu(){
			
		}
		void show(){
			cout << "\nWelcome to Shipping Calculator!\n\nEnter the option number.\n1. Press '1' to calculate Fee.\n2. Press '2' to show all previous records.\n3. Press any other key to exit the applicaion.";
			int option;
			cin >> option;
			switch(option){
				case 1:
					{
						calculateFee();
						cout << "Profit($): " << calculator->getProfit() << endl;
						cout << "Sales Tax($): " << calculator->getSalesTax() << endl;
						cout << "Fee($): " << calculator->getFee() << endl;
						break;
					}
				case 2:
					{
						filing.read();
						break;
					}
				default:
					cout << "Exiting the application...";
					sleep(2);
					exit(0);
			}
		}
};

int main(){  //main method to trigger the code
	Menu menu;
	while(1)
		menu.show();   //show the menu structure
}
