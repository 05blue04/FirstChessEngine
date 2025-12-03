#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to setup a clean board
Board* setup_empty_board() {
    Board *b = malloc(sizeof(Board));
    b->board = calloc(120, sizeof(int));  // 10x12 board
    b->turn = white;
    
    // Initialize all squares to EMPTY
    for(int i = 0; i < 120; i++) {
        b->board[i] = EMPTY;
    }
    
    return b;
}

// Helper to print test results
void test_move(Board *b, Square src, Square dst, int expected, const char *desc) {
    int result = is_legal_move(b, src, dst);
    printf("[%s] %s: %s\n", 
           result == expected ? "PASS" : "FAIL",
           desc,
           result == expected ? "✓" : "✗");
    
    if(result != expected) {
        printf("  Expected: %d, Got: %d\n", expected, result);
    }
}

void test_pawns() {
    printf("\n=== TESTING PAWNS ===\n");
    Board *b = setup_empty_board();
    
    // White pawn tests
    b->board[e2] = wPawn;
    b->turn = white;
    
    test_move(b, e2, e3, 1, "White pawn move forward 1");
    test_move(b, e2, e4, 1, "White pawn move forward 2 from start");
    test_move(b, e2, d3, 0, "White pawn can't capture empty diagonal");
    
    b->board[d3] = bPawn;
    test_move(b, e2, d3, 1, "White pawn capture diagonal left");
    
    b->board[f3] = bPawn;
    test_move(b, e2, f3, 1, "White pawn capture diagonal right");
    
    // Test blocking
    b->board[e3] = bPawn;
    test_move(b, e2, e3, 0, "White pawn blocked by piece");
    test_move(b, e2, e4, 0, "White pawn double move blocked");
    
    destroy_board(b);
    
    // Black pawn tests
    b = setup_empty_board();
    b->board[e7] = bPawn;
    b->turn = black;
    
    test_move(b, e7, e6, 1, "Black pawn move forward 1");
    test_move(b, e7, e5, 1, "Black pawn move forward 2 from start");
    
    b->board[d6] = wPawn;
    test_move(b, e7, d6, 1, "Black pawn capture diagonal");
    
    destroy_board(b);
}

void test_knights() {
    printf("\n=== TESTING KNIGHTS ===\n");
    Board *b = setup_empty_board();
    
    b->board[e4] = wKnight;
    b->turn = white;
    
    // All 8 possible knight moves
    test_move(b, e4, f6, 1, "Knight move: up 2, right 1");
    test_move(b, e4, g5, 1, "Knight move: up 1, right 2");
    test_move(b, e4, g3, 1, "Knight move: down 1, right 2");
    test_move(b, e4, f2, 1, "Knight move: down 2, right 1");
    test_move(b, e4, d2, 1, "Knight move: down 2, left 1");
    test_move(b, e4, c3, 1, "Knight move: down 1, left 2");
    test_move(b, e4, c5, 1, "Knight move: up 1, left 2");
    test_move(b, e4, d6, 1, "Knight move: up 2, left 1");
    
    // Invalid moves
    test_move(b, e4, e5, 0, "Knight can't move straight");
    test_move(b, e4, f5, 0, "Knight can't move diagonally");
    
    // Test capture
    b->board[f6] = bQueen;
    test_move(b, e4, f6, 1, "Knight captures enemy piece");
    
    b->board[f6] = wQueen;
    test_move(b, e4, f6, 0, "Knight can't capture own piece");
    
    destroy_board(b);
}

void test_bishops() {
    printf("\n=== TESTING BISHOPS ===\n");
    Board *b = setup_empty_board();
    
    b->board[d4] = wBishop;
    b->turn = white;
    
    // Valid diagonal moves
    test_move(b, d4, a7, 1, "Bishop diagonal up-left (long)");
    test_move(b, d4, h8, 1, "Bishop diagonal up-right (long)");
    test_move(b, d4, a1, 1, "Bishop diagonal down-left (long)");
    test_move(b, d4, g1, 1, "Bishop diagonal down-right (long)");
    test_move(b, d4, e5, 1, "Bishop diagonal up-right (short)");
    
    // Invalid moves
    test_move(b, d4, d8, 0, "Bishop can't move vertically");
    test_move(b, d4, h4, 0, "Bishop can't move horizontally");
    test_move(b, d4, e6, 0, "Bishop can't move non-diagonal");
    
    // Test blocking
    b->board[f6] = wPawn;
    test_move(b, d4, g7, 0, "Bishop blocked by own piece");
    test_move(b, d4, f6, 0, "Bishop can't capture own piece");
    
    b->board[f6] = bPawn;
    test_move(b, d4, f6, 1, "Bishop captures enemy piece");
    test_move(b, d4, g7, 0, "Bishop can't jump over enemy piece");
    
    destroy_board(b);
}

void test_rooks() {
    printf("\n=== TESTING ROOKS ===\n");
    Board *b = setup_empty_board();
    
    b->board[d4] = wRook;
    b->turn = white;
    
    // Valid moves
    test_move(b, d4, d8, 1, "Rook vertical up");
    test_move(b, d4, d1, 1, "Rook vertical down");
    test_move(b, d4, a4, 1, "Rook horizontal left");
    test_move(b, d4, h4, 1, "Rook horizontal right");
    
    // Invalid moves
    test_move(b, d4, f6, 0, "Rook can't move diagonally");
    test_move(b, d4, e6, 0, "Rook can't move non-straight");
    
    // Test blocking
    b->board[d6] = wPawn;
    test_move(b, d4, d7, 0, "Rook blocked by own piece");
    test_move(b, d4, d6, 0, "Rook can't capture own piece");
    
    b->board[d6] = bPawn;
    test_move(b, d4, d6, 1, "Rook captures enemy piece");
    test_move(b, d4, d7, 0, "Rook can't jump over enemy piece");
    
    // Horizontal blocking
    b->board[f4] = bQueen;
    test_move(b, d4, f4, 1, "Rook captures horizontally");
    test_move(b, d4, g4, 0, "Rook can't jump horizontally");
    
    destroy_board(b);
}

void test_queens() {
    printf("\n=== TESTING QUEENS ===\n");
    Board *b = setup_empty_board();
    
    b->board[d4] = wQueen;
    b->turn = white;
    
    // Diagonal moves (like bishop)
    test_move(b, d4, a7, 1, "Queen diagonal up-left");
    test_move(b, d4, h8, 1, "Queen diagonal up-right");
    test_move(b, d4, a1, 1, "Queen diagonal down-left");
    
    // Straight moves (like rook)
    test_move(b, d4, d8, 1, "Queen vertical up");
    test_move(b, d4, d1, 1, "Queen vertical down");
    test_move(b, d4, a4, 1, "Queen horizontal left");
    test_move(b, d4, h4, 1, "Queen horizontal right");
    
    // Invalid moves
    test_move(b, d4, e6, 0, "Queen can't move knight-style");
    
    // Test blocking diagonal
    b->board[f6] = bPawn;
    test_move(b, d4, f6, 1, "Queen captures diagonally");
    test_move(b, d4, g7, 0, "Queen can't jump diagonally");
    
    destroy_board(b);
}

void test_kings() {
    printf("\n=== TESTING KINGS ===\n");
    Board *b = setup_empty_board();
    
    b->board[e4] = wKing;
    b->turn = white;
    
    // All 8 directions (one square)
    test_move(b, e4, e5, 1, "King move up");
    test_move(b, e4, e3, 1, "King move down");
    test_move(b, e4, d4, 1, "King move left");
    test_move(b, e4, f4, 1, "King move right");
    test_move(b, e4, d5, 1, "King move diagonal up-left");
    test_move(b, e4, f5, 1, "King move diagonal up-right");
    test_move(b, e4, d3, 1, "King move diagonal down-left");
    test_move(b, e4, f3, 1, "King move diagonal down-right");
    
    // Invalid moves
    test_move(b, e4, e6, 0, "King can't move 2 squares");
    test_move(b, e4, g4, 0, "King can't move 2 squares horizontally");
    test_move(b, e4, g6, 0, "King can't move like knight");
    
    // Capture tests
    b->board[e5] = bQueen;
    test_move(b, e4, e5, 1, "King captures enemy piece");
    
    b->board[e5] = wQueen;
    test_move(b, e4, e5, 0, "King can't capture own piece");
    
    destroy_board(b);
}

void test_turn_order() {
    printf("\n=== TESTING TURN ORDER ===\n");
    Board *b = setup_empty_board();
    
    b->board[e2] = wPawn;
    b->board[e7] = bPawn;
    
    // White's turn
    b->turn = white;
    test_move(b, e2, e3, 1, "White moves on white's turn");
    test_move(b, e7, e6, 0, "Black can't move on white's turn");
    
    // Black's turn
    b->turn = black;
    test_move(b, e7, e6, 1, "Black moves on black's turn");
    test_move(b, e2, e3, 0, "White can't move on black's turn");
    
    destroy_board(b);
}

void test_edge_cases() {
    printf("\n=== TESTING EDGE CASES ===\n");
    Board *b = setup_empty_board();
    
    // Test corner squares
    b->board[a1] = wRook;
    b->turn = white;
    test_move(b, a1, a8, 1, "Rook on corner moves vertically");
    test_move(b, a1, h1, 1, "Rook on corner moves horizontally");
    
    // Test invalid squares
    test_move(b, 0, e4, 0, "Invalid source square");
    test_move(b, e4, 0, 0, "Invalid destination square");
    test_move(b, e4, 99, 0, "Out of bounds destination");
    
    destroy_board(b);
}

void test_movement(){

    printf("Starting Chess Move Validation Tests\n");
    printf("=====================================\n");
    
    test_pawns();
    test_knights();
    test_bishops();
    test_rooks();
    test_queens();
    test_kings();
    test_turn_order();
    test_edge_cases();
    
    printf("\n=====================================\n");
    printf("Tests Complete!\n");
}