/**
 * Copyright (c) 2024 trev-git
 * This program is published under the MIT license.
 * Refer to the LICENSE file for more information.
 */

#ifndef LIFE_H
#define LIFE_H

typedef struct {
    int rows;
    int cols;
} termsize;

void get_terminal_size(termsize *ws);
void fill_random(char **arr, int rows, int cols);
void print_arr(char **arr, int rows, int cols);
void update(char **arr, int rows, int cols);
int count_neighbours(char **arr, int rows, int cols, int row, int col);
void alloc(char ***arr, int rows, int cols);
void free_arr(char **arr, int rows);

#endif // LIFE_H
