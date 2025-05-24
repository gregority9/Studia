import pygame
import random
from enum import Enum
from typing import Tuple, Optional, List
from world import World

class Direction(Enum):
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3

    @classmethod
    def from_int(cls, value: int):
        return list(cls)[value]
    

class Organism:
    def __init__(self, x: int, y: int, world: World):
        self.x = x
        self.y = y
        self.strength = 0
        self.initiative = 0
        self.symbol = ' '
        self.name = ""
        self.age = 0
        self.world = world
        self.is_alive = True

        # Atrybuty do renderowania w Pygame
        self.color = (255, 255, 255)  # Domyślny kolor (biały)
        self.size = 20  # Rozmiar kwadratu w pikselach

    def action(self):
        raise NotImplementedError("Subclasses must implement this method")
    
    def draw(self, screen: pygame.Surface, offset_x: int = 0, offset_y: int = 0):
        """Renderuje organizm na ekranie Pygame"""
        rect = pygame.Rect(
            self.x * self.size + offset_x,
            self.y * self.size + offset_y,
            self.size,
            self.size
        )
        pygame.draw.rect(screen, self.color, rect)
        
        # Opcjonalnie: rysowanie symbolu
        font = pygame.font.SysFont(None, 20)
        text = font.render(self.symbol, True, (0, 0, 0))
        screen.blit(text, (rect.x + 5, rect.y + 5))

    def die(self):
        self.is_alive = False
        self.world.map[self.x][self.y] = '.'
        if isinstance(self, Human):
            self.world.handle_human_death()

    def increase_age(self):
        self.age += 1

    def try_move(self) -> Tuple[int, int]:
        good_dir = False
        direction = None

        while not good_dir:
            direction = Direction.from_int(random.randint(0, 3))
            
            if direction == Direction.UP and self.y - 1 >= 0:
                good_dir = True
            elif direction == Direction.DOWN and self.y + 1 < self.world.size_y:
                good_dir = True
            elif direction == Direction.LEFT and self.x - 1 >= 0:
                good_dir = True
            elif direction == Direction.RIGHT and self.x + 1 < self.world.size_x:
                good_dir = True

        new_x, new_y = self.x, self.y
        
        if direction == Direction.UP:
            new_y -= 1
        elif direction == Direction.DOWN:
            new_y += 1
        elif direction == Direction.LEFT:
            new_x -= 1
        elif direction == Direction.RIGHT:
            new_x += 1

        return new_x, new_y

    def move(self, new_x: int, new_y: int):
        self.x = new_x
        self.y = new_y

    def respond_to_collision(self, other) -> bool:
        raise NotImplementedError("Subclasses must implement this method")

    # Gettery i settery (w Pythonie zwykle używamy bezpośredniego dostępu do atrybutów)
    @property
    def position(self) -> Tuple[int, int]:
        return self.x, self.y

    @position.setter
    def position(self, value: Tuple[int, int]):
        self.x, self.y = value
