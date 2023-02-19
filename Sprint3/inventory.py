import pygame
class InventorySlot():
    # Creation,placement, amount and,display for items
    def __init__(self,name,pos):
        self.image = pygame.image.load(name)
        self.rect = self.image.get_rect()
        self.rect.topleft = pos
        self.count = 0
       
        self.font = pygame.font.Font("Sprint3/font/Midspicy Regular.ttf",(50))
    
    def render(self,screen):
        text = self.font.render(str(self.count),True,(0,0,0))
        screen.blit(self.image,self.rect)
        screen.blit(text, self.rect.midright)

class Inventory():
    # Actual inventory and class made for updating items
    def __init__(self,player):
        self.slots = []
        self.image = pygame.image.load("Sprint3/images/nothing.png")
        
        self.player = player
        self.rect = self.image.get_rect()
        self.rect.topleft  = (0,100)
        self.slots.append(InventorySlot("Sprint3\images\key.png", (0,420)))
        self.slots.append(InventorySlot("Sprint3\images\chest.png",(0,0)))

    def render(self,screen):
        screen.blit(self.image,self.rect)
        for slot in self.slots:
            slot.render(screen)

    def update(self):
        self.slots[0].count = self.player.key
        self.slots[1].count = self.player.chest
