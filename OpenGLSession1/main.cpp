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


AppManager appManager;
Window Mywindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings


Camera myCamera;

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

    myCamera.AddShaderProgramPath(shaderProgram);
    myCamera.AddAppManager(&appManager);
    appManager.myCamera = &myCamera;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);


/*    Line MyLine;
    ReadFiles::ReadFileVertexData("D:/School/Matte3/09.01/Testing/Oppgave2.txt", MyLine);
    MyLine.Bind(shaderProgram);*/ 

    // Mesh Homer;
    // ReadFiles::ReadOBJ("C:/Users/soroe/Documents/CubeToTestWith.obj", Homer);
    // Meshes.push_back(&Homer);
    // Homer.SetLocation(glm::vec3(0, 3, 0));


    //Mesh Center;
    //ReadFiles::ReadOBJ("C:/Users/soroe/Documents/Center.obj", Center);
    //Model CenterModel;
    //CenterModel.AddMesh(&Center);
    //CenterModel.SetName("Center Point");
    //appManager.AddModel(&CenterModel);


    // BALL 1 //////////////////////
    //Mesh Ball1;
    //ReadFiles::ReadOBJ("C:/Users/soroe/Documents/Ball.obj", Ball1);
    //Ball1.AddSphereCollider(glm::vec3(0,0,0), 1);
    ////Ball1.AddSphereCollider(glm::vec3(0, 1, 0), 1);
    //Ball1.AddLocation(glm::vec3(0, 0, 0));


    //Model BallModel;
    //BallModel.AddMesh(&Ball1);
    //BallModel.AddMesh(&Ball1);

    //BallModel.SetName("Ball1");
    //appManager.AddModel(&BallModel);
    //BallModel.SetLocation(glm::vec3(5, 0, 0));


    //Mesh Ball2 = Ball1;
    ////ReadFiles::ReadOBJ("C:/Users/soroe/Documents/Ball.obj", Ball2);
    //Ball2.AddSphereCollider(glm::vec3(0, 0, 0), 1);

    //Model BallModel2;
    //BallModel2.AddMesh(&Ball2);
    //BallModel2.SetName("Ball2");
    //appManager.AddModel(&BallModel2);
    //BallModel2.SetLocation(glm::vec3(8, 0, 0));




 //   Mesh MyTestMeshMonke;
 //   ReadFiles::ReadOBJ("C:/Users/soroe/Documents/monke.obj", MyTestMeshMonke);
 //   MyTestMeshMonke.AddSphereCollider(glm::vec3(3, 0, 0), 1);
	//Model MonkeyModel;
 //   MonkeyModel.SetLocation(glm::vec3(-3, 0, 0));
 //   MonkeyModel.AddMesh(&MyTestMeshMonke);
 //   MonkeyModel.SetName("Monkey");


 //   appManager.AddModel(&MonkeyModel);

    
    //Mesh Mountains;
    //ReadFiles::ReadOBJ("C:/Users/soroe/Documents/Mountain1.obj", Mountains);
    //Model MountainModel;
    //MountainModel.AddMesh(&Mountains);
    //MountainModel.SetLocation(glm::vec3(10, 0, 0));
    //MountainModel.SetScale(glm::vec3(10));
    //MountainModel.SetName("Mountain");

    //appManager.AddModel(&MountainModel);


    Model MyNewTestModel;
    //MyNewTestModel.LoadModel("C:/Users/soroe/Documents/MyCube.fbx");
    MyNewTestModel.LoadModel("C:/Users/soroe/Documents/ConveyorBelt.fbx");
    MyNewTestModel.SetName("Box");
    MyNewTestModel.SetRotation(glm::vec3(0));
    appManager.AddModel(&MyNewTestModel);





    appManager.ModelSetup(shaderProgram);


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
        
        //MyLine.Draw();
        appManager.Tick();
        myCamera.tick(appManager.GetDeltaTime());

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    appManager.CleanUp();
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
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
  
    myCamera.HandleInput(window);

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
            appManager.SelectedModel->AddLocation(glm::vec3(0, 0, -1) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(0, 0, 1) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(1, 0, 0) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(-1, 0, 0) * appManager.GetDeltaTime());
        }

        if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(0, 1, 0) * appManager.GetDeltaTime());
        }
        if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
        {
            appManager.SelectedModel->AddLocation(glm::vec3(0, -1, 0) * appManager.GetDeltaTime());
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    appManager.SetScreenSize(width, height);
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    myCamera.AddRotation(static_cast<float>(xpos), static_cast<float>(ypos));
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    myCamera.SetSpeed(myCamera.GetSpeed() + (static_cast<float>(yoffset) * 1000) * appManager.GetDeltaTime());
    std::cout << myCamera.GetSpeed() << std::endl;

    
}