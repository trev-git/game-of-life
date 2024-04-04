/**
 * Conway's Game of Life written in C
 *
 * Copyright (c) 2024 trev-git
 * This program is published under the MIT license.
 * Refer to the LICENSE file for more information.
 */

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
# include <Windows.h>
#else
# include <unistd.h>
#endif

#include "life.h"

int main()
{
    termsize ws;
    get_terminal_size(&ws);

    char **game_of_life;
    alloc(&game_of_life, ws.rows-1, ws.cols);
    fill_random(game_of_life, ws.rows-1, ws.cols);
    int generation = 1;
    while (generation <= 5)
    {
        #ifdef _WIN32 
           system("cls");
        #else
           system("clear");
        #endif

        print_arr(game_of_life, ws.rows-1, ws.cols);
        update(game_of_life, ws.rows-1, ws.cols);
        printf("Generation: %d\n", generation);
        generation++;
        #ifdef _WIN32
        Sleep(1000);
        #else
        usleep(1000000);
        #endif
    }

    free_arr(game_of_life, ws.rows-1);
    return 0;
}
