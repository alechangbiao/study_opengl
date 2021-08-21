#pragma once

#include <GL/glew.h>
#include "../debugbreak/debugbreak.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) \
    if (!(x))     \
        debug_break();

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) // #x turn x function into a string

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer
{
private:
    /* data */
public:
    Renderer(/* args */);
    ~Renderer();

    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader);
};
