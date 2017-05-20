
import Cocoa

// @DOC NSObject
// @Interface NSApplicationDelegate
// @brief The App Controller implements function delegates, which will be run
//        once a notification from the OS-notification center gets sent to the app.
//        The app is sort of subscribing to certain events, by creating delegates,
//        and implementing NSApplicationDelegate
// @DOC https://developer.apple.com/reference/appkit/nsapplicationdelegate
//
class AppController: NSObject, NSApplicationDelegate {
    var mainWindow: NSWindow?


    func applicationDidFinishLaunching(aNotification: NSNotification){
        let window = NSWindow(contentRect: NSMakeRect(0,0,640, 480),     // @DOC NSWindow - https://developer.apple.com/reference/appkit/nswindow/1419477-init
                              styleMask: [.closable,
                                          .titled,
                                          .borderless],   // @DOC NSWindowStyleMAsk - https://developer.apple.com/reference/appkit/nswindowstylemask
                              backing:  .buffered,        // @DOC NSBackingStoreType - https://developer.apple.com/reference/appkit/nsbackingstoretype
                              defer: true)

        window.orderFrontRegardless()
        self.mainWindow = window
        NSApp.activate(ignoringOtherApps: true)
    }

                                    // @DOC func https://developer.apple.com/reference/appkit/nsapplicationdelegate/1428381-applicationshouldterminateafterl?language=objc
    private func applicationShouldTerminateAfterLastWindowClosed(app: NSApplication) -> Bool {
        return true
    }
}

NSApplication.shared()             // @DOC NSApplication - https://developer.apple.com/reference/appkit/nsapplication

NSApp.setActivationPolicy(.regular)
let controller = AppController()
NSApp.delegate = controller
NSApp.run()
