#include "mesh.h"

#include <glad/glad.h>
#include <string>

using namespace std;

Mesh::Mesh(vector<Vertex> verts, vector<unsigned int> indi,
		   vector<Texture> texs)
{
	this->vertices = verts;
	this->indices = indi;
	this->textures = texs;

	setup();
}

void Mesh::Draw(Shader &shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = to_string(specularNr++);

		shader.setInt(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setup()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

// Move Constructor
Mesh::Mesh(Mesh&& other) noexcept 
    : vertices(std::move(other.vertices)), 
      indices(std::move(other.indices)), 
      textures(std::move(other.textures)),
      VAO(other.VAO), 
      VBO(other.VBO), 
      EBO(other.EBO) 
{
    // clear out the temporary object's buffers so we don't delete them in the destructor
    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
}

// move assignment
Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        
		// free the existing things
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        // get the new stuff
        vertices = std::move(other.vertices);
        indices = std::move(other.indices);
        textures = std::move(other.textures);
        VAO = other.VAO;
        VBO = other.VBO;
        EBO = other.EBO;

        // clean other object
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
    }
    return *this;
}

// destructor
Mesh::~Mesh() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
}