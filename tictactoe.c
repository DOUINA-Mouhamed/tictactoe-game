/*
//  PERSONAL PROJECT
//  tictactoe.c
//  PROJECT DESCRIPTION :
//  Un jeu "tictactoe" codé en C, en anglais.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3]; //Array 2D
const char PLAYER = 'X'; //Le joueur joue le X
const char COMPUTER = 'O'; //L'ordinateur joue le O

void reset_board();
void print_board();
int check_free_spaces();
void player_move();
void computer_move();
char check_winner();
void print_winner(char);

int main()
{
    char winner = ' '; //Si il n'y a rien, c'est qu'il n'y a pas de gagnant.
    
    reset_board();
    while (winner == ' ' && check_free_spaces() != 0) { 
        print_board();

        player_move();
        winner = check_winner();
        if (winner != ' ' || check_free_spaces() == 0) {
            break;
        }
        computer_move();
        winner = check_winner();
        if (winner != ' ' || check_free_spaces() == 0) {
            break;
        }
    }
    print_board();
    print_winner(winner);
    return 0;
}

void reset_board()
{
    int i;
    int j;

    for(i = 0; i < 3; i++) { //Outter loop pour les lignes
        for (j = 0; j < 3; j++) { //Inner loop pour les colonnes
            board[i][j] = ' '; //Reset toutes les cases par un espace
        }
    }
}

void print_board()
{
    printf("\nTICTACTOE BY DOUINA MOUHAMED @epitech\n\n");
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]); //Première ligne du tableau
    printf("\n---|---|---\n"); //Délimitation
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n\n");
}

int check_free_spaces()
{
    int free_spaces = 9; //Le nombre de cases disponible au début d'une partie
    int i;
    int j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                free_spaces--;
            }
        }
    }
    return free_spaces; //Si on "return 0;" la partie sera terminé.
}

void player_move()
{
    int x; //Pour demander au joueur la ligne
    int y; //et la colonne dans laquelle il veut placer 'X'.

    do {
        printf("Enter row (from 1 to 3): ");
        scanf("%d", &x); //Le soucis c'est qu'en C, on commence par 0 pour la première case. Pour que l'utilisateur ne soit pas confu, on commence par 1.
        x--; //Donc, pour une valeur de int x de 1 à 3, int x prend -1. Si l'utilisateur tape 1, ça sera donc 0.
        printf("Enter column (from 1 to 3): ");
        scanf("%d", &y);
        y--; //Même processus pour les colonnes.
        if (board[x][y] != ' ') {
            printf("Invalid choice.\n");
        } else {
            board[x][y] = PLAYER; //On rappelle que la constante char PLAYER est égale à X. Donc si l'utilisateur défini avec succès un espace vide, un X y sera marqué.
            break;
        }
    } while (board[x][y] != ' '); //Tant que le joueur n'a pas rentré une place valide, il devra redonner une valeur de x et y valide.
}

void computer_move()
{
    int x;
    int y;

    //En C, l'aléatoire se fait selon le temps
    srand(time(0));

    if (check_free_spaces() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        board[x][y] = COMPUTER;
    } else {
        print_winner(' '); //Egalité
    }
}

char check_winner()
{
    int i;
    int j;

    //Première partie de la fonction pour check les lignes ( X | X | X )
    for (i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }
    //Deuxième partie de la fonction pour check les colonnes
    for (i = 0; i < 3; i++) {
        if (board[0][i] == board[1][0] && board[0][i] == board[2][i]) {
            return board[i][0];
        }
    }
    //Troisième partie de la fonction pour check la diagonale top left to bot right
    for (i = 0; i < 3; i++) {
        if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
            return board[0][0];
        }
    }
    //Quatrième partie de la fonction pour check la diagonale bot left to top right
    for (i = 0; i < 3; i++) {
        if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            return board[0][2];
        }
    }
    return ' '; //Toujours pas de gagnant
}

void print_winner(char winner)
{
    if (winner == PLAYER)
    {
        printf("You win!\n\n");
    } else if (winner == COMPUTER) {
        printf("You lose!\n\n");
    } else {
        printf("It's a tie!\n\n");
    }
}
