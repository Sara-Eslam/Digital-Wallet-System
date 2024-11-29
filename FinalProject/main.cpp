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
int main() {
	cout << "\t\t\t\*****************---------Welcome to our simple digital wallet system---------******************" << endl;


	User user;

	transaction tr;

	user.ReadUsernameAndPass();

	user.ReadUsersNames();

	tr.display_user_Transictions();

	user.LoadPendingRequests("pending_requests.txt", user.pendingRequests);

	user.welcome();

	return 0;
}
