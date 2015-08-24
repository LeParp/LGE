#ifndef GROUND_H
#define GROUND_H

class Mesh;
class Ground
{
    public:
        Ground();

        void set_terrain(Mesh& terrain);

    private:
        Mesh* terrain_;
};

#endif // GROUND_H
