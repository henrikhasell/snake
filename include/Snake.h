#ifndef SNAKE_H
#define SNAKE_H

#define MAXIMUM_SNAKE_LENGTH 32

class Terrain;
class Tile;

class Snake
{
    public:
        enum Direction
        {
            UP, DOWN, LEFT, RIGHT
        };

        Snake(Terrain &terrain, int x, int y);
        Tile *GetNextTile(Terrain &terrain);
        Tile *GetNextTile(Terrain &terrain, Direction direction);
        void SetDirection(Terrain &terrain, Direction direction);
        void Collide(Terrain &terrain);
        void Remove(Terrain &terrain);
        void Move(Terrain &terrain);
        void Draw();
    private:
        Tile *position[MAXIMUM_SNAKE_LENGTH];
        Direction direction;
        int length;
        int growth;
};

#endif // SNAKE_H
