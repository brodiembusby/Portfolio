import pygame
from pygame.locals import *
pygame.init()

class drawable_object():

    image = "Sprint3\warning.png"
    
    def __init__(self,image,x,y):
        self.x = x
        self.y = y
        self.image = pygame.image.load(image)
        self.image_rect = self.image.get_rect()

    def draw(self):
        self.rect = screen.blit(self.image,(self.x,self.y))


size = width, height = 500, 500
ball_speed = [1,1]


pro_x = 0
pro_y = 0
pro_speed = [pro_x,pro_y]

black = 0,0,0

playing = True

screen = pygame.display.set_mode(size)
ballClass = drawable_object("Sprint3\picture_of_me.png",0,0)

ball = pygame.image.load("Sprint3\picture_of_me.png")
ballrect = ball.get_rect()

pro = pygame.image.load("Sprint3\The_Cat_in_the_Hat.png")
prorect = pro.get_rect()

background = [ball,pro]


while playing:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()

    ballrect = ballrect.move(ball_speed)    
    if ballrect.left < 0 or ballrect.right > width:
        ball_speed[0] = -ball_speed[0]
    if ballrect.top < 0 or ballrect.bottom > height:
        ball_speed[1] = -ball_speed[1]

    if pygame.key.get_pressed()[K_w]:
        pro_x -=1   
    screen.fill(black)
    screen.blit(ball, ballrect)
    pygame.display.flip()