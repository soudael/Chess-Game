// chess_game.c // version 0.1.0-alpha // debugging stage -- 12/15/24
#include <stdio.h>
#include <string.h>

/*PAWN MOVEMENT FUNCTION*/
int pawn_Move(char start_pos[3], char end_pos[3])
{
    if(end_pos[0] != start_pos[0]) return 0;
    if(end_pos[1] <= start_pos[1]) return 0;
    if(end_pos[1] > start_pos[1]+2) return 0;

    return 1;
}

/*PAWN CAPTURE FUNCTION*/
int pawn_Capture(char start_pos[3], char end_pos[3])
{
    if(end_pos[0] != start_pos[0]+1 && end_pos[0] != start_pos[0]-1) return 0;
    if(end_pos[1] != start_pos[1]+1) return 0;

    return 1;
}

main()
{
    char piece_name[4][8] = {{'r','n','b','q','k','b','n','r'},
                             {'p','p','p','p','p','p','p','p'},
                             {'P','P','P','P','P','P','P','P'},
                             {'R','N','B','Q','K','B','N','R'}};

    int square_status[8][8], board_layout[8][8], piece_type[8][8];
    char start_pos[3], end_pos[3], chessboard[8][8][3];
    int run_WhiteMove, run_BlackMove, run_WhiteCapture, run_BlackCapture;
    int i, j;

    /*
    piece_name: determines the name (identifier) of each piece in the game.
    board_layout: assigns the name (identifier) of each piece to its respective positions.
    square_status: assigns a value of 0 (empty) or 1 (occupied) to each square on the board.
    piece_type: assigns a constant value (-6 to 6) for each piece, depending on its type.
    start_pos & end_pos: variables for reading the move of each player.
    chessboard: contains all constant and specific coordinates of the board.
    run_ColorAction: variables for controlling the execution of specific functions.
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
        for(j=0;j<8;j++)
            if(square_status[i][j])
                printf(" %c", board_layout[i][j]);
            else
                printf(" %c", '.');
        printf("\n");
    }

    printf("\n Make your move:\n ");
    scanf("%2s>%2s", &start_pos, &end_pos);

    run_WhiteMove=0;
    run_BlackMove=0;
    run_WhiteCapture=0;
    run_BlackCapture=0;

    printf("\n start_pos: %s\n end_pos: %s\n\n", start_pos, end_pos);

    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            if(strcmp(start_pos, chessboard[i][j]) == 0){
                printf(" >> tile exists.\n\n");
                if(square_status[i][j] && piece_type[i][j]>0){
                    run_WhiteMove=1;
                    run_WhiteCapture=1;
                }else
                if(square_status[i][j] && piece_type[i][j]<0){
                    run_BlackMove=1;
                    run_BlackCapture=1;
                }else
                    printf(" >> tile without present pieces.\n\n");
            }else
                ;

    printf(" run_WhiteMove=%d\n", run_WhiteMove);
    printf(" run_BlackMove=%d\n", run_BlackMove);
    printf(" run_WhiteCapture=%d\n", run_WhiteCapture);
    printf(" run_BlackCapture=%d\n\n", run_BlackCapture);

    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            if(strcmp(end_pos, chessboard[i][j]) == 0)
                if(square_status[i][j] && run_WhiteCapture)
                    if(piece_type[i][j]<0)
                        run_WhiteMove=0;
                    else
                        run_WhiteCapture=0;
                else
                if(square_status[i][j] && run_BlackCapture)
                    if(piece_type[i][j]>0)
                        run_BlackMove=0;
                    else
                        run_BlackCapture=0;
                else
                if(!square_status[i][j] && run_WhiteMove)
                    run_WhiteCapture=0;
                else
                if(!square_status[i][j] && run_BlackMove)
                    run_BlackCapture=0;


    printf(" run_WhiteMove=%d\n", run_WhiteMove);
    printf(" run_BlackMove=%d\n", run_BlackMove);
    printf(" run_WhiteCapture=%d\n", run_WhiteCapture);
    printf(" run_BlackCapture=%d\n\n", run_BlackCapture);

    if(run_WhiteCapture)
        if(pawn_Capture(start_pos, end_pos))
            printf(" valid\n");
        else
            printf(" invalid\n");
    else
    if(run_BlackCapture)
        if(pawn_Capture(start_pos, end_pos))
            printf(" valid\n");
        else
            printf(" invalid\n");
    else
    if(run_WhiteMove)
        if(pawn_Move(start_pos, end_pos))
            printf(" valid\n");
        else
            printf(" invalid\n");
    else
    if(run_BlackMove)
        if(pawn_Move(start_pos, end_pos))
            printf(" valid\n");
        else
            printf(" invalid\n");
}