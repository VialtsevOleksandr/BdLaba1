#pragma once

struct Pupil
{
	static int currentId;
	int Id;
	char LastName[35];
	char FirstName[35];
	char MiddleName[35];
	char BirthDay[11];
	char ParentsPhoneNumber[14];
	int GroupId;
	int nextPupilIdInGroup;

	Pupil()
	{
		Id = currentId++;
	}
};

int Pupil::currentId = 1;
