#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "move.h"

void print_usage(const char *program_name) {
    printf("Usage: %s [OPTIONS]\n", program_name);
    printf("Options:\n");
    printf("  (no args)         Start new game with default position\n");
    printf("  --fen <string>    Load position from FEN string\n");
    printf("  --help            Show this help message\n");
}

int main(int argc, char **argv){

    Board *b = NULL;

    if(argc == 1) {
        // No arguments - default board
        b = create_board_default();
        if(b == NULL)
            return EXIT_FAILURE;
        print_board(b);
        make_move(b,e2,e4);
        make_move(b,e7,e5);
        make_move(b,f1,a6);
        make_move(b,c1,e3);

        print_board(b);
        destroy_board(b);
    }
    else if(argc == 2 && strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    }
    else if(argc == 3 && strcmp(argv[1], "--fen") == 0) {
        // Load from FEN have to implement type shit
        if(b == NULL) {
            fprintf(stderr, "Error: Invalid FEN string\n");
            return EXIT_FAILURE;
        }
    }
    else {
        fprintf(stderr, "Error: Invalid arguments\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    
    if(b == NULL) {
        fprintf(stderr, "Error: Failed to create board\n");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}