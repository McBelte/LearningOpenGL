#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    GLFWwindow* window() const;

    void close() const;
    bool shouldClose() const;
    void update() const;

private:
    GLFWwindow* m_window;
    std::string m_title;

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);


