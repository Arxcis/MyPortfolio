//
//  main.swift
//  CollectionView
//
//  Created by Hoon H. on 2015/01/18.
//  Copyright (c) 2015 Eonil. All rights reserved.
//   http://stackoverflow.com/questions/30763229/display-window-on-osx-using-swift-without-xcode-or-nib
//
// HAVE TO INSTALL XCODE FOR THIS TO WORK

import AppKit

let     app1            =       NSApplication.sharedApplication()
let     con1            =       TestApplicationController()

app1.delegate   =       con1
app1.run()
