#ifndef TILE_H
#define TILE_H

class Terrain;
class Snake;

class Tile
{
	public:
		enum Type
		{
			EMPTY, FRUIT, WALL
		};

		Tile *Up(Terrain &terrain);
		Tile *Down(Terrain &terrain);
		Tile *Left(Terrain &terrain);
		Tile *Right(Terrain &terrain);

		void Initialise(Type type, int x, int y);

		Type type;

		int x;
		int y;

		Snake *occupant;
};

#endif // TILE_H
