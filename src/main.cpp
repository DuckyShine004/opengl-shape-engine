#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * @brief Initializes the application window.
 *
 * All initialization procedures should go here.
 *
 * @param window
 */
void init(GLFWwindow *window)
{
}

/**
 * @brief Updates and clears the color buffer.
 *
 * The glClearColor(r, g, b, a) corresponds to RGB color with opacity considered.
 * Then call glClear(GL_COLOR_BUFFER_BIT) to actually fill the color buffer with
 * the specified color.
 *
 * @param window
 * @param time
 */
void display(GLFWwindow *window, double time)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * @brief The main driver code.
 *
 * The main driver code where initializing the program's functionalities should go.
 *
 * @return int
 */
int main()
{
    /* Initialize the glfw library. */
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
        return 0;
    }

    /* Create OpenGL contexts. */
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create an application window. */
    GLFWwindow *window = glfwCreateWindow(800, 800, "Triangle", NULL, NULL);

    /* Make the window's context current. */
    glfwMakeContextCurrent(window);

    /* Initialize glad library. */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        exit(EXIT_FAILURE);
        return 0;
    }

    /* Initialize the window. */
    init(window);

    /* While the application window is still open, update every frame. */
    while (!glfwWindowShouldClose(window))
    {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* User has closed the window, and terminate. */
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}