#ifndef MOVE_H
#define MOVE_H

#include "board.h"

//function that checks if move from src to dst is valid on the chess board
int is_legal_move(Board *b, Square src, Square dst);

void make_move(Board *b, Square src, Square dst);

void test_movement();

#endif