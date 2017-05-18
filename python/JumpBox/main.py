


import time
import math
import random
from turtle import *

# --- Setup screen --- 
screen = Screen()
screen.setup(900, 600)
screen.delay(0)
screen.colormode(255)
max_x = 1/2*screen.window_width()
min_x = 1/2*screen.window_width() * (-1)
max_y = 1/2*screen.window_height() 
min_y = 1/2*screen.window_height() * (-1)

#---------------------------------

cube_list = []
gravity = -9.81


class Ground(Turtle):
    def __init__(self):
        super().__init__()
        self.floor = min_y + 50
        self.speed(0)
        self.ht
        self.penup()
        self.goto(min_x, self.floor)

        self.drawground()

    def drawground(self):
        self.pendown()
        self.goto(max_x, self.floor)
        self.penup()


class Cube(Turtle):
    def __init__(self, x, y):
        super().__init__()

        self.shape('square')
        self.shapesize(2)
        self.penup()
        self.speed(0)

        self.goto(x, y)

        self.angle = 0
        self.speed_x = 0
        self.speed_y = 0

        self.c_before = None
        self.c_after = None
        self.c_delta = None

    def updateposition(self, floor):
        x, y = self.position()

        correction = 21
        if self.c_before: 
            self.c_after = time.clock()
            self.c_delta = self.c_after - self.c_before

        if y > floor + correction:
            if self.c_delta:
                self.speed_y += gravity
                self.goto(x + self.speed_x, (y + ((self.speed_y)*self.c_delta)))
        else: 
            self.goto(x, floor + correction)

        self.c_before = time.clock()

    def jump(self, x, y):
        x, y = self.position()
        self.goto(x, y + 30)
        self.speed_y = 600

        self.color(random.randrange(256), random.randrange(256), random.randrange(256))


class EventHandler():
    def __init__(self):
        screen.onclick(self.place_cube)
        self.created = 0

    def place_cube(self, x, y):

        if self.created < 7:
            cube_list.append(Cube(x, y))

            for cube in cube_list:
                cube.onclick(cube.jump)

            self.created += 1
       

# --------- MAIN -----------
def main(fps):
    # ---- Init ---------
    update_ms = int(1000/fps)
    events = EventHandler()
    ground = Ground()

    # --- Engine -----
    def gameloop():
        for cube in cube_list:
            cube.updateposition(ground.floor)
            cube.clear()
            #cube.write(('%.2f, %.2f' % (cube.speed_x, cube.speed_y)), move=False)
        screen.ontimer(gameloop, update_ms)
    

    gameloop()

main(60.0)

screen.listen()
screen.mainloop()


"""
session 14:30
        16:50 - 18:14
"""