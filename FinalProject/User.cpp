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

unordered_map<string, string> User::usersdata;
vector<string> User::allUsersName;
vector<RequestMessage> User::pendingRequests;
unordered_map<string, userInfoo>User::userInfo;


//////////////////////////////getPassword:///////////////////////////////
string User::getPassword() {
	string password;
	char ch;

	cout << "Enter Password: ";

	while ((ch = _getch()) != '\r') { // '\r' is Enter key
		if (ch == '\b') { // Backspace
			if (!password.empty()) {
				cout << "\b \b"; // Erase the last asterisk
				password.pop_back();
			}
		}
		else {
			password += ch;
			cout << '*'; // Display asterisk
		}

	}
	cout << endl;

	return password;
}


//////////////////////////////////////////////////////////////////////////////////
void User::Register() {
	string userName;
	string userPassword;
	bool exist = false;
	cout << "Enter Username : \n";
	cin >> userName;
	for (int i = 0; i < allUsersName.size(); i++) {
		if (allUsersName[i] == userName)
			exist = true;
	}
	if (exist) {
		cout << "This UserName is unavailable , Try another one please : " << endl;
		Register();
	}
	else {
		userPassword = getPassword();
		allUsersName.push_back(userName);
		UserInfo newUser;
		newUser.userName = userName;
		newUser.userPassword = userPassword;
		usersdata.insert({ userName,userPassword });
		cout << "*** Your Account has been created Successfully ***" << endl;
		cout << "Enter your current balance :" << endl;
		cin >> newUser.currentBalance;
		userInfoo user;
		user.userName = userName;
		user.currentBalance = newUser.currentBalance;
		userInfo[userName] = user;
	}
}


//////////////////////////////////////////////////////////////////////////////////////

void User::ReadUsersNames() {   //read only usersnames from file for Register function
	ifstream username("usersnames.txt");
	if (username.is_open()) {
		string line;
		while (getline(username, line)) {
			allUsersName.push_back(line);
		}
		username.close();
	}
	else {
		cout << " FILE IS NOT FOUND";
	}
}

///////////////////////////////////////////////////////////////////////////////
void User::ReadUsernameAndPass() {
	ifstream userinfo("usernameandpass.txt");

	if (userinfo.is_open()) {
		string line;
		while (getline(userinfo, line)) {
			// Find the position of the first space (separating username and password)
			size_t firstSpacePos = line.find(' ');
			// Find the position of the second space (separating password and balance)
			size_t secondSpacePos = line.find(' ', firstSpacePos + 1);

			if (firstSpacePos != string::npos && secondSpacePos != string::npos) {
				// Extract username, password, and balance
				string userName = line.substr(0, firstSpacePos);
				string userPassword = line.substr(firstSpacePos + 1, secondSpacePos - firstSpacePos - 1);
				double userBalance = stod(line.substr(secondSpacePos + 1)); // Convert balance to double

				// Insert into the usersdata map (for username-password)
				usersdata[userName] = userPassword;

				// Update userInfo map with the new user information
				userInfoo user;
				user.userName = userName;
				user.currentBalance = userBalance;
				userInfo[userName] = user; // Store the new user information
			}
		}
		userinfo.close(); // Close the file stream
	}
	else {
		cout << "FILE IS NOT FOUND" << endl;
	}
}



void User::WriteUsernameAndPass() { // write username and password in file to register the new account(if the username is unique)
	ofstream userinfo("usernameandpass.txt");
	if (userinfo.is_open()) {
		for (auto& pair : usersdata) {

			const string& username = pair.first;
			const string& password = pair.second;
			double balance = userInfo[username].currentBalance;

			// Write the username, password, and balance separated by spaces
			userinfo << username << " " << password << " " << balance << endl;
		}
		userinfo.close();
	}
	else {
		cout << "FILE IS NOT FOUND";
	}
}

void User::WriteUserNames() { //write only usersnames into file for Register function
	ofstream username("usersnames.txt");
	if (username.is_open()) {
		for (string item : allUsersName) {
			username << item << endl;
		}
		username.close();
	}
	else {
		cout << "FILE IS NOT FOUND";
	}
}


void User::UserLogIn() {
	string userName;
	string userPassword;
	bool flag = false;
	cout << "Enter The Username : " << endl;
	cin >> userName;
	userPassword = getPassword();
	for (auto& pair : usersdata) {
		if (userName == pair.first && userPassword == pair.second) {
			flag = true;
			break;
		}
	}
	if (flag) {
		cout << "*** Login Done Successfully ***" << endl;
		userInfo[userName].loggedInUser = userName;
		//displayMessages(userName);
		approveRequest(userName);
	}
	else {
		int choice;
		cout << "Your Account Cannot be Found !!\n";
		cout << "press 1: To Try Again\n";
		cout << "press 2: To Create New Account\n";
		cin >> choice;
		if (choice == 1) {
			UserLogIn();
		}
		else if (choice == 2) {
			Register();
		}
		else {
			cout << "Invalid Choice , Please Try Again \n";
			UserLogIn();
		}
	}
}



void User::user_Services()
{
	transaction tr;
	//system("CLS");
	cout << "welcome to the main page choose the number of the choice you want: \n";
	cout << "1.If you want to send money to someone .\n";
	cout << "2.If you want to request money from someone .\n";
	cout << "3.If you want to edit any of your information.\n";
	cout << "4.If you want to see your current balance . \n";
	cout << "6.See your transactions history . \n";
	cout << "7.If you want to log out from your account . \n";

	char choice;
	cin >> choice;
	if (choice == '1')
	{
		sendMoney();
	}
	else if (choice == '2')
	{
		requestMoney();
	}
	else if (choice == '3')
	{
		UserProfileEdit();
	}
	else if (choice == '4')
	{
		view_Current_Balance();


	}
	else if (choice == '6')
	{
		//tr.display_user_Transictions();
	}
	else if (choice == '7')
	{
		for (string user : allUsersName)
		{
			if (user == userInfo[user].loggedInUser) {
				userInfo[user].loggedInUser = "";
			}
		}

		system("CLS");
		cout << "Log Out is done successfuly . \n";
		welcome();
	}
	else
	{
		cout << "Invalid choice , Please Try Again . \n"; \
	}

	user_Services();
}




///////////////////////Hafsa's Functions///////////////////////////

/////////////////////////////////sendMoney function//////////////////////////////
void User::sendMoney() {
	string senderUsername, recipientUsername;
	double amount;
	transaction ts;

	for (string user : allUsersName)
	{
		if (user == userInfo[user].loggedInUser) {
			senderUsername = user;
		}
	}

	if (userInfo[senderUsername].state == false) {
		cout << "User account is suspended by the admin !" << endl;
		user_Services();
	}
	else {
		cout << "Enter the recipient username:";
		while (true)
		{
			cin >> recipientUsername;
			if (usersdata.find(recipientUsername) != usersdata.end() && recipientUsername != userInfo[senderUsername].loggedInUser)
			{
				break;
			}
			else
			{
				cout << "Error: Invalid Recipient username. Please enter a valid one: " << endl;
			}
		}
		ts.recipient = recipientUsername;
		userInfoo& sender = userInfo[senderUsername];
		userInfoo& recipient = userInfo[recipientUsername];
		double senderBalance = sender.currentBalance;

		// Get current time
		time_t now = time(0);
		tm* localTime = localtime(&now);

		// Format date into a string
		stringstream date_ss;
		date_ss << put_time(localTime, "%Y-%m-%d"); // Format string as "YYYY-MM-DD"
		ts.formatted_date = date_ss.str();

		// Format time into a string
		stringstream time_ss;
		time_ss << put_time(localTime, "%H:%M:%S"); // Format string as "HH:MM:SS"
		ts.formatted_time = time_ss.str();

		// Now, 'formattedDate' contains the date and 'formattedTime' contains the time


		cout << "Enter the amount of money you want to send to " << recipientUsername << endl;
		cin >> amount;

		// Check if the sender has enough balance to send the specified amount
		if (senderBalance < amount) {
			cout << "Error: Your current balance is not suffiecient right now" << endl;
			user_Services();
		}
		else
		{
			sender.currentBalance -= amount;
			recipient.currentBalance += amount;
			ts.amount = amount;
			ts.transaction_history[senderUsername] = ts; // this line to go to save the information in the data structure
			
			//ts.writeTransactions();
			cout << "Transaction successful. " << senderUsername << " sent " << amount
				<< " to " << recipientUsername << "." << endl;
			cout << "Your current balance is: " << sender.currentBalance << endl;
		}
		while (true)
		{
			cout << "choose 1 if you want to try to send money again.\n";
			cout << "choose 2 if you want to go to the main page. \n";
			char letter;
			cin >> letter;
			if (letter == '1')
				sendMoney();
			else if (letter == '2')
				user_Services();
			else
				cout << "Invalid choice , please choose again. \n";
		}


	}

}

///////////////////////////requestMoney function////////////////////////////////////
void User::requestMoney() {
	string requestor, requestedFrom;
	double amount;
	transaction ts;

	for (string user : allUsersName)
	{
		if (user == userInfo[user].loggedInUser) {
			requestor = user;
		}
	}

	if (userInfo[requestor].state == false) {
		cout << "User account is suspended!" << endl;
		user_Services();//return function ?
	}
	else {

		cout << "Enter the person username you want to request money from:";
		while (true)
		{
			cin >> requestedFrom;
			if (usersdata.find(requestedFrom) != usersdata.end() && userInfo[requestor].loggedInUser != requestedFrom)
			{
				break;
			}
			else
			{
				cout << "Error:Invalid username. please enter a valid one:" << endl;
			}
		}
		ts.recipient = requestedFrom;
		cout << "Enter the amount of money you want to request:";
		cin >> amount;
		if (amount <= 0)
		{
			cout << "Error: The amount must be greater than zero." << endl;
		}
		ts.amount = amount;


		// Get current time
		time_t now = time(0);
		tm* localTime = localtime(&now);

		// Format date into a string
		stringstream date_ss;
		date_ss << put_time(localTime, "%Y-%m-%d"); // Format string as "YYYY-MM-DD"
		ts.formatted_date = date_ss.str();

		// Format time into a string
		stringstream time_ss;
		time_ss << put_time(localTime, "%H:%M:%S"); // Format string as "HH:MM:SS"
		ts.formatted_time = time_ss.str();
		ts.transaction_history[requestor] = ts; // this line to go to save the information in the data structure
	
		// Create and store a request message
		RequestMessage newRequest = { requestor, requestedFrom, amount };
		pendingRequests.push_back(newRequest);

		while (true)
		{
			cout << "choose 1 if you want to try to request  money again.\n";
			cout << "choose 2 if you want to go to the main page. \n";
			char letter;
			cin >> letter;
			if (letter == '1')
				requestMoney();
			else if (letter == '2')
				user_Services();
			else
				cout << "Invalid choice , please choose again. \n";
		}
	}
}


/////////////////////save pending requests vector to the file///////////////////
void User::SavePendingRequests(const string& filename) {
	ofstream outfile(filename);
	if (outfile.is_open()) {
		for (const auto& request : pendingRequests) {
			if (request.approved == "suspended") {  // Only save the suspended requests
				outfile << request.requestor << " "
					<< request.recipient << " "
					<< request.amount << " "
					<< request.approved <<
					endl;
			}
		}
		outfile.close();
	}
	else {
		cout << "Error: Could not open file to save pending requests." << endl;
	}
}

////////////////////////////read pending requests vector from the file///////////////////

void User::LoadPendingRequests(const string& filename, vector<RequestMessage>& pendingRequests) {
	ifstream infile(filename);  // Open the file
	if (!infile.is_open()) {
		cout << "Error: Could not open file to load pending requests." << endl;
		return;
	}

	pendingRequests.clear();  // Clear the current list of pending requests

	string requestor;
	string recipient;
	double amount;
	string approvalStatus;

	while (infile >> requestor >> recipient >> amount >> approvalStatus) {
		// Determine the approval status


		// Create a new RequestMessage object and add it to the vector if not approved or denied
		if (approvalStatus == "suspended") {
			RequestMessage request = { requestor, recipient, amount, approvalStatus };
			pendingRequests.push_back(request);
		}

	}

	infile.close();  // Close the file
}


//////////////////////////sendMessage function///////////////////////////
void User::sendMessage(string& userName, string& content) { //& is for updating the original data in the file
	//int messageID = ++userInfo[userName].nextMessageID;
	Message newMessage = { content };
	userInfo[userName].messages.push(newMessage);
}


////////////////////////////displayMessagesFunction///////////////////////
/*void User::displayMessages(string& userName) {

	//loadMessagesFromFile(userInfo[userName].messages); // Load messages from file

	 //auto& user = it->second; // Get the user's info

	cout << "Messages for " << userName << ":\n";
	if (userInfo[userName].messages.empty()) {
		cout << "You have no messages." << endl;
	}
	else {
		int messageId = 1;
		for (Message& msg : userInfo[userName].messages) {
			cout << messageId++ << "- " << msg.content << "\n";
			msg.display = "seen";
		}
	}
}*/

////////////////////////////////approveFunction/////////////////////////////
void User::approveRequest(string requestedFrom) {
	//LoadPendingRequests("pending_requests.txt", pendingRequests);

	if (pendingRequests.empty()) { //first check if the user has pending requests
		cout << "No pending requests to approve." << endl;
		return;
	}


	// Loop through pending requests to find those for the specified user
	for (auto& request : pendingRequests) //& is to change the original address and after exitting the function it's still changed
	{
		if (request.recipient == requestedFrom && request.recipient == userInfo[requestedFrom].loggedInUser && request.approved != "denied")
		{
			string messageContent;
			char response;
			cout << request.requestor << " requests " << request.amount
				<< " LE from you. Do you want to approve? (y/n): ";

			while (true) {
				cin >> response;
				if (response == 'y' || response == 'Y' || response == 'n' || response == 'N') {
					break;
				}
				else {
					cout << "Invalid input. Please enter 'y' for yes or 'n' for no.";
				}
			}

			if (response == 'y' || response == 'Y')
			{
				if (userInfo[requestedFrom].currentBalance >= request.amount)
				{
					userInfo[requestedFrom].currentBalance -= request.amount;
					userInfo[request.requestor].currentBalance += request.amount;
					//WriteUsernameAndPass();
					request.approved = "approved";
					messageContent = "Your request from " + request.recipient + " for " + to_string(request.amount) + " LE has been approved.";
					sendMessage(request.requestor, messageContent);

					cout << "Request approved. " << request.amount << " LE transferred to "
						<< request.requestor << "." << endl;
				}
				else {
					cout << "Insufficient funds to fulfill the request" << endl;
					request.approved = "suspended";
				}
			}
			else if (response == 'n' || response == 'N') {
				messageContent = "Your request from " + request.recipient + " for " + to_string(request.amount) + " LE has been denied.";
				sendMessage(request.requestor, messageContent);
				request.approved = "denied";
			}
		}
	}
	//SavePendingRequests("pending_requests.txt"); //lazm b3d el approve w request
}


//he does not update it in the file
void User::UserProfileEdit() {
	string oldUserName, oldPassword, newUserName, newPassword;
	int choice;
	cout << "Enter The Current Username: ";
	cin >> oldUserName;
	cout << "Enter The Current Password: ";
	oldPassword = getPassword();
	// Validate user credentials
	auto it = usersdata.find(oldUserName);
	if (it == usersdata.end() || it->second != oldPassword)
	{
		cout << "Invalid Username Or Password. Please Try Again.\n";
		UserProfileEdit();
		return;
	}
	cout << "1. Edit Username\n";
	cout << "2. Edit Password\n";
	cout << "3. Edit Both Username And Password\n";
	cout << "Enter Your Choice: ";
	cin >> choice;
	if (cin.fail()) {
		cout << "Invalid Input. Please Enter A Number.\n";
		cin.clear(); // Clear error flags
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
		UserProfileEdit(); // Restart the function
		return;
	}
	switch (choice)
	{
	case 1: // Edit username
	{
		cout << "Enter The New Username: ";
		cin >> newUserName;
		// Check if the new username already exists
		if (usersdata.find(newUserName) != usersdata.end())
		{
			cout << "Username Already Exists. Please Retry The Process.\n";
			UserProfileEdit();
			return; // exit the function
		}
		// Update username in usersdata and userInfo
		string oldPassword = it->second;
		usersdata.erase(it); // Remove old username
		usersdata[newUserName] = oldPassword; // Add new username
		// Update userInfo map and allUsersName vector
		auto userIt = userInfo.find(oldUserName);
		if (userIt != userInfo.end())
		{
			userInfo[newUserName] = userIt->second;
			userInfo.erase(oldUserName); // Erase old entry
			// Update allUsersName
			for (auto& uname : allUsersName)
			{
				if (uname == oldUserName)
				{
					uname = newUserName;
					break;
				}
			}
		}
		cout << "Username Updated Successfully.\n";
		return;
	}
	break;
	case 2: // Edit password
	{
		cout << "Enter The New Password: ";
		newPassword = getPassword();

		// Update the password in usersdata
		usersdata[oldUserName] = newPassword;
		cout << "Password Updated Successfully.\n";
		return;
	}
	break;
	case 3: // Edit both username and password
	{
		cout << "Enter The New Username: ";
		cin >> newUserName;
		// Check if the new username already exists
		if (usersdata.find(newUserName) != usersdata.end())
		{
			cout << "Username Already Exists , Please Retry Again.\n";
			UserProfileEdit();
			return; // exit the function
		}
		cout << "Enter The New Password: ";
		newPassword = getPassword();
		// Update username and password without affecting balance or other data
		string oldPassword = usersdata[oldUserName];
		usersdata.erase(oldUserName); // Remove old entry
		usersdata[newUserName] = newPassword; // Add new username
		// Update userInfo and allUsersName
		auto userIt = userInfo.find(oldUserName);
		if (userIt != userInfo.end())
		{
			auto userCopy = userIt->second; // Copy user data
			userCopy.userName = newUserName; // Change the username
			userInfo[newUserName] = userCopy; // Add to map with new key
			userInfo.erase(oldUserName); // Erase old entry

			// Update allUsersName
			for (auto& uname : allUsersName)
			{
				if (uname == oldUserName)
				{
					uname = newUserName;
					break;
				}
			}
		}
		cout << "Username And Password Updated Successfully.\n";
		return;
	}
	break;

	}
}

void User::view_Current_Balance()
{

	for (string user : allUsersName)
	{
		if (user == userInfo[user].loggedInUser) {
			cout << "Your current balance is: " << userInfo[user].currentBalance << "\n";
		}
	}


}

void User::welcome()
{
	Admin admin;
	cout << "enter the number of the option you need : \n";
	cout << "1.Log in as an admin to your account \n";
	cout << "2.Log in as an user to your account \n";
	cout << "3.Create new account \n";
	cout << "4.Exist from the system \n";
	int answer;
	cin >> answer;
	if (cin.fail()) {
		cout << "Invalid Input. Please Enter A Number.\n";
		cin.clear(); // Clear error flags
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
		welcome(); // Restart the function
		return;
	}

	if (answer == 1)
	{
		admin.AdminLogIN();

	}
	else if (answer ==2)
	{
		UserLogIn();
		user_Services();
	}
	else if (answer ==3)
	{
		Register();
		user_Services();
	}
	else if (answer == 4)
	{
		exitFromSystem();
	}
	else
	{
		cout << "Invalid choice ,please choose again\n";
		welcome();
	}

}

void User::exitFromSystem() {
	transaction tr;
	WriteUsernameAndPass();
	WriteUserNames();
	tr.writeTransactions();
	SavePendingRequests("pending_requests.txt");
	cout << "^^ THANK YOU FOR USING OUR DIGITAL WALLET SYSTEM ^^\n";
	exit(0);
}
















