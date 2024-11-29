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




void transaction::writeTransactions() {
	ofstream trans("transaction_history.txt", ios::app); // Open file in append mode

	if (trans.is_open()) {
		for (const auto& pair : transaction_history) {
			const string& username = pair.first;
			const transaction& transac = pair.second;

			// Write the transaction details to the file
			trans << username << " " << transac.amount << " " << transac.recipient << " " << transac.formatted_date << " " << transac.formatted_time << endl;
		}
		trans.close();
		cout << "Transactions written to file successfully." << endl;
	}
	else {
		cout << "Error: Unable to open transaction_history.txt for writing." << endl;
	}
}

void transaction::display_Allusers_Transaction() // For admin
{

	ifstream trans("transaction_history.txt");
	if (trans.is_open()) {
		string senderUsername, recipientUsername, formattedDate, formattedTime;
		double amount;
		while (trans >> senderUsername >> amount >> recipientUsername >> formattedDate >> formattedTime) {
			// Display transaction details
			cout << "This is the transaction history for all users in this system. \n";
			cout << "Sender: " << senderUsername << ", Recipient: " << recipientUsername
				<< ", Amount: " << amount << ", Date: " << formattedDate << ", Time: " << formattedTime << endl;
		}
		trans.close();
	}
	else {
		cout << "Error: Unable to open transaction_history.txt for reading." << endl;
	}
}


void transaction::display_user_Transictions()
{
	for (string user : User::allUsersName)
	{
		if (user == User::userInfo[user].loggedInUser) {
			display_User_Transactions(user);
		}
	}
}

void transaction::display_User_Transactions(const string& username) // for the user which logged in in our system he can see its transaction history
{
	ifstream trans("transaction_history.txt");
	if (trans.is_open()) {
		string senderUsername, recipientUsername, formattedDate, formattedTime;
		double amount;
		bool found = false; // Flag to track if any transactions were found for the user

		while (trans >> senderUsername >> amount >> recipientUsername >> formattedDate >> formattedTime) {
			if (senderUsername == username || recipientUsername == username) {
				// Display transaction details if sender or recipient matches the username
				cout << "Sender: " << senderUsername << ", Recipient: " << recipientUsername
					<< ", Amount: " << amount << ", Date: " << formattedDate << ", Time: " << formattedTime << endl;
				found = true; // Set flag to true indicating at least one transaction found
			}
		}

		if (!found) {
			cout << "No transactions found for user: " << username << endl;
		}

		trans.close();
	}
	else {
		cout << "Error: Unable to open transaction_history.txt for reading." << endl;
	}
}




