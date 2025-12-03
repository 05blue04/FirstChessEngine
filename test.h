#ifndef TEST_H
#define TEST_H

#include "board.h"
#include "move.h"

#include <stdio.h>
#include <stdlib.h>

// Test suite functions
void test_pawns(void);
void test_knights(void);
void test_bishops(void);
void test_rooks(void);
void test_queens(void);
void test_kings(void);
void test_turn_order(void);
void test_edge_cases(void);

// Helper functions
Board* setup_empty_board(void);
void test_move(Board *b, Square src, Square dst, int expected, const char *desc);


#endif