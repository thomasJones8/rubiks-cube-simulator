#include <stdio.h>

#define SIDES 6

#ifndef N
#define N 5
#endif

void multi_print(int len, char symbol)
{
    for (int i = 0; i < len; i++)
    {
        printf("%c", symbol);
    }
}

void print_list(int list[])
{
    for (int i = 0; i < N; i++)
    {
        printf("%d", list[i]);
    }
}

void print_cube(int cube[SIDES][N][N])
{
    printf("\n");
    // góra reprezentacji - sciana gorna
    for (int i = 0; i < N; i++)
    {
        multi_print(N + 1, ' ');
        print_list(cube[0][i]);
        printf("\n");
    }

    // środek reprezentacji - 4 sciany
    for (int floor = 0; floor < N; floor++)
    {
        for (int i = 1; i < SIDES - 1; i++)
        {
            print_list(cube[i][floor]);
            if (i < SIDES - 2)
            {
                printf("|");
            }
        }
        printf("\n");
    }

    // dół reprezentacji - sciana dolna
    for (int i = 0; i < N; i++)
    {
        multi_print(N + 1, ' ');
        // if (N > 1)
        {
            print_list(cube[5][i]);
        }
        printf("\n");
    }
}

// rotacja pojedynczej sciany
void rotate_side(int side[][N], int angle)
{
    for (int i = 0; i < angle; i++)
    {
        int result[N][N];

        for (int row = 0; row < N; row++)
        {
            for (int column = 0; column < N; column++)
            {
                result[column][N - row - 1] = side[row][column];
            }
        }

        // przekopiowywanie z powrotem
        for (int row = 0; row < N; row++)
        {
            for (int column = 0; column < N; column++)
            {
                side[row][column] = result[row][column];
            }
        }
    }
}

void copy_array(int from[N], int to[N])
{
    for (int i = 0; i < N; i++)
    {
        to[i] = from[i];
    }
}

// Rotacja jednej warstwy jako przesuniecie 4 tablic
void rotate_arrays(int one[N], int two[N], int three[N], int four[N])
{
    // Nowa tablica, do ktorej przekopiujemy one
    int tmp[N];

    copy_array(one, tmp);
    copy_array(four, one);
    copy_array(three, four);
    copy_array(two, three);
    copy_array(tmp, two);
}

/*
    Główna logika obrotu:
    1. Obracamy ścianę bazową obrotu
    2. Przekręcamy 4 sąsiednie ściany tak, by sąsiadujace ze sciana bazową
    kolumny/wiersze staly sie pierwszym wierszem
    3. Zaczynajac od pierwszego wiersza, przesuwamy odpowiednia liczbe
    razy (zgodnie z katem) odpowiednia liczbe wierszy (zgodnie z liczba wartstw obrotu)
    4. Obracamy te 4 sciany z powrotem

    Kąt obrotu = (angle) * (90 stopni w prawo). Obracamy się zawsze w prawo
    (tzn. obrot w lewo to obrot 3 razy w prawo)
*/

// framing sides - dla każdej sciany sa to 4 sciany sasiadujace
// angles_framing_sides - kat obrotu przygotowawczego dla kazdej sciany sasiedniej

void rotate_layers(int (*framing_sides[4])[N], int angles_framing_sides[4], int how_many_layers, int angle)
{

    for (int i = 0; i < 4; i++)
    {
        rotate_side(framing_sides[i], angles_framing_sides[i]);
    }

    for (int j = 0; j < angle; j++)
    {
        for (int i = 0; i < how_many_layers; i++)
        {
            rotate_arrays(framing_sides[0][i], framing_sides[1][i], framing_sides[2][i], framing_sides[3][i]);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        // Przesuwamy o tyle, ile zostalo do pelnego obrotu, czyli
        // byl obrot o x, to teraz o 4 -x. Suma = 4.
        rotate_side(framing_sides[i], 4 - angles_framing_sides[i]);
    }
}

void rotate_cube(int how_many_layers, int base_side, int angle, int cube[][N][N])
{
    int(*u)[N] = cube[0];
    int(*l)[N] = cube[1];
    int(*f)[N] = cube[2];
    int(*r)[N] = cube[3];
    int(*b)[N] = cube[4];
    int(*d)[N] = cube[5];

    int(*selected_side)[N] = NULL;
    int(*opposite_side)[N] = NULL;
    int(*framing_sides[4])[N] = {NULL, NULL, NULL, NULL};
    int angles_framing_sides[4] = {0, 0, 0, 0};

    switch (base_side)
    {
        case 'u':
            selected_side = u;
            opposite_side = d;
            framing_sides[0] = b;
            framing_sides[1] = r;
            framing_sides[2] = f;
            framing_sides[3] = l;
            break;

        case 'l':
            selected_side = l;
            opposite_side = r;
            framing_sides[0] = u;
            framing_sides[1] = f;
            framing_sides[2] = d;
            framing_sides[3] = b;
            angles_framing_sides[0] = 1;
            angles_framing_sides[1] = 1;
            angles_framing_sides[2] = 1;
            angles_framing_sides[3] = 3;
            break;

        case 'f':
            selected_side = f;
            opposite_side = b;
            framing_sides[0] = l;
            framing_sides[1] = u;
            framing_sides[2] = r;
            framing_sides[3] = d;
            angles_framing_sides[0] = 3;
            angles_framing_sides[1] = 2;
            angles_framing_sides[2] = 1;
            break;

        case 'r':
            selected_side = r;
            opposite_side = l;
            framing_sides[0] = b;
            framing_sides[1] = d;
            framing_sides[2] = f;
            framing_sides[3] = u;
            angles_framing_sides[0] = 1;
            angles_framing_sides[1] = 3;
            angles_framing_sides[2] = 3;
            angles_framing_sides[3] = 3;
            break;

        case 'b':
            selected_side = b;
            opposite_side = f;
            framing_sides[0] = d;
            framing_sides[1] = r;
            framing_sides[2] = u;
            framing_sides[3] = l;
            angles_framing_sides[0] = 2;
            angles_framing_sides[1] = 3;
            angles_framing_sides[3] = 1;
            break;

        case 'd':
            selected_side = d;
            opposite_side = u;
            framing_sides[0] = l;
            framing_sides[1] = f;
            framing_sides[2] = r;
            framing_sides[3] = b;
            angles_framing_sides[0] = 2;
            angles_framing_sides[1] = 2;
            angles_framing_sides[2] = 2;
            angles_framing_sides[3] = 2;
            break;
    }

    // obrot glownej sciany
    rotate_side(selected_side, angle);
    // obrot warstw dookola glownej sciany
    rotate_layers(framing_sides, angles_framing_sides, how_many_layers, angle);
    // obrot o N warstw = obrot całą kostką. A więc przeciwległą sciane rowniez obracamy
    if (how_many_layers == N)
    {
        // kat dopelniajcy kat podstawowy do 360
        //  bo jak tyl obracamy w lewo, to przód w prawo
        rotate_side(opposite_side, 4 - angle);
    }
}

int main(void)
{
    int cube[SIDES][N][N];
    int color = 0;

    for (int side = 0; side < SIDES; side++)
    {
        for (int a = 0; a < N; a++)
        {
            for (int b = 0; b < N; b++)
            {
                cube[side][a][b] = color;
            }
        }
        color++;
    }

    int dot_found = 0;
    // wartosci -1 oznaczaja, ze odpowiednie wartosci jeszcze nie sa przypisane
    // lub ze obrot o takich wartosciach juz zostal zrobiony
    // czyli przyrownanie do -1 jest resetem
    int how_many_layers = -1;
    int base_side = -1;
    int angle = -1;
    int error = 0;
    int scanf_result;

    while (!dot_found && !error)
    {
        int c = getchar();

        if (c == '.')
        {
            dot_found = 1;
        }

        else if (c == '\n')
        {
            print_cube(cube);
        }

        else if ('0' <= c && c <= '9')
        {
            ungetc(c, stdin);
            scanf_result = scanf("%d", &how_many_layers);
            if (scanf_result < 1)
            {
                error = 1;
            }
        }

        else if ('a' <= c && c <= 'z')
        {
            base_side = c;
            if (how_many_layers == -1)
            {
                how_many_layers = 1;
            }

            angle = getchar();

            if (angle == '\'')
            {
                angle = 3;
            }

            else if (angle == '\"')
            {
                angle = 2;
            }

            // jesli po literze nie ma kata
            else
            {
                ungetc(angle, stdin);
                angle = 1;
            }

            rotate_cube(how_many_layers, base_side, angle, cube);
            how_many_layers = -1;
            angle = -1;
            base_side = -1;
        }
    }
}
