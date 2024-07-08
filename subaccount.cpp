#pragma once
//Joanna Hughes
#include <iostream>
#include<string>
#include <windows.h>
#include <vector>
using namespace std;
#include "subaccount.h"

SubAccount::SubAccount() {
	memName = "N/A";
	money = 0;
	name = "N/A";
	type = 0;
}
SubAccount::SubAccount(string memName, int money, string name, int type/*1 for save 2 for check*/) {
	this->memName = memName;
	this->money = money;
	this->name = name;
	this->type = type;
}
int SubAccount::getType() {
	return type;
}
string SubAccount::getName() {
	return name;
}
double SubAccount::getBalance() {
	return money;
}
void SubAccount::withdraw(int change) {//minus money
	money -= change;
}
void SubAccount::deposit(int change) {//add money
	money += change;
}
void SubAccount::setmax(int max) {
	this->max = max;
}
double SubAccount::getMax() {
	return max;
}
bool SubAccount::isMax(int withdraw) {
	if (withdraw > max) {
		return false;
	}
}
void SubAccount::setLock(string ul) {
	if (ul[0] == 'l' || ul[0] == 'L') {
		locked = true;
	}
}
void SubAccount::lock() {
	locked = true;
}
void SubAccount::unlock() {
	locked = false;
}
bool SubAccount::isLocked() {
	return locked;
}
void SubAccount::close() {
	closed = true;
}
bool SubAccount::isClosed() {
	return closed;
}
string SubAccount::getMem() {
	return memName;
}
