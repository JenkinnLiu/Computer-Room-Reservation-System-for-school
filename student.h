#pragma once
#include<iostream>
#include "identity.h"
#include "student.h"
#include<fstream>
#include "globalFile.h"
#include "computerRoom.h"
#include<string>
#include"orderfile.h"
#include<vector>
#include<cstring>
using namespace std;

class Student : public Identity {
public:
	Student();

	Student(int id, string name, string pwd);

	vector<ComputerRoom> vCom;

	virtual void openMenu();

	void applyOrder();//申请预约

	void showMyOrder();//查看预约

	void showAllOrder();//查看所有预约

	void cancelOrder();//取消预约

	int m_Id;//学号


};