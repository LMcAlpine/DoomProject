# DoomProject

A small C++ experiment that loads classic DOOM file data and renders a 2D representation with SDL2. The project goal is to read a WAD file, parse level information, and display an overhead view.

# Features
- WAD parsing with ```WADReader``` extracting data from IWAD/PWAD files and populating the in-memory ```Level``` Representation.
- 2D level rendering with ```Level``` translating map geometry to screen coordinates and renders an overhead view using an SDL renderer.
- Basic engine loop with ```Game``` setting up an SDL window/renderer and delegates to ```Engine``` for updating, input handling, and drawing.
- Unit tests in ```DoomGameTests``` using Google Test to validate core WAD reading routines such as header parsing and safe byte access helpers.

# Project Structure
```graphql
DoomProject/
├── DoomGame/          # Game/engine source
│   ├── Engine.*       # Core engine loop and WAD loading
│   ├── Game.*         # SDL initialization and frame processing
│   ├── Level.*        # Map data structures and rendering
│   ├── Player.*       # Player representation
│   └── WADReader.*    # WAD file parser
├── DoomGameTests/     # Google Test unit tests
├── MyDoomProject.sln  # Visual Studio solution
```
