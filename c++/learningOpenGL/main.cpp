//
//  main.cpp
//  test_openGL
//
//  Created by Jonas Solsvik on 03.09.2016.
//  Copyright © 2016 Jonas Solsvik. All rights reserved.
//

// --------- STEP0 : Include, define and const --------------------

#include <iostream>
#define GLEW_STATIC          // GLEW - talks to openGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>      // GLFW - window manager

const GLuint WIDTH=800, HEIGHT=600;

// ----------------------------------------------------------------

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(){

    // -------- STEP1: Configure the window and openGL -------------

                // Init glfw
                // Sets up the GLF-window i think.
    glfwInit();
                // glfwInit() - makes it possible to use "WindowHint(options)"
                // We can select an option from a large enum of possible
                // options prefixed with GLFW_
                // Two next lines - Used to tell which version of OpenGL to be
                // used. In this case OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

                // Restrict which parts of OpenGL to use, which files to used
                // If we used CORE, then legacy is exluded.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

                // Next line is for compatability with mac
                // Without this line, mac osx wont work.
                // It will still run on windows.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

                // Enables window to be resizeable
                // Can have GL_TRUE and GL_FALSE
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // ----------------------------------------------------------

    // -------- STEP2: Init the GLFW-window object---------------

                // Uses a pointer here
                // You really always want to make pointers to
                // window objects, because if not, you might end up with
                // multiple windows. The window object is a really big one.
    GLFWwindow *window = glfwCreateWindow(WIDTH,
                                          HEIGHT,
                                          "Test OpenGL",
                                          nullptr,
                                          nullptr);

    if (window == nullptr){

        std::cout << "Failed to create OpenGL-window\n";
        glfwTerminate();
        return -1;
    }
                // We tell GLFW to make the context of this window the main
                // context of the current thread.
    glfwMakeContextCurrent(window);

    // -------------------------------------------------------

    // -------- STEP3: Init GLEW openGL-library ----------------------------

                // GLEW handles pointers to functions in the openGL library
                // By setting glewExperiemental to GL_TRUE we force GLEW to
                // to use newer functionality.
    glewExperimental = GL_TRUE;

                // This initialized GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to init openGL-library";
        return -1;
    }

    // ------- STEP4: Init OpenGL viewport ---------------------

    int screenwidth, screenheight;
                // Here we get the width and height which has been used
                // when creating the GLFW-window object. Ideally we want the
                // OpenGl-viewport-size to be the same size as the
                // Mac-window. If the viewport is bigger, we are wasting
                // rendering-resources on an area which is not displayed on
                // the screen. The viewport is basically a camera into the
                // game-environment. It is the viewport that gets rendered
                // by the OpenGl-engine, and then the viewport is sent
                // to and displayed in the GLFW-window.
    glfwGetFramebufferSize(window, &screenwidth, &screenheight);

                // The first two parameters sets the location of the lower
                // left corner of the window.
                // This basically syncs the viewport to the window.
    glViewport(0,0, screenwidth, screenheight);

    // ----------------------------------------------------------

    // ------------ STEP4.5: Register callback functions -----------
                // Callback functions should be registered after the
                // window has been created, and before the game-loop is
                // started.
                // This basically works as event-listeneres.
                //
                // Eksamples of callback-functions:
                //      Key callback
                //      Window resize callback
                //      Mouse callback

    glfwSetKeyCallback(window, key_callback);

    // --------------------------------------------------------------

    // -------------- STEP5: Turn on the ENGINE ---------------------

                // This is the gameloop
                // It will run as long as not told otherwise.
    while (!glfwWindowShouldClose(window)) {

                // glfwPollEvents - checks if any events has happened during
                //   the last iteration of the loop, such as keyboard/mouse
                //   input.
                //   Eventprocessing is usually called at the beginning of the
                //   loop.
        glfwPollEvents();

        // ------------- STEP5.1: Rendering calls -----------------

                // Sets the color which glClear uses to clear the screen
                // The color-spec is RGB and the values range between 0.0f-1.0f
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

                // Clears the screen. Makes sure that every new frame is not
                // effected by the frame that came before.
                // Options:
                // GL_COLOR_BUFFER_BIT - if we only want to clear color
                // GL_DEPTH_BUFFER_BIT
                // GL_STENCIL_BUFFER_BIT
        glClear(GL_COLOR_BUFFER_BIT);

        // ------------------------------------------------------------

                // Swapping framebuffers - There is a buffered version
                // (back buffer) of the window frame that has been changed
                //  since last time. Here we swap the old frame with the new
                //  frame, and draws it on the screen.
                // "The front buffer contains the final output image that is
                //  shown at the screen, while all the rendering commands draw
                //  to the back buffer. As soon as all the rendering commands
                //  are finished we swap the back buffer to the front buffer
                //  so the image is instantly displayed to the user, removing
                //  all the aforementioned artifacts."
        glfwSwapBuffers(window);
    }
    // ---------------------------------------------------------------


    // --------- STEP6: Clean up the mess on exit --------------------

                // Makes sure that everything terminates cleanily.
                // Clean/deletes all recourses that was allocated to the app.
    glfwTerminate();
    return 0;
}

    // ---------------------------------------------------------

    // --------- STEP7: Setup input callback function ----------------

                // key_callback() should be called whenever the user interacts
                // with the keyboard.
                // param: window   - is a pointer to a GLFW-windo-object
                // param: key      - an int with value of key-pressed
                // param: scancode -
                // param: action   - specifies if key is pressed or released.
                // param: mode     -  tells if shift, control alt.. is pressed.
    void key_callback(GLFWwindow* window, int key,
                                          int scancode,
                                          int action,
                                          int mode) {

                // When user presses escape key we set the WindowShouldClose
                // property to true, closing the APP.
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){

                // This should terminate the game engine, since the engine uses
                // this as a true/false-statement.
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    // --------------------------------------------------------------
}
