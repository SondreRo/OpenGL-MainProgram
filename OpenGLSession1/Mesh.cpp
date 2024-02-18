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
    MeshLocation = glm::vec3(0.0f);
    MeshRotation = glm::vec3(0.0f);
    MeshScale = glm::vec3(1.0f);

    VBO = -1;
    VAO = -1;
    EBO = -1;
    Owner = nullptr;
    meshMemoryLocation = -1;
}

Mesh::Mesh(std::vector<Vertex> Vertices, std::vector<unsigned> indices, std::vector<Texture> textures)
{
    this->vertices = Vertices;
    this->indices = indices;
    this->textures = textures;

    MeshLocation = glm::vec3(0.0f);
    MeshRotation = glm::vec3(0.0f);
    MeshScale = glm::vec3(1.0f);

    VBO = -1;
    VAO = -1;
    EBO = -1;
    Owner = nullptr;
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Triangle), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // TextureCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    


    meshMemoryLocation = glGetUniformLocation(ShaderProgram, "mesh");

   /* if(!SphereColliders.empty())
    {
	    for (auto sphere_collider: SphereColliders)
	    {
            if(sphere_collider->SphereMesh)
            {
                sphere_collider->SphereMesh->Bind(ShaderProgram);
            }
	    }
    }*/

}

void Mesh::Draw()
{    
    glUniformMatrix4fv(meshMemoryLocation, 1, GL_FALSE, glm::value_ptr(CalculateMeshMatrix()));

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


    /*if (!SphereColliders.empty())
    {
        for (auto sphere_collider : SphereColliders)
        {
            sphere_collider->SphereMesh->Draw();
        }
    }*/

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

glm::mat4 Mesh::CalculateMeshMatrix()
{
    glm::mat4 MeshMatrix(1.0f);

    MeshMatrix *= glm::translate(glm::mat4(1.0f), MeshLocation);

    MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(MeshRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(MeshRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    MeshMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(MeshRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    MeshMatrix *= glm::scale(glm::mat4(1.0f), MeshScale);
    glm::vec3 test = MeshMatrix[3];
    return MeshMatrix;
}

void Mesh::SetName(std::string NewName)
{
    Name = NewName;
}

Model* Mesh::GetOwner()
{
    return Owner;
}

void Mesh::SetLocation(glm::vec3 NewLocation)
{
    MeshLocation = NewLocation;
}

void Mesh::AddLocation(glm::vec3 AddLocation)
{
    MeshLocation += AddLocation;
}


glm::vec3 Mesh::GetLocation()
{
    return MeshLocation;//GetOwner()->GetLocation() + MeshLocation;
}

void Mesh::SetRotation(glm::vec3 NewRotation)
{
    MeshRotation = NewRotation;
}

void Mesh::AddRotation(glm::vec3 AddRotation)
{
    MeshRotation += AddRotation;
}

glm::vec3 Mesh::GetRotation()
{
    return MeshRotation;
}

void Mesh::SetScale(glm::vec3 NewScale)
{
    MeshScale = NewScale;
}

void Mesh::AddScale(glm::vec3 AddScale)
{
    MeshScale += AddScale;
}

glm::vec3 Mesh::GetScale()
{
    return MeshScale;//GetOwner()->GetScale() * MeshScale;
}
//
//void Mesh::AddSphereCollider(glm::vec3 Center, float Radius, Mesh* SphereMesh)
//{
//    SphereMesh->SetScale(glm::vec3(Radius));
//    SphereMesh->SetLocation(Center);
//    SphereCollider* new_sphere_collider = new SphereCollider(Center, Radius, true, SphereMesh);
//    new_sphere_collider->Owner = this;
//	SphereColliders.push_back(new_sphere_collider);
//    
//}
//
//void Mesh::AddAxisAlignedCollider(glm::vec3 Center, glm::vec3 Size, Mesh* BoxMesh)
//{
//    BoxMesh->SetScale(Size);
//    BoxMesh->SetLocation(Center);
//    AxisAlignedBox* new_box_collider = new AxisAlignedBox(Center, Size, true, BoxMesh);
//    AxisAlignedBoxColliders.push_back(new_box_collider);
//}
//
//std::vector<SphereCollider*> Mesh::GetSphereColliders()
//{
//    return SphereColliders;
//}
//
//std::vector<AxisAlignedBox*> Mesh::GetAxisAlignedBoxColliders()
//{
//    return AxisAlignedBoxColliders;
//}
