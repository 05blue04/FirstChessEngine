#include "move.h"


static int is_square_valid(Square sq){
    if(sq < 21)
        return 0;
    
    if(sq > 98)
        return 0;

    if((sq % 10 < 1) || (sq % 10 > 8))
        return 0;

    return 1;
}


void debug_is_legal_move(Board *b, Square src, Square dst){
    fprintf(stderr,"Checking to see if move %d to %d is valid\n",src,dst);
    is_legal_move(b,src,dst);
}

int is_legal_move(Board *b, Square src, Square dst){
    
    if (b == NULL){
        fprintf(stderr, "is_legal_move: board must be initialized\n");
        return 0;
    }

    if (!is_square_valid(src)){

        fprintf(stderr, "square %d is an invalid square\n",src);
        return 0;
    }

    if (!is_square_valid(dst)){
        fprintf(stderr, "square %d is an invalid square\n",dst);
        return 0;
    }

    Piece p = b->board[src];
    Piece dst_p = b->board[dst];

    //check if a piece exists
    if(p == EMPTY){
        fprintf(stderr,"piece at src:%d is empty\n",src);
        return 0;
    }

    //ensure turn order 
    if(b->turn == white && p > wKing)
        return 0;

    if(b->turn ==  black && p <= wKing)
        return 0;

    //check if capturing not capturing own piece
    if (dst_p != EMPTY){
        if(b->turn == white && (dst_p <= wKing)){
            return 0;
        }else if(b->turn == black && (dst_p > wKing)){
            return 0;
        }
    }


    //case analysis
    int check = 0;
    printf("evaluating piece %d\n",p);
    switch (p)
    {
    case wPawn:
        check = src - dst;
        
        if(check == 10){ // move straight up
            return (dst_p == EMPTY);
        }

        if(check == 9 || check == 11){ // capture diagonaly 
            return (dst_p != EMPTY);
        }

        if(check == 20 && (src >= 81 && src <= 88)){ //move up 2 ONLY on starting move
            return (dst_p == EMPTY && b->board[src - 10] == EMPTY);
        }

        break;
    
    case bPawn:
        check = dst - src;
        
        if(check == 10){ // move straight down
            return (dst_p == EMPTY);
        }

        if(check == 9 || check == 11){ // capture diagonaly
            return (dst_p != EMPTY);
        }

        if(check == 20 && (src >= 31 && src <= 38)){ //move up 2 ONLY on starting move
            return (dst_p == EMPTY && b->board[src + 10] == EMPTY);
        }
        break;

    case wKnight:
    case bKnight:{
        check = dst - src;

        if(check == 21 || check == 19 || check == 12 || check == 8 ||
            check == -21 || check == -19 || check == -12 || check == 8){
                return 1;
        }

        break;            
    }

    case wKing:
    case bKing: {
        int diff = dst - src;

        if (diff == 1  || diff == -1  ||  // horizontal
            diff == 10 || diff == -10 ||  // vertical
            diff == 11 || diff == -11 ||  // diagonal
            diff == 9  || diff == -9) {   // diag 
            return 1;
        }

        break;
    }
        
    default:
        break;
    }

    return 0;

}