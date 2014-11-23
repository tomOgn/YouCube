#ifndef RUBIX_CUBE_H
#define RUBIX_CUBE_H

#include <cstdlib>
#include <list>
#include <GL/glut.h>

enum Side { FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM };
const Side Sides[] = { Side::FRONT, Side::BACK, Side::LEFT, Side::RIGHT, Side::TOP, Side::BOTTOM };

struct Move
{
public:
	Move();
	Move(int type, int level) { Type = type; Level = level; }
	int Type, Level;
};

class Item
{
    public:
		Item();
        int color[6];
		void RotateX();
		void RotateY();
		void RotateZ();
};

class Cube
{
    public:
		Cube();
		void Revert();
		void RotateX(size_t n);
		void RotateY(size_t n);
		void RotateZ(size_t n);
        void Display(size_t x, size_t y, size_t z);
		void Shuffle();
		bool IsCompleted();
		GLfloat Colors[6][3];
		GLfloat GetColors();
		void SetColors(GLfloat colors[6][3]);
    private:
		void CheckCube();
		void AddMove(int type, int level);
		Item _items[3][3][3];
		std::list<Move> _history;
};
#endif