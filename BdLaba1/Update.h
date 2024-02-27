#pragma once

void update_m(const string& fileName, int id)
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
        file.close();
        return;
    }
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
    file.seekg(lineNumber + 11, ios::beg);
    file.write("GroupName: ", 12);
    file.write(string(group.GroupName).c_str(), 20);
    file.write("\nMottoOfGroup: ", 15);
    file.write(string(group.MottoOfGroup).c_str(), 30);
    file.write("\nMaxPupilsAmount: ", 18);
    file.write(to_string(group.MaxPupilsAmount).c_str(), 5);
    file.close();
}

void update_s(const string& fileName, int id)
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
		file.close();
		return;
	}
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

    file.seekg(lineNumber + 11, ios::beg);
    file.write("LastName: ", 10);
    file.write(string(pupil.LastName).c_str(), 35);
    file.write("\nFirstName: ", 12);
    file.write(string(pupil.FirstName).c_str(), 35);
    file.write("\nMiddleName: ", 13);
    file.write(string(pupil.MiddleName).c_str(), 35);
    file.write("\nBirthDay: ", 11);
    file.write(string(pupil.BirthDay).c_str(), 11);
    file.write("\nParentsPhoneNumber: ", 21);
    file.write(string(pupil.ParentsPhoneNumber).c_str(), 14);
    file.write("\nIdOfGroup: ", 12);
    file.write(to_string(pupil.GroupId).c_str(), 5);
    file.write("\nNextPupilIdInGroup: ", 21);
    file.write(to_string(id).c_str(), 5);
    file.close();
}
