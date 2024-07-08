#pragma once
using namespace std;

class Bank; //forward definition

class MemberAccount {
protected:
	string first, last, ssn, memberAccNum;
	bool closed = false;
	int aggregate;//to sort memberAccounts based based on aggregated balances
public:
	MemberAccount();
	MemberAccount(string first, string last, string ssn, string memberAccNum);
	void close();
	bool isClosed();
	string getName();
	void setAgg(int agg);
	int getAgg();
	string getFullName();
	string getSSN();
};