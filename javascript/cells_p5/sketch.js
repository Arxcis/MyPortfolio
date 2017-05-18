var cells = [];

function setup() {
    createCanvas(800, 800);
    frameRate(120);
    cells.push(new Cell());
    cells.push(new Cell());
}

function draw() {
    background(51);
    for(var i = 0; i < cells.length; i++) {
        cells[i].move();
        cells[i].show();
    }
}

function mousePressed() {
    noStroke();
    fill(0,0,255);
    ellipse(mouseX, mouseY, 50,50);
    
    for(var i = cells.length-1; i >= 0; --i) {
        if (cells[i].clicked(mouseX, mouseY)) {
            cells.push(cells[i].mitosis());
            cells.push(cells[i].mitosis());
            console.log("CLICKED!");
        }
    }
}
