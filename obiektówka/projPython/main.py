from utils.mainProjectFiles.world import World
from utils.graphicDesign.graphics import Graphics

import pygame


sizeX = int(input("Podaj szerokość świata: "))
sizeY = int(input("Podaj wysokość świata: "))

# Inicjalizacja świata i grafiki
myWorld = World("moj kochany swiat", sizeX, sizeY)
graphics = Graphics(myWorld.name, 800, 600, 40)

clock = pygame.time.Clock()
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    graphics.draw_grid()
    graphics.update_display()
    clock.tick(60)

graphics.quit()