#pragma once

#include <exception>
using namespace std;

class MoveOnWallException: public exception
{
	virtual const char* what() const throw()
	{
		return "Robot moved on wall";
	}
} e_MoveOnWall;

class PickEmptyCellException: public exception
{
	virtual const char* what() const throw()
	{
		return "Robot picked empty cell";
	}
} e_PickEmptyCell;

class MoveOnRockException : public exception
{
	virtual const char* what() const throw()
	{
		return "Robot moved on rock";
	}
} e_MoveOnRock;
