#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include "math.h"

/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum {
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

bool has_won(board_t board, player_t player)
{
    int row_win = 0;
    for (int i = 0; i < 4; i++)
    {
        int row_win1 = 1;
        for (int j = 0; j < 4; j++)
        {

            if (board[i][j] != player)
            {
                row_win1 = 0;
                break;
            }
        }
        if (row_win1)
        {
            return true;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        int row_win2 = 1;
        for (int j = 1; j < 5; j++)
        {

            if (board[i][j] != player)
            {
                row_win2 = 0;
            }
        }
        if (row_win2)
        {
            return true;
        }
    }

    for (int j = 0; j < 5; j++)
    {
        int col_win = 1;
        for (int i = 0; i < 4; i++)
        {
            if (board[i][j] != player)
            {
                col_win = 0;
                break;
            }
        }
        if (col_win)
            return true;
    }

    int d1_win = 1;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][i] != player)
        {
            d1_win = 0;
            break;
        }
    }
    if (d1_win)
        return true;

    int d2_win = 1;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][i+1] != player)
        {
            d2_win = 0;
            break;
        }
    }
    if (d2_win)
        return true;

    int d3_win = 1;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][4 - i] != player)
        {
            d3_win = 0;
            break;
        }
    }
    if (d3_win)
        return true;

    int d4_win = 1;
    for (int i = 0; i < 4; i++)
    {
        if (board[i][3 - i] != player)
        {
            d4_win = 0;
            break;
        }
    }
    if (d4_win)
        return true;

    return false;
}

bool is_full(board_t board)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            if (board[i][j] == EMPTY)
                return false;
    return true;
}

typedef struct {
    int col;
    int score;
} move_t;

player_t opposite_player(player_t player)
{
    if (player == RED)
    {
        return BLUE;
    }
    else if (player == BLUE)
    {
        return RED;
    }
    else
    {
        assert(0);
    }
}

move_t best_moves[33554432];

void init_game(board_t board)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            board[i][j] = EMPTY;

    int j = 0;
    while (j < 33554432)
    {
        move_t m = {-2, -1};
        best_moves[j] = m;
        j++;
    }
}

move_t best_move(board_t board, player_t player)
{
    int fi = 0, si = 0;
    for (int i = 0; i < 5; i++)
    {
        int f = 0, bm = 0;
        for (int j = 3; j >= 0; j--)
        {
            if (board[j][i] != EMPTY)
            {
                if (!f)
                {
                    if (board[j][i] == player)
                        fi += (1 << i);
                    f = (int)board[j][i];
                }
                if (f == board[j][i])
                    bm = (bm << 1) + 1;
                else
                    bm <<= 1;
            }
        }
        si += bm * (1 << (4 * i));
    }
    si += fi * (1 << 20);

    if (best_moves[si].col != -2)
    {
        return best_moves[si];
    }

    move_t m, bm = {-1, -21}, draw = {-1, 0}, won = {-1, 21}, lost = {-1, -21}, mm;

    if (has_won(board, player))
    {
        best_moves[si] = won;
        return won;
    }

    if (has_won(board, opposite_player(player)))
    {
        best_moves[si] = lost;
        return lost;
    }

    if (is_full(board))
    {
        best_moves[si] = draw;
        return draw;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (board[j][i] == EMPTY)
            {
                board[j][i] = player;
                m = best_move(board, opposite_player(player));
                board[j][i] = EMPTY;
                mm.col = i;

                if (m.score > 0)
                    mm.score = -m.score + 1;
                else if (m.score < 0)
                    mm.score = -m.score - 1;
                else
                    mm.score = 0;

                if (mm.score > bm.score)
                    bm = mm;
            }
        }
    }
    best_moves[si] = bm;
    return bm;
}

void make_move(board_t board, move_t move, player_t player)
{
    for (int i = 3; i >= 0; i--)
    {
        if (board[i][move.col] == EMPTY)
        {
            board[i][move.col] = player;
            return;
        }
    }
}

void print_board(board_t board)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            switch (board[i][j])
            {
            case RED:
                printf("R ");
                break;
            case BLUE:
                printf("B ");
                break;
            case EMPTY:
                printf("- ");
                break;
            default:
                assert(0);
            }
        }
        printf("\n");
    }
}

int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    char c;
    printf("Enter your color (R/B): ");
    scanf(" %c", &c);
    board_t board;
    player_t comp, user, curr = RED;
    init_game(board);
    if (c == 'R')
    {
        comp = BLUE;
        user = RED;
    }
    else if (c == 'B')
    {
        comp = RED;
        user = BLUE;
    }
    else
    {
        assert(0);
    }
    while (!is_full(board) && !has_won(board, user) && !has_won(board, comp))
    {
        if (curr == comp)
        {
            move_t computerMove = best_move(board, comp); // Get the computer's move
            make_move(board, computerMove, comp);
            printf("Computer's move: %d\n", computerMove.col); // Print the computer's move
        }
        else
        {
            print_board(board);
            int choice;
            printf("Enter your move: ");
            scanf("%d", &choice);

            move_t m = {choice, 0};
            make_move(board, m, user);
        }
        if (has_won(board, user))
        {
            print_board(board);
            printf("\nYou Won!\n\n");
        }
        else if (has_won(board, comp))
        {
            print_board(board);
            printf("\nYou Lost.\n\n");
        }
        else if (is_full(board))
        {
            print_board(board);
            printf("\nIt's a Draw.\n\n");
        }
        curr = opposite_player(curr);
    }
    return 0;
}