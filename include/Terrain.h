#ifndef TERRAIN_H
#define TERRAIN_H

class Tile;

class Terrain
{
    public:
        Terrain(int w, int h, const char data[]);
        Terrain(int w, int h);
        ~Terrain();

        Tile *GetTile(int x, int y);
        Tile *GetEmptyTile();

        void Draw();
    private:
        Tile *tiles;
        int w;
        int h;
};

#endif // TERRAIN_H
