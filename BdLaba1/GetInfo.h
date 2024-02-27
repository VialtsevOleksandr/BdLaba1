#pragma once
#include "Slave.h"
#include "Master.h"
#include "Const.h"
#include "Id.h"

using namespace std;

//void get_m1(const string& fileName, int id)
//{
//	ifstream file(fileName);
//	if (!file.is_open()) {
//		cout << "File could not be opened\n";
//		return;
//	}
//
//	int lineNumber = findIdInFile(fileName, id);
//	if (lineNumber == -1)
//	{
//		cout << indentation;
//		cout << "Group with ID " << id << " not found.\n";
//		cout << indentation;
//	}
//	else
//	{
//		string line;
//		for (int i = 0; i < lineNumber; i++)
//		{
//			getline(file, line);
//		}
//		cout << indentation;
//		for (int i = 0; i < 4; i++)
//		{
//			getline(file, line);
//			cout << line << endl;
//		}
//		cout << indentation;
//	}
//	file.close();
//}

void get_m(const string& fileName, int id)
{
	ifstream inf(fileName);
	if (!inf) {
		cout << "File could not be opened\n";
		return;
	}

	int lineNumber = findIdInFile(fileName, id);
	if (lineNumber == -1)
	{
		cout << indentation;
		cout << "Group with ID " << id << " not found.\n";
		cout << indentation;
	}
	else
	{
		string line;
		inf.seekg(lineNumber, ios::beg);
		cout << indentation;
		for (int i = 0; i < 4; i++)
		{
			getline(inf, line);
			cout << line << endl;
		}
		cout << indentation;
	}
	inf.close();
}

//void get_s1(const string& fileName, int id)
//{
//	ifstream file(fileName);
//	if (!file.is_open()) {
//		cout << "File could not be opened\n";
//		return;
//	}
//
//	int lineNumber = findIdInFile(fileName, id);
//	if (lineNumber == -1)
//	{
//		cout << indentation;
//		cout << "Pupil with ID " << id << " not found.\n";
//		cout << indentation;
//	}
//	else
//	{
//		string line;
//		for (int i = 0; i < lineNumber; i++)
//		{
//			getline(file, line);
//		}
//		cout << indentation;
//		for (int i = 0; i < 8; i++)
//		{
//			getline(file, line);
//			cout << line << endl;
//		}
//		cout << indentation;
//	}
//	file.close();
//}

void get_s(const string& fileName, int id)
{
	ifstream inf(fileName);
	if (!inf) {
		cout << "File could not be opened\n";
		return;
	}

	int lineNumber = findIdInFile(fileName, id);
	if (lineNumber == -1)
	{
		cout << indentation;
		cout << "Pupil with ID " << id << " not found.\n";
		cout << indentation;
	}
	else
	{
		string line;
		inf.seekg(lineNumber, ios::beg);
		cout << indentation;
		for (int i = 0; i < 8; i++)
		{
			getline(inf, line);
			cout << line << endl;
		}
		cout << indentation;
	}
	inf.close();
}

//void get_m(struct Group groups[], int size, int id)
//{
//	if (id > size)
//	{
//		cout << indentation;
//		cout << "����� � ID " << id << " �� ��������.\n";
//		cout << indentation;
//	}
//	else
//	{
//		for (int i = 0; i <= id; i++)
//		{
//			if (groups[i].Id == id)
//			{
//				cout << indentation;
//				cout << "����� �����: " << groups[i].GroupName << "\t ���i� �����: " << groups[i].MottoOfGroup << "\t����������� �i���i��� �����: " << groups[i].MaxPupilsAmount << "\n";
//				cout << indentation;
//			}
//		}
//	}
//}

//void get_s(struct Pupil pupils[], int size, int id)
//{
//	if (id > size)
//	{
//		cout << indentation;
//		cout << "���� � ID " << id << " �� ��������.\n";
//		cout << indentation;
//	}
//	else
//	{
//		for (int i = 0; i <= id; i++)
//		{
//			if (pupils[i].Id == id)
//			{
//				cout << indentation;
//				cout << "�I�: " << pupils[i].LastName << " " << pupils[i].FirstName << " " << pupils[i].MiddleName << "\n";
//				cout << "���� ����������(dd/mm/yyyy): " << pupils[i].BirthDay << "\n";
//				cout << "������� �����i�: " << pupils[i].ParentsPhoneNumber << "\n";
//				cout << "����� ����� � ��i� ���������: " << pupils[i].GroupId << "\n";
//				cout << indentation;
//			}
//		}
//	}
//}