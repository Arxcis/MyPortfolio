using Gtk;
using System;

class HelloWorld {
    
    static public void Main() {
        Application.Init();

        Window window = new Window("Hello mono world");
        window.show();

        Application.Run();

        Console.WriteLine("Hello from CodeTuts!\n");
    }
}
