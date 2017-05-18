class Segment 
{
  Segment parent = null;
  Segment child  = null;

  PVector a;
  PVector b;

  float   len;
  float   localAngle   = 0.0;
  float   globalAngle  = 0.0;
  float   angularSpeed = 0.03;
  

  float xoff = random(1000);
  //float xoff = 0.0;  // for sine function
  //
  // @function constructor
  //
  Segment(float x, float y, float len_, float localAngle_) 
  {
    a          = new PVector(x, y);
    len        = len_;
    localAngle = localAngle_;
    calculateB();
    
  }

  //
  // @function constructor
  //
  Segment(Segment parent_, float len_, float localAngle_)
  {
    parent      = parent_;
    a           = parent.b.copy();
    len         = len_;
    localAngle  = localAngle_;
    calculateB();
  }

  //
  // @function wiggle()
  //
  void wiggle() 
  { 
    // PI is magic variable, processing is magic
    float maxangle = -PI/3;
    float minangle = PI/3;
    localAngle = map(noise(xoff), 0.0, 1.0, maxangle, minangle);
    //localAngle = map(sin(xoff), 0, 1, maxangle, minangle);  // for sine function
    xoff += 0.005;
    
    // old simples movement localAngle  += angularSpeed;  
  }

  //
  // @function update()
  //
  void update() 
  {
    globalAngle = localAngle;
    if (parent != null) 
    {
      a = parent.b.copy();
      globalAngle += parent.globalAngle;
    } 
    else 
    {
      globalAngle -= PI/2;
    }

    calculateB();
  }


  //
  // @function
  //
  void calculateB(){
    float dx = len * cos(globalAngle);    // Thes cos and sin has to get radians in.
    float dy = len * sin(globalAngle);
    
    b = new PVector(a.x + dx, a.y + dy);
  }
  
  //
  // @function
  //
  void render()
  {
    stroke(255);
    strokeWeight(4);
    line(a.x, a.y, b.x, b.y);
  }
}