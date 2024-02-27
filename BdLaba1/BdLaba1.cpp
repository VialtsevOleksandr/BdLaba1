#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip> 

#include "Slave.h"
#include "Master.h"
#include "GetInfo.h"
#include "Id.h"
#include "Calculate.h"
#include "Const.h"
#include "Update.h"
#include "Delete.h"
#include "Utility.h"


using namespace std;


//int findLastPupilInGroup(const string& fileName, int groupId) {
//	ifstream file(fileName);
//	if (!file.is_open()) {
//		cout << "File could not be opened\n";
//		return -1;
//	}
//	string line;
//	int currentPupilId = -1;
//	while (getline(file, line)) {
//		if (line.find("Id: ") != string::npos) {
//			currentPupilId = stoi(line.substr(line.find(": ") + 2));
//		}
//		if (line.find("IdOfGroup: " + to_string(groupId)) != string::npos) {
//			getline(file, line); // Чтение строки NextPupilIdInGroup
//			int nextPupilId = stoi(line.substr(line.find(": ") + 2));
//			if (nextPupilId == currentPupilId) {
//				file.close();
//				return currentPupilId;
//			}
//		}
//	}
//	file.close();
//	return -1;
//}
int findLastPupilInGroup(const string& fileName, int groupId) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "File could not be opened\n";
		return -1;
	}
	file.seekg(0, ios::end);
	int length = file.tellg();
	file.seekg(0, ios::beg);
	string line;
	int currentPupilId = -1;
	for (int i = 0; i * sizeOfPupil <= length; i++)
	{
		file.seekg(i * sizeOfPupil, ios::beg);
		getline(file, line);
		if (line.find("Id: ") != string::npos) {
			currentPupilId = stoi(line.substr(line.find(": ") + 2));
		}
		file.seekg(-11, ios::cur);
		file.seekg(214, ios::cur);
		getline(file, line);
		if (line.find("IdOfGroup: " + to_string(groupId)) != string::npos) {
			getline(file, line);
			int nextPupilId = stoi(line.substr(line.find(": ") + 2));
			if (nextPupilId == currentPupilId) {
				file.close();
				return currentPupilId;
			}
		}
		file.seekg(-232, ios::cur);//-231
	}
	file.close();
	return -1;
}

int findLastLPupilInGroup(const string& fileName, int groupId) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "File could not be opened\n";
		return -1;
	}
	file.seekg(0, ios::end);
	int length = file.tellg();
	file.seekg(0, ios::beg);
	string line;
	int currentPupilId = -1;
	for (int i = length; i / sizeOfPupil >= 0; i--)
	{
		file.seekg(i - sizeOfPupil, ios::beg);
		getline(file, line);
		if (line.find("Id: ") != string::npos) {
			currentPupilId = stoi(line.substr(line.find(": ") + 2));
		}
		file.seekg(-11, ios::cur);
		file.seekg(214, ios::cur);
		getline(file, line);
		if (line.find("IdOfGroup: " + to_string(groupId)) != string::npos) {
			getline(file, line);
			int nextPupilId = stoi(line.substr(line.find(": ") + 2));
			if (nextPupilId == currentPupilId) {
				file.close();
				return currentPupilId;
			}
		}
		file.seekg(-232, ios::cur);//-231
	}
	file.close();
	return -1;
}

void updateNextPupilIdInGroup(const string& fileName, int pupilId, int nextPupilId)
{
	fstream file(fileName, ios::in | ios::out);
	if (!file) {
		cout << "File could not be opened\n";
		return;
	}
	file.seekg(findIdInFile(fileName, pupilId) + 232, ios::beg);
	ostringstream oss;
	oss << "NextPupilIdInGroup: " << left << setw(5) << nextPupilId;
	string idString = oss.str();
	file.write(idString.c_str(), idString.size());
	file.close();
}

//void updateNextPupilIdInGroup(const string& fileName, int pupilId, int nextPupilId) {
//	fstream file(fileName, ios::in | ios::out);
//	if (!file.is_open()) {
//		cout << "File could not be opened\n";
//		return;
//	}
//	string line;
//	streampos oldPos;
//	while (getline(file, line)) {
//		if (line.find("Id: " + to_string(pupilId)) != string::npos) {
//			for (int i = 0; i < 7; ++i) {
//				oldPos = file.tellg();
//				getline(file, line);
//			}
//			if (line.find("NextPupilIdInGroup: " + to_string(pupilId)) != string::npos) {
//				file.seekp(oldPos);
//				file << "\t\t\t\t\t" << endl; 
//				file.seekp(oldPos);
//				file << "NextPupilIdInGroup: " << nextPupilId << endl;
//				break;
//			}
//		}
//	}
//	file.close();
//}

void updateLinksBeforeDeletion(const string& fileName, int id) {
	fstream file(fileName, ios::in | ios::out);
	if (!file.is_open()) {
		cout << "File could not be opened\n";
		return;
	}

	file.seekg(0, ios::end);
	int length = file.tellg();
	file.seekg(0, ios::beg);
	string line;
	int nextPupilId = -1;
	int previousPupilId = -1;
	int tempId = findIdInFile("Slave.txt", id);
	file.seekg(tempId + 232, ios::beg);
	getline(file, line);
	if (line.find("NextPupilIdInGroup: ") != string::npos) {
		nextPupilId = stoi(line.substr(line.find(": ") + 2));
		if (nextPupilId == id)
			return;
	}
	file.seekg(0, ios::beg);
	for (int i = 0; i * sizeOfPupil <= length; i++) {
		file.seekg(i * sizeOfPupil, ios::beg);
		getline(file, line);
		if (line.find("Id: ") != string::npos) {
			previousPupilId = stoi(line.substr(line.find(": ") + 2));
		}
		file.seekg(-11, ios::cur);
		file.seekg(232, ios::cur);
		getline(file, line);
		if (line.find("NextPupilIdInGroup: " + to_string(id)) != string::npos) {
			file.seekg(0, ios::beg);
			updateNextPupilIdInGroup("Slave.txt", previousPupilId, nextPupilId);
		}
	}
	file.close();
}

void removeEmptyLinesInFile(const string& fileName) {

	ifstream inputFile(fileName);
	stringstream buffer;

	if (!inputFile.is_open()) {
		cout << "File could not be opened\n";
		return;
	} 
	string line;
	while (getline(inputFile, line)) {
		if (!line.empty()) {
			buffer << line << endl;
			for (int i = 0; i < 8; ++i) {
				if (getline(inputFile, line)) {
					buffer << line << endl;
				}
				else {
					break;
				}
			}
		}
	}
	inputFile.close();
	ofstream outputFile(fileName);
	outputFile << buffer.rdbuf();
	outputFile.close();
}


int main()
{
	setlocale(LC_ALL, "ukrainian");
	int key;
	cout << "Press appropriate key for a specific action:\n 0 - Insert pupil\t 1 - Insert group\n 2 - Get pupil\t\t 3 - Get group\n 4 - Update pupil\t 5 - Update group\n 6 - Delete pupil\t 7 - Delete group\n 8 - Calculate pupil\t 9 - Calculate group\n 10 - Print all pupils\t 11 - Print all groups\n 12 - Exit\n" ;
	do
	{
		cout << "Enter key: ";
		try {
			if (!(cin >> key)) {
				throw invalid_argument("Key must be an integer");
			}
		}
		catch (const invalid_argument& e) {
			cout << e.what() << "\nPlease try again.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		switch (key)
		{
		case 0:
		{
			ifstream file("Master.txt");
			if (file.peek() == ifstream::traits_type::eof())
			{
				cout << "Unable to add a pupil because there are no groups\n";
				file.close();
			}
			else
			{
				file.close();
				Pupil pupil;
				bool inputSuccessful = false;
				do
				{
					try
					{
						inputPupil(pupil);
						inputSuccessful = true;
					}
					catch (const exception& message)
					{
						cout << message.what() << "\nPlease try again.\n";
					}
				} while (!inputSuccessful);
				int lastPupilId = findLastPupilInGroup("Slave.txt", pupil.GroupId);
				if (lastPupilId != -1) {
					updateNextPupilIdInGroup("Slave.txt", lastPupilId, pupil.Id);
				}
				pupil.nextPupilIdInGroup = pupil.Id;
				ofstream outFile("Slave.txt", ios::app);
				if (!outFile)
				{
					cout << "Unable to open file for writing\n";
				}
				else
				{
					outFile << "Id: " << left << setw(5) << pupil.Id << endl;
					outFile << "LastName: " << left << setw(35) << pupil.LastName << endl;
					outFile << "FirstName: " << left << setw(35) << pupil.FirstName << endl;
					outFile << "MiddleName: " << left << setw(35) << pupil.MiddleName << endl;
					outFile << "BirthDay: " << left << setw(11) << pupil.BirthDay << endl;
					outFile << "ParentsPhoneNumber: " << left << setw(14) << pupil.ParentsPhoneNumber << endl;
					outFile << "IdOfGroup: " << left << setw(5) << pupil.GroupId << endl;
					outFile << "NextPupilIdInGroup: " << left << setw(5) << pupil.nextPupilIdInGroup << endl;
				}
				outFile.close();
			}
			break;
		}
		case 1:
		{
			Group group;
			bool inputSuccessful = false;
			do
			{
				try
				{
					inputGroup(group);
					inputSuccessful = true;
				}
				catch (const exception& message)
				{
					cout << message.what() << "\nPlease try again.\n";
				}
			} while (!inputSuccessful);
			ofstream outFile("Master.txt", ios::app);
			if (!outFile)
			{
				cout << "Unable to open file for writing\n";
			}
			else
			{
				outFile << "Id: " << left << setw(5) << group.Id << endl;
				outFile << "GroupName: " << left << setw(20) << group.GroupName << endl;
				outFile << "MottoOfGroup: " << left << setw(30) << group.MottoOfGroup << endl;
				outFile << "MaxPupilsAmount: " << left << setw(5) << group.MaxPupilsAmount << endl;
			}
			outFile.close();
			break;
		}
		case 2:
		{
			int id;
			cout << "Enter PupilId: ";
			cin >> id;
			get_s("Slave.txt", id);
			break;
		}
		case 3:
		{
			int id;
			cout << "Enter GroupId: ";
			cin >> id;
			get_m("Master.txt", id);
			break;
		}
		case 4:
		{
			int id;
			cout << "Enter PupilId you wish to update: ";
			cin >> id;
			fstream file("Slave.txt", ios::in | ios::out);
			if (!file.is_open()) {
				cout << "File could not be opened\n";
				file.close();
			}
			int lineNumber = findIdInFile("Slave.txt", id);
			int groupId = -1;
			if (lineNumber != -1)
			{
				string line;
				file.seekg(lineNumber + 214, ios::beg);
				getline(file, line);
				if (line.find("IdOfGroup: ") != string::npos) {
					groupId = stoi(line.substr(line.find(": ") + 2));
					file.close();
				}
			}
			updateLinksBeforeDeletion("Slave.txt", id);
			update_s("Slave.txt", id);
			if (CountStudentsInGroup(groupId) <= 2)
			{
				if(findLastLPupilInGroup("Slave.txt", groupId)!=-1)
					updateNextPupilIdInGroup("Slave.txt", id, findLastLPupilInGroup("Slave.txt", groupId));
				else if(findLastPupilInGroup("Slave.txt", groupId) != -1)
					updateNextPupilIdInGroup("Slave.txt", id, findLastPupilInGroup("Slave.txt", groupId));
			}
			break;
		}
		case 5:
		{
			int id;
			cout << "Enter GroupId you wish to update: ";
			cin >> id;
			update_m("Master.txt", id);
			break;
		}
		case 6:
		{
			int id;
			cout << "Enter PupilId you wish to delete: ";
			cin >> id;
			fstream file("Slave.txt", ios::in | ios::out);
			if (!file.is_open()) {
				cout << "File could not be opened\n";
				file.close();
			}
			int lineNumber = findIdInFile("Slave.txt", id);
			int groupId = -1;
			int nextPupilIdInGroup = -1;
			if (lineNumber != -1)
			{
				string line;
				file.seekg(lineNumber + 214, ios::beg);
				getline(file, line);
				if (line.find("IdOfGroup: ") != string::npos) {
					groupId = stoi(line.substr(line.find(": ") + 2));
					getline(file, line);
					if (line.find("NextPupilIdInGroup: ") != string::npos) {
						nextPupilIdInGroup = stoi(line.substr(line.find(": ") + 2));
					}
				}
			}
			file.seekg(0, ios::end);
			int length = file.tellg();
			file.seekg(0, ios::beg);
			string line;
			int previousPupilId = -1;
			for (int i = 0; i * sizeOfPupil <= length; i++)
			{
				file.seekg(i * sizeOfPupil, ios::beg);
				getline(file, line);
				if (line.find("Id: ") != string::npos) {
					previousPupilId = stoi(line.substr(line.find(": ") + 2));
				}
				file.seekg(-11, ios::cur);
				file.seekg(214, ios::cur);
				getline(file, line);
				if (line.find("IdOfGroup: " + to_string(groupId)) != string::npos) {
					getline(file, line);
					if (line.find("NextPupilIdInGroup: " + to_string(id)) != string::npos)
					{
						break;
					}
				}

			}
			if (nextPupilIdInGroup == id)
			{
				updateNextPupilIdInGroup("Slave.txt", previousPupilId, previousPupilId);
			}
			else if (nextPupilIdInGroup != -1 && previousPupilId!=-1)
			{
				updateLinksBeforeDeletion("Slave.txt", id);
			}
			file.close();
			del_s("Slave.txt", id);
			break;
		}
		case 7:
		{
			int id;
			cout << "Enter GroupId you wish to delete: ";
			cin >> id;
			del_m("Master.txt", id);
			break;
		}
		case 8:
		{
			int count = calc_s("Slave.txt");
			if(count != -1)
			{
				cout << indentation;
				cout << "Number of pupils: " << count << endl;
				cout << indentation;
			}
			break;
		}
		case 9:
		{
			calc_m("Master.txt");
			break;
		}
		case 10:
			ut_s("Slave.txt");
			break;
		case 11:
			ut_m("Master.txt");
			break;
		case 12:
			cout << "\n@2024. This program was created by the 2nd year student of the Faculty of Computer Science and Cybernetics, group K-27, Oleksandr Vialtsev. All rights reserved\n";
			break;
		default:
			cout << "Incorrect key!\n";
			continue;
		}
	} while (key != 12);
	return 0;
}
