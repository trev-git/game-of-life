/**
 * Copyright (c) 2024 trev-git
 * This program is published under the MIT license.
 * Refer to the LICENSE file for more information.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
# include <Windows.h>
#else
# include <sys/ioctl.h>
#endif

#include "life.h"

void get_terminal_size(termsize *ws)
{
    #ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);
    if(ret)
    {
        printf("Console Buffer Width: %d\n", csbi.dwSize.X);
        printf("Console Buffer Height: %d\n", csbi.dwSize.Y);
    }
    ws->rows = csbi.dwSize.Y;
    ws->cols = csbi.dwSize.X;
    #else
    struct winsize size;
    ioctl(1, TIOCGWINSZ, &size);
    ws->rows = size.ws_row;
    ws->cols = size.ws_col;
    #endif
}

void fill_random(char **arr, int rows, int cols)
{
    const char *cells = " #";

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = cells[rand() % 2];
        }
    }
}

void print_arr(char **arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

void update(char **arr, int rows, int cols)
{
    char **old_gen;
    alloc(&old_gen, rows, cols);
    for (int i = 0; i < rows; i++)
        memcpy(old_gen[i], arr[i], sizeof(char) * cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (old_gen[i][j] == '#' && (count_neighbours(old_gen, rows, cols, i, j) == 2 ||
                                        count_neighbours(old_gen, rows, cols, i, j) == 3))
                continue;
            if (old_gen[i][j] == '#' && (count_neighbours(old_gen, rows, cols, i, j) < 2 ||
                                        count_neighbours(old_gen, rows, cols, i, j) > 3))
                arr[i][j] = ' ';
            if (old_gen[i][j] == ' ' && (count_neighbours(old_gen, rows, cols, i, j) == 3))
                arr[i][j] = '#';
        }
    }

    free_arr(old_gen, rows);
}

int count_neighbours(char **arr, int rows, int cols, int row, int col)
{
    int count = 0;

    if (row > 0 && arr[row-1][col] == '#')
        count++;

    if (col < cols - 1 && arr[row][col+1] == '#')
        count++;

    if (row < rows - 1 && arr[row+1][col] == '#')
        count++;

    if (col > 0 && arr[row][col-1] == '#')
        count++;

    if (row > 0 && col > 0 && arr[row-1][col-1] == '#')
        count++;

    if (row > 0 && col < cols - 1 && arr[row-1][col+1] == '#')
        count++;

    if (row < rows - 1 && col > 0 && arr[row+1][col-1] == '#')
        count++;

    if (row < rows - 1 && col < cols - 1 && arr[row+1][col+1] == '#')
        count++;

    return count;
}

void alloc(char ***arr, int rows, int cols)
{
    *arr = malloc(sizeof(char *) * rows);
    for (int i = 0; i < rows; i++)
        (*arr)[i] = malloc(sizeof(char) * cols);
}

void free_arr(char **arr, int rows)
{
    for (int i = 0; i < rows; i++)
        free(arr[i]);
    free(arr);
}
