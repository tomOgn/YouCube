#include "stdafx.h"
#include "ColorsPicker.h"
#include "Globals.h"

void ChangeColor(int face, Color color)
{
	TheCube->Colors[face][0] = (GLfloat)color.R / 255.f;
	TheCube->Colors[face][1] = (GLfloat)color.G / 255.f;
	TheCube->Colors[face][2] = (GLfloat)color.B / 255.f;
}