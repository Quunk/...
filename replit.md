# Arkanoid Game Project

## Overview

This is a basic Arkanoid (brick breaker) game built in Java using Swing. The game features a paddle that can be controlled with keyboard input, a bouncing ball with collision detection, and a grid of colorful bricks.

**Purpose**: Classic arcade-style brick breaker game with object-oriented design.

**Tech Stack**: Java (GraalVM 22.3), Swing GUI framework

**Date Created**: October 5, 2025

## User Preferences

Preferred communication style: Simple, everyday language.

## System Architecture

### Class Hierarchy

The game follows object-oriented principles with a clear class hierarchy:

- **GameObject** (abstract): Base class for all game objects
  - Provides position (x, y), dimensions (width, height), and bounding box
  - Defines abstract methods: `update()` and `render(Graphics g)`

- **MovableObject** (extends GameObject): Base for objects with velocity
  - Adds velocity properties (velocityX, velocityY)
  - Extended by Paddle and Ball

- **Paddle** (extends MovableObject): Player-controlled paddle
  - Moves left/right with arrow keys or A/D keys
  - Constrained to stay within game boundaries
  - Speed: 7 pixels per frame

- **Ball** (extends MovableObject): Bouncing ball
  - Bounces off walls and paddle
  - Detects collision with paddle and adjusts angle based on hit position
  - Resets when it falls below the screen
  - Initial velocity: (3, -3)

- **Brick** (extends GameObject): Static brick objects
  - Rendered in a 5x10 grid with different colors per row
  - Currently for display only (collision detection not implemented yet)

- **GameManager** (extends JPanel): Main game controller
  - Implements game loop using Swing Timer (60 FPS, 16ms per frame)
  - Handles keyboard input via KeyListener
  - Manages all game objects (paddle, ball, bricks)
  - Renders all objects via paintComponent

- **Game**: Main entry point
  - Creates JFrame window (800x600)
  - Initializes and displays GameManager panel

### Game Loop

The game uses a Swing Timer that fires every 16ms (~60 FPS):
1. Update all game objects
2. Check collisions
3. Repaint the screen

### Controls

- **Left Arrow** or **A**: Move paddle left
- **Right Arrow** or **D**: Move paddle right

## Project Structure

```
src/
├── GameObject.java       - Abstract base class
├── MovableObject.java    - Base for moving objects
├── Paddle.java          - Player paddle
├── Ball.java            - Bouncing ball
├── Brick.java           - Brick objects
├── GameManager.java     - Game loop and rendering
└── Game.java            - Main entry point
```

## Running the Game

The game runs via the "Arkanoid Game" workflow which compiles and executes:
```bash
cd src && javac *.java && java Game
```

## Future Enhancements

Potential additions to expand beyond the base version:
1. Brick collision detection and removal
2. Score tracking system
3. Multiple lives with ball respawning
4. Level progression with different brick layouts
5. Power-ups (multi-ball, paddle size changes, speed modifications)
6. Sound effects and background music
7. Win/lose game states
