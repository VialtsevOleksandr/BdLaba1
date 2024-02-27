#pragma once

void ut_s(const string& fileName)
{
    fstream file(fileName);
    if (!file.is_open()) {
        cout << "File could not be opened\n";
        return;
    }

    file.seekg(0, ios::end);
    int length = file.tellg();
    file.seekg(0, ios::beg);
    string line;
    vector<int> pupilIds;
    int tempId = -1;
    for (int i = 0; i * sizeOfPupil < length; i++)
    {
        file.seekg(i * sizeOfPupil, ios::beg);
        getline(file, line);
        if (line.find("Id: ") != string::npos) {
            tempId = stoi(line.substr(line.find(": ") + 2));
            pupilIds.push_back(tempId);
        }
    }
    if (pupilIds.empty())
    {
        cout << "File is empty.\n";
        return;
    }
    file.close();
    for (int pupilId : pupilIds) {
		get_s("Slave.txt", pupilId);
	}
}

void ut_m(const string& fileName)
{
    fstream file(fileName);
    if (!file.is_open()) {
        cout << "File could not be opened\n";
        return;
    }

    file.seekg(0, ios::end);
    int length = file.tellg();
    file.seekg(0, ios::beg);
    string line;
    vector<int> groupIds;
    int tempId = -1;
    for (int i = 0; i * sizeOfGroup < length; i++)
    {
        file.seekg(i * sizeOfGroup, ios::beg);
        getline(file, line);
        if (line.find("Id: ") != string::npos) {
            tempId = stoi(line.substr(line.find(": ") + 2));
            groupIds.push_back(tempId);
        }
    }
    if (groupIds.empty())
    {
        cout << "File is empty.\n";
        return;
    }
    file.close();
    for (int groupId : groupIds) {
        get_m("Master.txt", groupId);
    }
}