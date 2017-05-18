    # Libraries
import pygame
import random

    # Project
from blob import Blob

STARTING_BLUE_BLOBS = 10
STARTING_RED_BLOBS = 3

WIDTH  = 800
HEIGHT = 600

WHITE = (255,255,255)
RED   = (255,0,0)
BLUE  = (0,0,255)
GREEN = (0,255,0)
BLACK = (0,0,0)

game_display = pygame.display.set_mode((WIDTH,HEIGHT))  # Setting window width and height creating the display object
pygame.display.set_caption("Blob World")                # Setting window title
clock = pygame.time.Clock()                             # Init Clock() object


class BlueBlob(Blob):

    def __init__(self, color, x_boundary, y_boundary):
        super().__init__(color, x_boundary, y_boundary)
        self.color = BLUE

    def move_fast(self):
        self.x += random.randrange(-7, 8)
        self.y += random.randrange(-7, 8)


def update(blob_list):                       # Updating game state

    for blob_dict in blob_list:
        for blob_id in blob_dict:
            blob = blob_dict[blob_id]
            blob.move_fast()
            blob.check_bounds()

def render(blob_list):                        # Rendering the frame buffer, then swapping with front buffer
        # Clear buffer
    game_display.fill(WHITE)

        # Draw objects to buffer
    for blob_dict in blob_list:
        for blob_id in blob_dict:
            blob = blob_dict[blob_id]
            pygame.draw.circle(game_display, blob.color, [blob.x, blob.y], blob.size)

        # Swap frame buffer
    pygame.display.update()                         # Asks pygame to update window with new frame from frame buffer

def main():
        # Instantiating objects
    blue_blobs = dict(enumerate([BlueBlob(BLUE, WIDTH, HEIGHT) for i in range(STARTING_BLUE_BLOBS)]))
    red_blobs = dict(enumerate([BlueBlob(RED, WIDTH, HEIGHT) for i in range(STARTING_RED_BLOBS)]))

        # Game loop
    while True:
            # Event system
        for event in pygame.event.get():
            if event.type == pygame.QUIT:           # pygame.QUIT - exit button on window
                pygame.quit()

            # Update frame model
        update([blue_blobs, red_blobs])

            # Render model to frame
        render([blue_blobs, red_blobs])

            # End of loop
        clock.tick(60)                              # Sets static FPS to 60 FPS


if __name__ == '__main__':
    main()
    print("Program exit!")
