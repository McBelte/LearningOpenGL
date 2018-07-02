#include <vector>
#include <string>

#include "Shader.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
    Model(const char* path);
    void Draw(const Shader& shader) const;

private:
    std::vector<Texture> m_texturesLoaded;
    std::vector<Mesh> m_meshes;
    std::string m_directory;

    void loadModel(const std::string& path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
};

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);