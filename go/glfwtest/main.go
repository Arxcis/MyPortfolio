package main

import (
  "runtime"
  "github.com/go-gl/glfw/v3.2/glfw" 
)

func main() {
    err := glfw.Init()
    if err != nil {
        panic(err)  // Failed to initialize glfw
    }
    defer glfw.Terminate()

    window, err := glfw.CreateWindow(640, 480, "Testing", nil, nil)
    if err != nil {
        panic(err)
    }

    window.MakeContextCurrent()

    for !window.ShouldClose() {
        runOpenGLCommands()
        window.SwapBuffers()
        glfw.PollEvents()
    }
}

func init() { runtime.LockOSThread() } // To make sure main() runs on the main thread

func runOpenGLCommands(){
    // Draw to the window here
}
