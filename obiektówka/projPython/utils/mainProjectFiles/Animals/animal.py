from ..organism import Organism
from ..world import World

class Animal(Organism):
    def __init__(self, x: int, y: int, world: World):
        super.__init__(x, y, World)
        self.symbol = 'A'
        self.name = "Animal"

        # Domyślne wartości dla zwierzęcia (możesz zmienić)
        self.strength = 3
        self.initiative = 2
        self.color = (255, 165, 0)  # Pomarańczowy dla zwierząt

    def action(self):
        new_x, new_y = self.try_move()

        # Sprawdź czy nowa pozycja jest pusta lub czy jest tam inny organizm
        target = self.world.get_organism_at(new_x, new_y)
        
        if target is None:
            self.move(new_x, new_y)
        else:
            # Kolizja - zwierzę próbuje zjeść inny organizm
            