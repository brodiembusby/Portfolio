import pygame
from inventory import * # Imports UI,Inventory
from pygame.locals import *
from random import randint #Randint for postioning
pygame.init()   # Start pygame
vec = pygame.math.Vector2 # Vector for postion
class Player():

    def __init__(self,x,y):
        
        # Postition
        self.pos = vec(x,y)

        # Inventory values
        self.key = 0
        self.chest = 0
        
        # Movement settings
        self.acc = vec(0,0)
        self.vel = vec(0,0)
        self.ACC = .3
        self.FRIC = -0.1
        
        # Image and rect wall
        self.image = pygame.image.load('Sprint3\images\main.png')
        self.rect = self.image.get_rect()

    def move(self):
        self.acc = vec(0,0)
        
        keys = pygame.key.get_pressed()

        # Movement controls
        if keys[K_LEFT]:
            self.acc.x  = -self.ACC
        if keys[K_RIGHT]:
            self.acc.x = self.ACC
        if keys[K_UP]:
            self.acc.y  = -self.ACC
        if keys[K_DOWN]:
            self.acc.y = self.ACC

        # Accelerate, friction and velocity added for smoother movement
        self.acc.x += self.vel.x * self.FRIC
        self.vel += self.acc
        self.pos += self.vel + 0.5 * self.acc

    def render(self):
        # Render player
        screen.blit(self.image,self.pos)
class Object(Player):
    # Any interactable object thats not a player
    def __init__(self,image,x,y):
        self.pos = vec(x,y)
        
        self.image = pygame.image.load(image)
        self.rect = self.image.get_rect()
        
    def render(self):
        screen.blit(self.image,self.pos)
class UserInterface():
    
    def __init__(self,player):

        self.inventory = Inventory(player)              

    def update(self):
        # Updates value variables
        self.inventory.update()
    def render(self,screen):  
        # Updates values on screen
        self.inventory.render(screen)         
def boundaries(ob):
    # Redundant at the moment for future use
    if ob.pos.x <= 0:
        ob.pos.x = 10
        ob.vel = vec(0,0)
    if ob.pos.x > 500:
        ob.pos.x = 450
        ob.vel = vec(0,0)
    if ob.pos.y <= 0 :
        ob.pos.y = 10
        ob.vel = vec(0,0)
    if ob.pos.y > 500:
        ob.pos.y = 450
        ob.vel = vec(0,0)

# Screen settings
size = width, height = 500, 500
transparent = (0,0,0,0)
screen = pygame.display.set_mode(size)

#All Objects called
chest = Object("Sprint3\images\chest.png",100,200)
key = Object("Sprint3\images\key.png",50,300)
flame = Object("Sprint3/images/flame.png",randint(50,400),randint(50,400))

# Player call
player = Player(400,300)
Ui = UserInterface(player)

background = pygame.image.load('Sprint3/images/background.png')

fps= 60
clock = pygame.time.Clock()

pygame.display.set_caption("Adventure")
playing = True

while playing:
    # Quit application
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()
    
    # Boundaries
    boundaries(player)

    # Move chest and keys around/add points
    if player.pos.x <= key.pos.x <= (player.pos.x+20 or player.pos.x -20)  and player.pos.y <= key.pos.y <= (player.pos.y+20) and player.key <=1: 
        key.image.fill(transparent)
        player.key = 1
        key = Object("Sprint3\images\key.png",randint(50,400),randint(50,400))    
    if player.pos.x <= chest.pos.x <= (player.pos.x+20 or player.pos.x -20)  and player.pos.y <= chest.pos.y <= (player.pos.y+20): 
        chest.image.fill(transparent)
        player.chest += 100
        player.key = 0
        chest = Object("Sprint3\images\chest.png",randint(50,400),randint(50,400))
        
    
    # Player controls
    player.move()
    
    # Render screen and objects
    screen.blit(background,(0,0))

    player.render()
    key.render()
    chest.render()
    #For future use
    # flame.render()
    Ui.render(screen)
    
    # Update screen and objects
    Ui.update()
    pygame.display.update()
    clock.tick(fps)
