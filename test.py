import pygame
import numpy as np
import math
import random
from pygame.locals import *

# Initialize Pygame
pygame.init()

# Constants
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
FOV = math.pi / 3  # Field of view
HALF_FOV = FOV / 2
MAX_DEPTH = 20
TILE_SIZE = 1
PLAYER_HEIGHT = 0.5
PLAYER_SPEED = 0.05
TURN_SPEED = 0.03
WORLD_SIZE = 32

# Colors
SKY_COLOR = (135, 206, 235)
GRASS_COLOR = (34, 139, 34)
DIRT_COLOR = (139, 69, 19)
STONE_COLOR = (128, 128, 128)
WOOD_COLOR = (205, 133, 63)
LEAF_COLOR = (0, 100, 0)

# Block types
AIR = 0
GRASS = 1
DIRT = 2
STONE = 3
WOOD = 4
LEAF = 5

# Block properties
block_colors = {
    GRASS: GRASS_COLOR,
    DIRT: DIRT_COLOR,
    STONE: STONE_COLOR,
    WOOD: WOOD_COLOR,
    LEAF: LEAF_COLOR
}

# Set up display
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Minecraft 3D")
clock = pygame.time.Clock()

class Player:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y  # Height
        self.z = z
        self.angle = 0
        self.pitch = 0
        
    def move(self, world, dx=0, dz=0):
        # Calculate movement based on player's angle
        new_x = self.x + dx * math.cos(self.angle) - dz * math.sin(self.angle)
        new_z = self.z + dx * math.sin(self.angle) + dz * math.cos(self.angle)
        
        # Simple collision detection
        block_x, block_z = int(new_x), int(new_z)
        if (0 <= block_x < WORLD_SIZE and 0 <= block_z < WORLD_SIZE and 
            world[block_x][int(self.y)][block_z] == AIR and 
            world[block_x][int(self.y) + 1][block_z] == AIR):
            self.x, self.z = new_x, new_z
            
    def update(self, world):
        # Gravity
        if self.y > 0 and world[int(self.x)][int(self.y - 0.1)][int(self.z)] == AIR:
            self.y -= 0.1
        
        # Prevent falling through the floor
        if self.y < 0.5:
            self.y = 0.5

def create_world():
    # Create a 3D numpy array for the world (x, y, z)
    world = np.zeros((WORLD_SIZE, WORLD_SIZE, WORLD_SIZE), dtype=int)
    
    # Generate terrain height map
    height_map = np.zeros((WORLD_SIZE, WORLD_SIZE), dtype=int)
    for x in range(WORLD_SIZE):
        for z in range(WORLD_SIZE):
            # Simple terrain generation
            height = int(WORLD_SIZE/4 + 
                         math.sin(x/5) * math.cos(z/5) * 2 + 
                         random.uniform(-0.5, 0.5))
            height_map[x][z] = min(max(height, 1), WORLD_SIZE//2)
    
    # Fill the world with blocks
    for x in range(WORLD_SIZE):
        for z in range(WORLD_SIZE):
            height = height_map[x][z]
            
            # Add grass on top
            world[x][height][z] = GRASS
            
            # Add dirt layer
            for y in range(height-3, height):
                if y >= 0:
                    world[x][y][z] = DIRT
            
            # Add stone below dirt
            for y in range(0, height-3):
                world[x][y][z] = STONE
    
    # Add some trees
    for _ in range(5):
        tx = random.randint(5, WORLD_SIZE-5)
        tz = random.randint(5, WORLD_SIZE-5)
        th = height_map[tx][tz]
        
        # Tree trunk
        tree_height = random.randint(3, 5)
        for y in range(th+1, th+tree_height+1):
            if y < WORLD_SIZE:
                world[tx][y][tz] = WOOD
        
        # Tree leaves
        leaf_height = th + tree_height
        for lx in range(tx-2, tx+3):
            for ly in range(leaf_height-1, leaf_height+2):
                for lz in range(tz-2, tz+3):
                    if (0 <= lx < WORLD_SIZE and 
                        0 <= ly < WORLD_SIZE and 
                        0 <= lz < WORLD_SIZE and
                        world[lx][ly][lz] == AIR and
                        abs(lx-tx) + abs(ly-leaf_height) + abs(lz-tz) <= 3):
                        world[lx][ly][lz] = LEAF
    
    return world, height_map

def cast_ray(player, world, ray_angle, ray_pitch):
    # Calculate direction vector
    dx = math.cos(ray_angle) * math.cos(ray_pitch)
    dy = math.sin(ray_pitch)
    dz = math.sin(ray_angle) * math.cos(ray_pitch)
    
    # Normalize direction vector
    length = math.sqrt(dx*dx + dy*dy + dz*dz)
    dx /= length
    dy /= length
    dz /= length
    
    # Ray starting position
    rx, ry, rz = player.x, player.y, player.z
    
    # Ray casting loop
    for i in range(MAX_DEPTH):
        # Move along ray
        rx += dx * 0.1
        ry += dy * 0.1
        rz += dz * 0.1
        
        # Check if ray is out of bounds
        bx, by, bz = int(rx), int(ry), int(rz)
        if not (0 <= bx < WORLD_SIZE and 0 <= by < WORLD_SIZE and 0 <= bz < WORLD_SIZE):
            return None, MAX_DEPTH
        
        # Check if ray hit something
        if world[bx][by][bz] != AIR:
            block_type = world[bx][by][bz]
            distance = math.sqrt((rx-player.x)**2 + (ry-player.y)**2 + (rz-player.z)**2)
            return block_type, distance
    
    return None, MAX_DEPTH

def render(player, world):
    screen.fill(SKY_COLOR)
    
    # Calculate visible screen slice sizes
    slice_width = SCREEN_WIDTH / 120
    
    # Cast rays for each screen column
    for i in range(120):  # Lower resolution for better performance
        # Calculate ray angle
        ray_angle = player.angle - HALF_FOV + (i / 120) * FOV
        
        # Cast multiple rays at different pitches for vertical rendering
        for j in range(90):  # Lower resolution for better performance
            ray_pitch = player.pitch - HALF_FOV/2 + (j / 90) * HALF_FOV
            
            block, distance = cast_ray(player, world, ray_angle, ray_pitch)
            
            if block:
                # Calculate wall height based on distance
                height = min(int(SCREEN_HEIGHT / (distance + 0.0001)), SCREEN_HEIGHT)
                
                # Darken color based on distance
                color = block_colors[block]
                darkness = max(0.2, 1.0 - distance / MAX_DEPTH)
                display_color = (color[0] * darkness, color[1] * darkness, color[2] * darkness)
                
                # Calculate position
                x = int(i * slice_width)
                y = int(SCREEN_HEIGHT/2 - height/2 + (player.pitch * SCREEN_HEIGHT/4))
                
                # Draw a small rectangle for this ray hit
                pygame.draw.rect(
                    screen, 
                    display_color, 
                    (x, y, math.ceil(slice_width), height)
                )

def main():
    # Create world
    world, height_map = create_world()
    
    # Create player at a suitable spawn position
    spawn_x, spawn_z = WORLD_SIZE//2, WORLD_SIZE//2
    spawn_y = height_map[spawn_x][spawn_z] + 1
    player = Player(spawn_x, spawn_y, spawn_z)
    
    # Main game loop
    running = True
    pygame.mouse.set_visible(False)
    pygame.event.set_grab(True)
    
    while running:
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False
            elif event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    running = False
            elif event.type == MOUSEMOTION:
                # Look around with mouse
                dx, dy = event.rel
                player.angle += dx * TURN_SPEED / 20
                player.pitch -= dy * TURN_SPEED / 20
                # Clamp pitch to prevent flipping
                player.pitch = max(min(player.pitch, math.pi/3), -math.pi/3)
        
        # Handle movement keys
        keys = pygame.key.get_pressed()
        if keys[K_w]:
            player.move(world, dz=PLAYER_SPEED)
        if keys[K_s]:
            player.move(world, dz=-PLAYER_SPEED)
        if keys[K_a]:
            player.move(world, dx=-PLAYER_SPEED)
        if keys[K_d]:
            player.move(world, dx=PLAYER_SPEED)
        if keys[K_SPACE] and not world[int(player.x)][int(player.y)-1][int(player.z)] == AIR:
            player.y += 0.5  # Simple jump
        
        # Update player
        player.update(world)
        
        # Render the scene
        render(player, world)
        
        # Display FPS
        fps = font.render(f"FPS: {int(clock.get_fps())}", True, (255, 255, 255))
        screen.blit(fps, (10, 10))
        
        pygame.display.flip()
        clock.tick(60)

if __name__ == "__main__":
    # Initialize font
    font = pygame.font.SysFont('Arial', 18)
    main()
    pygame.quit()