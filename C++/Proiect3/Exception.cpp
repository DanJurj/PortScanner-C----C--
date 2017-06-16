#include "Exception.h"

Exception::Exception(int cod, char* message)
{
	e_cod=cod;
	e_message=_strdup(message);
	CHECK_ALOC(e_message);
}

Exception::~Exception()
{
	delete []e_message;
}

void Exception::message()
{
	cout<<e_message<<endl;
}

int  Exception::get_cod()
{
	return e_cod;
}
