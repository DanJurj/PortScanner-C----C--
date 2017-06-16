#pragma once
#include"Errors.h"
class Exception
{
public:
	Exception(int cod, char* message);
	~Exception();
	void message();
	int  get_cod();

private:
	int		e_cod;
	char*	e_message;
};

