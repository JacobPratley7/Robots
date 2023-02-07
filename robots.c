#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int grid[8][8];
int player_location[2];
int escape[2];
int player_previous = 0;

struct robot
{
    int x;
    int y;
    int dead;
    int displayable;
};

struct robot Robots[10];
int total_robots;
//hi
void removeLine(char line[]) {
    int len = strlen(line);
    for(int i = 0; i < len; i++) {
        if(line[i] == '\n') {
            line[i] = 0;
            break;
        }
    }
}

void setExit(int seed) {
    srand(seed);
    escape[1] = rand() % 8;
    escape[0] = rand() % 8;
    return;
}

int setPlayer(int row, int column) {
    if(row < 0 || row >= 8) {
        printf("Invalid Coordinates, Try again\n");
        return 0;
    }
    if(column < 0 || column >= 8) {
        printf("Invalid Coordinates, Try again\n");
        return 0;
    }
    if(row == escape[0] && column == escape[1]) {
        printf("Invalid coordinates, Try again\n");
        return 0;
    }
    player_location[1] = row;
    player_location[0] = column;
    return 1;
}

int generateRobot(int row, int column, int index) {
    for(int i = 0; i < index; i++) {
        if(Robots[i].y == row && Robots[i].x == column) {
            printf("Invalid Coordinates, Try again\n");
            return 0;
        }
    }
    if(row < 0 || row >= 8) {
        printf("Invalid Coordinates, Try again\n");
        return 0;
    }
    if(column < 0 || column >= 8) {
        printf("Invalid Coordinates, Try again\n");
        return 0;
    }
    int y_dist = abs(player_location[1] - row);
    int x_dist = abs(player_location[0] - column);
    if( (x_dist + y_dist > 3) || (x_dist + y_dist == 3 && (x_dist == 0 || y_dist == 0)) ) {
        struct robot new_robot;
        new_robot.y = row;
        new_robot.x = column;
        new_robot.dead = 0;
        if(abs(player_location[1] - row) > 5 || abs(player_location[0] - column) > 5) {
            new_robot.displayable = 0;
        } else {
            new_robot.displayable = 1;
        }
        Robots[index] = new_robot;
        return 1;
    } else {
        printf("Invalid Coordinates, Try again\n");
        // printf("%d %d\n", row, column);
        // printf("%d %d\n", player_location[1], player_location[0]);
        //printf("%d")
        return 0;
    }
}

void checkCollisions() {
    if(total_robots <= 1) {
        return;
    }
    for(int i = 0; i < total_robots; i++) {
        struct robot current_robot = Robots[i];
        for(int j = i + 1; j < total_robots; j++) {
            struct robot other_robot = Robots[j];
            if(current_robot.x == other_robot.x && current_robot.y == other_robot.y && current_robot.dead == 0 && other_robot.dead == 0) {
                current_robot.dead = 1;
                other_robot.dead = 1;
                break;
            }
        }
    }
}

void moveRobots(char previous) {
    for(int i = 0; i < total_robots; i++) {
        int y_dist = player_location[0] - Robots[i].y;
        int x_dist = player_location[1] - Robots[i].x;
        int abs_y_dist = abs(player_location[0] - Robots[i].y);
        int abs_x_dist = abs(player_location[1] - Robots[i].x);
        if(abs_y_dist > abs_x_dist) {
            if(y_dist < 0) {
                int new_y = Robots[i].y - 1;
                Robots[i].y = new_y;
            } else {
                int new_y = Robots[i].y + 1;
                Robots[i].y = new_y;
            }
        } else if(abs_y_dist < abs_x_dist) {
            if(x_dist < 0) {
                int new_x = Robots[i].x - 1;
                Robots[i].x = new_x;

            } else {
                int new_x = Robots[i].x + 1;
                Robots[i].x = new_x;
            }
        } else {
            if(previous == 'V') {
                if(x_dist < 0) {
                    int new_x = Robots[i].x - 1;
                    Robots[i].x = new_x;
                } else {
                    int new_x = Robots[i].x + 1;
                    Robots[i].x = new_x;
                }
            } else {
                if(y_dist < 0) {
                    int new_y = Robots[i].y - 1;
                    Robots[i].y = new_y;
                } else {
                    int new_x = Robots[i].x + 1;
                    Robots[i].x = new_x;
                }
            }
        }
        
    }
}

int movePlayer(char direction[]) {
    while(1) {
        if(strstr(direction, "NT") != NULL) {
            if(player_location[0] == 0) {
                printf("Invalid\n");
            } else {
                player_location[0] -= 1;
                return 1;
            }
        } else if(strstr(direction, "ST") != NULL) {
            if(player_location[0] == 7) {
                printf("Invalid\n");
            } else {
                player_location[0] += 1;
                return 1;
            }
        } else if(strstr(direction, "ET") != NULL) {
            if(player_location[1] == 7) {
                printf("Invalid\n");
            } else {
                player_location[1] += 1;
                return 2;
            }
        } else if(strstr(direction, "WT") != NULL) {
            if(player_location[1] == 0) {
                printf("Invalid\n");
            } else {
                player_location[1] -= 1;
                return 2; 
            }
        } else {
            printf("Invalid\n");
            return 0;
        }
    }
}

void updateGrid() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            grid[i][j] = 0;
        }
    }

    for(int i = 0; i < total_robots; i++) {
        struct robot current_robot = Robots[i];
        if(current_robot.dead == 1) {
            grid[current_robot.y][current_robot.x] = 1;
        }
    }
    grid[escape[0]][escape[1]] = 2;

    for(int i = 0; i < total_robots; i++) {
        struct robot current_robot = Robots[i];
        if(current_robot.dead == 0) {
            grid[current_robot.y][current_robot.x] = 3;
        }
    }

    grid[player_location[0]][player_location[1]] = 4;
    return;
}

int checkLost() {
    for(int i = 0; i < total_robots; i++) {
        struct robot current_robot = Robots[i];
        if(current_robot.y == player_location[0] && current_robot.x == player_location[1]) {
            return 1;
        }
    }
    return 0;
}

int checkWon() {
    if(escape[0] == player_location[0] && escape[1] == player_location[1]) {
        return 1;
    }
    return 0;
}

void draw() {
    printf("\n");
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(grid[i][j] == 1) {
                printf("|D");
            } else if(grid[i][j] == 2) {
                printf("|E");
            } else if(grid[i][j] == 3) {
                printf("|R");
            } else if(grid[i][j] == 4) {
                printf("|H");
            } else {
                printf("| ");
            }
        }
        printf("%s\n", "|");
    }
    printf("\n");
    return;
}

void setup() {
    while(1) {
        char input[6];
        printf("Human starting point: ");
        fgets(input, 6, stdin);
        removeLine(input);
        int y_coord = input[0] - 48;
        int x_coord = input[2] - 48;
        if(setPlayer(y_coord, x_coord) == 1) {
            break;
        }
    }
    while(1) {
        char input[3];
        printf("%s", "Number of robots: ");
        fgets(input, 3, stdin);
        removeLine(input);
        if(strlen(input) != 1) {
            printf("Invalid number, Try again\n");
        } else {
            int amount = input[0] - 48;
            if(amount <= 0 || amount >= 8) {
                printf("Invalid number, Try again\n");
            } else {
                total_robots = amount;
                break;
            }
        }
    }

    int i = 1;
    int limit = total_robots + 1;
    while(i < limit) {
        char input[6];
        printf("%s %d%s", "Robot", i, ": ");
        fgets(input, 6, stdin);
        removeLine(input);
        // printf("%s\n", input);
        // printf("%d %d\n", player_location[1], player_location[0]);
        // printf("%d %d\n", escape[1], escape[0]);
        if(strlen(input) != 3) {
            printf("Invalid Coordinates, Try again\n");
            //printf("%s\n", input);
        } else {
            int y_coord = input[0] - 48;
            int x_coord = input[2] - 48;
            if(generateRobot(y_coord, x_coord, i - 1) == 1) {
                i++;
            }

        }
    }
    printf("\n");
    return;
}

int checkString(char line[]) {
    if(strstr(line, "NT") != NULL || strstr(line, "ST") != NULL || strstr(line, "ET") != NULL || strstr(line, "WT") != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char** argv) {
    if(argc <= 1) {
        printf("No seed provided\n");
    } else {
        int seed = atoi(argv[1]);
        setExit(seed);
        setup();
        while(1) {
            if(checkWon() == 1) {
                //printf("\n");
                printf("Well done! You survived, but it isn't over!\n");
                printf("\n");
                printf("\n");
                seed = atoi(argv[1]);
                setExit(seed);
                setup();
            } else if(checkLost() == 1) {
                printf("\n");
                printf("The robots got you! We are doomed!\n");
                printf("\n");
                break;
            } else {
                //printf("\n");
                updateGrid();
                char command[9];
                fgets(command, 9, stdin);
                removeLine(command);
                if(strstr(command, "move") != NULL) {
                    if(strlen(command) != 7 || checkString(command) != 1) {
                        printf("Invalid\n");
                    } else {
                        if(movePlayer(command) == 1) {
                            player_previous = 1;
                            moveRobots('V');
                            checkCollisions();
                            printf("\n");
                        } else {
                            player_previous = 2;
                            moveRobots('H');
                            checkCollisions();
                            printf("\n");
                        }
                    }
                } else if(strstr(command, "display") != NULL) {
                    if(strlen(command) != 7) {
                        printf("Invalid\n");
                    } else {
                        updateGrid();
                        draw();
                    }
                } else if(strstr(command, "exit") != NULL) {
                    if(strlen(command) != 4) {
                        printf("Invalid\n");
                    } else {
                        break;
                    }
                } else {
                    printf("Invalid\n");
                }
            }

        }
    }
}

//hi