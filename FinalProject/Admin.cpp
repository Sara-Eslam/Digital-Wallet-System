#pragma warning(disable : 4996)
#include<algorithm>
#include<unordered_map>
#include<iostream>
#include <sstream>
#include <string>
#include<fstream>
#include<vector>
#include<queue>
#include <conio.h>
#include "User.h"
#include "Admin.h"
#include "transaction.h"
#include <ctime>//for the date and the time
#include <iomanip> // For formatting date and time
using namespace std;



void Admin::AdminLogIN() {
	AdminInfo admindata;
	string userName;
	string userPassword;
	cout << "Enter The Admin Username : \n";
	cin >> userName;
	cout << "Enter The Password Of The Admin Account : \n";
	cin >> userPassword;
	if (userName == admindata.AdminName && userPassword == admindata.AdminPass) {
		cout << "*** Login Done Successfully ***" << endl;
	}
	else {
		cout << "Your Account Cannot be Found . \n";
		cout << "choose 1 if you want to try again. \n";
		cout << "choose 2 if you want to back for the welcome page . \n";
		char answer;
		cin >> answer;
		if (answer == '1')
			AdminLogIN();
		//else if (answer == '2')
			//welcome();
		else
		{
			cout << "Invalid Choice , please try again . \n ";
			AdminLogIN();
		}

	}
	AdminMenu();
}
 

void Admin::addUser() {
	string userName, userPassword;
	double balance;
	cout << "Enter the User Name" << endl;
	cin >> userName;
	cout << "Enter the User Password" << endl;
	cin >> userPassword; //we want to define the least number of password we must allow
	cout << "Enter the User Balance" << endl;
	cin >> balance;
	if (User::usersdata.find(userName) == User::usersdata.end()) {
		User::usersdata[userName] = userPassword;
		User::userInfo[userName].userName = userName;
		User::userInfo[userName].currentBalance = balance;
		User::allUsersName.push_back(userName);
		cout << "User " << userName << " created successfully!" << endl;
		//WriteUsernameAndPass();
		//WriteUserNames();
	}
	else {
		cout << "Username already exists. Please choose a different one." << endl;
	}
	while (true)
	{
		cout << "choose 1 if you want to add another user .\n";
		cout << "choose 2 if you want to back to the main page . \n";
		char choice;
		cin >> choice;
		if (choice == '1')
			addUser();
		else if (choice == '2')
			AdminMenu();
		else
			cout << "Invalid choice ,please choose again. \n";
	}
}

void Admin::deleteUser() {
	
	string userName;
	cout << "Enter the Username" << endl;
	cin >> userName;
	for (int i = 0; i < User::allUsersName.size(); i++) {
	   
		if (User::usersdata.find(userName) != User::usersdata.end()) {
			User::usersdata.erase(userName);
			User::userInfo.erase(userName);
			User::allUsersName.erase(remove(User::allUsersName.begin(), User::allUsersName.end(), userName), User::allUsersName.end());
			cout << "User " << userName << " deleted successfully!" << endl;
			//user.WriteUsernameAndPass();
			//WriteUserNames();
			break;
		}
		else {
			cout << "User " << userName << " does not exist." << endl;
		}
	}
	while (true)
	{
		cout << "choose 1 if you want to delete another user .\n";
		cout << "choose 2 if you want to back to the main page . \n";
		char choice;
		cin >> choice;
		if (choice == '1')
			deleteUser();
		else if (choice == '2')
			AdminMenu();
		else
			cout << "Invalid choice ,please choose again. \n";
	}

}

void Admin::editUser() {
	string userName, newPassword;
	double newBalance;
	int choicee;
	cout << "Enter the User Name" << endl;
	cin >> userName;
	cout << "\n Edit Menu: " << endl;
	cout << "1. Edit password" << endl;
	cout << "2. Edit Balance" << endl;
	cout << "3. Edit password & Balance" << endl;
	cin >> choicee;
	for (int i = 0; i < User::allUsersName.size(); i++) {
		if (User::usersdata.find(userName) != User::usersdata.end()) {//what if it equal equal to the end ?
			switch (choicee) {
			case 1:
			{
				cout << "Enter the new password" << endl;
				cin >> newPassword;
				User::usersdata[userName] = newPassword;
				cout << "User's password " << userName << " edited successfully!" << endl;
				//WriteUsernameAndPass();
				AdminMenu();
				break;
			}
			case 2:
			{
				while (true) {
					cout << "Enter the new Balance" << endl;
					cin >> newBalance;
					if (newBalance >= 0) {
						User::userInfo[userName].currentBalance = newBalance;
						cout << "User's balance " << userName << " edited successfully!" << endl;
						//WriteUsernameAndPass();
						break;
					}
					else
					{
						cout << "Invalid balance ,please enter available balance\n";

					}
				}
				AdminMenu();
				break;
			}
			case 3:
			{
				cout << "Enter the new password" << endl;
				cin >> newPassword;
				User::usersdata[userName] = newPassword;
				cout << "User's password " << userName << " edited successfully!" << endl;
				//WriteUsernameAndPass();
				while (true) {
					cout << "Enter the new Balance" << endl;
					cin >> newBalance;
					if (newBalance >= 0) {
						User::userInfo[userName].currentBalance = newBalance;
						cout << "User's balance " << userName << " edited successfully!" << endl;
						//WriteUsernameAndPass();
						break;
					}
					else
					{
						cout << "Invalid balance ,please enter available balance\n ";
					}
				}
				AdminMenu();
				break;
			}
			default:
			{
				cout << "User " << userName << " does not exist." << endl;
				AdminMenu();
				break;
			}
			}

		}
	}

}

void Admin::suspendUser() {
	string userName;
	cout << "Enter the username \n";
	cin >> userName;

	for (int i = 0; i < User::allUsersName.size(); i++) {
		if (User::usersdata.find(userName) != User::usersdata.end()) {
			User::userInfo[userName].state = false;
			cout << "This user account is suspended successfully" << endl;
			AdminMenu();
		}
		else {
			cout << "User " << userName << " does not exist." << endl;
		}

	}
	while (true)
	{
		cout << "choose 1 if you want to suspend another user .\n";
		cout << "choose 2 if you want to back to the main page . \n";
		char choice;
		cin >> choice;
		if (choice == '1')
			suspendUser();
		else if (choice == '2')
			AdminMenu();
		else
			cout << "Invalid choice ,please choose again. \n";
	}
}

void Admin::AdminMenu() {
	User user;
	transaction tr;
	int choice;
	cout << "\n Admin Menu:" << endl;
	cout << "1. Add User\n";
	cout << "2. Edit User\n";
	cout << "3. Delete User\n";
	cout << "4. Suspend User\n";
	cout << "5. View all transactions within the system\n";
	cout << "6. View all registered users in the system and all information about them\n";
	cout << "7. log out from admin account\n";
	cout << "Enter Your Choice: ";
	cin >> choice;
	if (cin.fail()) {
		cout << "Invalid input. Please enter a number.\n";
		cin.clear(); // Clear error flags
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
		AdminMenu(); // Restart the function
		return;
	}
	switch (choice)
	{
	case 1:
		addUser();
		AdminMenu();
		break;
	case 2:
		editUser();
		AdminMenu();
		break;
	case 3:
		deleteUser();
		AdminMenu();
		break;
	case 4:
		suspendUser();
		AdminMenu();
		break;
	case 5:
		//tr.display_Allusers_Transiction();
		AdminMenu();
		break;
	case 6:
		displayUsersInfo();
		AdminMenu();
		break;
	case 7:
		system("CLS");
		cout << "Log Out is done successfuly . \n";
		user.welcome();
		break;
	default:
		cout << "Invalid choice" << endl;
		break;
	}
}



void Admin::displayUsersInfo() {
	cout << "Registered Users:" << endl;
	for (int i = 0; i < User::allUsersName.size(); i++)//and transiction history for each user
	{
		cout << "Username: " << User::userInfo[User::allUsersName[i]].userName << endl;
		cout << "Current Balance: " << User::userInfo[User::allUsersName[i]].currentBalance << endl;
	}

}
