#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& texture){
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    VAO.Bind();

	VBO VBO(vertices);
	EBO EB0(indices);

	VAO.LinkAttrib(VBO,0,3,GL_FLOAT, 11 * sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO,1,3,GL_FLOAT, 11 * sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO,2,2,GL_FLOAT, 11 * sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO,3,3,GL_FLOAT, 11 * sizeof(Vertex), (void*)(8 * sizeof(float)));


	VAO.Unbind();
	VBO.Unbind();
	EB0.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera){
	// Bind shader to be able to access uniforms
	shader.Activate();
	VAO.Bind();

	// Keep track of how many of each type of textures we have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}