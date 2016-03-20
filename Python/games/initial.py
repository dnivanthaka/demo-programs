#!/usr/bin/env python

import pygame
from pygame.locals import *

pygame.init();
window_size = [640, 480];
screen = pygame.display.set_mode( window_size )

pygame.display.set_caption("Pygame Test")

clock = pygame.time.Clock() # controlling the game speed

font = pygame.font.Font(None, 36);
game_msg = font.render("Pygame", True, (255, 0, 0))
game_msg_rect = game_msg.get_rect()
game_msg_rect.centerx = (window_size[0] / 2)
game_msg_rect.centery = (window_size[1] / 2)

game_exit = False;

while game_exit == False:
    #screen.fill((255, 255, 255));
    screen.fill((0, 0, 0));

    screen.blit(game_msg, game_msg_rect)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            game_exit = True

    clock.tick(60)

    pygame.display.flip()
