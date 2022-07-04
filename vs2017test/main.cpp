#include <iostream>
#include <time.h>
#include "glut.h"
#include "GameManager.h"

using namespace std;

GameManager* gameManager;

void init()
{	//          Red Green Blue 
	glClearColor(1, 1, 1, 0);// color of window background

	// set the main axes
	glOrtho(0, MSZ, 0, MSZ, -1, 1);

	srand((unsigned int)time(NULL));
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	gameManager->show();

	glutSwapBuffers(); // show all
}

void idle()
{
	gameManager->idle();

	glutPostRedisplay(); // indirect call to refresh function (display)
}

void menu(int choice)
{
	gameManager->setGameState((GameManager::state)choice);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double buffering for animation
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(700, 50);
	glutCreateWindow("Final Project");

	glutDisplayFunc(display); // sets display function as window refresh function
	glutIdleFunc(idle); // runs all the time when nothing happens

	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Start Game", GameManager::state::START_GAME);
	glutAddMenuEntry("Stop Game", GameManager::state::STOP_GAME);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	gameManager = new GameManager("map.txt");

	glutMainLoop(); // starts window queue of events
	return EXIT_SUCCESS;
}
