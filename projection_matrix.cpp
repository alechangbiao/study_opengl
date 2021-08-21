#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

// classes
#include "classes/Renderer.h"
#include "classes/VertexBuffer.h"
#include "classes/IndexBuffer.h"
#include "classes/VertexArray.h"
#include "classes/Shader.h"
#include "classes/VertexBufferLayout.h"
#include "classes/Texture.h"

// glm libs
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set opengl major version as 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // set opengl minor version as 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // to achieve a smoother animations

    /* Init GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "glewInit() -> Error!" << std::endl;
        std::cout << glewGetErrorString(err) << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {100.0f, 100.0f, 0.0f, 0.0f,
                         200.0f, 100.0f, 1.0f, 0.0f,
                         200.0f, 200.0f, 1.0f, 1.0f,
                         100.0f, 200.0f, 0.0f, 1.0f};

    unsigned int indicies[] = {0, 1, 2,
                               2, 3, 0};

    /* Blending here */
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;

    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indicies, 6); // replace the above with 'IB' class

    /* Math Part*/
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    // glm::vec4 vp(100.0f, 100.0f, 0.0f, 1.0f);
    // glm::vec4 result = proj * vp;

    Shader shader("shaders/Math.shader");
    shader.Bind();
    // shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.SetUniformMat4f("u_MVP", proj);

    Texture texture("res/shuriken-dart.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    /* Unbind Everything */
    va.Unbind();     // GLCall(glBindVertexArray(0));
    vb.Unbind();     // GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    ib.Unbind();     // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    shader.Unbind(); // GLCall(glUseProgram(0));

    Renderer renderer;

    float red = 0.0f;
    float increment = 0.02f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear(); // GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // GLCall(glUseProgram(shader));                         // bind our shader
        shader.Bind();
        // GLCall(glUniform4f(location, red, 0.3f, 0.8f, 1.0f)); // set up the uniform
        // shader.SetUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);

        renderer.Draw(va, ib, shader);

        if (red > 1.0f)
            increment = -0.02f;
        else if (red < 0.0f)
            increment = 0.02f;

        red += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// To compile this example, run:
// g++ -pthread -o abstract_classes abstract_classes.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lGLEW
