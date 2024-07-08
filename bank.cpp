//Joanna Hughes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <windows.h>
#include "bank.h"
#include "memberaccount.h"
#include "subaccount.h"
using namespace std;

void color(int value) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}
/*1: Blue
2: Green
3: Cyan
4: Red
5: Purple
6: Yellow (Dark)
7: Default white
8: Gray/Grey
9: Bright blue
10: Brigth green
11: Bright cyan
12: Bright red
13: Pink/Magenta
14: Yellow
15: Bright white*/

Bank::Bank() { //default constructor
	name = "N/A";
	address = "N/A";
	workingHours = "N/A";
}
Bank::Bank(string name, string address, string workingHours) { //default constructor
	this->name = name;
	this->address = address;
	this->workingHours = workingHours;
}
bool compareSub(SubAccount a, SubAccount b) {//to compare and sort subAca
	return (a.getBalance() > b.getBalance());
}
bool compareMem(MemberAccount a, MemberAccount b) {//to compare and sort memAca
	return (a.getAgg() > b.getAgg());
}
void Bank::setSave() {
	SAV += 1;
}
int Bank::getSave() {
	return SAV;
}
void Bank::setCheck() {
	CHK += 1;
}
int Bank::getCheck() {
	return CHK;
}
int Bank::getNumBankAcc() {
	return bankAcc.size();
}
double Bank::aggregated(string name) {
	double total = 0;
	for (auto& i : subAccVec) {
		if (name == i.getMem()) {
			total += i.getBalance();
		}
	}
	return total;
}
void Bank::makeMemberAccount() {
	memberAccNum = "BNK" + to_string(num);
	string first, last, ssn;
	color(14);
	cout << "Enter the first name of the account holder: ";
	color(7);
	getline(cin, first);
	color(14);
	cout << "Enter the last name of the account holder: ";
	color(7);
	getline(cin, last);
	color(14);
	cout << "Enter the Social Security Number of the account holder: ";
	color(7);
	bool validssn = false;
	while (!validssn) {
		getline(cin, ssn);
		validssn = true;
		color(4);
		for (int i = 0; i < ssn.size(); i++) {
			if (ssn.size() != 11) {
				cout << "Invalid SSN. Format : 123-45-6789" << endl << "Re-enter SSN:";
				validssn = false;
				break;
			}
			if (i < 3 || (i > 3 && i < 6) || (i > 6 && i < 11)) {
				if (isdigit(ssn[i]) == false) {//checks if is a digit in correct location
					cout << "Invalid SSN. Format : 123-45-6789" << endl << "Re-enter SSN:";
					validssn = false;
					break;
				}
			}
			if (i == 3 || i == 6) {
				if (ssn[i] != '-') {//checks dashes
					cout << "Invalid SSN. Format : 123-45-6789" << endl << "Re-enter SSN:";
					validssn = false;
					break;
				}
			}
		}
	}
	color(4);
	cout << endl << "- A new bank account " << memberAccNum << " was successfully created. -" << endl << endl;
	MemberAccount memberAccount = MemberAccount(first, last, ssn, memberAccNum);
	bankAcc.push_back(memberAccount);
	num++;
	accountOptions(memberAccount);
}
void Bank::close(string acc) {
	if (searchMembers(acc) != -1) {
		MemberAccount& mem = returnBankAcc(searchMembers(acc));
		mem.close();
	}
	else {
		cout << acc << "does not exist." << endl;
	}
}
void Bank::addSubAcc(SubAccount acc) {
	subAccVec.push_back(acc);
}
int Bank::searchSubVec(string search) {
	int location = 0;
	for (auto& i : subAccVec) {
		if (i.getName() == search) {
			return location;
		}
		location++;
	}
	return -1;
}
SubAccount& Bank::returnSubAcc(int location) {
	return subAccVec.at(location);
}
int Bank::searchMembers(string search) {
	int location = 0;
	for (auto& i : bankAcc) {
		if (i.getName() == search) {
			return location;
		}
		location++;
	}
	return -1;
}
MemberAccount& Bank::returnBankAcc(int location) {
	return bankAcc.at(location);
}
void Bank::accountOptions(MemberAccount mem) {//services available for their account
	string selection;
	do {//loops until exited
		color(2);
		cout << "Eligiable services for Bank Account " << memberAccNum << endl;
		cout << "	S -- Open Saving Sub-Account" << endl;
		cout << "	C -- Open Checking Sub-Account" << endl;
		cout << "	M -- Modify Sub-Account" << endl;
		cout << "	E -- Close Sub-Account" << endl;
		cout << "	D -- Detailed Bank Account Info Sorted Based on Balances of Sub-Accounts" << endl;
		cout << "	B -- Brief Bank Account Info" << endl;
		cout << "	X -- Exit" << endl;
		do {
			color(14);
			cout << "Please enter your selection: ";
			color(7);
			getline(cin, selection);
		} while (selection.size() < 0);

		int x = 0;
		string sName = "SAV" + to_string(getSave()), cName = "CHK" + to_string(getCheck());
		string money;
		stringstream makeInt;
		SubAccount s, c;
		string subName;
		int location;//for sub acc search
		string choice, lock; //for modify menus and lock respectively

		color(4);
		switch (selection[0]) {
		case 'S'://Open Saving Sub-Account
		case 's':
			color(14);
			cout << "Enter initial balance: $";
			color(7);
			getline(cin, money);
			makeInt = stringstream(money);
			makeInt >> x;
			s = SubAccount(mem.getName(), x, sName, 1);
			addSubAcc(s);
			if ((SAV - 1000) == 0) {
				s.deposit(100);
			}
			color(4);
			cout << "| Saving Sub-Account " << sName << " successfully created" << endl;
			setSave();
			break;

		case 'C'://Open Checking Sub-Account
		case 'c':
			color(14);
			cout << "Enter initial balance: $";
			color(7);
			getline(cin, money);
			makeInt = stringstream(money);
			makeInt >> x;
			c = SubAccount(mem.getName(), x, cName, 2);
			color(14);
			cout << "Enter max capacity: $";
			getline(cin, money);
			color(7);
			makeInt = stringstream(money);
			makeInt >> x;
			while (x < c.getBalance()) {
				color(4);
				cout << "ERROR. Max Capacity can not be less than initial balance." << endl;
				cout << "Enter Max capacity >= $" << c.getBalance() << endl;
				cout << "Max capacity: $";
				getline(cin, money);
				color(7);
				makeInt = stringstream(money);
				makeInt >> x;
			}
			c.setmax(x);
			color(4);
			cout << "Enter initial state ( (L)ocked, (U)nlocked ): ";
			color(7);
			getline(cin, money);
			c.setLock(money);
			addSubAcc(c);
			color(4);
			cout << "| Checking Sub-Account " << cName << "successfully created" << endl;
			setCheck();
			break;

		case 'M':// Modify Sub-Account
		case 'm': //brown();
			modifySubAccount();
			break;
		case 'E'://Close Sub-Account
		case 'e':
			closeSubAccount();
			break;
		case 'D'://Detailed Bank Account Info Sorted Based on Balances of Sub-Accounts
		case 'd':
			printSortedSubAcc(mem);

			break;																																																																																																																																																																																													
		case 'B'://Brief Bank Account Info
		case 'b':
			cout << "| Aggregated balance of " << memberAccNum << " is $" << aggregated(memberAccNum) << " with " << subAccVec.size() << " Sub-Accounts" << endl << endl;
			break;

			cout << endl << endl;
		}
	} while (selection[0] != 'x' && selection[0] != 'X');
	cout << "End of service for " << memberAccNum << endl;//exit
}

void Bank::closeSubAccount() {
	string money;
	stringstream makeInt;
	string choice, subName;
	int location, x;

	color(14);
	cout << "Enter name of Sub-Account you wish to close: ";
	getline(cin, subName);
	location = searchSubVec(subName);
	color(7);
	while (location == -1) {
		color(4);
		cout << "Sub-Account not found. Enter valid account, ex. SAV2139: ";
		getline(cin, subName);
		color(7);
		location = searchSubVec(subName);
	}
	SubAccount& modify = returnSubAcc(location) = returnSubAcc(location);
	if (!modify.isClosed()) {
		if (location >= 0) {
			color(4);
			cout << "Closing Sub-Account " << modify.getName() << " with $" << modify.getBalance() << endl;
			modify.close();
			cout << "| " << modify.getName() << " successfully closed." << endl << endl;
		}
	}
}

void Bank::modifySubAccount() {
	string money;
	stringstream makeInt;
	string choice, subName;
	int location, x;

	color(4);
	cout << "Enter name of Sub-Account you wish to modify: ";
	color(7);
	getline(cin, subName);
	location = searchSubVec(subName);
	while (location == -1) {
		color(4);
		cout << "Sub-Account not found. Enter valid account, ex. SAV2139: ";
		getline(cin, subName);
		color(7);
		location = searchSubVec(subName);
	}
	SubAccount& modify = returnSubAcc(location);
	if (!modify.isClosed()) {
		if (location >= 0) {
			color(2);
			do {
				cout << "Modifying " << modify.getName() << " with $" << modify.getBalance() << endl;
				if (modify.getType() == 1) {//saving acc
					cout << "D -- Desposit" << endl;
					cout << "W -- Withdraw" << endl;
					cout << "X -- Exit" << endl;
					cout << "Please enter your selection: ";
					color(7);
					getline(cin, choice);
					if (choice[0] == 'D' || choice[0] == 'd') {//deposit 
						color(4);
						cout << "Enter amount to deposit: $";
						color(7);
						getline(cin, money);
						makeInt = stringstream(money);
						makeInt >> x;
						modify.deposit(x);
						color(4);
						cout << "| Deposit successful" << endl;
						cout << "| Current balance of" << modify.getName() << " is $" << modify.getBalance() << endl << endl;
					}
					else if (choice[0] == 'W' || choice[0] == 'w') {//withdraw
						color(4);
						cout << "Enter amount to withdraw: $";
						color(7);
						getline(cin, money);
						makeInt = stringstream(money);
						makeInt >> x;
						while (modify.getBalance() - x < 0) {
							color(4);
							cout << "Error. " << modify.getName() << " has $" << modify.getBalance() << " a withdraw this large would result in a negative balance." << endl;
							cout << "Enter the amount you wish to withdraw ( must be <= " << modify.getBalance() << "): $" << endl;
							color(7);
							getline(cin, money);
							makeInt = stringstream(money);
							makeInt >> x;
						}
						modify.withdraw(x);
						color(4);
						cout << "| Withdrawl successful" << endl;
						cout << "| Current balance of" << modify.getName() << " is $" << modify.getBalance() << endl << endl;
					}
				}
				else {//checking
					color(2);
					cout << "D -- Desposit" << endl;
					cout << "W -- Withdraw" << endl;
					cout << "C -- Max Capacity" << endl;
					cout << "L -- Lock Sub-Account" << endl;
					cout << "U -- Unlock Sub-Account" << endl;
					cout << "X -- Exit" << endl;
					cout << "Please enter your selection: ";
					color(7);
					getline(cin, choice);
					color(4);

					switch (choice[0]) {
					case 'd'://deposit
					case 'D':
						color(4);
						if (modify.isLocked()) {
							cout << "|" << modify.getName() << " is currently locked. Unlock to make changes to balance." << endl;
						}
						else {
							cout << "Enter amount to deposit: $";
							color(7);
							getline(cin, money);
							makeInt = stringstream(money);
							makeInt >> x;
							color(4);
							while (modify.getBalance() + x > modify.getMax()) {
								cout << "Error. " << modify.getName() << " has $" << modify.getBalance() << " a deposit this large exceeds the max capacity" << endl;
								cout << "Enter the amount you wish to withdraw ( must be <= " << (modify.getMax() - modify.getBalance()) << "): $" << endl;
								color(7);
								getline(cin, money);
								makeInt = stringstream(money);
								makeInt >> x;
							}
							modify.deposit(x);
							color(4);
							cout << "| Deposit successful" << endl;
							cout << "| Current balance of" << modify.getName() << " is $" << modify.getBalance() << endl << endl;
						}
						break;

					case 'w':
					case 'W':
						color(4);
						if (modify.isLocked()) {
							cout << "|" << modify.getName() << " is currently locked. Unlock to make changes to balance." << endl;
						}
						else {
							cout << "Enter amount to withdraw: $";
							color(7);
							getline(cin, money);
							makeInt = stringstream(money);
							makeInt >> x;
							while (modify.getBalance() - x < 0) {
								color(4);
								cout << "Error. " << modify.getName() << " has $" << modify.getBalance() << " a withdraw this large would result in a negative balance." << endl;
								cout << "Enter the amount you wish to withdraw ( must be <= " << modify.getBalance() << "): $" << endl;
								color(7);
								getline(cin, money);
								makeInt = stringstream(money);
								makeInt >> x;
							}
							modify.withdraw(x);
							color(4);
							cout << "| Withdrawl successful" << endl;
							cout << "| Current balance of" << modify.getName() << " is $" << modify.getBalance() << endl << endl;
						}
						break;
					case 'l':
					case 'L':
						color(4);
						modify.lock();
						cout << "| " << modify.getName() << " is successfully locked" << endl << endl;
						break;

					case 'u':
					case 'U':
						color(4);
						modify.unlock();
						cout << "| " << modify.getName() << " is successfully unlocked" << endl << endl;
						break;
					}
				}
				color(4);
			} while (choice[0] != 'x' && choice[0] != 'X');
			cout << "Exiting Modify Sub-Account" << endl;
		}
		else {
		color(4);
			cout << "No known Sub-Account" << endl << "returning to previos menu" << endl << endl;
		}
	}
	else {
		cout << modify.getName() << " is closed." << endl << "Returning to previous menu." << endl << endl;
	}

}
void Bank::printBankInfo() {
	int aggBank = 0;
	for (auto& i : bankAcc) {
		aggBank += aggregated(i.getName());
	}
	color(4);
	cout << "| Bank Name: " << name << endl;
	cout << "| Bank Address: " << address << endl;
	cout << "| Bank Working Hours: " << workingHours << endl;
	cout << "| Aggregated Balance: $" << aggBank << endl;
	cout << "| Consists of " << bankAcc.size() << " Bank Accounts" << endl;
	cout << endl;
	for (auto& i : bankAcc) {
		cout << "Aggregated Balance of " << i.getName() << " with " << numSubAcc(i.getName()) << " Sub-Accounts is $" << aggregated(i.getName()) << endl;
	}
}
void Bank::printSortedSubAcc(MemberAccount mem) {
	sort(subAccVec.begin(), subAccVec.end(), ::compareSub);
	color(4);
	for (auto& i : subAccVec) {
		if (i.getMem() == mem.getName()) {
			if (!i.isClosed()) {
				if (i.getType() == 1) {//sav
					cout << "| Sub-Account: " << i.getName() << endl;
					cout << "| Balance: $" << i.getBalance() << endl;
					cout << endl;
				}
				else {
					cout << "| Sub-Account: " << i.getName() << endl;
					cout << "| Balance: $" << i.getBalance() << endl;
					cout << "| Maximumum capacity is $" << i.getMax() << endl;
					if (i.isLocked()) {
						cout << "| The Sub-Account is locked" << endl;
					}
					else {
						cout << "| The Sub-Account is unlocked" << endl;
					}
				}
				cout << endl;
			}
			else {
				cout << "| " << i.getName() << " CLOSED" << endl << endl;
			}
		}
	}
}
int Bank::numSubAcc(string name) {
	int num = 0;
	for (auto& i : subAccVec) {
		if (i.getMem() == name) {
			num++;
		}
	}
	return num;
}
void Bank::printSortedMemberAcc() {
	color(4);
	for (auto& i : bankAcc) {
		i.setAgg(aggregated(i.getName()));
	}
	sort(bankAcc.begin(), bankAcc.end(), ::compareMem);
	for (auto& i : bankAcc) {
		cout << "| Bank Account Number: " << i.getName() << endl;
		if (i.isClosed()) {
			cout << "| Account Holder Full Name :" << i.getFullName() << endl;
			cout << "| Account Holder SSN: " << i.getSSN() << endl;
			cout << "| Aggregated Balance: " << aggregated(i.getName()) << endl;
			cout << "| Consists of " << numSubAcc(i.getName()) << " Sub-Accounts" << endl;
		}
		else{
			cout << "CLOSED" << endl;
		}
		cout << endl;

		printSortedSubAcc(i);
	}

}