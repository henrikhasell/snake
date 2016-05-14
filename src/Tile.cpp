#include "Tile.h"
#include "Terrain.h"

Tile *Tile::Up(Terrain &terrain)
{
    return terrain.GetTile(x + 0, y - 1);
}

Tile *Tile::Down(Terrain &terrain)

{
    return terrain.GetTile(x + 0, y + 1);
}

Tile *Tile::Left(Terrain &terrain)
{
    return terrain.GetTile(x - 1, y + 0);
}

Tile *Tile::Right(Terrain &terrain)
{
    return terrain.GetTile(x + 1, y + 0);
}

void Tile::Initialise(Type type, int x, int y)
{
    this->type = type;

    this->x = x;
    this->y = y;

    occupant = nullptr;
}
