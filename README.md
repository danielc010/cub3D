*This project has been created as part of the 42 curriculum by dachin and luimarti.*

# CUB3D

## DESCRIPTION

cub3D is a 3D game engine built as part of the 42 curriculum, using only the MLX42 graphics library. The goal is to reproduce the visual style of Wolfenstein 3D (1992): a first-person, real-time view of a maze rendered with ray-casting, complete with textured walls, a flat-colored floor, and a flat-colored ceiling.

The project is divided between two authors: **dachin** is responsible for the parser and world data - reading and validating the `.cub` map file, loading textures, parsing colors, and detecting the player's starting position and direction; **luimarti** is responsible for the engine and renderer - the ray-casting algorithm, wall rendering and texture mapping, the MLX42 window and game loop, and player movement.

### How it works

The program follows this pipeline for every `.cub` file passed as an argument:

1. **Parser** - reads the map file line by line, extracts the four wall texture paths (`NO`, `SO`, `EA`, `WE`), the floor and ceiling colors (`F`, `C`), and the map grid itself.
2. **Validation** - checks the map is well-formed and fully enclosed by walls using a flood-fill from the player's starting position, and confirms exactly one player start marker (`N`, `S`, `E`, or `W`) exists.
3. **World setup** - packs colors into MLX42's pixel format, loads wall textures with `mlx_load_png()`, and derives the player's initial direction vector and camera plane from the start marker.
4. **Ray-casting** - for every vertical column of pixels on screen, casts a ray from the player into the map using DDA, finds the perpendicular distance to the nearest wall, and draws a vertical stripe scaled to that distance.
5. **Rendering** - samples the correct wall texture based on which face (N/S/E/W) was hit, fills the floor and ceiling with their flat colors, and pushes the finished frame to the MLX42 image buffer every loop.
6. **Input** - keyboard hooks read `W`/`A`/`S`/`D` for movement and the arrow keys for rotation each frame, and `ESC` or the window-close button exits cleanly with no leaks.

### Key Concepts

* **Ray-casting**
  For each screen column, an imaginary ray is cast from the player into the map. The distance it travels before hitting a wall determines how tall that column is drawn. It isn't true 3D - it works because every wall is the same height - but it's cheap enough to run in real time on a CPU.

* **DDA (Digital Differential Analysis)**
  The algorithm that steps each ray through the map grid cell by cell, rather than checking every pixel along its path, making the ray-caster fast enough for real-time rendering.

* **Fish-eye correction**
  Using the straight-line (Euclidean) distance from the player to the wall hit point makes walls curve at the edges of the screen. The fix is to measure the perpendicular distance to the camera plane instead.

* **Camera plane & direction vector**
  The direction vector points where the player is facing; the camera plane is perpendicular to it and controls the field of view. Rotating the player rotates both vectors together.

* **Texture mapping**
  Each pixel in a wall column is mapped to a corresponding pixel in the hit wall's texture image, based on exactly where the ray struck the wall and how far up the column that pixel sits.

* **Flood fill**
  Starting from the player's position, flood fill expands outward through open cells. If it ever reaches the edge of the map or an undefined cell, the map isn't fully enclosed and parsing fails with an error.

---

## INSTRUCTIONS

### Compilation

Compile the program using the Makefile:

    make

Remove object files:

    make clean

Remove object files and the executable:

    make fclean

Recompile everything:

    make re

### Execution

Run the program with a `.cub` map file:

    ./cub3D maps/example.cub

Controls:

| Key | Action |
|---|---|
| `W` / `A` / `S` / `D` | Move forward / left / back / right |
| `←` / `→` | Rotate the camera left / right |
| `ESC` | Close the window and exit cleanly |

### Map file format (`.cub`)

| Element | Description |
|---|---|
| `NO`, `SO`, `EA`, `WE` | Paths to the north, south, east, and west wall textures |
| `F` | Floor color as `R,G,B` |
| `C` | Ceiling color as `R,G,B` |
| Map grid | A block of `1` (wall), `0` (empty), and one player marker (`N`/`S`/`E`/`W`), fully enclosed by walls |

---

## RESOURCES

* Lode's Computer Graphics Tutorial - Raycasting
  https://lodev.org/cgtutor/raycasting.html

* MLX42 documentation
  https://github.com/codam-coding-college/MLX42

* Wolfenstein 3D - game design reference
  https://en.wikipedia.org/wiki/Wolfenstein_3D

* Linux man pages: `open`, `read`, `malloc`, `free`
  https://man7.org/linux/man-pages/

### AI Usage

AI tools were used in this project for:
* Helping to understand the underlying concepts better.
* Identifying and debugging of bugs.

