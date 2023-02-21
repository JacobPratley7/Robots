# Robots

A survival game, in which the aim is to get to the exit without being caught by the robots.

## Map

The map will hold the location of the robots, human and exit. Each map will have an exit the human must reach to proceed into the next level. Once a all robots are destroyed or the human has reached the exit, the player will be moved to the next level.

Every time the human escapes, a new map will need to be generated. Specifying the starting location of the human, how many robots and each robot's starting location.

Each 8x8 map, will denote a robot using an `R` symbol and the human will be denoted using a `H` symbol. When two robots have collided the cell remaining is `D`, which shows that the robots have been destroyed on that location. Exits are shown using the `E` symbol.

Example of a map.

```
| | | | | | | | |
| | | | | | |E| |
| |H| | | | | | |
| | | | | | | | |
| | | | | | |R| |
| | | | |D| | | |
| | | | | | | | |
| |R| | |R| | | |

```

## Robots

Each robot will have a position on the board which is specified from user input. A robot can be destroyed when two robots collide by occupying the same cell on a move. A robot will move towards the human until it has captured it. Once it has captured the human, the robots have won.

## Human

The human will move around the map and the program will take commands from the user. The following commands will be accepted by the program to move the human:

* North (NT)
* South (ST)
* West (WT)
* East (ET)

## Exit Location

The exit location will use a number provided by via command line arguments. This will act as a seed for the random number generated.

## Commands

* move <(NT|ST|WT|ET)> - Moves the human to a new cell.
* display - Displays the grid and where the robots, human and exit is.
* exit - Quits the program
