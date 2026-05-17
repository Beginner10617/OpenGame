# OpenGame

A small OpenGL-based car racing / driving game project built in C++.

The project is currently in development stage and serves as an experiment in rendering, basic physics, and gameplay for a simple 3D driving game.

## Features

- OpenGL-based rendering pipeline
- `Mesh3D` abstraction for rendering geometry
- `Model` system for grouping and rendering meshes
- Basic transform system
- `RigidBody` physics implementation
- Velocity-based movement
- Simple car controller
- Player input handling (steering + acceleration)
- Basic ground rendering and textured meshes
- Separation of rendering and physics logic

## Overview

### Mesh3D

`Mesh3D` is responsible for low-level geometry rendering and GPU interaction.

It includes:

- Vertex/index data
- Texture handling
- OpenGL draw calls
- Rendering mesh data

### Model

`Model` acts as a higher-level rendering abstraction composed of one or more meshes.

It includes:

- Grouping meshes together
- Rendering complete objects
- Managing position and orientation data
- Scene-level organization of visual assets

`Model` is intended to remain rendering-only

### RigidBody

`RigidBody` stores physical state for entities.

Current responsibilities:

- Linear velocity
- Force accumulation
- Physics integration

Physics currently focuses on simple arcade-style motion rather than realism.

### Car

The `Car` class combines:

1. Input handling  
2. Physics interaction  
3. Rendering coordination

The goal is to keep gameplay logic centralized while keeping rendering (`Model`) and simulation (`RigidBody`) separate.

## Project Structure

Example structure:

```txt
OpenGame/
├── build/
├── include/
├── src/
├── shaders/
├── textures/
├── meshes/
├── Makefile
└── README.md
```

## Build

The project is written in:

- C++
- OpenGL
- GLM
- SDL (for window/input handling)
- stb_image (texture loading)

To build just run the Makefile:

```
make
```

## Current State

Development is temporarily paused after implementing:

- Rendering abstractions (`Mesh3D`, `Model`)
- Basic rigidbody physics
- Initial car movement/controller logic

Future goals include:

- Better car handling physics
- Better camera system (to follow player)
- Config-driven resource loading
- Level system and gameplay
- UI / HUD

## Status

Early prototype / work in progress

This repository is currently experimental