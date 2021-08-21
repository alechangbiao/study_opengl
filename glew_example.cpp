#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Init GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "glewInit() -> Error!" << std::endl;
        std::cout << glewGetErrorString(err) << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw a triangle */
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// To compile this example, run:
// g++ -pthread -o glew_example glew_example.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lGLEW

// steps to resolve: error while loading shared libraries: libGLEW.so.2.2: cannot open shared object file: No such file or directory
// sudo find / -name libGLEW.so.2.2* -type f
// >> /usr/lib64/libGLEW.so.2.2.0
// cd /etc/ld.so.conf.d/
// sudo touch glew.conf && sudo vim glew.conf
// add: /usr/lib64
// sudo ldconfig
