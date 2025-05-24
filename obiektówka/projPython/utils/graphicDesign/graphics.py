import pygame

class Graphics:
    def __init__(self, world, width=800, height=600, cell_size=40):
        self.world = world
        self.width = width
        self.height = height
        self.cell_size = cell_size

        # Kolory
        self.background = (240, 240, 240)
        self.grid_color = (0, 0, 0)
        self.line_width = 1

        # Inicjalizacja Pygame
        pygame.init()
        self.screen = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption(self.world.name)

        # Parametry kratownicy
        self.grid_width = self.width // self.cell_size
        self.grid_height = self.height // self.cell_size

    def draw_grid(self):
        self.screen.fill(self.background)

        # Rysowanie pionowych linii
        for x in range(0, self.width, self.cell_size):
            pygame.draw.line(
                self.screen,
                self.grid_color,
                (x, 0),
                (x, self.height),
                self.line_width
            )

        # Rysowanie poziomych linii
        for y in range(0, self.height, self.cell_size):
            pygame.draw.line(
                self.screen,
                self.grid_color,
                (0, y),
                (self.width, y),
                self.line_width
            )

    def update_display(self):
        pygame.display.flip()
    
    def quit(self):
        pygame.quit()