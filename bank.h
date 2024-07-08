#pragma once
using namespace std;
#include <vector>

class MemberAccount;  //forward definition
class SubAccount;  //forward definition

class Bank {
private:
	string name, address, workingHours, memberAccNum = "BNK";
	vector<MemberAccount> bankAcc;
	int num = 1000; // use this number to name bank accounts
	int SAV = 1000; 
	int CHK = 1000;//starting acc num
	vector<SubAccount> subAccVec;
	void modifySubAccount();
	void closeSubAccount();
public:
	Bank();
	Bank(string name, string address, string workingHours);
	void printBankInfo();
	void setSave();
	int getSave();
	void setCheck();
	int getCheck();
	int getNumBankAcc();
	bool compareMem(MemberAccount a, MemberAccount b);
	void makeMemberAccount();
	void close(string acc);
	void addSubAcc(SubAccount acc);
	int searchSubVec(string search);
	SubAccount& returnSubAcc(int location);
	void accountOptions(MemberAccount mem);
	double aggregated(string name);//total $$ of subaccount for named member
	int searchMembers(string search);
	MemberAccount& returnBankAcc(int location);
	void printSortedSubAcc(MemberAccount mem);
	void printSortedMemberAcc();//based on agg sum
	int numSubAcc(string name);

};