#include "Mesh.h"

//#include <windows.h>

#include "AppManager.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include "Vertex.h"
#include "Model.h"
#include "Triangle.h"

//#include "glad/glad.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/type_ptr.hpp"
//#include "glm/gtx/euler_angles.hpp"
//#include "glm/gtx/matrix_decompose.hpp"
//#include "glm/gtx/quaternion.hpp"
//#include "glm/gtx/rotate_vector.hpp"
//#include "AppManager.h"


Mesh::Mesh()
{
    VBO = -1;
    VAO = -1;
    EBO = -1;
    meshMemoryLocation = -1;
}

Mesh::Mesh(std::vector<Vertex> Vertices, std::vector<unsigned> indices, std::vector<Texture> textures)
{
    this->vertices = Vertices;
    this->indices = indices;
    this->textures = textures;


    VBO = -1;
    VAO = -1;
    EBO = -1;
    meshMemoryLocation = -1;
}


void Mesh::Bind(unsigned int ShaderProgram)
{
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Index), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // TextureCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glBindVertexArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 2);
    glBindVertexArray(2);

    meshMemoryLocation = glGetUniformLocation(ShaderProgram, "mesh");

}

void Mesh::Draw()
{    
    if(textures.empty())
    {
        glBindTexture(GL_TEXTURE_2D, -1);
    }
    else
    {
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glBindTexture(GL_TEXTURE_2D, textures[0].id);
        }
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

    glActiveTexture(GL_TEXTURE0);

}

void Mesh::CleanUp()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

std::string Mesh::GetName()
{
    return Name;
}

void Mesh::SetName(std::string NewName)
{
    Name = NewName;
}