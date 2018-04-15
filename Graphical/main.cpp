//
//  main.cpp
//  Graphical
//
//  Created by Melanie Jouaiti on 29/09/2017.
//  Copyright © 2017 Melanie Jouaiti. All rights reserved.
//

#include <iostream>
#include <math.h>

#ifdef __APPLE__
#   define _OSX
#elif defined(__linux__)
#   define _LINUX
#endif

#if defined(_LINUX)
#   include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "Grapher.h"
#include "../Simulation/Simulation2.h"
#include "../common.h"

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

std::vector<std::string> mico_names = {"Mico_joint1", "Mico_joint2", "Mico_joint3", "Mico_joint4", "Mico_joint5", "Mico_joint6"};

#define PI acos(-1)

GLint WIDTH = 1024, HEIGHT = 768;

#ifdef __APPLE__
int f = 2;
#else
int f = 1;
#endif

#ifdef _LINUX
std::string path = "../Graphical/";
GLint V_WIDTH = WIDTH / 2, V_HEIGHT = HEIGHT / 2;
#else
std::string path = "/Users/Melanie/Documents/Studies/LORIA/Handshaking/Graphical/";
GLint V_WIDTH = WIDTH, V_HEIGHT = HEIGHT;
#endif

void init();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, int button, int action, int mods);
void position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float cursorPositionX, cursorPositionY;

GLFWwindow* _Window;
Grapher* grapher;

int main()
{
    init();
    //Create Shader
    Shader shader((path + "shaders/shader.vs").c_str(), (path + "shaders/shader.frag").c_str());
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    grapher = new Grapher(0);
    
    Simulation2 simulation(mico_names);
    
    simulation.init();

    float t = 0.0, dt = 0.01;

    while (t < TMAX && !glfwWindowShouldClose(_Window))
    {
        glfwPollEvents();

        grapher->update(simulation.step());
        t += dt;

        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, V_WIDTH, V_HEIGHT);
        grapher->render0(shader);

        glViewport(0, V_HEIGHT, V_WIDTH, V_HEIGHT);
        grapher->render1(shader);

        glViewport(V_WIDTH, V_HEIGHT, V_WIDTH, V_HEIGHT);
        grapher->render2(shader);

        glViewport(V_WIDTH, 0, V_WIDTH, V_HEIGHT);
        grapher->render3(shader);

        glfwSwapBuffers(_Window);
    }
    
    glfwTerminate();
    
    GLenum errGL;
    while ((errGL = glGetError()) != GL_NO_ERROR)
    {
        cerr << "OpenGL error: " << errGL << endl;
    }
    
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        
    }
}

void position_callback(GLFWwindow* window, double xpos, double ypos)
{
    cursorPositionX = (xpos - (float)WIDTH / 2.0)/(WIDTH / 2.0);
    cursorPositionY = ((float)HEIGHT / 2.0 - ypos) / (HEIGHT / 2.0);
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

void init()
{
    if (!glfwInit())
    {
        printf("glfwInit() fail to initialize. \n");
        glfwTerminate();
        exit(-1);
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    _Window = glfwCreateWindow(WIDTH, HEIGHT, "MultiViewModelling", 0, 0);
    
    
    if (!_Window)
    {
        printf("Display window fail to create. \n");
        glfwTerminate();
        exit(-1);
    }
    
    glfwMakeContextCurrent(_Window);
    
#ifdef _LINUX
    glewExperimental = GL_TRUE;
    glewInit();
#endif
    
    glfwSetKeyCallback(_Window, key_callback);
    glfwSetCursorPosCallback(_Window, position_callback);
    glfwSetMouseButtonCallback(_Window, mouse_callback);
    glfwSetScrollCallback(_Window, scroll_callback);
    
#ifdef _LINUX
    glViewport(0, 0, WIDTH, HEIGHT);
#else
    glViewport(0, 0, WIDTH * 2, HEIGHT * 2);
#endif
    
    std::cout << glGetString(GL_VERSION) << std::endl;
}
