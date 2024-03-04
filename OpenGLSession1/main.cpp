#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include "Vertex.h"
#include "ReadFiles.h"
#include <vector>
#include "glad/glad.h"
#include "Triangle.h"
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Line.h"
#include "Camera.h"
#include "Mesh.h"
#include "glm/gtx/rotate_vector.hpp"
#include "ShaderProgram.h"
#include <gl/GL.h>
#include "AppManager.h"
#include "Window.h"
#include "Model.h"
#include "MeshLoader.h"
#include "Character.h"


AppManager appManager;
Window Mywindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------

    unsigned int SCR_WIDTH = 1920;
    unsigned int SCR_HEIGHT = 1080;
    appManager.SetScreenSize(SCR_WIDTH, SCR_HEIGHT);

    GLFWwindow* window = Mywindow.Setup(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int shaderProgram = ShaderProgram::CreateProgram();

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);




	MeshLoader meshLoader;
    // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ##
    ///////////////////////////////////////////////// HERE YOU CAN LOAD MESH //////////////////////////////////////////////
    // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ## // ##

    Mesh* SphereDisplayMesh = meshLoader.LoadMesh("Defaults/Mesh/SphereStripped.fbx", shaderProgram);
    SphereDisplayMesh->SetName("SphereDisplayMesh");
    Mesh* CubeDisplayMesh = meshLoader.LoadMesh("Defaults/Mesh/CubeStripped.fbx", shaderProgram);
    CubeDisplayMesh->SetName("CubeDisplayMesh");

	Mesh* CharacterMesh = meshLoader.LoadMesh("C:/Users/soroe/Documents/Oblig2Prog/Character.fbx", shaderProgram);
    //CharacterMesh->AddAxisAlignedBoundingBoxCollider(glm::vec3(0, 1, 0), glm::vec3(.4, 1, .4), CubeDisplayMesh);
    CharacterMesh->AddAxisAlignedBoundingBoxColliderAuto(CubeDisplayMesh);
    CharacterMesh->SetName("CharacterMesh");

    
    Mesh* FelixCubeMesh = meshLoader.LoadMesh("C:/Users/soroe/Documents/FelixCube.fbx", shaderProgram);
    FelixCubeMesh->SetName("FelixCubeMesh");
    FelixCubeMesh->AddAxisAlignedBoundingBoxCollider(glm::vec3(0, 0, 0), glm::vec3(1), CubeDisplayMesh);
	//FelixCubeMesh->AddSphereCollider(glm::vec3(2,-1,0),2, SphereDisplayMesh);

    Mesh* GroundPlaneMesh = meshLoader.LoadMesh("C:/Users/soroe/Documents/Oblig2Prog/GroundPlane.fbx", shaderProgram);
    GroundPlaneMesh->SetName("GroundPlaneMesh");
    GroundPlaneMesh->AddAxisAlignedBoundingBoxCollider(glm::vec3(0, 0, 0), glm::vec3(40, 0.1, 40), CubeDisplayMesh);

    Mesh* HouseMesh = meshLoader.LoadMesh("C:/Users/soroe/Documents/Oblig2Prog/House.fbx", shaderProgram);
    HouseMesh->SetName("HouseMesh");

    
    Model* FelixCubeModel = new Model();
    FelixCubeModel->SetName("FelixCubeModel");
    FelixCubeModel->AddMesh(FelixCubeMesh);
    FelixCubeModel->SetLocation(glm::vec3(3, 2, 0));
    appManager.AddModel(FelixCubeModel);

    Model* FelixCubeModel2 = new Model();
    FelixCubeModel2->SetName("FelixCubeModel2");
    FelixCubeModel2->AddMesh(FelixCubeMesh);
    FelixCubeModel2->SetLocation(glm::vec3(0, 2, 0));
    appManager.AddModel(FelixCubeModel2);
    
    Model* CubeTest = new Model();
    CubeTest->SetName("CubeTest");
    CubeTest->AddMesh(FelixCubeMesh);
    CubeTest->SetLocation(glm::vec3(10, 10, 10));
    appManager.AddModel(CubeTest);




    Model* GroundPlaneModel = new Model();
    GroundPlaneModel->SetName("GroundPlane");
    GroundPlaneModel->AddMesh(GroundPlaneMesh);
    appManager.AddModel(GroundPlaneModel);

    Model* HouseModel = new Model();
    HouseModel->SetName("House");
    HouseModel->AddMesh(HouseMesh);
    //appManager.AddModel(HouseModel);

    Character* MyCharacter = new Character();
    MyCharacter->SetName("MyCharacter");
    MyCharacter->AddMesh(CharacterMesh);
    MyCharacter->SetLocation(glm::vec3(1, 6, 1));
    appManager.AddModel(MyCharacter);
    //appManager.AddModel(HouseModel);

    appManager.Setup(shaderProgram);


    // render loop
    // -----------
  
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        
        appManager.Update();
        

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);


        
    	glUseProgram(shaderProgram);

       
        appManager.Tick();
        appManager.Draw();
        

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    appManager.CleanUp();

    glDeleteProgram(shaderProgram);
    
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // // // Change Poligon mode
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 

    // // // Camera Input
  
    
    appManager.HandleInput(window);

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        std::cout << appManager.GetClosestModel()->GetName() << std::endl;

    }

    // if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    // {
    //     std::cout << "Tab" << std::endl;
    //     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //
    // }
    // if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
    // {
    //     std::cout << "Tab" << std::endl;
    //     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    // }


    if (appManager.SelectedModel != nullptr)
    {
        if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(0, 0, -2) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(0, 0, 2) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(2, 0, 0) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(-2, 0, 0) * appManager.GetDeltaTime());
        }

        if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(0, 2, 0) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(0, -2, 0) * appManager.GetDeltaTime());
        }

        if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddScale(glm::vec3(0.5) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddScale(glm::vec3(-0.5) * appManager.GetDeltaTime());
        }
    
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddRotation(glm::vec3(0,90,0)*appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddRotation(glm::vec3(0, -90, 0) * appManager.GetDeltaTime());
        }
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    appManager.SetScreenSize(width, height);
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    appManager.myCamera->AddRotation(static_cast<float>(xpos), static_cast<float>(ypos));
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    appManager.myCamera->SetSpeed(appManager.myCamera->GetSpeed() + (static_cast<float>(yoffset) * 1000) * appManager.GetDeltaTime());
    std::cout << appManager.myCamera->GetSpeed() << std::endl;

    
}