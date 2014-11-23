#include "stdafx.h"
#include "YouCube.h"
#include <list>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Xml;

// Initialize a single item.
Item::Item()
{
	for (int i = 0; i < 6; i++)
		color[i] = i;
}

// Initialize the Cube.
Cube::Cube()
{
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
				_items[x][y][z] = Item();

	Colors[0][0] = 1.0; Colors[0][1] = 0.0; Colors[0][2] = 0.0; // Red
	Colors[1][0] = 1.0; Colors[1][1] = 0.6; Colors[1][2] = 0.0; // Orange
	Colors[2][0] = 0.0; Colors[2][1] = 1.0; Colors[2][2] = 0.0; // Green
	Colors[3][0] = 0.0; Colors[3][1] = 0.0; Colors[3][2] = 1.0; // Blue
	Colors[4][0] = 1.0; Colors[4][1] = 1.0; Colors[4][2] = 0.0; // Yellow
	Colors[5][0] = 1.0; Colors[5][1] = 1.0; Colors[5][2] = 1.0; // White
}

// X item rotation.
void Item::RotateY()
{
	int front = color[Side::FRONT];
	color[Side::FRONT] = color[Side::BOTTOM];
	color[Side::BOTTOM] = color[Side::BACK];
	color[Side::BACK] = color[Side::TOP];
	color[Side::TOP] = front;
}

// Y item rotation.
void Item::RotateX()
{
	int front = color[Side::FRONT];
	color[Side::FRONT] = color[Side::RIGHT];
	color[Side::RIGHT] = color[Side::BACK];
	color[Side::BACK] = color[Side::LEFT];
	color[Side::LEFT] = front;
}

// Z item rotation.
void Item::RotateZ()
{
	int top = color[Side::TOP];
	color[Side::TOP] = color[Side::RIGHT];
	color[Side::RIGHT] = color[Side::BOTTOM];
	color[Side::BOTTOM] = color[Side::LEFT];
	color[Side::LEFT] = top;
}

// X slice rotation.
void Cube::RotateX(size_t n)
{
    Item temp = _items[0][n][0];
    _items[2][n][0].RotateX();
	_items[0][n][0] = _items[2][n][0];
    _items[2][n][2].RotateX();
	_items[2][n][0] = _items[2][n][2];
    _items[0][n][2].RotateX();
	_items[2][n][2] = _items[0][n][2];
    temp.RotateX();
	_items[0][n][2] = temp;

    temp = _items[0][n][1];
    _items[1][n][0].RotateX();
	_items[0][n][1] = _items[1][n][0];
    _items[2][n][1].RotateX();
	_items[1][n][0] = _items[2][n][1];
    _items[1][n][2].RotateX();
	_items[2][n][1] = _items[1][n][2];
    temp.RotateX();
	_items[1][n][2] = temp;
    _items[1][n][1].RotateX();

	CheckCube();
}

// Y slice rotation.
void Cube::RotateY(size_t n)
{
	Item temp = _items[n][0][0];
	_items[n][2][0].RotateY();
	_items[n][0][0] = _items[n][2][0];
	_items[n][2][2].RotateY();
	_items[n][2][0] = _items[n][2][2];
	_items[n][0][2].RotateY();
	_items[n][2][2] = _items[n][0][2];
	temp.RotateY();
	_items[n][0][2] = temp;

	temp = _items[n][0][1];
	_items[n][1][0].RotateY();
	_items[n][0][1] = _items[n][1][0];
	_items[n][2][1].RotateY();
	_items[n][1][0] = _items[n][2][1];
	_items[n][1][2].RotateY();
	_items[n][2][1] = _items[n][1][2];
	temp.RotateY();
	_items[n][1][2] = temp;
	_items[n][1][1].RotateY();

	CheckCube();
}

// Z slice rotation.
void Cube::RotateZ(size_t n)
{
    Item temp = _items[0][0][n];
	_items[2][0][n].RotateZ();
	_items[0][0][n] = _items[2][0][n];
	_items[2][2][n].RotateZ();
	_items[2][0][n] = _items[2][2][n];
	_items[0][2][n].RotateZ();
	_items[2][2][n] = _items[0][2][n];
	temp.RotateZ();
	_items[0][2][n] = temp;

    temp = _items[0][1][n];
	_items[1][0][n].RotateZ();
	_items[0][1][n] = _items[1][0][n];
	_items[2][1][n].RotateZ();
	_items[1][0][n] = _items[2][1][n];
	_items[1][2][n].RotateZ();
	_items[2][1][n] = _items[1][2][n];
	temp.RotateZ();
	_items[1][2][n] = temp;
	_items[1][1][n].RotateZ();

	CheckCube();
}

void Cube::Display(size_t x, size_t y, size_t z)
{
	Item theItem = _items[x][y][z];
	
    // Back face
	glBegin(GL_POLYGON);
		glColor3fv(&Colors[theItem.color[Side::BACK]][0]);
		glVertex3f(2.0, 0.0, 0.0);
		glVertex3f(2.0, 2.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();
        
    // Front face
	glBegin(GL_POLYGON);
		glColor3fv(&Colors[theItem.color[Side::FRONT]][0]);
		glVertex3f(2.0, 0.0, 2.0);
		glVertex3f(2.0, 2.0, 2.0);
		glVertex3f(0.0, 2.0, 2.0);
		glVertex3f(0.0, 0.0, 2.0);
	glEnd();

    // Left face
    glBegin(GL_POLYGON);
		glColor3fv(&Colors[theItem.color[Side::LEFT]][0]);
		glVertex3f(2.0, 0.0, 0.0);
		glVertex3f(2.0, 2.0, 0.0);
		glVertex3f(2.0, 2.0, 2.0);
		glVertex3f(2.0, 0.0, 2.0);
    glEnd();
 
    // Right face
    glBegin(GL_POLYGON);
		glColor3fv(&Colors[theItem.color[Side::RIGHT]][0]);
		glVertex3f(0.0, 0.0, 2.0);
		glVertex3f(0.0, 2.0, 2.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
    glEnd();
 
    // Top face
    glBegin(GL_POLYGON);
		glColor3fv(&Colors[theItem.color[Side::TOP]][0]);
		glVertex3f(2.0, 2.0, 2.0);
		glVertex3f(2.0, 2.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(0.0, 2.0, 2.0);
    glEnd();
 
    // Bottom face
    glBegin(GL_POLYGON);
		glColor3fv(&Colors[theItem.color[Side::BOTTOM]][0]);
		glVertex3f(2.0, 0.0, 0.0);
		glVertex3f(2.0, 0.0, 2.0);
		glVertex3f(0.0, 0.0, 2.0);
		glVertex3f(0.0, 0.0, 0.0);
    glEnd();
}

bool Cube::IsCompleted()
{
	// Check back face
	if (_items[0][0][0].color[Side::BACK] != _items[0][1][0].color[Side::BACK] ||
		_items[0][1][0].color[Side::BACK] != _items[0][2][0].color[Side::BACK] ||
		_items[0][2][0].color[Side::BACK] != _items[1][0][0].color[Side::BACK] ||
		_items[1][0][0].color[Side::BACK] != _items[1][1][0].color[Side::BACK] ||
		_items[1][1][0].color[Side::BACK] != _items[1][2][0].color[Side::BACK] ||
		_items[1][2][0].color[Side::BACK] != _items[2][0][0].color[Side::BACK] ||
		_items[2][0][0].color[Side::BACK] != _items[2][1][0].color[Side::BACK] ||
		_items[2][1][0].color[Side::BACK] != _items[2][2][0].color[Side::BACK])
		return false;

	// Check front face
	if (_items[0][0][2].color[Side::FRONT] != _items[0][1][2].color[Side::FRONT] ||
		_items[0][1][2].color[Side::FRONT] != _items[0][2][2].color[Side::FRONT] ||
		_items[0][2][2].color[Side::FRONT] != _items[1][0][2].color[Side::FRONT] ||
		_items[1][0][2].color[Side::FRONT] != _items[1][1][2].color[Side::FRONT] ||
		_items[1][1][2].color[Side::FRONT] != _items[1][2][2].color[Side::FRONT] ||
		_items[1][2][2].color[Side::FRONT] != _items[2][0][2].color[Side::FRONT] ||
		_items[2][0][2].color[Side::FRONT] != _items[2][1][2].color[Side::FRONT] ||
		_items[2][1][2].color[Side::FRONT] != _items[2][2][2].color[Side::FRONT])
		return false;

	// Check top face
	if (_items[0][2][0].color[Side::TOP] != _items[0][2][1].color[Side::TOP] ||
		_items[0][2][1].color[Side::TOP] != _items[0][2][2].color[Side::TOP] ||
		_items[0][2][2].color[Side::TOP] != _items[1][2][0].color[Side::TOP] ||
		_items[1][2][0].color[Side::TOP] != _items[1][2][1].color[Side::TOP] ||
		_items[1][2][1].color[Side::TOP] != _items[1][2][2].color[Side::TOP] ||
		_items[1][2][2].color[Side::TOP] != _items[2][2][0].color[Side::TOP] ||
		_items[2][2][0].color[Side::TOP] != _items[2][2][1].color[Side::TOP] ||
		_items[2][2][1].color[Side::TOP] != _items[2][2][2].color[Side::TOP])
		return false;

	// Check bottom face
	if (_items[0][0][0].color[Side::BOTTOM] != _items[0][0][1].color[Side::BOTTOM] ||
		_items[0][0][1].color[Side::BOTTOM] != _items[0][0][2].color[Side::BOTTOM] ||
		_items[0][0][2].color[Side::BOTTOM] != _items[1][0][0].color[Side::BOTTOM] ||
		_items[1][0][0].color[Side::BOTTOM] != _items[1][0][1].color[Side::BOTTOM] ||
		_items[1][0][1].color[Side::BOTTOM] != _items[1][0][2].color[Side::BOTTOM] ||
		_items[1][0][2].color[Side::BOTTOM] != _items[2][0][0].color[Side::BOTTOM] ||
		_items[2][0][0].color[Side::BOTTOM] != _items[2][0][1].color[Side::BOTTOM] ||
		_items[2][0][1].color[Side::BOTTOM] != _items[2][0][2].color[Side::BOTTOM])
		return false;

	// Check left face
	if (_items[2][0][0].color[Side::LEFT] != _items[2][1][0].color[Side::LEFT] ||
		_items[2][1][0].color[Side::LEFT] != _items[2][2][0].color[Side::LEFT] ||
		_items[2][2][0].color[Side::LEFT] != _items[2][0][1].color[Side::LEFT] ||
		_items[2][0][1].color[Side::LEFT] != _items[2][1][1].color[Side::LEFT] ||
		_items[2][1][1].color[Side::LEFT] != _items[2][2][1].color[Side::LEFT] ||
		_items[2][2][1].color[Side::LEFT] != _items[2][0][2].color[Side::LEFT] ||
		_items[2][0][2].color[Side::LEFT] != _items[2][1][2].color[Side::LEFT] ||
		_items[2][1][2].color[Side::LEFT] != _items[2][2][2].color[Side::LEFT])
		return false;

	// Check right face
	if (_items[0][0][0].color[Side::RIGHT] != _items[0][1][0].color[Side::RIGHT] ||
		_items[0][1][0].color[Side::RIGHT] != _items[0][2][0].color[Side::RIGHT] ||
		_items[0][2][0].color[Side::RIGHT] != _items[0][0][1].color[Side::RIGHT] ||
		_items[0][0][1].color[Side::RIGHT] != _items[0][1][1].color[Side::RIGHT] ||
		_items[0][1][1].color[Side::RIGHT] != _items[0][2][1].color[Side::RIGHT] ||
		_items[0][2][1].color[Side::RIGHT] != _items[0][0][2].color[Side::RIGHT] ||
		_items[0][0][2].color[Side::RIGHT] != _items[0][1][2].color[Side::RIGHT] ||
		_items[0][1][2].color[Side::RIGHT] != _items[0][2][2].color[Side::RIGHT])
		return false;

	return true;
}

void Cube::Shuffle()
{
	int color[6] = { 0, 0, 0, 0, 0, 0 };
	int choice;
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
				for (int side = 0; side < 6; side++)
				{
					do
						choice = rand() % 6;
					while (color[choice] > 27);
					color[choice]++;
					_items[x][y][z].color[side] = choice;
				}
}

/* Verify victory. */
void Cube::CheckCube()
{
	if (!IsCompleted()) return;

	MessageBox::Show("You have won!", "Victory", MessageBoxButtons::OK);
}

// Add a move in game history.
void Cube::AddMove(int type, int level)
{
	if (_history.size() >= _history.max_size()) return;

	_history.push_back(Move(type, level));
}

// Revert the last move previously saved in game history.
void Cube::Revert()
{
	if (_history.size() == 0) return;

	Move move = _history.back();
}

GLfloat Cube::GetColors()
{ 
	return 0.0;
}

void Cube::SetColors(GLfloat colors[6][3])
{

}