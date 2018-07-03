#include "Window.h"

#include <iostream>

Window::Window(const std::string& title, int width, int height) 
    : m_window(glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr))
    , m_title(title)
{

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(!m_window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwDestroyWindow(m_window);
    } else {
        glfwMakeContextCurrent(m_window);
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    }
}

Window::~Window() {
    glfwDestroyWindow(m_window);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::window() const {
    return m_window;
}

void Window::update() const {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Window::close() const {
    glfwSetWindowShouldClose(m_window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
