#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"
#include "stb_image.h"
#include "camera.h"
#include "config.h"
#include "window.h"

int main()
{
/*     // GLFW initialization and specifiying OpenGL window context version 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates the actual window, throws an error in case of failure
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Error! Could not create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // GLFW specific parameters
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))		// This function requires a valid OpenGL context 
    {
        std::cerr << "Error! Could not load glad" << std::endl;
        glfwTerminate();
        return -1;
    } */

    GLFWWindow WindowInstance(800, 600, "Window");
    WindowInstance.SetCallback();

    // Misc GL functions
    glViewport(0, 0, 800, 600);		// Defines the size of the OpenGL rendering viewport, this is independent of window size
    glEnable(GL_DEPTH_TEST);

    // OpenGL version info and GPU currently in use
    std::cout << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OPENGL VERSION: " << glGetString(GL_VERSION) << std::endl;

    //-------------------------------------------------
    // Shader compile functions
    //-------------------------------------------------

    Shader ShaderLoader("vertex.glsl", "fragment.glsl");

    //-------------------------------------------------
    // OpenGL buffers
    //-------------------------------------------------

    unsigned int VBO;
    unsigned int VAO;
    //unsigned int IBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); 	// OpenGL core profile requires a VAO to be bound

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);		// Copies the data from system RAM to GPU RAM

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);	// we can unbind the VBO because it has be registered to the VAO using glVertexAttribPointer

    //-------------------------------------------------
    // Texture loading
    //-------------------------------------------------

    int width;
    int height;
    int nrChannels;

    unsigned int texture1;
    unsigned int texture2;

    unsigned char* image;

    stbi_set_flip_vertically_on_load(true);
 
    //-------------
    // Texture 1
    //-------------

    image = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
         
    // The usual glGen and glBind
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // Texture wrapping methods
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Texture filtering method
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Output the data to be processed by shaders and error checking
    if(image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Texture loading failed" << std::endl;
    }
    // Cleanup
    stbi_image_free(image);

    //-------------
    // Texture 2
    //-------------

    image = stbi_load("lemon.png", &width, &height, &nrChannels, 0);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Texture loading failed" << std::endl;
    }
    
    stbi_image_free(image);

    //-------------------------------------------------
    // Uniforms
    //-------------------------------------------------

    ShaderLoader.use();

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 100.0f);
    ShaderLoader.setMat4("projection", projection);

    // Passing the texture sampler location to OpenGL
    glUniform1i(glGetUniformLocation(ShaderLoader.ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(ShaderLoader.ID, "texture2"), 1);


    //-------------------------------------------------
    // Main render loop
    //-------------------------------------------------

    while (!WindowInstance.ShouldClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //processInput(window);

        glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ShaderLoader.use();

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ShaderLoader.setMat4("projection", projection);

        // Look At matrice
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ShaderLoader.setMat4("view", view);

        // Box rendering
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.f * i;

            if(i >= 5)
                angle = glfwGetTime() * 25.0f;

            if(i <= 6)
                angle = glfwGetTime() * -25.0f;

            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ShaderLoader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(WindowInstance.GetWindow());
        glfwPollEvents();
    }

    // Resource de-allocation for a cleaner exit. This is optionnal as the OS should handle this automatically
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}

/* void processInput(GLFWwindow *window)
{    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.5f * deltaTime;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Locking the Y axis to avoid going 360
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}
 */