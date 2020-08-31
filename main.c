#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct ShaderSource
{
    char VertexShader[512];
    char FragmentShader[512];
};

struct ShaderSource parseShader(const char filepath[])
{
    // instantiate a temp version of our struct
    struct ShaderSource tmp;

    // Open our target file for parsing. This is the shader source
    FILE *fp = fopen(filepath, "r");

    // Establish a buffer array for the file stream 
    const char buffer[512];

    // unsigned char ptr that has the same size array as the buffer and 
    // struct variables. This is probably not needed... Checking in on 
    // that.
    unsigned char (*src)[512];

    // Determiners... These values determine when parsing if source code pertains to
    // a vertex or a fragment shader.
    char divider[] = "#shader";
    char version[] = "#version";
    char v[] = "vertex";
    char f[] = "fragment";

    while(fgets(buffer, 512, fp))
    {
        if (strstr(buffer, divider))
        {
            if (strstr(buffer, v))
            {
                src = &tmp.VertexShader;
            }
            else if (strstr(buffer, f))
            {
                src = &tmp.FragmentShader;
            }
        }
        else if (strstr(buffer, version))
        {
            strcpy(src, buffer);
        }
        else
        {
            strcat(src, buffer);
        }
    }
    // Lets close that file as we don't need it.
    fclose(fp);

    // Return our parsed shader sources.
    return tmp;
}

static unsigned int compileShader(unsigned int type, const char source[]) 
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    // Syntax error checking needing for shader files
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

    glfwSwapInterval(1);

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
    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Binding for Array Buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    // Bind buffer to layer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // Binding for index buffer
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    // Bind buffer to layer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Unbind buffer... Necessary to reduce overhead and prevent weird behaviour
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
    char filepath[] = "shaders/basic.shader";
    struct ShaderSource Source = parseShader(filepath);

    unsigned int shader = createShader(Source.VertexShader, Source.FragmentShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, 1.0, 0.0, 0.0, 1.0);

    float r = 0.0f;
    float increment = 0.05f;


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Animation of colour
        glUniform4f(location, r, 0.0, 0.0, 1.0);
        // Draw pull or function..
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        // Colour animation.
        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}