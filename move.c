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

    if(src == dst){
        fprintf(stderr, "cant move piece to same square\n");
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
    if(b->turn == white && p > wKing){
        fprintf(stderr,"moving out of order whites turn\n");
        return 0;
    }

    if(b->turn ==  black && p <= wKing){
        fprintf(stderr,"moving out of order blacks turn\n");
        return 0;
    }

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
            check == -21 || check == -19 || check == -12 || check == -8){
                return 1;
        }

        break;            
    }

    case wKing:
    case bKing: {
        printf("check\n");
        int diff = dst - src;

        if (diff == 1  || diff == -1  ||  // horizontal
            diff == 10 || diff == -10 ||  // vertical
            diff == 11 || diff == -11 ||  // diagonal
            diff == 9  || diff == -9) {   // diag 
            return 1;
        }

        break;
    }

    case wBishop:
    case bBishop:{
        check = dst - src;
        int dir = 0;

        // determining diagonal direction
        if(check % 11 == 0){
            if(check > 0 ){
                dir = 11;
            }else{
                dir = -11;
            }
        } else if (check % 9 == 0){
            if( check > 0 ){
                dir = 9;
            }else{
                dir = -9;
            }
        } else{
            return 0;
        }

        //traverse the path of the diagonal to ensure nothing is blocking the move
        int square = src + dir; 
        while(square != (int)dst){
            if(b->board[square] != EMPTY){ //check if path is occupied
                return 0;
            }
            square += dir;
        }

        return 1;

    }

    case wRook:
    case bRook:{
        check = dst - src;
        int dir = 0;

        if(check % 10  == 0){
            if(check > 0){
                dir = 10;
            }else{
                dir = -10;
            }
        } else if(src / 10 == dst / 10){
            if(check > 0 ){
                dir = 1;
            } else{
                dir = -1;
            }
        } else{
            return 0;
        }

        //traverse path of rook to ensure no pieces are blocking its path
        int square = src + dir;
        while(square != (int)dst){
            if (b->board[square] != EMPTY){
                return 0;
            }
            square += dir;
        }

        return 1;
    }

    case wQueen:
    case bQueen:{
        check = dst - src;
        int dir = 0;

        //lowk light just a combo of rook + bishop moves
        if(check % 10  == 0){
            if(check > 0){
                dir = 10;
            }else{
                dir = -10;
            }
        } else if(src / 10 == dst / 10){
            if(check > 0 ){
                dir = 1;
            } else{
                dir = -1;
            }
        } else if(check % 11 == 0){
            if(check > 0 ){
                dir = 11;
            }else{
                dir = -11;
            }
        } else if (check % 9 == 0){
            if( check > 0 ){
                dir = 9;
            }else{
                dir = -9;
            }
        } else{
            return 0;
        }

        // traverse the path
        int square = src + dir;
        while(square != (int)dst){
            if(b->board[square] != EMPTY){
                return 0;
            }
            square += dir;
        }

        return 1;
    }
        
    default:
        break;
    }

    return 0;

}

void make_move(Board *b, Square src, Square dst){
    if(!is_legal_move(b,src,dst)){
        fprintf(stderr,"move is illegal \n");
        return;
    }

   Piece p = b->board[src];
   b->board[src] = EMPTY; 
   b->board[dst] = p;

   b->turn ^= 1;
}