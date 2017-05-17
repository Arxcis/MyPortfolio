import AppKit

final class TestApplicationController: NSObject, NSApplicationDelegate
{

        ///     Seems fine to create AppKit UI classes before `NSApplication` object
        ///     to be created starting OSX 10.10. (it was an error in OSX 10.9)
        let     window1 =       NSWindow()
        let     view1   =       TestView(frame: NSRect(x: 0, y: 0, width: 1000, height: 1000))

        func applicationDidFinishLaunching(aNotification: NSNotification)
        {
                window1.setFrame(CGRect(x: 0, y: 0, width: 1000, height: 1000), display: true)
                window1.contentView =   view1
                window1.opaque      =   false
                window1.center();
                window1.makeKeyAndOrderFront(self)
        //      window1.backgroundColor = view1.colorgreen
        //      window1.displayIfNeeded()
        }

        func applicationWillTerminate(aNotification: NSNotification) {
                // Insert code here to tear down your application
        }
}
