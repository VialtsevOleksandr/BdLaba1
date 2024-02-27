#pragma once

void del_s(const string& fileName, int id)
{
    fstream file(fileName, ios::in | ios::out);
    if (!file.is_open()) {
        cout << "File could not be opened\n";
        return;
    }

    int lineNumber = findIdInFile(fileName, id);
    if (lineNumber == -1)
    {
        cout << "Pupil with ID " << id << " not found.\n";
        return;
    }
    file.seekg(lineNumber, ios::beg);
    string emptyLine1 = string(11, ' ');
    file.write(emptyLine1.c_str(), emptyLine1.size());
    file << endl;
    string emptyLine2 = string(45, ' ');
    file.write(emptyLine2.c_str(), emptyLine2.size());
    file << endl;
    string emptyLine3 = string(46, ' ');
    file.write(emptyLine3.c_str(), emptyLine3.size());
    file << endl;
    string emptyLine4 = string(47, ' ');
    file.write(emptyLine4.c_str(), emptyLine4.size());
    file << endl;
    string emptyLine5 = string(21, ' ');
    file.write(emptyLine5.c_str(), emptyLine5.size());
    file << endl;
    string emptyLine6 = string(34, ' ');
    file.write(emptyLine6.c_str(), emptyLine6.size());
    file << endl;
    string emptyLine7 = string(15, ' ');
    file.write(emptyLine7.c_str(), emptyLine7.size());
    file << endl;
    string emptyLine8 = string(24, ' ');
    file.write(emptyLine8.c_str(), emptyLine8.size());
    file << endl;
    file.close();
}

void del_m(const string& fileName, int id)
{
	fstream file(fileName, ios::in | ios::out);
    if (!file.is_open()) {
		cout << "File could not be opened\n";
		return;
	}

	int lineNumber = findIdInFile(fileName, id);
    if (lineNumber == -1)
    {
		cout << "Group with ID " << id << " not found.\n";
		return;
	}
	file.seekg(lineNumber, ios::beg);
	string emptyLine1 = string(10, ' ');
	file.write(emptyLine1.c_str(), emptyLine1.size());
	file << endl;
	string emptyLine2 = string(30, ' ');
	file.write(emptyLine2.c_str(), emptyLine2.size());
	file << endl;
	string emptyLine3 = string(44, ' ');
	file.write(emptyLine3.c_str(), emptyLine3.size());
	file << endl;
    string emptyLine4 = string(22, ' ');
    file.write(emptyLine4.c_str(), emptyLine4.size());
    file << endl;
	file.close();

    ifstream file1("Slave.txt");
    if (!file1.is_open()) {
        cout << "File could not be opened\n";
        return;
    }
    string line;
    int nextPupilIdInGroup = -1;
    int tempId;
    vector<int> pupilIds;
    file1.seekg(0, ios::end);
    int length = file1.tellg();
    file1.seekg(0, ios::beg);
    for (int i = 1; i * sizeOfPupil <= length; i++)
    {
        file1.seekg(i * sizeOfPupil - 45, ios::beg);
        int temp = file1.tellg();
        getline(file1, line);
        if (line.find("IdOfGroup: " + to_string(id)) != string::npos) {
            file1.seekg(temp - 214, ios::beg);
            getline(file1, line);
            if (line.find("Id: ") != string::npos) {
                tempId = stoi(line.substr(line.find(": ") + 2));
                pupilIds.push_back(tempId);
            }
            file1.seekg(-11, ios::cur);
            file1.seekg(232, ios::cur);
            getline(file1, line);
            if(line.find("NextPupilIdInGroup: ") != string::npos)
            {
				nextPupilIdInGroup = stoi(line.substr(line.find(": ") + 2));
                if (nextPupilIdInGroup == tempId)
                {
                    for (int pupilId : pupilIds) {
                        del_s("Slave.txt", pupilId);
                    }
                    return;
                }
            }
            break;
		}
    }
    if(nextPupilIdInGroup == -1)
	{return;}
    do
    {
        file1.seekg(findIdInFile("Slave.txt", nextPupilIdInGroup) + 232, ios::beg);
        getline(file1, line);
        if (line.find("NextPupilIdInGroup: ") != string::npos)
        {
			tempId = nextPupilIdInGroup;
			nextPupilIdInGroup = stoi(line.substr(line.find(": ") + 2));
			pupilIds.push_back(tempId);
		}
    } while (nextPupilIdInGroup != tempId);

    file1.close();
    for (int pupilId : pupilIds) {
        del_s("Slave.txt", pupilId);
    }
}
