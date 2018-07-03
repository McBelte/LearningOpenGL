#include "Shader.h"
#include "Mesh.h"

class Grid {
public:
    Grid(double size);
    void Draw(const Shader& shader) const;
private:
    void createGrid(double size);

    Mesh m_mesh;
};