#include<iostream>
#include<fstream>
#include "identity.h"
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
using namespace std;

void managerMenu(Identity*& manager) {
	while (true) {
		manager->openMenu();
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1) {
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) {
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3) {
			cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4) {
			cout << "清空预约" << endl;
			man->cleanFile();
		}
		else {
			delete manager;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void studentMenu(Identity*& student) {
	while (true) {
		student->openMenu();
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) {
			stu->applyOrder();
		}
		else if (select == 2) {
			stu->showMyOrder();
		}
		else if (select == 3) {
			stu->showAllOrder();
		}
		else if (select == 4) {
			stu->cancelOrder();
		}
		else {
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void TeacherMenu(Identity*& teacher) {
	while (true) {
		teacher->openMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1) {
			tea->showAllOrder();
		}
		else if (select == 2) {
			tea->validOrder();
		}
		else {
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void LoginIn(string fileName, int type) {
	Identity* person = NULL;

	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open()) {
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout<< "文件为空！" << endl;
		ifs.close();
		return ;
	}
	ifs.putback(ch);

	int id = 0;
	string name;
	string pwd;

	if (type == 1) { //学生登录
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if(type == 2) {//教师
		cout << "请输入你的职工号" << endl;
		cin >> id;
	}
	cout << "请输入用户名" << endl;
	cin >> name;

	cout << "请输入密码" << endl;
	cin >> pwd;

	if (type == 1) {//学生验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) {//教师验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd) {
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				TeacherMenu(person);
				return;
			}
		}
	}
	else if(type == 3) {//管理员验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd) {
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败！" << endl;

	system("pause");
	system("cls");
	return;
}



int main() {
	int select = 0;

	while (true)
	{

		cout << "======================  欢迎来到刘健强的机房预约系统  =====================" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";

		cin >> select; //接受用户选择

		switch (select)
		{
		case 1:  //学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:  //老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:  //管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:  //退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}

	}
	system("pause");
	return 0;
}