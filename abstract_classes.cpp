#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "classes/Renderer.h"
#include "classes/VertexBuffer.h"
#include "classes/IndexBuffer.h"
#include "classes/VertexArray.h"
#include "classes/Shader.h"
#include "classes/VertexBufferLayout.h"

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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    float positions[] = {-0.5f, -0.5f,
                         0.5f, -0.5f,
                         0.5f, 0.5f,
                         -0.5f, 0.5f};

    unsigned int indicies[] = {0, 1, 2,
                               2, 3, 0};

    /* Vertex Array Part */
    // unsigned int vao; // vertex array object
    // GLCall(glGenVertexArrays(1, &vao));
    // GLCall(glBindVertexArray(vao));
    VertexArray va;

    /* Vertex Buffer part */
    // unsigned int buffer;
    // glGenBuffers(1, &buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
    VertexBuffer vb(positions, 4 * 2 * sizeof(float)); // replace the above with 'VB' class

    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // this line link the buffer with the 'vao'

    /* index buffer part */
    // unsigned int ibo; // ibo - index buffer object
    // GLCall(glGenBuffers(1, &ibo));
    // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    // GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW));
    IndexBuffer ib(indicies, 6); // replace the above with 'IB' class

    /* Shader Part */
    // ShaderProgramSource source = ParseShader("Uniform.shader");
    // unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    // GLCall(glUseProgram(shader));
    Shader shader("shaders/Uniform.shader");
    shader.Bind();

    /* Uniform part */
    // GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    // ASSERT(location != -1);
    // GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

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
        shader.SetUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);

        /* The Next Lines of Code Are Replaced with  renderer.Draw(va, ib, shader); call */
        // /* The belowing 3 lines are not needed since we are using vertex array */
        // // GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer)); // bind vertex buffer
        // // GLCall(glEnableVertexAttribArray(0));          // set up the layout of our vertex buffer
        // // GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

        // /* Only vertex array and index buffer are need to be bound */
        // va.Bind(); // (glBindVertexArray(vao));
        // ib.Bind(); // replace the next line with 'IB' class method
        // // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo)); // bind our index buffer

        // /* Draw the rectangle */
        // GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
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

        /* Clean up the shader program */
        // glDeleteProgram(shader);     // will be deleted by the destructor of Shader
    }

    glfwTerminate();
    return 0;
}

// To compile this example, run:
// g++ -pthread -o abstract_classes abstract_classes.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lGLEW
