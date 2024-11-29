#pragma once
#include<iostream>
using namespace std;
#include <string>
#include<unordered_map>
#include<queue>
#include"User.h"
#include"Admin.h"
#include<vector>
#include<string>
class transaction
{
public:
	//we will not need to nake attribute for the main user because he will be the key
	double amount = 0.0;
	string recipient = "";
	string formatted_date = "";
	string formatted_time = "";
	unordered_map<string, transaction>transaction_history;

	void display_user_Transictions();
	void display_User_Transactions(const string& username);

	void display_Allusers_Transaction();  //display all transaction for admin we will call it in the admin class
	void writeTransactions();
};
