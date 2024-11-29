#pragma once
#include "transaction.h"
#include "User.h"
#include<algorithm>
#include<iostream>
#include <string>
#include<unordered_map>
#include<queue>
#include<vector>

using namespace std;

struct AdminInfo {
	string AdminName = "admin";
	string AdminPass = "2024";
};


class Admin
{

public:

	void AdminLogIN();
	void addUser();
	void deleteUser();
	void editUser();
	void suspendUser();
	void AdminMenu();
	void displayUsersInfo();
};

