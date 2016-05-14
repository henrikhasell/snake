#include <iostream>
#include <GL/glut.h>
#include "Terrain.h"
#include "Snake.h"

#define FRAME_TIME 100

const char terrain_data[20 * 20] = {
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
};


Terrain terrain(20, 20, terrain_data);
Snake player(terrain, 10, 10);
Snake other(terrain, 8, 15);

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    terrain.Draw();
    glColor3f(1.0f, 0.0f, 0.0f);
    player.Draw();
    glColor3f(0.0f, 0.0f, 1.0f);
    other.Draw();
    glFinish();
}

void special(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            player.SetDirection(terrain, Snake::UP); break;
        case GLUT_KEY_DOWN:
            player.SetDirection(terrain, Snake::DOWN); break;
        case GLUT_KEY_LEFT:
            player.SetDirection(terrain, Snake::LEFT); break;
        case GLUT_KEY_RIGHT:
            player.SetDirection(terrain, Snake::RIGHT); break;
    }

}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
		case 'w': case 'W':
            other.SetDirection(terrain, Snake::UP);  break;
        case 's': case 'S':
            other.SetDirection(terrain, Snake::DOWN); break;
        case 'a': case 'A':
            other.SetDirection(terrain, Snake::LEFT); break;
        case 'd': case 'D':
            other.SetDirection(terrain, Snake::RIGHT); break;
    }
}

void timer(int i)
{
        glutTimerFunc(FRAME_TIME, timer, ++i);
        player.Move(terrain);
        other.Move(terrain);
        player.Collide(terrain);
        other.Collide(terrain);
        glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Simple Snake Game");
    glOrtho(0.0, 100.0, 100.0, 0.0, 1.0, -1.0);
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(FRAME_TIME, timer, 0);
    glutMainLoop();
    return 0;
}
