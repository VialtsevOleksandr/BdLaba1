#pragma once

struct Group
{
	static int currentId;
	int Id;
	char GroupName[20];
	char MottoOfGroup[30];
	int MaxPupilsAmount;
	Group()
	{
		Id = currentId++;
	}
};

int Group::currentId = 1;
