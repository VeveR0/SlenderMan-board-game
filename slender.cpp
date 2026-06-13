#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <conio.h>
using namespace std;

struct coord {
    int x, y; 
} c1, c2, c3, c4, c5, p, aux, SM, t[101];
//c1-5 = clues
// p = player
// t = trees
// SM = Slender Man
char Map[201][201];
// the map is a 200x200 matrix, where:
// '_' and 'I' are map boundaries/ fences
// '1' is the player
// '*' is Slender Man
// '/', '\', '|' and '-' are Slender Man's killing area
// '#' are walls and '`' are doors
// 'Y' are trees
// '?' are clues the player has to collect
// '!' are clues that are in Slender Man's killing area

int xd = 0, LG = 101, LT = 26, trees = 100, s = 5, d = 0; 
// LG = map's length
// LT = map's width; 
// s = number of clues
// trees = nb. of trees
// xd = verifies if the player died/ lost

void seeds() 
{ 
    //each tree gets a random location
    for (int i = 1;i <= trees;i++) 
    { 
        t[i].x = rand() % LG; 
        t[i].y = rand() % LT; 
    } 
}

void plant() 
{
    //tree planting function
    for (int i = 1;i <= trees;i++) 
    { 
        if (
                Map[t[i].x][t[i].y] == ' ' &&\
                !(
                    t[i].x >= 16 && t[i].x <= 43 &&\
                    t[i].y >= 5 && t[i].y <= 9
                 ) && 
                !(
                    t[i].x >= 26 && t[i].x <= 43 && t[i].y >= 9 &&\
                    t[i].y <= 12
                 ) && 
                !(
                    t[i].x >= 86 &&
                    t[i].x <= 93 &&
                    t[i].y >= 2 &&
                    t[i].y <= 6) && 
                !(
                    t[i].x >= 86 &&
                    t[i].x <= 93 &&
                    t[i].y >= 9 &&
                    t[i].y <= 13
                ) &&
                !(
                    t[i].x >= 86 &&
                    t[i].x <= 93 &&
                    t[i].y >= 16 &&
                    t[i].y <= 20
                )
           ) 
            Map[t[i].x][t[i].y] = 'Y'; 
    } 
}

void create_map() {
    //creating/ updating map
    for (int j = 0;j <= LT;j++)
        for (int i = 0;i < LG;i++)
        {
            if ((i == 0 && j == 0) || (j == 0 && i == LG - 1)) Map[i][j] = '.';
            else if (i == 0 || i == LG - 1) Map[i][j] = 'I'; //adding borders
            else if ((j == 0 || j == LT - 1) && !(j == LT - 1 && (i >= LG / 2 - 1 && i <= LG / 2 + 1))) Map[i][j] = '_'; //adding borders
            else if (Map[p.x][p.y] == '|' || Map[p.x][p.y] == '-') Map[i][j] = 'x';
            else if (i == p.x && j == p.y) Map[i][j] = '1';
            else if ((j == 9 && i >= 20 && i <= 21) || (i == 85 && (j == 4 || j == 11 || j == 18)) || (i == 68 && (j == 4 || j == 11 || j == 18))) Map[i][j] = '`';       //adding doors
            else if ((j == 4 && i >= 16 && i <= 43) || (i == 16 && j >= 5 && j <= 9) || (j == 9 && i >= 17 && i <= 24) || (i == 25 && j >= 9 && j <= 12) || (j == 12 && i >= 26 && i <= 43) || (i == 43 && j >= 5 && j <= 12)) Map[i][j] = '#';   //adding house
            else if ((j == 2 && i >= 86 && i <= 93) || (j == 6 && i >= 86 && i <= 93) || (i == 93 && j >= 3 && j <= 5) || (i == 86 && (j == 3 || j == 5)) || (i == 85 && (j == 3 || j == 5))) Map[i][j] = '#';          //adding cabin1
            else if ((j == 9 && i >= 86 && i <= 93) || (j == 13 && i >= 86 && i <= 93) || (i == 93 && j >= 10 && j <= 12) || (i == 86 && (j == 10 || j == 12)) || (i == 85 && (j == 10 || j == 12))) Map[i][j] = '#';   //adding cabin2
            else if ((j == 16 && i >= 86 && i <= 93) || (j == 20 && i >= 86 && i <= 93) || (i == 93 && j >= 17 && j <= 19) || (i == 86 && (j == 17 || j == 19)) || (i == 85 && (j == 17 || j == 19))) Map[i][j] = '#';  //adding cabin3
            else if ((j == 2 && i >= 60 && i <= 67) || (j == 6 && i >= 60 && i <= 67) || (i == 60 && j >= 3 && j <= 5) || (i == 67 && (j == 3 || j == 5)) || (i == 68 && (j == 3 || j == 5))) Map[i][j] = '#';          //adding cabin4
            else if ((j == 9 && i >= 60 && i <= 67) || (j == 13 && i >= 60 && i <= 67) || (i == 60 && j >= 10 && j <= 12) || (i == 67 && (j == 10 || j == 12)) || (i == 68 && (j == 10 || j == 12))) Map[i][j] = '#';   //adding cabin5
            else if ((j == 16 && i >= 60 && i <= 67) || (j == 20 && i >= 60 && i <= 67) || (i == 60 && j >= 17 && j <= 19) || (i == 67 && (j == 17 || j == 19)) || (i == 68 && (j == 17 || j == 19))) Map[i][j] = '#';  //adding cabin6
            else if ((c1.x == i && c1.y == j) || (c2.x == i && c2.y == j) || (c3.x == i && c3.y == j) || (c4.x == i && c4.y == j) || (c5.x == i && c5.y == j)) Map[i][j] = '?'; //adding clues
            else if (SM.x == i && SM.y == j) Map[i][j] = '*';   //spawning SlenderMan
            else Map[i][j] = ' '; // air
        }
    plant();
}

void show_map() 
{
    //map display
    int i, j;
    for (j = 0;j < LT;j++)
    {
        for (i = 0;i < LG;i++)
            cout << Map[i][j];
        cout << endl;
    }
}
void hide_clues() {
    //each clue gets a random location
    while (Map[c1.x][c1.y] != ' ') { c1.x = rand() % LG; c1.y = rand() % LT; }
    Map[c1.x][c1.y] = '?';
    while (Map[c2.x][c2.y] != ' ') { c2.x = rand() % LG; c2.y = rand() % LT; }
    Map[c2.x][c2.y] = '?';
    while (Map[c3.x][c3.y] != ' ') { c3.x = rand() % LG; c3.y = rand() % LT; }
    Map[c3.x][c3.y] = '?';
    while (Map[c4.x][c4.y] != ' ') { c4.x = rand() % LG; c4.y = rand() % LT; }
    Map[c4.x][c4.y] = '?';
    while (Map[c5.x][c5.y] != ' ') { c5.x = rand() % LG; c5.y = rand() % LT; }
    Map[c5.x][c5.y] = '?';
}
void Setup() {
    //starting point
    xd = 0;
    p.x = LG / 2;
    p.y = LT - 2;
}

int radius(int a, int b, int c) {
    if (Map[a][b] == ' ') Map[a][b] = c;
    else if (Map[a][b] == '?')Map[a][b] = '!';
    else if (Map[a][b] == '1') Map[a][b] = 'x';
    return (Map[a][b] == '-' || Map[a][b] == '|');
}
void SM_atk() {
    radius(SM.x - 1, SM.y, '-');           // left
    radius(SM.x + 1, SM.y, '-');           // right
    radius(SM.x, SM.y - 1, '|');           // up
    radius(SM.x, SM.y + 1, '|');           // down
    if (radius(SM.x - 1, SM.y, '~') && radius(SM.x, SM.y - 1, '~')) Map[SM.x - 1][SM.y - 1] = '\\';      //up-left diagonal
    if (radius(SM.x - 1, SM.y, '~') && radius(SM.x, SM.y + 1, '~')) Map[SM.x - 1][SM.y + 1] = '/';       //down-left diagonal
    if (radius(SM.x + 1, SM.y, '~') && radius(SM.x, SM.y - 1, '~')) Map[SM.x + 1][SM.y - 1] = '/';       //up-right diagonal
    if (radius(SM.x + 1, SM.y, '~') && radius(SM.x, SM.y + 1, '~')) Map[SM.x + 1][SM.y + 1] = '\\';      //up-left diagonal
    if (radius(SM.x - 1, SM.y, '~')) radius(SM.x - 2, SM.y, '-');
    if (radius(SM.x + 1, SM.y, '~')) radius(SM.x + 2, SM.y, '-');
    if (radius(SM.x, SM.y - 1, '~')) radius(SM.x, SM.y - 2, '|');
    if (radius(SM.x, SM.y + 1, '~')) radius(SM.x, SM.y + 2, '|');
}

void Logic()
{
    //what happens depending on player's movement
    if (_kbhit())
        switch (_getch())
        {
        case 'a': if (Map[p.x - 1][p.y] != 'I' && Map[p.x - 1][p.y] != '#' && Map[p.x - 1][p.y] != 'Y' && Map[p.x - 1][p.y] != '_') { p.x--;d++; } break;
        case 'd': if (Map[p.x + 1][p.y] != 'I' && Map[p.x + 1][p.y] != '#' && Map[p.x + 1][p.y] != 'Y' && Map[p.x + 1][p.y] != '_') { p.x++;d++; } break;
        case 'w': if (Map[p.x][p.y - 1] != '_' && Map[p.x][p.y - 1] != '#' && Map[p.x][p.y - 1] != 'Y') { p.y--;d++; } break;
        case 's': if (Map[p.x][p.y + 1] != '_' && Map[p.x][p.y + 1] != '#' && Map[p.x][p.y + 1] != 'Y') { p.y++;d++; } break;
        default: break;
        }
    if (p.x == c1.x && p.y == c1.y) { c1.x = 0; s--; }
    if (p.x == c2.x && p.y == c2.y) { c2.x = 0; s--; }
    if (p.x == c3.x && p.y == c3.y) { c3.x = 0; s--; }
    if (p.x == c4.x && p.y == c4.y) { c4.x = 0; s--; }
    if (p.x == c5.x && p.y == c5.y) { c5.x = 0; s--; }
    if (p.x >= LG / 2 - 1 && p.x <= LG / 2 + 1 && p.y == LT && s == 0) { xd = 1; system("Color 0A"); }
    else if (p.y >= 26 || (Map[p.x][p.y] == '|' || Map[p.x][p.y] == '-') || Map[p.x][p.y] == '\\' || Map[p.x][p.y] == '/') Map[p.x][p.y] = 'x'; if (Map[p.x][p.y] == 'x') { xd = 1; system("Color 04"); }
}

int main()
{
    srand(time(NULL));
    Setup();
    seeds();
    create_map();
    hide_clues();
    while (!xd)
    {
        system("cls");
        create_map();
        SM_atk();
        show_map();
        for (int i = 0;i <= LG;i++) if (i == LG / 2 - 2) cout << '/';else if (i == LG / 2 + 2)cout << "\\";else cout << ' ';
        cout << endl;
        aux.x = p.x;aux.y = p.y;
        if (d % 3 == 0) do { SM.x = rand() % LG; SM.y = rand() % LT; } while (Map[SM.x][SM.y] == '|' || Map[SM.x][SM.y] == '_' || Map[SM.x][SM.y] == '#' || Map[SM.x][SM.y] == '1' || Map[SM.x][SM.y] == '?' || Map[SM.x][SM.y] == '`' || Map[SM.x][SM.y] == 'Y');
        while (aux.x == p.x && aux.y == p.y) Logic();
    }
    return 0;
}
