#include "stdafx.h"
#include "CubeWindow.h"
using namespace YouCube;

int main(array<System::String^>^ args)
{
	char arg[] = "";
	char *argv[1] = { arg };
	gcnew CubeWindow(1, argv);
	return 0;
}