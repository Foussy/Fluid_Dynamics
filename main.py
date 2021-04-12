import time
import numpy as np
import pygame

from Fluid import Fluid
from Field import Field

def pygame_window():
    pygame.init()

    white = (255,255,255)
    black = (0, 0, 0)

    size = 32
    scale = 15
    fluid = Fluid(dt=0.5, diffusion=0, viscosity=0)
    field = Field(size, fluid)

    gameDisplay = pygame.display.set_mode((scale*size,scale*size))
    gameDisplay.fill(black)

    clock = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.MOUSEMOTION:
                pos = pygame.mouse.get_pos()
                vel = pygame.mouse.get_rel()
                x = int(pos[1] / scale)
                y = int(pos[0] / scale)
                field.add_density(x, y, 200)
                field.add_velocity(x, y, vel[1], vel[0])

            
                 
            for i in range(size - 2):
                for j in range(size - 2):
                    d = int(field.density[i+j*size])
                    try:
                        pygame.draw.rect(
                            gameDisplay, (d,d,d), [j* scale, i*scale, scale, scale])
                    except Exception as e:
                        print(e)
    
        field.fluidstep()
        pygame.display.update()
        clock.tick(1/fluid.dt)

if __name__== '__main__':
    pygame_window()

