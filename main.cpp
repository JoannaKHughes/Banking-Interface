//Joanna Hughes
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
#include "memberaccount.h"
#include "subaccount.h"
#include "bank.h"

void setColor(int value) {
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

int main() {

	string name, address, hours;
	setColor(6);
	cout << "Enter the name of the Bank: ";
	setColor(15);
	getline(cin, name);
	setColor(6);
	cout << "Enter the address: ";
	setColor(15);
	getline(cin, address);
	setColor(6);
	cout << "Enter the working hours: ";
	setColor(15);
	getline(cin, hours);
	cout << endl << endl;
	Bank bank = Bank(name, address, hours);

	string selection;//for menu options and switch cases
	string acc;//input for accounts to open or close
	MemberAccount mem;

	do {//loops until exited
	//begining menu for the teller

		setColor(2);
		cout << "Eligiable services for " << name << ":" << endl;
		cout << "	A -- Number of Bank-Accounts" << endl;
		cout << "	S -- Number of Savings-Accounts" << endl;
		cout << "	H -- Number of Checking-Accounts" << endl;
		cout << "	O -- Open Bank-Account" << endl;
		cout << "	C -- Close Bank-Account" << endl;
		cout << "	M -- Modify Bank-Account" << endl;
		cout << "	D -- Detailed Bank-Accounts" << endl;
		cout << "	B -- Brief Bank-Account Info Sorted Based om Aggregated Balances" << endl;
		cout << "	X -- Exit" << endl;
		do {
			cout << "Please enter your selection: ";
			setColor(15);
			getline(cin, selection);
		} while (selection.size() < 0);

		setColor(4);
		switch (selection[0]) {
		case 'A'://Number of Bank - Accounts
		case 'a':
			
			cout << "The number of bank accounts: " << bank.getNumBankAcc() << endl;
			break;
		case 'S'://Number of Savings - Accounts
		case 's':
			cout << "The total number of saving accounts in " << name << " is " << (bank.getSave()- 1000) << ".\n";
			break;
		case 'H'://Number of Checking - Accounts
		case 'h':
			cout << "The total number of checking accounts in " << name << " is " << (bank.getCheck() - 1000) << ".\n";
			break;
		case 'O'://Open Bank - Account
		case 'o':
			bank.makeMemberAccount();
			break;
		case 'C'://Close Bank - Account
		case 'c':
			cout << "Enter name of Bank account to close: ";
			setColor(15);
			getline(cin, acc);
			bank.close(acc);

			break;
		case 'M'://Modify Bank - Account
		case 'm':
			cout << "Enter account name to be modified:";
			setColor(15);
			getline(cin, acc);
			while (bank.searchMembers(acc) == -1 || (acc[0] == 'x' && acc[0] == 'X')) {
				setColor(4);
				cout << "Invalid entry" << endl;
				cout << "Valid accounts are written as BNK1000, re-enter account num or 'X' to exit: ";
				setColor(15);
				getline(cin, acc);
			}
			mem = bank.returnBankAcc(bank.searchMembers(acc));
			bank.accountOptions(mem);

			break;
		case 'D'://Detailed Bank - Accounts
		case 'd':
			bank.printBankInfo();
			bank.printSortedMemberAcc();

			break;
		case 'B'://Brief Bank - Account Info Sorted Based om Aggregated Balances
		case 'b':
			bank.printBankInfo(); 
			break;
		}
		cout << endl;
	} while (selection[0] != 'x' || selection[0] != 'X');
	cout << "End of service for " << name << endl;//exit
}