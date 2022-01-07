// Nayli 4706 OOP2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	char name[30], phonenumber[10], address[100];
	char pizza1[] = "Chicken BBQ", pizza2[] = "Peri Peri";
	char roll1[] = "Chicken Mayo Roll", roll2[] = "Beef Peperoni Roll";
	char bur1[] = "Beef Burger", bur2[] = "Chicken Burger", bur3[] = "Lamb Burger";
	char sand1[] = "Crispy Chicken", sand2[] = "Tuna Sandwich";
	char ric1[] = "Butter Chicken Rice", ric2[] = "Sweet and Sour Rice", ric3[] = "Chicken Rice", gotostart;
	int  pchoice, pchoice1;
	double choice = 0, quantity;
	char h;																		//This coding is use to show the food flavors according to the correct data type.

	system("CLS");																//This code will clear the text before it and show only the next content.
	cout << "\t\t\t----------Z Food Corner-----------\n\n";						//This code will show the restaurant's name.
	cout << "Please Enter Your Name: ";											//This code will allow you to enter a text like "please enter your name".
	cin.getline(name, 20);														//This code will give the limit of words you can give.
	cout << "Please Enter Your Phone number: ";									//This code will allow you to enter a text like "please enter your phone number".
	cin.getline(phonenumber, 10);												//This code will give the limit of number you can type.
	cout << "Please Enter Your Address: ";										//This code will allow you to enter a text like "please enter your address".
	cin.getline(address, 100);													//It will show the limit of word you can type.

	cout << "Hello " << name << "\n\nWhat would you like to order?\n\n";		//This code will allow you to give and show a text when you run your code.
beginning:

	cout << "\t\t\t\t--------Menu--------\n\n";									//This code will allow you to give a title in your coding.

	cout << "1) Pizzas\n";
	cout << "2) Burgers\n";
	cout << "3) Sandwich\n";
	cout << "4) Rolls\n";
	cout << "5) Rice\n\n";
	cout << "6) Help on ordering\n";
	cout << "7) Feedbacks\n";
	cout << "8) Context\n";														//Here are varieties of foods and also help function you can choose and enter the number.
	cout << "\nPlease Enter your Choice: ";										//This will allow you to insert a text in your coding.
	cin >> choice;																//Your choice will showup here.
	h = choice;


	if (choice == 1)															//This will showup if you choose to order a pizza.
	{
		cout << "\n1) " << pizza1 << "\n";										//This will allow you to type in the flavors of the pizza
		cout << "2) " << pizza2 << "\n";
		cout << "\nPlease Enter which Flavour would you like to have?:";		//This code will show a text in your coding.
		cin >> pchoice;
		if (pchoice >= 1 && pchoice <= 3)										//This code will allow you to choose which choices you want to order.
		{
			cout << "\n1) Regular $19.90\n" << "2) Large $29.99\n";				//This code will give allow you to key in the different sizes with different price.
			cout << "\nChoose Size Please:";
			cin >> pchoice1;
			if (pchoice1 >= 1 && pchoice1 <= 3)									//This code will allow you to choose which choices you want to order.
				cout << "\nPlease Enter Quantity: ";
			cin >> quantity;													//This code will show the quantity you are ordering.
			switch (pchoice1)
			{
			case 1: choice = 19.90 * quantity;									//This code will calculate the total amount of your orders.
				break;

			case 2: choice = 29.99 * quantity;
				break;


			}
			system("CLS");
			switch (pchoice1)
			{
			case 1:																								//For this code, it is like a receipt which shows you the details of your orders.
				cout << "\t\t\t--------Your Order---------\n";													//This will give a title to it		
				cout << "" << quantity << " " << pizza1;														//This code will show the quantity and which flavour of pizza you are ordering.
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";		//This code will give you the estimate of time of delivery.
				cout << "\nName: " << name << "\n";																//This code will give your name.
				cout << "\nAddress: " << address << "\n";														//This code will give your address.
				cout << "\nPhone Number: " << phonenumber << "\n";												//This code will give your phone number
				cout << "\n\nThank you For Ordering From Z Food Corner\n";										//This message will give out the thank you message with the restaurant name in it.
				break;																							//This code means you are breaking the code or asking you to end this code.
			case 2:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << "  " << pizza2;
				cout << "\nYour Total Bill is " << choice << "\nYour Order Will be delivered in 40 Minutes";
				cout << "\nThank you For Ordering From Z Food Corner\n";
				break;

			}
			cout << "Would you like to order anything else? Y / N:";											//This code will ask you if you want to order anything else if yes then choose "Y" and if no choose "N".
			cin >> gotostart;																					//If you are choosing yes, this code will bring you to the start which is the menu section.
			if (gotostart == 'Y' || gotostart == 'y')															//This code will allow you give either capital or non-capital letter.
			{
				goto beginning;																					//This code will bring you to go to the beginning which is the menu section.
				//return 0; 
			}



		}

	}


	else if (choice == 2)
	{
		cout << "\n1) " << bur1 << "\n";
		cout << "2) " << bur2 << "\n";
		cout << "3) " << bur3 << "\n";
		cout << "\nPlease Enter which Flavour would you like to have?:";
		cin >> pchoice;
		if (pchoice >= 1 && pchoice <= 4)
		{
			cout << "\n1) Beef regular $3.50\n" << "2)Beef large $4.50\n" << "3)Chicken regular $3.00\n" << "4)Chicken large $4.00\n" << "5)Lamb regular $4.00\n" << "6)Lamb large $5.00\n";
			cout << "\n Choose size please:";
			cin >> pchoice1;
			if (pchoice1 >= 1 && pchoice1 <= 7)
				cout << "\nPlease Enter Quantity: ";
			cin >> quantity;
			switch (pchoice1)
			{
			case 1: choice = 3.50 * quantity;
				break;

			case 2: choice = 4.50 * quantity;
				break;

			case 3: choice = 3.00 * quantity;
				break;

			case 4: choice = 4.00 * quantity;
				break;

			case 5: choice = 4.00 * quantity;
				break;

			case 6: choice = 6.00 * quantity;
				break;

			}


			system("CLS");
			switch (pchoice1)																					//This code is used so that it can make a choice.
			{
			case 1:																								//This code is for the first burger flavour.	
				cout << "\t\t--------Your Order---------\n";													//This code will allow a text like "your order" show-up on your screen when you run your code.
				cout << "" << quantity << " " << bur1;															//Here it will show how many burger you are ordering.
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";		//This code will show you the total bill of your orders and the estimated time of delivery.
				cout << "\nThank you For Ordering From Z Food Corner\n";										//This code will show you a thank you message with your restaurant name in it.
				break;																							//This code will allow you to stop here or teminate the code immediately.
			case 2:																								//This code is for the second burger flavour.
				cout << "\t\t--------Your Order---------\n";													//This code will allow a text like "your order" show-up on your screen when you run your code.
				cout << "" << quantity << "  " << bur2;															//Here it will show how many burger you are ordering.
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";		//This code will show you the total bill of your orders and the estimated time of delivery.
				cout << "\nThank you For Ordering From Z Food Corner\n";										//This code will show you a thank you message with your restaurant name in it.
				break;																							//This code will allow you to stop here or teminate the code immediately.
			case 3:																								//This code is for the third burger flavour.
				cout << "\t\t--------Your Order---------\n";													//This code will allow a text like "your order" show-up on your screen when you run your code.
				cout << "" << quantity << " " << bur3;															//Here it will show how many burger you are ordering.
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";		//This code will show you the total bill of your orders and the estimated time of delivery.
				cout << "\nThank you For Ordering From Z Food Corner\n";										//This code will show you a thank you message with your restaurant name in it.
				break;																							//This code will allow you to stop here or teminate the code immediately.


			}
			cout << "\nWould you like to order anything else? Y / N:";											//This code will now ask you if you want to order anything else and the choices are given which is Y stands for yes and N stands for no.
			cin >> gotostart;																					//This code will allow you to go to the start page which is the menu part if you are choosing to order more foods.
			if (gotostart == 'Y' || gotostart == 'y')															//This code will allow you to use the capital and non-capital letter when choosing the 'yes' part.
			{
				goto beginning;																					//This code will bring you to the bginning part which is choosing the menu part.
				//return 0;
			}

		}
	}
	else if (choice == 3)
	{
		cout << "\n1  " << sand1 << "\n";
		cout << "2  " << sand2 << "\n";
		cout << "\nPlease Enter which Sandwich you would like to have?:";
		cin >> pchoice1;
		if (pchoice1 >= 1 && pchoice1 <= 3)
		{
			cout << "\n1 Crispy Chicken regular $3.00\n" << "2 Crispy Chicken Large $5.00\n" << "3 Tuna regular $4.00\n" << "4 Tuna large $6.00\n";
			cout << "\nChoose Size Please: ";
			cin >> pchoice1;
			if (pchoice1 >= 1 && pchoice1 <= 5)
				cout << "\nPlease Enter Quantity: ";
			cin >> quantity;
			switch (pchoice1)
			{
			case 1: choice = 3.00 * quantity;
				break;

			case 2: choice = 5.00 * quantity;
				break;

			case 3: choice = 4.00 * quantity;
				break;

			case 4: choice = 6.00 * quantity;
				break;
			}
			system("CLS");
			switch (pchoice1)
			{
			case 1:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << sand1;
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";
				cout << "\nThank you For Ordering From Z Food Corner\n";
				break;
			case 2:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << "  " << sand2;
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";
				cout << "\nThank you For Ordering From Z Food Corner\n";
				break;


			}
			cout << "Would you like to order anything else? Y / N:";
			cin >> gotostart;
			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				//return 0;
			}
		}
	}


	else if (choice == 4)
	{
		cout << "\n1 " << roll1 << "\n";
		cout << "2 " << roll2 << "\n";
		cout << "\nPlease Enter which you would like to have?: ";
		cin >> pchoice1;
		if (pchoice1 >= 1 && pchoice1 <= 3)
		{
			cout << "\n1 Chicken Mayo regular $3.00\n" << "2 Chicken Mayo large $4.00\n" << "3 Beef Peperoni regular $3.50\n" << "4 Beef Peperoni large $4.50\n";
			cout << "\nChoose Size Please:";
			cin >> pchoice1;
			if (pchoice1 >= 1 && pchoice1 <= 5)
				cout << "\nHow Much Rolls Do you want: ";
			cin >> quantity;
			switch (pchoice1)
			{
			case 1: choice = 3.00 * quantity;
				break;

			case 2: choice = 4.00 * quantity;
				break;

			case 3: choice = 3.50 * quantity;
				break;

			case 4: choice = 4.50 * quantity;
				break;

			}
			system("CLS");
			switch (pchoice1)																					//This code is used so that it can make a choice.
			{
			case 1:																								//This code is for the first rolls flavour.
				cout << "\t\t--------Your Order---------\n";													//This code will allow a text like "your order" show-up on your screen when you run your code.
				cout << "" << quantity << "" << roll1;															//Here it will show how many rolls you are ordering.
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";		//This code will show you the total bill of your orders and the estimated time of delivery.
				cout << "\nThank you For Ordering From Z Food Corner\n";										//This code will show you a thank you message with your restaurant name in it.
				break;																							//This code will allow you to stop here or teminate the code immediately.
			case 2:																								//This code is for the second rolls flavour.
				cout << "\t\t--------Your Order---------\n";													//This code will allow a text like "your order" show-up on your screen when you run your code.
				cout << "" << quantity << "" << roll2;															//Here it will show how many rolls you are ordering.
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";		//This code will show you the total bill of your orders and the estimated time of delivery.
				cout << "\nThank you For Ordering From Z Food Corner\n";										//This code will show you a thank you message with your restaurant name in it.
				break;																							//This code will allow you to stop here or teminate the code immediately.

			}
			cout << "Would you like to order anything else? Y / N:";
			cin >> gotostart;
			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				//return 0;

			}

		}
	}
	else if (choice == 5)
	{
		cout << "\n1 " << ric1 << " $5.00" << "\n";
		cout << "2 " << ric2 << " $5.00" << "\n";
		cout << "3 " << ric3 << " $5.00" << "\n";
		cout << "\nPlease Enter which rice you would like to have?:";
		cin >> pchoice1;
		if (pchoice1 >= 1 && pchoice1 <= 4)
		{
			cout << "\nPlease Enter Quantity: ";
			cin >> quantity;
			switch (pchoice1)
			{
			case 1: choice = 5.00 * quantity;
				break;

			case 2: choice = 5.00 * quantity;
				break;

			case 3: choice = 5.00 * quantity;
				break;

			}
			system("CLS");
			switch (pchoice1)
			{
			case 1:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << ric1;
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";
				cout << "\nThank you For Ordering From Z Food Corner\n";
				break;
			case 2:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << "  " << ric2;
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";
				cout << "\nThank you For Ordering From Z Food Corner\n";
				break;
			case 3:
				cout << "\t\t--------Your Order---------\n";
				cout << "" << quantity << " " << ric3;
				cout << "\nYour Total Bill is" << choice << "\nYour Order Will be delivered in 40 Minutes";
				cout << "\nThank you For Ordering From Z Food Corner\n";
				break;


			}
			{cout << "Would you like to order anything else? Y / N:";
			cin >> gotostart;
			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				//return 0;
			}
			}

		}
	}

	else if (choice == 6)

	{
		system("CLS");
		{cout << "\t\t\t\t--------Ways to order--------\n\n";
		cout << "1) You must enter correct name,phone number and most important is your address.\n";
		cout << "2) First you need to choose which food you want to order and enter te quantity.\n";
		cout << "3) If you want to order other food you can go back to the menu part and make another order.\n";
		cout << "4) The estimated time of delivery will be shown when you are done ordering the foods.\n";
		cout << "5) Payment can be made through online or you can give the delivery guy.\n\n";
		}
		{

			cout << "Please Select Right Option: \n";
			cout << "Would You like to Start the program again? Y / N: ";
			cin >> gotostart;

			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				//return 0;
			}
		}

	}

	else if (choice == 7)

	{
		system("CLS");
		{cout << "\t\t\t\t--------Feedbacks--------\n\n";

		cout << "To give us a feedbacks kindly click this email ZFoodCorner@gmail.com. Thank for ordering in our restaurant.\n";


		{

			cout << "Please Select Right Option: \n";
			cout << "Would You like to Start the program again? Y / N: ";
			cin >> gotostart;

			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				//return 0;
			}
		}
		}
	}
	else if (choice == 8)

	{
		system("CLS");
		{cout << "\t\t\t\t--------Context--------\n\n";

		cout << " Do contact us if you have further question, +673 8776655 or +673 8778989.\n";
		cout << " Follow our instagram page @Zfoodrestaurant.\n";
		cout << " Our facebook page @Zfood_restaurant.\n";

		}
		{

			cout << "Please Select Right Option: \n";
			cout << "Would You like to Start the program again? Y / N: ";
			cin >> gotostart;

			if (gotostart == 'Y' || gotostart == 'y')
			{
				goto beginning;
				//return 0;
			}
		}

	}


	else
	{
		system("CLS");
		cout << "Please Select Right Option: \n";
		cout << "Would You like to Start the program again? Y / N: ";
		cin >> gotostart;

		if (gotostart == 'Y' || gotostart == 'y')
		{
			goto beginning;
			//return 0;
		}
	}
}


