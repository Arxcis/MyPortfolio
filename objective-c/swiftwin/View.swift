import AppKit

class TestView: NSView
{
        override init(frame: NSRect)
        {
                super.init(frame: frame)
        }

        required init?(coder: NSCoder)
        {
                fatalError("init(coder:) has not been implemented")
        }

        var colorgreen = NSColor.greenColor()

        override func drawRect(rect: NSRect)
        {
                colorgreen.setFill()
                NSRectFill(self.bounds)

                let h = rect.height
                let w = rect.width
                let color:NSColor = NSColor.yellowColor()

                let drect = NSRect(x: (w * 0.25),y: (h * 0.25),width: (w * 0.5),height: (h * 0.5))
                let bpath:NSBezierPath = NSBezierPath(rect: drect)

                color.set()
                bpath.stroke()

                NSLog("drawRect has updated the view")
        }
}
