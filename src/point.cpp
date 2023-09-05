#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SHADER/err.h>
#include <SHADER/reader.h>
#include <string>
#include <iostream>

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint createShaderProgram()
{
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;

    const char *vshaderSource =
        "#version 430 \n"
        "void main(void) \n"
        "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0);}";

    const char *fshaderSource =
        "#version 430 \n"
        "out vec4 color; \n"
        "void main(void) \n"
        "{color = vec4(0.0, 0.0, 1.0, 1.0);}";

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    /** Compile the vertex shader and catch any errors if any. */
    glCompileShader(vShader);

    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);

    if (vertCompiled != 1)
    {
        std::cout << "Vertex shader compilation failed!" << std::endl;
        printShaderLog(vShader);
    }

    /** Compile the fragment shader and catch any errors if any. */
    glCompileShader(fShader);

    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);

    if (fragCompiled != 1)
    {
        std::cout << "Fragment shader compilation failed!" << std::endl;
        printShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();

    /** Link the shaders and catch errors if any during the linking. */
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram);

    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);

    if (linked != 1)
    {
        std::cout << "Linking failed!" << std::endl;
        printProgramLog(vfProgram);
    }

    return vfProgram;
}

/**
 * @brief Initializes the application window.
 *
 * All initialization procedures should go here.
 *
 * @param window
 */
void init(GLFWwindow *window)
{
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
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
    glUseProgram(renderingProgram);
    glDrawArrays(GL_POINTS, 0, 1);
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    // glClear(GL_COLOR_BUFFER_BIT);
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
    GLFWwindow *window = glfwCreateWindow(800, 800, "Point", NULL, NULL);

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