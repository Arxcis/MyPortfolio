

Segment tentacle;

void setup() 
{   
    // Width and height are magic variables
    size(1000, 700);
    tentacle = new Segment(width/2, height-100, 100, -PI/2);
    
    Segment current = tentacle;
    for( int i = 0; i < 2; i++) 
    {
        Segment next = new Segment(current, 100, radians(0));
        current.child = next;
        current = next;
    }
}

void draw() 
{
    background(51);
  
    Segment next = tentacle;
    while(next != null) 
    {
        next.wiggle();
        next.update();
        next.render();

        next = next.child;
    }
}