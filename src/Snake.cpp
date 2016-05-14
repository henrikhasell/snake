#include "Snake.h"
#include "Terrain.h"
#include "Tile.h"
#include <cstdlib>
#include <cstdio>
#include <GL/gl.h>

Snake::Snake(Terrain &terrain, int x, int y) : direction(UP), length(1), growth(3)
{
    *position = terrain.GetTile(x, y);
}

Tile *Snake::GetNextTile(Terrain &terrain)
{
    return GetNextTile(terrain, direction);
}

Tile *Snake::GetNextTile(Terrain &terrain, Direction direction)
{
    Tile *head = position[0];

    switch(direction)
    {
        case UP:
            return head->Up(terrain);
        case DOWN:
            return head->Down(terrain);
        case LEFT:
            return head->Left(terrain);
        case RIGHT:
            return head->Right(terrain);
    }

    return nullptr;
}

void Snake::Collide(Terrain &terrain)
{
    if(length != 0)
    {
        Tile *head = position[0];

        switch(head->type)
        {
            case Tile::EMPTY:
                if(head->occupant)
                {
                    if(head->occupant == this)
                    {
                        printf("%p collided with itself!\n", this);
                    }
                    else
                    {
                        printf("%p collided with %p!\n", this, head->occupant);
                    }
                    Remove(terrain);
                }
                break;
            case Tile::FRUIT:
                printf("%p ate the fruit!\n", this);
                head->type = Tile::EMPTY;
                terrain.GetEmptyTile()->type = Tile::FRUIT;
                growth++;
                break;
            case Tile::WALL:
                printf("%p collided with a wall!\n", this);
                Remove(terrain);
                break;
        }

        if(length != 0)
        {
            position[0]->occupant = this;
        }
    }
}

void Snake::Remove(Terrain &terrain)
{
    for(int i = 0; i < length; i++)
    {
        position[i]->occupant = nullptr;
    }
    length = 0;
}

void Snake::SetDirection(Terrain &terrain, Direction direction)
{
    if(GetNextTile(terrain, direction) != position[1])
    {
        this->direction = direction;
    }
}

void Snake::Move(Terrain &terrain)
{
    if(length != 0)
    {
        for(int i = length; i > 0; i--)
        {
            position[i] = position[i - 1];
        }

        position[0] = GetNextTile(terrain);

        if(growth && length < MAXIMUM_SNAKE_LENGTH - 1)
        {
            length++;
            growth--;
        }
        else
        {
            position[length]->occupant = nullptr;
        }
    }
}

void Snake::Draw()
{
    glPushMatrix();
    glScalef(5.0f, 5.0f, 1.0f);
    for(int i = 0; i < length; i++)
    {
        Tile *selected = position[i];
        glPushMatrix();
            // Type-casting this often is unfortunate.
            glTranslatef(selected->x, selected->y, 0.0f);
            glBegin(GL_TRIANGLE_STRIP);
                glVertex2f(0.0f, 0.0f);
                glVertex2f(1.0f, 0.0f);
                glVertex2f(0.0f, 1.0f);
                glVertex2f(1.0f, 1.0f);
            glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}
