#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int compileShader(unsigned int type, const char source[]) 
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    // Syntax error checking needing for shader files
    // ...
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char message[len];
        glGetShaderInfoLog(id, len, &len, message);
        printf("%s\n", message);
        printf("FILE: %s\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        glDeleteShader(id);
        return 0;
    }
    
    return id;
};

static unsigned int createShader(const char vertexShader[], const char fragmentShader[]) 
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};

int main(void)
{
    GLFWwindow* window;

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

    // GLEW implementation
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1; 
    }
    // Let's print the GLEW Version
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // Let's print the target processor (your computer's integrated or external GPU) OpenGL Version
    fprintf(stdout, "Status: Using OpenGL %s\n", glGetString(GL_VERSION));

    fprintf(stdout, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Define data Buffer for drawing
    float positions[6] = {
        -0.5f, -0.5,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);

    // Bind buffer to layer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // Unbind buffer... Necessary to reduce overhead and prevent weird behaviour
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    char vertexShader[] = "#version 120\n\nattribute vec4 position;\n\nvoid main(){ gl_Position = position; }\n";
    char fragmentShader[] = "#version 120\n\nvoid main(){ gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); }\n";
    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // // Render triangle in legacy openGL
        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f(0.0f, 0.5f);
        // glVertex2f(0.5f, -0.5f);
        // glEnd();

        // Draw pull
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}