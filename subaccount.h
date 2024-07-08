#pragma once
#include <string>
using namespace std;
class SubAccount {
protected:
	string memName;//to show who each sub account belongs to
	double money, max;
	int type;
	string name;
	bool locked = false;
	bool closed = false;
public:
	SubAccount();
	SubAccount(string memName, int money, string name, int type/*1 for save 2 for check*/);
	int getType();
	string getName();
	double getBalance();
	void withdraw(int change);
	void deposit(int change);
	void setmax(int max);
	double getMax();
	bool isMax(int withdraw);
	void setLock(string ul);
	void lock();
	void unlock();
	bool isLocked();
	bool isClosed();
	void close();
	string getMem();
};