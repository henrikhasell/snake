#include "Terrain.h"
#include "Tile.h"
#include <cstdlib>
#include <cstdio>
#include <GL/glut.h>

Terrain::Terrain(int w, int h, const char data[]) : Terrain(w, h)
{
    for(int x = 0; x < w; x++)
    {
        for(int y = 0; y < h; y++)
        {
            Tile::Type type;

            switch(data[x + (y * w)])
            {
                case 1:
                    type = Tile::WALL; break;
                case 2:
                    type = Tile::FRUIT; break;
                default:
                    type = Tile::EMPTY; break;
            }

            GetTile(x, y)->Initialise(type, x, y);
        }
    }
}

Terrain::Terrain(int w, int h)
{
    this->w = w;
    this->h = h;

    tiles = new Tile[w * h];
}

Terrain::~Terrain()
{
    delete[] tiles;
}

Tile *Terrain::GetTile(int x, int y)
{
    if(x < 0)
    {
        x += w;
    }

    else if(x >= w)
    {
        x -= w;
    }

    if(y < 0)
    {
        y += h;
    }

    else if(y >= h)
    {
        y -= h;
    }

    return tiles + x + (y * w);
}

Tile *Terrain::GetEmptyTile()
{
    Tile *result;

    do
    {
        result = GetTile(rand() % w, rand() % h);
    }
    while(result->type != Tile::EMPTY || result->occupant);

    return result;
}

void Terrain::Draw()
{
    glPushMatrix();
    glScalef(5.0f, 5.0f, 1.0f);
    for(int x = 0; x < w; x++)
    {
        glPushMatrix();
        for(int y = 0; y < h; y++)
        {
            Tile *tile = GetTile(x, y);

            switch(tile->type)
            {
                case Tile::EMPTY:
                    glColor3f(0.5f, 0.5f, 0.5f);
                    break;
                case Tile::WALL:
                    glColor3f(0.1f, 0.1f, 0.1f);
                    break;
                case Tile::FRUIT:
                    glColor3f(0.0f, 1.0f, 0.0f);
                    break;
            }

            glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(1.0f, 0.0f);
            glVertex2f(0.0f, 1.0f);
            glVertex2f(1.0f, 1.0f);
            glEnd();

            glTranslatef(0.0f, 1.0f, 0.0f);
        }
        glPopMatrix();
        glTranslatef(1.0f, 0.0f, 0.0f);
    }
    glPopMatrix();
}
