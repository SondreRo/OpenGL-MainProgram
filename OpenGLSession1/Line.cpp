#include "Line.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

Line::Line()
{
	
	ModelLocation = glm::vec3(0);
	ModelRotation = glm::vec3(0);
	ModelScale = glm::vec3(1);
}

void Line::Bind(unsigned ShaderProgram)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    modelMemoryLocation = glGetUniformLocation(ShaderProgram, "model");
}

void Line::Draw()
{
	glLineWidth(4);
	glPointSize(5);
    glUniformMatrix4fv(modelMemoryLocation, 1, GL_FALSE, glm::value_ptr(CalculateMeshMatrix()));
    glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP,0, mVertices.size());
}

glm::mat4 Line::CalculateMeshMatrix()
{
    glm::mat4 MeshMatrix(1.0f);

    MeshMatrix *= glm::translate(glm::mat4(1.0f), ModelLocation);

    MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(ModelRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(ModelRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(ModelRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    MeshMatrix *= glm::scale(glm::mat4(1.0f), ModelScale);

    return MeshMatrix;
}

void Line::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
