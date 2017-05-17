package main

import "github.com/hajimehoshi/ebiten"
import "github.com/hajimehoshi/ebiten/ebitenutil"

const screenWidth = 800
const screenHeight = 600

//var screen *ebiten.image.RGBA

func update(screen *ebiten.Image) error {
        ebitenutil.DebugPrint(screen, "Hello world!")
        return nil
}

func main() {
        ebiten.Run(update, screenWidth, screenHeight, 1, "Hello world!")
}
