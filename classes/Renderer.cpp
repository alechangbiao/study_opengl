#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogCall(const char *function, const char *file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << function
                  << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer(/* args */)
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader)
{

    // GLCall(glUseProgram(shader));                         // bind our shader
    shader.Bind();

    // GLCall(glUniform4f(location, red, 0.3f, 0.8f, 1.0f)); // set up the uniform
    // shader.SetUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);

    /* The belowing 3 lines are not needed since we are using vertex array */
    // GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer)); // bind vertex buffer
    // GLCall(glEnableVertexAttribArray(0));          // set up the layout of our vertex buffer
    // GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

    /* Only vertex array and index buffer are need to be bound */
    va.Bind(); // (glBindVertexArray(vao));
    /* replace the next line with 'IB' class method */
    ib.Bind(); // GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo)); // bind our index buffer

    /* Draw the rectangle */
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
