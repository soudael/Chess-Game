// chess_game.c // version 0.5.0-alpha // --debugging
#include <stdio.h>
#include <string.h>

/*PAWN MOVEMENT FUNCTION*/
int pawn_Move(char start_pos[3], char end_pos[3], int square_status[8][8], int color)
{
    int column = start_pos[0] - 'a';
    int start_row = 8 - (start_pos[1] - '0');
    int end_row = 8 - (end_pos[1] - '0');

    if(color){
        if(start_pos[1] == '2'){
            if (end_pos[0]==start_pos[0] && end_pos[1]>start_pos[1] && end_pos[1]<start_pos[1]+3){
                for(int i = end_row; i < start_row; i++)
                    if(square_status[i][column] == 1) return 0;
                return 1;
            }
        }else{
            if (end_pos[0]==start_pos[0] && end_pos[1] == start_pos[1]+1)
                return 1;
        }
    }else{
        if(start_pos[1] == '7'){
            if (end_pos[0]==start_pos[0] && end_pos[1]<start_pos[1] && end_pos[1]>start_pos[1]-3){
                for(int i = end_row; i > start_row; i--)
                    if(square_status[i][column] == 1) return 0;
                return 1;
            }
        }else{
            if (end_pos[0]==start_pos[0] && end_pos[1] == start_pos[1]-1)
                return 1;
        }
    }
    return 0;
}

/*PAWN CAPTURE FUNCTION*/
int pawn_Capture(char start_pos[3], char end_pos[3], int color)
{
    if (color){
        if((end_pos[0]==start_pos[0]+1 || end_pos[0]==start_pos[0]-1) && end_pos[1]==start_pos[1]+1)
            return 1;
    }else{
        if((end_pos[0]==start_pos[0]+1 || end_pos[0]==start_pos[0]-1) && end_pos[1]==start_pos[1]-1)
            return 1;
    }
    return 0;
}

int main()
{
    char piece_name[4][8] = {{'r','n','b','q','k','b','n','r'},
                             {'p','p','p','p','p','p','p','p'},
                             {'P','P','P','P','P','P','P','P'},
                             {'R','N','B','Q','K','B','N','R'}};

    int square_status[8][8], board_layout[8][8], piece_type[8][8];
    char start_pos[3], end_pos[3], chessboard[8][8][3], square_color[8][8];
    int run_WhiteMove, run_BlackMove, run_WhiteCapture, run_BlackCapture;
    int color= -1, selected_piece, update_board=0;
    int i, j, start_i, start_j, end_i, end_j;
    int round_count= 0, round=1;

    /*
    Along the code, positive(true) values means white pieces
    and negative(false) values means black pieces.

    piece_name: determines the name (identifier) of each piece in the game.
    board_layout: assigns the name (identifier) of each piece to its respective positions.
    square_status: assigns a value of 0 (empty) or 1 (occupied) to each square on the board.
    piece_type: assigns a constant value (-6 to 6) for each piece, depending on its type.
    start_pos & end_pos: variables for reading the move of each player.
    chessboard: contains all constant and specific coordinates of the board.
    run_ColorAction: variables for controlling the execution of specific functions.
    color: decides between running white or black functions.
    selected_piece: assign the type of the piece being moved.
    square_colors: black and white board square colors.
    update_board: update the board layout after a move according to the player's move.
    */

    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            if(i<2)
                switch(piece_name[i][j])
                {
                case 'r': piece_type[i][j]= -1; break;
                case 'n': piece_type[i][j]= -2; break;
                case 'b': piece_type[i][j]= -3; break;
                case 'q': piece_type[i][j]= -4; break;
                case 'k': piece_type[i][j]= -5; break;
                case 'p': piece_type[i][j]= -6; break;
                }
            else
            if(i>5)
                switch(piece_name[i-4][j])
                {
                case 'R': piece_type[i][j]= 1; break;
                case 'N': piece_type[i][j]= 2; break;
                case 'B': piece_type[i][j]= 3; break;
                case 'Q': piece_type[i][j]= 4; break;
                case 'K': piece_type[i][j]= 5; break;
                case 'P': piece_type[i][j]= 6; break;
                }
            else
                piece_type[i][j]= 0;

    printf("\n");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(i<2){
                square_status[i][j]=1;
                board_layout[i][j]=piece_name[i][j];
            }else
                if(i>5){
                    square_status[i][j]=1;
                    board_layout[i][j]=piece_name[i-4][j];
                }else{
                    square_status[i][j]=0;
                    board_layout[i][j]='\0';
                }
            printf(" %d", square_status[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            chessboard[i][j][0]='a'+j;
            chessboard[i][j][1]='8'-i;
            chessboard[i][j][2]='\0';
            printf(" %s", chessboard[i][j]);

            if((i+1)%2==0)
                if((j+1)%2==0)
                    square_color[i][j]= '\xDB';
                else
                    square_color[i][j]= ' ';
            else
                if((j+1)%2==0)
                    square_color[i][j]= ' ';
                else
                    square_color[i][j]= '\xDB';
        }
        printf("\n");
    }

    printf("\n");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++)
            if(i<2)
                printf(" %d", piece_type[i][j]);
            else
                printf("  %d", piece_type[i][j]);
        printf("\n");
    }

    printf("\n");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            printf("%c%c%c", square_color[i][j], square_color[i][j], square_color[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("  \xC9");
    for(i=0; i<8; i++) printf("\xCD\xCD\xCD");
    printf("\xCD\xCD\xBB\n");

    for(i=0;i<8;i++){
        printf("%d \xBA ", 8-i);
        for(j=0;j<8;j++){
            if(square_status[i][j])
                printf(" %c ", board_layout[i][j]);
            else
                printf("%c%c%c", square_color[i][j], square_color[i][j], square_color[i][j]);
        }
        printf(" \xBA");
        printf("\n");
    }
    printf("  \xC8");
    for(i=0; i<8; i++) printf("\xCD\xCD\xCD");
    printf("\xCD\xCD\xBC\n");
    printf("    ");
    for(i=0; i<8; i++) printf(" %c ", 'a'+i);

    while(1){

    printf("\n\n");
    for(i=0;i<11;i++) printf(" ");
    printf(":Round = %d\n", round);
    for(i=0;i<11;i++) printf(" ");
    if(round%2==0)
        printf(":PRETAS\n");
    else
        printf(":BRANCAS\n");

    printf("\n Make your move:\n ");
    scanf("%2s>%2s", start_pos, end_pos);

    run_WhiteMove=0;
    run_BlackMove=0;
    run_WhiteCapture=0;
    run_BlackCapture=0;

    printf("\n start_pos: %s\n end_pos: %s\n\n", start_pos, end_pos);

    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            if(strcmp(start_pos, chessboard[i][j]) == 0){
                start_i=i;
                start_j=j;
                printf(" >> start tile exists.\n\n");
                if(square_status[i][j]){
                    if (piece_type[i][j]>0){
                        color=1;
                        selected_piece=piece_type[i][j];
                    }else
                    if (piece_type[i][j]<0){
                        color=0;
                        selected_piece=piece_type[i][j];
                    }
                }else
                    printf(" >> tile without present pieces.\n\n");
            }

    printf(" run_WhiteMove=%d\n", run_WhiteMove);
    printf(" run_BlackMove=%d\n", run_BlackMove);
    printf(" run_WhiteCapture=%d\n", run_WhiteCapture);
    printf(" run_BlackCapture=%d\n", run_BlackCapture);

    printf("\n selected piece: %d\n", selected_piece);
    printf("\n color: %d\n\n", color);

    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            if(strcmp(end_pos, chessboard[i][j]) == 0){
                end_i=i;
                end_j=j;
                printf(" >> end tile exists.\n\n");
                if(color==1){
                    if(piece_type[i][j]<=0){
                        if(square_status[i][j])
                            run_WhiteCapture=1;
                        else
                            run_WhiteMove=1;
                    }
                }else
                if(color==0){
                    if(piece_type[i][j]>=0){
                        if(square_status[i][j])
                            run_BlackCapture=1;
                        else
                            run_BlackMove=1;
                    }
                }
            }

    printf(" run_WhiteMove=%d\n", run_WhiteMove);
    printf(" run_BlackMove=%d\n", run_BlackMove);
    printf(" run_WhiteCapture=%d\n", run_WhiteCapture);
    printf(" run_BlackCapture=%d\n\n", run_BlackCapture);

    switch(selected_piece)
    {
        case  1: // White Rook --------------------------------------------------------------------
            break;
        case -1: // Black Rook --------------------------------------------------------------------
            ;
            break;
        case  2: // White Knight ------------------------------------------------------------------
            break;
        case -2: // Black Knight ------------------------------------------------------------------
            ;
            break;
        case  3: // White Bishop ------------------------------------------------------------------
            break;
        case -3: // Black Bishop ------------------------------------------------------------------
            ;
            break;
        case  4: // White Queen -------------------------------------------------------------------
            break;
        case -4: // Black Queen -------------------------------------------------------------------
            ;
            break;
        case  5: // White King --------------------------------------------------------------------
            break;
        case -5: // Black King --------------------------------------------------------------------
            ;
            break;
        case  6: // White Pawn --------------------------------------------------------------------
            if(run_WhiteMove){
                if(pawn_Move(start_pos, end_pos, square_status, color)){
                    printf(" --valid movement\n");
                    update_board=1;
                }else{
                    printf(" --invalid movement\n");
                    update_board=0;
                }
            }else
            if(run_WhiteCapture){
                if(pawn_Capture(start_pos, end_pos, color)){
                    printf(" --valid movement\n");
                    update_board=1;
                }else{
                    printf(" --invalid movement\n");
                    update_board=0;
                }
            }
            break;

        case -6: // Black Pawn --------------------------------------------------------------------
            if(run_BlackMove){
                if(pawn_Move(start_pos, end_pos, square_status, color)){
                    printf(" --valid movement\n");
                    update_board=1;
                }else{
                    printf(" --invalid movement\n");
                    update_board=0;
                }
            }else
            if(run_BlackCapture){
                if(pawn_Capture(start_pos, end_pos, color)){
                    printf(" --valid movement\n");
                    update_board=1;
                }else{
                    printf(" --invalid movement\n");
                    update_board=0;
                }
            }
            break;

        default:
            ;
    }

    if(update_board){
        if(round%2==0){
            if(selected_piece>0){
                update_board=0;
            }
        }else
            if(selected_piece<0){
                update_board=0;
            }
    }

    if(update_board){
        square_status[start_i][start_j]= 0;
        printf("\nsquare_status[start_i][start_j]: %d\n", square_status[start_i][start_j]);
        square_status[end_i][end_j]= 1;
        printf("square_status[end_i][end_j]: %d\n", square_status[end_i][end_j]);
        piece_type[end_i][end_j] = piece_type[start_i][start_j];
        printf("piece_type[end_i][end_j]: %d\n", piece_type[end_i][end_j]);
        piece_type[start_i][start_j]= 0;
        printf("piece_type[start_i][start_j]: %d\n", piece_type[start_i][start_j]);
        board_layout[end_i][end_j] = board_layout[start_i][start_j];
        printf("board_layout[end_i][end_j]: %c\n", board_layout[end_i][end_j]);
        board_layout[start_i][start_j]= '\0';
        printf("board_layout[start_i][start_j]: %c\n\n", board_layout[start_i][start_j]);
        printf("Start color: %c\n", square_color[start_i][start_j]);
        printf("End color: %c\n", square_color[end_i][end_j]);
    }

    printf("\n");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            printf(" %d", square_status[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if(piece_type[i][j]>=0)
                printf("  %d", piece_type[i][j]);
            else
                printf(" %d", piece_type[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("  \xC9");
    for(i=0; i<8; i++) printf("\xCD\xCD\xCD");
    printf("\xCD\xCD\xBB\n");

    for(i=0;i<8;i++){
        printf("%d \xBA ", 8-i);
        for(j=0;j<8;j++){
            if(square_status[i][j])
                printf(" %c ", board_layout[i][j]);
            else
                printf("%c%c%c", square_color[i][j], square_color[i][j], square_color[i][j]);
        }
        printf(" \xBA");
        printf("\n");
    }
    printf("  \xC8");
    for(i=0; i<8; i++) printf("\xCD\xCD\xCD");
    printf("\xCD\xCD\xBC\n");
    printf("    ");
    for(i=0; i<8; i++) printf(" %c ", 'a'+i);

    if(update_board) round++;
    round_count++;
    update_board=0;
    }
    printf("\n");
    return 0;
}