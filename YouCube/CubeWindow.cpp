#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <gl/glut.h>
#include "Globals.h"
#include "CubeWindow.h"
#include "YouCube.h"
#include "ColorsPicker.h"

using namespace System;

namespace YouCube
{
	GLfloat Angle, RotationY, RotationX;
	int SelectionY, SelectionX, SelectionZ;

	static void menu(int index)
	{
		switch (index)
		{
		case 0: // Revert
			//TheCube->Revert();
		case 3: // Shuffle
			TheCube->Shuffle();
			break;
		case 6: // Colors
			ColorsPicker^ form;
			form = gcnew ColorsPicker();
			form->Show();
			break;
		case 7: // Exit
			DialogResult result; 
			result = MessageBox::Show("Do you want to exit?", "Close the application", MessageBoxButtons::YesNo);
			if (result == DialogResult::Yes) exit(0);
		}

		glutPostRedisplay();
	}

	static void createMenu(void)
	{
		glutCreateMenu(menu);
		//glutAddMenuEntry("Revert", 0);
		//glutAddMenuEntry("Hint", 1);
		//glutAddMenuEntry("Solve", 2);
		glutAddMenuEntry("Shuffle", 3);
		//glutAddMenuEntry("Save", 4);
		//glutAddMenuEntry("Load", 5);
		glutAddMenuEntry("Colors", 6);
		glutAddMenuEntry("Exit", 7);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}

	static void init()
	{
		SelectionY = SelectionX = SelectionZ = -1;
		RotationY = RotationX = Angle = 0.0;
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.75, 0.75, 0.75, 1.0);
		TheCube = new Cube;
	}

	// Arrow keys to rotate our view.
	static void SpecialKeys(int key, int x, int y)
	{
		switch (key)
		{
		case GLUT_KEY_RIGHT:
			RotationY += 5;
			break;
		case GLUT_KEY_LEFT:
			RotationY -= 5;
			break;
		case GLUT_KEY_UP:
			RotationX += 5;
			break;
		case GLUT_KEY_DOWN:
			RotationX -= 5;
			break;
		}
		glutPostRedisplay();
	}

	static void Display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(RotationX, 1.0, 0.0, 0.0);
		glRotatef(RotationY, 0.0, 1.0, 0.0);
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
				for (int z = 0; z < 3; z++)
				{
					glPushMatrix();
					glTranslatef(0.0, 0.0, 0.0);

					if (y == SelectionX) 
						glRotatef(Angle, 0.0, 1.0, 0.0); // X slice rotation
					else if (x == SelectionY)
						glRotatef(-Angle, 1.0, 0.0, 0.0); // Y slice rotation
					else if (z == SelectionZ)
						glRotatef(-Angle, 0.0, 0.0, 1.0); // Z slice rotation 

					glTranslatef(x * 2.1 - 3.1, y * 2.1 - 3.1, z * 2.1 - 3.1);
					TheCube->Display(x, y, z);
					glPopMatrix();
				}
		glutSwapBuffers();
	}

	static void Animation()
	{
		for (int i = 0; i < 9000; i++)
		{
			if (i % 100 != 0) continue;
			Angle++;
			Display();
		}
		Angle = 0.0;
	}

	static void Reshape(int w, int h)
	{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, w / (double)h, 1.0, 200);
		gluLookAt(
			0.0, 5.5, 15.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0);
	}

	static void Keyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 27:
			exit(0);

		// X rotation
		case 'q':
			SelectionX = 0;
			Animation();
			TheCube->RotateX(0);
			break;
		case 'w':
			SelectionX = 1;
			Animation();
			TheCube->RotateX(1);
			break;
		case 'e':
			SelectionX = 2;
			Animation();
			TheCube->RotateX(2);
			break;

		// Y rotation		
		case 'a':
			SelectionY = 0;
			Animation();
			TheCube->RotateY(0);
			break;
		case 's':
			SelectionY = 1;
			Animation();
			TheCube->RotateY(1);
			break;
		case 'd':
			SelectionY = 2;
			Animation();
			TheCube->RotateY(2);
			break;

		// Z rotation
		case 'z':
			SelectionZ = 0;
			Animation();
			TheCube->RotateZ(0);
			break;
		case 'x':
			SelectionZ = 1;
			Animation();
			TheCube->RotateZ(1);
			break;
		case 'c':
			SelectionZ = 2;
			Animation();
			TheCube->RotateZ(2);
			break;
		}

		glutPostRedisplay();
		SelectionY = -1;
		SelectionX = -1;
		SelectionZ = -1;
	}

	void start(int argc, char *argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(800, 800);
		glutCreateWindow("YouCube");

		init();
		createMenu();

		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		glutSpecialFunc(SpecialKeys);
		glutMainLoop();
	}
}