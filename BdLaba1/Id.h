#pragma once

int findIdInFile(const string& fileName, int id) {
	ifstream inf(fileName);
	if (!inf) {
		cout << "File could not be opened\n";
		return -1;
	}
	inf.seekg(0, ios::end);
	int length = inf.tellg();
	inf.seekg(0, ios::beg);
	string line;
	int lineNumber = 0;
	if (fileName == "Master.txt") {
		for (int i = 0; i * sizeOfGroup < length; i++)
		{
			inf.seekg(i * sizeOfGroup, ios::beg);
			getline(inf, line);
			if (line.find("Id: " + to_string(id)) != string::npos) {
				lineNumber = i * sizeOfGroup;
				return lineNumber;
			}
		}
		inf.close();
		return -1;
	}
	else if (fileName == "Slave.txt") {
		for (int i = 0; i * sizeOfPupil < length; i++)
		{
			inf.seekg(i * sizeOfPupil, ios::beg);
			getline(inf, line);
			if (line.find("Id: " + to_string(id)) != string::npos) {
				lineNumber = i * sizeOfPupil;
				return lineNumber;
			}
		}
	}
	inf.close();
	return -1;
}

void inputGroup(Group& group) {
	cout << "GroupName: ";
	cin >> group.GroupName;
	if (strlen(group.GroupName) > 20)
	{
		throw invalid_argument("GroupName is too long. Please enter up to 20 characters.");
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
	cout << "MottoOfGroup: ";
	cin.getline(group.MottoOfGroup, 30);
	if (cin.fail()) // Если cin.getline не смог прочитать строку
	{
		cin.clear(); // Очистка флагов ошибок
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
		throw invalid_argument("MottoOfGroup is too long. Please enter up to 30 characters.");
	}
	string maxPupilsInput;
	cout << "MaxPupilsAmount: ";
	cin >> maxPupilsInput;
	istringstream iss(maxPupilsInput);
	int maxPupilsAmount;
	if (!(iss >> maxPupilsAmount) || !iss.eof())
	{
		throw invalid_argument("Invalid input for MaxPupilsAmount. Please enter an integer.");
	}
	group.MaxPupilsAmount = maxPupilsAmount;
}

void inputPupil(Pupil& pupil) {
    cout << "LastName: ";
    cin >> pupil.LastName;
    if (strlen(pupil.LastName) > 35)
    {
        throw invalid_argument("LastName is too long. Please enter up to 35 characters.");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
    cout << "FirstName: ";
    cin >> pupil.FirstName;
    if (strlen(pupil.FirstName) > 35)
    {
        throw invalid_argument("FirstName is too long. Please enter up to 35 characters.");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "MiddleName: ";
    cin >> pupil.MiddleName;
    if (strlen(pupil.MiddleName) > 35)
    {
        throw invalid_argument("MiddleName is too long. Please enter up to 35 characters.");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "BirthDay(dd/mm/yyyy): ";
    cin >> pupil.BirthDay;
    if (strlen(pupil.BirthDay) > 11)
    {
        throw invalid_argument("BirthDay is too long. Please enter up to 11 characters.");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "ParentsPhoneNumber: ";
    cin >> pupil.ParentsPhoneNumber;
    if (strlen(pupil.ParentsPhoneNumber) > 14)
    {
        throw invalid_argument("ParentsPhoneNumber is too long. Please enter up to 14 characters.");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string groupIdInput;
	cout << "IdOfGroup: ";
	cin >> groupIdInput;
	istringstream iss(groupIdInput);
	int groupId;
	if (!(iss >> groupId) || !iss.eof())
	{
		throw invalid_argument("Invalid input for GroupId. Please enter an integer.");
	}
	if (findIdInFile("Master.txt", groupId) == -1) {
		throw invalid_argument("Group with such id does not exist.");
	}
	pupil.GroupId = groupId;
}
