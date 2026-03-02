#include "Account.hpp"
#include <iostream>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

void Account::_displayTimestamp()
{
	std::time_t now = std::time(NULL);
	std::tm *ltm = std::localtime(&now);
	char buffer[20];
	std::strftime(buffer, 20, "[%Y%m%d_%H%M%S] ", ltm);
	std::cout << buffer;
}

Account::Account(int initial_deposit)
{
	_nbAccounts++;
	_totalAmount += initial_deposit;
	this->_accountIndex = _nbAccounts - 1;
	this->_amount = initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
}

Account::~Account()
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
}

int Account::getNbAccounts()
{
	return _nbAccounts;
}

int Account::getNbDeposits()
{
	return _totalNbDeposits;
}

int Account::getTotalAmount()
{
	return _totalAmount;
}

int Account::getNbWithdrawals()
{
	return _totalNbWithdrawals;
}

void Account::displayAccountsInfos()
{
	_displayTimestamp();
	std::cout	<< "accounts:" << getNbAccounts()
				<< ";total:" << getTotalAmount()
				<< ";deposits:" << getNbDeposits()
				<< ";withdrawals:" << getNbWithdrawals() << std::endl;
}

void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	int p_amount = this->_amount;
	this->_amount += deposit;
	this->_nbDeposits++;
	_totalAmount += deposit;
	_totalNbDeposits++;
	std::cout	<< "index:" << _accountIndex
				<< ";p_amount:" << p_amount
				<< ";deposit:" << deposit
				<< ";amount:" << this->_amount
				<< ";nb_deposits:" << this->_nbDeposits
				<< std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";p_amount:" << this->_amount;
	if(withdrawal > this->_amount)
	{
		std::cout <<";withdrawal:refused" << std::endl;
		return false;
	}
	else
	{
		this->_amount -= withdrawal;
		this->_nbWithdrawals++;
		_totalNbWithdrawals++;
		_totalAmount -= withdrawal;
		std::cout	<< ";withdrawal:" << withdrawal
					<< ";amount:" << this->_amount
					<< ";nb_withdrawals:" << this->_nbWithdrawals
					<<	std::endl;
		return true;
	}
}

int Account::checkAmount() const
{
	return this->_amount;
}

void Account::displayStatus( void ) const
{
	_displayTimestamp();
	std::cout	<< "index:" << _accountIndex << ";"
				<< "amount:" << _amount << ";"
				<< "deposits:" << _nbDeposits << ";"
				<< "withdrawals:" << _nbWithdrawals << std::endl;
}
