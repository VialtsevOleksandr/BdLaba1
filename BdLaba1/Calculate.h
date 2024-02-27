#pragma once

using namespace std;

int CountStudentsInGroup(int currentGroupId) {
	ifstream file("Slave.txt");
	string line;
	int count = 0;
	file.seekg(0, ios::end);
	int length = file.tellg();
	file.seekg(0, ios::beg);
	for (int i = 1; i * sizeOfPupil <= length; i++)
	{
		file.seekg((i * sizeOfPupil) - 45, ios::beg);
		int temp = file.tellg();
		getline(file, line);
		if (line.find("IdOfGroup: ") != string::npos) {
			int groupId = stoi(line.substr(line.find(": ") + 2));
			if (groupId == currentGroupId)
				count++;
		}
		file.seekg(temp + 45, ios::beg);

	}
	return count;
}

int calc_s(const string& fileName)
{
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "File could not be opened\n";
		return -1;
	}
	file.seekg(0, ios::end);
	int length = file.tellg();
	file.seekg(0, ios::beg);
	string line;
	int count = 0;
	for (int i = 0; i * sizeOfPupil < length; i++)
	{
		file.seekg(i * sizeOfPupil, ios::beg);
		getline(file, line);
		if (line.find("Id: ") != string::npos)
		{
			count++;
		}
	}
	file.close();
	if(count != 0)
		return count;
	else
	{
		cout << "File is empty\n";
		return -1;
	}
}
void calc_m(const string& fileName)
{
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "File could not be opened\n";
		return;
	}
	file.seekg(0, ios::end);
	int length = file.tellg();
	file.seekg(0, ios::beg);
	string line;
	int count = 0;
	cout << indentation;
	for (int i = 0; i * sizeOfGroup < length; i++)
	{
		file.seekg(i * sizeOfGroup, ios::beg);
		int temp = file.tellg();
		getline(file, line);
		if (line.find("Id: ") != string::npos) {
			int currentGroupId = stoi(line.substr(line.find(": ") + 2));
			if (CountStudentsInGroup(currentGroupId) != 0)
				cout << "Number of students in group " << currentGroupId << ": " << CountStudentsInGroup(currentGroupId) << endl;
		}
		file.seekg(-temp, ios::cur);
		count++;
	}
	file.close();
	if(count == 0)
	{
		cout << "File is empty\n";
		return;
	}
	else
	{
		cout << "Number of groups: " << count << endl;
	}
	cout << indentation;
}
