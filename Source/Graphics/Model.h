#pragma once
#include <vector>
#include <string>

class ShaderProgram;
class Mesh;

// Assimp //
struct aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;
enum aiTextureType;

class Model
{
public:
	Model(const std::string& filePath);

	void Update();
	void Draw(ShaderProgram* shaderProgram);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);

	std::string filePath;

	static std::vector<std::string> modelArchive;
};