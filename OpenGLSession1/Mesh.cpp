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
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glBindVertexArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 2);
    glBindVertexArray(2);

    meshMemoryLocation = glGetUniformLocation(ShaderProgram, "mesh");
    
    if(!SphereColliders.empty())
    {
        for (auto SphCol : SphereColliders)
        {
            if(SphCol->DisplayMesh)
            {
                SphCol->DisplayMesh->Bind(ShaderProgram);
            }
        }
    }
    if (!AxisAlignedBoundingBoxColliders.empty())
    {
        for (auto AABBCol : AxisAlignedBoundingBoxColliders)
        {
            if (AABBCol->DisplayMesh)
            {
                AABBCol->DisplayMesh->Bind(ShaderProgram);
            }
        }
    }
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

    if(!SphereColliders.empty())
    {
        for (auto SphCol : SphereColliders)
        {
            SphCol->DrawDisplayMesh();
            //if(SphCol->DisplayMesh)
            //{
            //    SphCol->DisplayMesh->Draw(SphCol->CalculateMatrix());
            //}
        }
    }
    if (!AxisAlignedBoundingBoxColliders.empty())
    {
        for (auto AABBCol : AxisAlignedBoundingBoxColliders)
        {
            AABBCol->DrawDisplayMesh();
            //if (AABBCol->DisplayMesh)
            //{
            //    AABBCol->DisplayMesh->Draw(AABBCol->CalculateMatrix());
            //}
        }
    }

}

void Mesh::Draw(glm::mat4 ParentMat)
{
    glUniformMatrix4fv(meshMemoryLocation, 1, GL_FALSE, glm::value_ptr(ParentMat * CalculateMeshMatrix()));
    

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

   /* if(!SphereColliders.empty())
    {
        for (auto SphCol : SphereColliders)
        {
            if(SphCol->DisplayMesh)
            {
                SphCol->DisplayMesh->Draw();
            }
        }
    }
    if (!AxisAlignedBoundingBoxColliders.empty())
    {
        for (auto AABBCol : AxisAlignedBoundingBoxColliders)
        {
            if (AABBCol->DisplayMesh)
            {
                AABBCol->DisplayMesh->Draw(AABBCol->CalculateMatrix());
            }
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

glm::vec3 Mesh::CalculateCenter()
{

    if (vertices.empty())
    {
        return glm::vec3(0,0,0);
    }


    float XValue = 0, YValue = 0, ZValue = 0;


	for (auto vert : vertices)
	{
        glm::vec3 Pos = vert.Position;

        XValue += Pos.x;
        YValue += Pos.y;
        ZValue += Pos.z;


	}


    float avgX = XValue / vertices.size();
    float avgY = YValue / vertices.size();
    float avgZ = ZValue / vertices.size();

    return glm::vec3(avgX, avgY, avgZ);

}

glm::vec3 Mesh::CalculateScale()
{
    if (vertices.empty())
    {
        return glm::vec3(0, 0, 0);
    }


    float XMax = 0, XMin = 0;
    float YMax = 0, YMin = 0;
    float ZMax = 0, ZMin = 0;


    for (auto vert : vertices)
    {
        if (vert.Position.x < XMin) XMin = vert.Position.x;
        if (vert.Position.x > XMax) XMax = vert.Position.x;

        if (vert.Position.y < YMin) YMin = vert.Position.y;
        if (vert.Position.y > YMax) YMax = vert.Position.y;

        if (vert.Position.z < ZMin) ZMin = vert.Position.z;
        if (vert.Position.z > ZMax) ZMax = vert.Position.z;
    }

    float SizeX = abs(XMax - XMin) / 2;
    float SizeY = abs(YMax - YMin) / 2;
    float SizeZ = abs(ZMax - ZMin) / 2;

    return glm::vec3(SizeX, SizeY, SizeZ);
}

void Mesh::AddSphereCollider(glm::vec3 Location, float Radius)
{
    SphereCollider* NewSphereCollider = new SphereCollider(Location, Radius);
    SphereColliders.emplace_back(NewSphereCollider);
}

void Mesh::AddSphereCollider(glm::vec3 Location, float Radius, Mesh* DisplayMesh)
{
    SphereCollider* NewSphereCollider = new SphereCollider(Location, Radius);
    NewSphereCollider->DisplayMesh = DisplayMesh;
    SphereColliders.emplace_back(NewSphereCollider);
}

void Mesh::AddAxisAlignedBoundingBoxCollider(glm::vec3 Location, glm::vec3 Scale)
{
    
    AxisAlignedBoundingBox* NewAxisAlignedBoxCollider = new AxisAlignedBoundingBox(Location, Scale);
    AxisAlignedBoundingBoxColliders.emplace_back(NewAxisAlignedBoxCollider);
}

void Mesh::AddAxisAlignedBoundingBoxCollider(glm::vec3 Location, glm::vec3 Scale, Mesh* DisplayMesh)
{
    CalculateScale();
    AxisAlignedBoundingBox* NewAxisAlignedBoxCollider = new AxisAlignedBoundingBox(Location, Scale);
    NewAxisAlignedBoxCollider->DisplayMesh = DisplayMesh;
    AxisAlignedBoundingBoxColliders.emplace_back(NewAxisAlignedBoxCollider);
}

void Mesh::AddAxisAlignedBoundingBoxColliderAuto(Mesh* DisplayMesh)
{
    
    AxisAlignedBoundingBox* NewAxisAlignedBoxCollider = new AxisAlignedBoundingBox(CalculateCenter(), CalculateScale());
    NewAxisAlignedBoxCollider->DisplayMesh = DisplayMesh;
    AxisAlignedBoundingBoxColliders.emplace_back(NewAxisAlignedBoxCollider);
}

