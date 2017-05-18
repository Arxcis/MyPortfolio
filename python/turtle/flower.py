import turtle

# Setting up turtle
turtle.shape("turtle")
turtle.color("green")
turtle.shapesize(3)
turtle.pensize(5)
turtle.speed(6)

# Draw flower
for i in range(10):
    turtle.circle(10*i)
    turtle.circle(-10*i)
    turtle.rt(90)

turtle.mainloop()
