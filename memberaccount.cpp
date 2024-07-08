//Joanna Hughes
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>
#include "memberaccount.h"

MemberAccount::MemberAccount() { //default constructor
	first = "N/A";
	last = "N/A";
	ssn = "000-00-0000";
	memberAccNum = "N/A";
}
MemberAccount::MemberAccount(string first, string last, string ssn, string memberAccNum) {
	this->first = first;
	this->last = last;
	this->ssn = ssn;
	this->memberAccNum = memberAccNum;
}
void MemberAccount::close() {
	closed = true;
}
bool MemberAccount::isClosed() {
	return closed;
}
string MemberAccount::getName() {
	return memberAccNum;
}
void MemberAccount::setAgg(int agg) {
	aggregate == agg;
}
int MemberAccount::getAgg() {
	return aggregate;
}
string MemberAccount::getFullName() {
	return (first + " " + last);
}
string MemberAccount::getSSN() {
	return ssn;
}