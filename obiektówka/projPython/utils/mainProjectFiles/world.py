class World:
    def __init__(self, name, sizeX, sizeY):
        self.name = name
        self.sizeX = self._validate_size(sizeX)
        self.sizeY = self._validate_size(sizeY)
        self.turn = 0
        self.map = [[0 for _ in range(sizeY)] for _ in range(sizeX)]
        self.organisms = []
        

    def _validate_size(self, value):
        return 10 if value <=0 else value
    


    