#ifndef GROUND_H
#define GROUND_H

class Mesh;
class Ground
{
    public:
        Ground(Mesh& mesh);

    private:
        Mesh& mesh_;
};

#endif // GROUND_H
