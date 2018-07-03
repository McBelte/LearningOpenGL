#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(const Window& window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float mixValue = 0.2;

glm::vec3 pointLightPositions[] = {
	glm::vec3( 0.7f,  0.2f,  2.0f),
	glm::vec3( 2.3f, -3.3f, -4.0f),
}; 

glm::vec3 pointLightColors[] = {
    glm::vec3(0.2f, 0.2f, 0.2f),
    glm::vec3(0.2f, 0.2f, 0.2f),
};

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

DirectionalLight dirLight(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));

std::vector<PointLight> pointLights {
    PointLight(pointLightPositions[0], pointLightColors[0] * 0.1f, pointLightColors[0], pointLightColors[0]),
    PointLight(pointLightPositions[1], pointLightColors[0] * 0.1f, pointLightColors[1], pointLightColors[1]),
};

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::string windowTitle("LearnOpenGL");
    Window window(windowTitle, SCR_WIDTH, SCR_HEIGHT);

    glfwSetCursorPosCallback(window.window(), mouse_callback);  
    glfwSetFramebufferSizeCallback(window.window(), framebuffer_size_callback);
    glfwSetScrollCallback(window.window(), scroll_callback);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    Shader ourShader("shaders/lighting/standardShader.vs", "shaders/lighting/standardShader.fs");
    
    const std::string path("nanosuit/nanosuit.obj");
    Model ourModel(path.c_str());
    // -----------
    while (!window.shouldClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        ourShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        ourShader.setMat4("model", model);

        ourShader.setVec3("viewPos", camera.position);
        ourShader.setDirectionalLight(dirLight);
        ourShader.setPointLight(pointLights);
        ourShader.setFloat("material.shininess", 32.0f);

        ourModel.Draw(ourShader);

        window.update();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(const Window& window)
{
    if(glfwGetKey(window.window(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window.close();
    }

    if(glfwGetKey(window.window(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixValue -= 0.01;
        if(mixValue <= 0.0) {mixValue = 0.0;}
    }
        
    if(glfwGetKey(window.window(), GLFW_KEY_UP) == GLFW_PRESS) {
        mixValue += 0.01;
        if(mixValue >= 1.0) {mixValue = 1.0;}
    }
        
    if (glfwGetKey(window.window(), GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::Forward, deltaTime);
    if (glfwGetKey(window.window(), GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::Backward, deltaTime);
    if (glfwGetKey(window.window(), GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::Left, deltaTime);
    if (glfwGetKey(window.window(), GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::Right, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset, true);
} 

void scroll_callback(GLFWwindow* window, double yOffset, double xOffset) {
    camera.processMouseScrolls(yOffset);
}