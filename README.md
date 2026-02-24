*This project has been created as part of the 42 curriculum by banne, jhauvill.*

# Cub3D - A 3D Maze Game using Raycasting

## Description

Cub3D is a realistic 3D maze exploration game developed in C using the **raycasting** technique. The project aims to create a pseudo-3D perspective inspired by classic games like Wolfenstein 3D, without using 3D graphics libraries.

### Key Features

- **3D Raycasting Engine**: Renders a first-person 3D view of a maze using mathematical raycasting algorithm
- **Dynamic Lighting & Textures**: Custom textured walls with proper perspective correction and shading
- **Weapon System**: Two weapons (pistol and knife) with ammunition management and reload mechanics
- **Interactive Map**: 
  - Doors that can be opened
  - Enemies with health system
  - Minimap display
- **Audio System**: Sound effects for actions (shooting, reloading, footsteps, etc.)
- **Input Handling**: Keyboard controls for movement and rotation, mouse support for aiming and menus
- **Menu System**: Enter animation and interactive main menu before gameplay

### Technical Highlights

- **Pure Software Rendering**: No 3D graphics libraries, entirely using pixel manipulation
- **Efficient File Parsing**: Robust `.cub` map format parser with validation
- **Memory Management**: Proper allocation and deallocation with leak-free gameplay

---

## Instructions

### Compilation

```bash
make
```

This will compile the project and produce the `cub3d` executable. The Makefile will automatically:
- Clone and build the minilibx library (if not present)
- Compile the libft library (custom C standard library)
- Link all object files with required libraries

### Running the Game

```bash
./cub3d maps/valid/map.cub
```

You need to provide a valid `.cub` map file as argument. Several example maps are provided in the `maps/valid/` directory.

### Map Format

The `.cub` file specifies:
- **NO**, **SO**, **WE**, **EA**: Paths to textures for north, south, west, and east walls
- **F** and **C**: Floor and ceiling colors in RGB format (0-255,0-255,0-255)
- **Map**: A 2D grid where:
  - `0` = empty space
  - `1` = wall
  - `N`, `S`, `E`, `W` = player spawn position and direction
  - `D` = door

Example:
```
NO ./textures/wall_north.xpm42
SO ./textures/wall_south.xpm42
WE ./textures/wall_west.xpm42
EA ./textures/wall_east.xpm42
F 220,100,0
C 225,30,0

111111
101001
101001
100001
111111
```

### Game Controls

| Key | Action |
|-----|--------|
| **W** | Move forward |
| **S** | Move backward |
| **A** | Strafe left |
| **D** | Strafe right |
| **← →** or **Mouse Movement** | Rotate view left/right |
| **Mouse Left Click** | Shoot (pistol) or Use knife attack |
| **E** | Open door |
| **M** | Open menu |
| **R** or **Mouse Right Click** | Reload weapon |
| **ESC** | Exit game |

### Cleaning Up

```bash
make clean       # Remove object files
make fclean      # Remove all generated files including executable
make re          # Full recompilation
```

---

## Resources

### References & Documentation

- **Raycasting Algorithm**: 
  - [Lode Vandevelde's Raycasting Guide](https://lodev.org/cgtutor/raycasting.html)

---

## Project Structure

```
cub3d/
├── includes/             # Header files
│   ├── cub3d.h           # Main header with function declarations
│   ├── struct.h          # Data structure definitions
│   ├── color.h           # Terminal color macros
│   ├── controls.h        # Game control and constant definitions
│   └── minilibx-linux/   # Graphics library
├── src/                  # Source code
│   ├── main.c            # Entry point
│   ├── parsing/          # Map and configuration file parsing
│   ├── initializer/      # Game initialization and resource loading
│   ├── raycasting/       # Raycasting rendering engine
│   ├── render/           # UI and sprite rendering
│   ├── game/             # Game logic and movement
│   ├── handle/           # Input handling (keyboard, mouse)
│   ├── weapons/          # Combat system and weapon mechanics
│   ├── audio/            # Sound and music management
│   ├── utils/            # Utility functions
│   └── libft/            # Custom C standard library
├── maps/                 # Game maps
│   ├── valid/            # Valid test maps
│   └── invalid/          # Invalid maps for testing error handling
├── textures/             # Game textures and sprites
├── sounds/               # Audio files
└── Makefile              # Build configuration
```

---

## Author

**banne**  **jhauvill** - 42 Student

---

## License

This project is part of the 42 curriculum and is provided as-is for educational purposes.
