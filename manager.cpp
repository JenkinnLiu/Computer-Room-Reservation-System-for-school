#include "manager.h"
#include<iostream>
using namespace std;

Manager::Manager() {
}

Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->initVector();//初始化容器

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom c;
	while (ifs >> c.m__ComId && ifs >> c.m_MaxNum) {
		vCom.push_back(c);
	}
	cout << "当前机房数量为：" << vCom.size() << endl;
}

void Manager::openMenu() {
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

void Manager::addPerson() {
	cout << "请输入添加账号的类型" << endl;
	cout << "1. 添加学生" << endl;
	cout << "2. 添加老师" << endl;

	string fileName;
	string tip, errorTip;
	ofstream ofs;

	int select = 0;
	cin >> select;
	if (select == 1) {
		fileName = STUDENT_FILE;
		tip = "请输入学号";
		errorTip = "学号重复，请重新输入!";
	}
	else if (select == 2) {
		fileName = TEACHER_FILE;
		tip = "请输入职工编号";
		errorTip = "职工号重复，请重新输入！";
	}

	ofs.open(fileName, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true) {
		cin >> id;

		bool ret = this->checkRepeat(id, select);

		if (ret) cout << errorTip << endl;
		else break;
	}
	

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");

	ofs.close();

	this->initVector();//防止刚添加的账号不会重复添加的bug

}

void printStudent(Student& s) {
	cout << "学号： " << s.m_Id << "姓名： " << s.m_Name << "密码： " << s.m_Pwd << endl;
}

void printTeacher(Teacher& t) {
	cout << "职工号" << t.m_EmpId << "姓名： " << t.m_Name << "密码： " << t.m_Pwd << endl;
}

void Manager::showPerson() {
	cout << "请选择查看内容：" << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有老师" << endl;
	
	int select = 0;
	cin >> select;

	if (select == 1) {
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), [](Student& s) {
			cout << "学号： " << s.m_Id << "姓名： " << s.m_Name << "密码： " << s.m_Pwd << endl;
		});
	}
	else {
		cout << "所有教师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), [](Teacher& t) {
			cout << "职工号： " << t.m_EmpId << "姓名： " << t.m_Name << "密码： " << t.m_Pwd << endl;
			});
	}
	system("pause");
	system("cls");
}

void Manager::showComputer() {
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++) {
		cout << "机房编号:" << it->m__ComId << "机房最大容量：" << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::initVector() {
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败" << endl;
		return;
	}
	/*char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
		return;
	}
	ifs.putback(ch);*/
	vStu.clear();
	vTea.clear();

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.push_back(t);
	}
	cout << "当前教师数量为：" << vTea.size() << endl;

	ifs.close();
}

bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
			if (id == it->m_Id) return true;
		}
	}
	else {
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
			if (id == it->m_EmpId) return true;
		}
	}
	return false;
}

void Manager::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}
