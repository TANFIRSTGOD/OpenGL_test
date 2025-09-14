#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const int WIDTH = 800;
const int HEIGHT = 800;

const float TRIANGLE_POS_Y = -0.7;
const float TRIANGLE_POS_X = 0.2;


int main() {

    glfwInit();



    // Tell the opengl version and which profile
    // This case using 4.4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // Tell glfw were using the CORE profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Triangle vertecies
    GLfloat vertecies[] = 
    {
        -0.5f + TRIANGLE_POS_X, (0.5f * float(sqrt(3)) / 3) + TRIANGLE_POS_Y, 0.0f,
        0.5f + TRIANGLE_POS_X, (0.5f * float(sqrt(3)) / 3) + TRIANGLE_POS_Y, 0.0f,
        0.0f + TRIANGLE_POS_X, (0.5f * float(sqrt(3)) * 2 / 3) + TRIANGLE_POS_Y, 0.0f,
        (-0.5f / 2) + TRIANGLE_POS_X, (0.5f * float(sqrt(3)) / 6) + TRIANGLE_POS_Y, 0.0f,
        (0.5f / 2) + TRIANGLE_POS_X, (0.5f * float(sqrt(3)) / 6) + TRIANGLE_POS_Y, 0.0f,
        0.0f + TRIANGLE_POS_X, (0.5f * float(sqrt(3)) / 3) + TRIANGLE_POS_Y, 0.0f,
    };

    GLuint indicies[] =
    {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1 // Upper triangle
    };

    // Create a GLFWwindow object that is 800 x 800 pixels
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Test", NULL, NULL);
    // Checks if the window has been successfully created, if not then terminate the program
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Tell glfw what window we are currently using
    glfwMakeContextCurrent(window);
    
    
    // Loads opengl
    gladLoadGL();
    // Specify the viewport of OpenGL in the window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, WIDTH, HEIGHT);


    // Compiles the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Compiles the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Links the 2 shaders to the program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Cleans up the 2 shaders becasue we already have it in our program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Clears prev buffer and sets bg color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Sets bg color
    glClear(GL_COLOR_BUFFER_BIT);  // Clears the last buffer
    glfwSwapBuffers(window);  // Swaps the buffers

    // MUST GEN VAO BEFORE VBO
    // VAO = Vertex Array Object, is used to switch between multiple VBOs
    // VBO = Vertex Buffer Object, is a grphics buffer that stores vertex data (positions, color, texture etc.)
    GLuint VAO, VBO, EBO;

    // Generates the VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Makes the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Binds the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    // Configures the Vertex Atribute so OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enables the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    while(!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Sets bg color
        glClear(GL_COLOR_BUFFER_BIT);  // Clears the last buffer
        // Tells OpenGL which shader program to use
        glUseProgram(shaderProgram);
        // Binds the VAO so OpenGL knows to use it
        glBindVertexArray(VAO);
        // chooses what kind of primatives to use, how many indicies, data type of indicies and index of indicies
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);  // Swaps the buffers

        glfwPollEvents(); // Process poll events such as resized window, closed etc. if we dont process window will not respond
    
    }


    // Termination code
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}