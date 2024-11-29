#pragma once
#include <string>
#include<unordered_map>
#include<iostream>
#include<queue>
#include<vector>
#include"Admin.h"
#include"transaction.h"
using namespace std;
struct UserInfo
{
	string userName;
	string userPassword;
	double currentBalance = 0.0; 
};

struct Message {
	//int messagedID;
	string content;
	string display = "unseen";
};

struct userInfoo
{
	string userName;
	queue<Message> messages;
	double currentBalance = 0.0;
	string loggedInUser = "";
	bool state = true; //this account is not suspended
};

struct RequestMessage {
	string requestor;
	string recipient;
	double amount;
	string approved = "suspended";
};


class User
{
public:
	static unordered_map<string, string>usersdata; //contains useresnames and passwords
	static unordered_map<string, userInfoo>userInfo;
	static vector<string>allUsersName; // contains usersnames
	static vector<RequestMessage> pendingRequests;


	///////////////functions://////////////
	void Register();
	void ReadUsersNames();// read only usersnames from file
	void WriteUserNames();//write only usersnames into file
	void ReadUsernameAndPass();// read username and password from file
	void WriteUsernameAndPass();// write username and password in file
	void UserLogIn();

	string getPassword();
	void sendMoney();
	void requestMoney();
	void sendMessage(string& userName, string& content);
	void displayMessages(string&);
	void approveRequest(string);
	void SavePendingRequests(const string& filename);
	void LoadPendingRequests(const string& filename, vector<RequestMessage>&);
	
	void UserProfileEdit();
	void view_Current_Balance();

	void user_Services();

	void welcome();
	void exitFromSystem();
};

