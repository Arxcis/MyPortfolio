// @app miniwindow
// @file main.swift
// @created 20.05.17
// @author Jonas Solsvik
// @brief mini-app inspired by http://czak.pl/2015/09/23/single-file-cocoa-app-with-swift.html

import Cocoa

NSApplication.shared()
NSApp.setActivationPolicy(.regular) // Configure as regular app, appearing in Dock and having UI

let window = NSWindow(contentRect: NSMakeRect(0,0,640, 480),                     // https://developer.apple.com/reference/appkit/nswindow/1419477-init
                      styleMask: NSWindowStyleMask.borderless, // https://developer.apple.com/reference/appkit/nswindowstylemask
                      backing:  .buffered,                                        // https://developer.apple.com/reference/appkit/nsbackingstoretype
                      defer: true)

window.orderFrontRegardless()

DispatchQueue.main.async {
    NSApp.activate(ignoringOtherApps: true)
}

NSApp.run()
