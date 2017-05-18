package main

type Color struct {
    red, green, blue, alpha uint8
}

type Transform struct {

}

type Bullshit struct {
    weight float32,
    color Color,
}

func (b *Bullshit) throw() {
    fmt.Println("Throwing bullshit.....\n")
}

func main() {
    bull Bullshit

    bull.throw()
}
