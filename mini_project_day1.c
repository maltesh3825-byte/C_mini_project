#include <stdio.h>
#include <math.h>

#define ROWS 40
#define COLS 80

char canvas[ROWS][COLS];

void init_canvas() {
    int i, j;
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}

void display_canvas() {
    int i, j;
    printf("\n");
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

void draw_circle(int cx, int cy, int r) {
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            int dx = j - cx;
            int dy = i - cy;
            int dist = (int)sqrt(dx*dx + dy*dy);
            if (dist == r)
                canvas[i][j] = '*';
        }
    }
}

void draw_rectangle(int r1, int c1, int r2, int c2) {
    int i, j;
    // top and bottom line
    for (j = c1; j <= c2; j++) {
        canvas[r1][j] = '*';
        canvas[r2][j] = '*';
    }
    // left and right line
    for (i = r1; i <= r2; i++) {
        canvas[i][c1] = '*';
        canvas[i][c2] = '*';
    }
}

void draw_line(int r1, int c1, int r2, int c2) {
    int i;
    int dr = r2 - r1;
    int dc = c2 - c1;
    int steps = abs(dr) > abs(dc) ? abs(dr) : abs(dc);
    float ri = (float)dr / steps;
    float ci = (float)dc / steps;
    float r = r1, c = c1;
    for (i = 0; i <= steps; i++) {
        if ((int)r >= 0 && (int)r < ROWS && (int)c >= 0 && (int)c < COLS)
            canvas[(int)r][(int)c] = '*';
        r += ri;
        c += ci;
    }
}

void draw_triangle(int r1, int c1, int r2, int c2, int r3, int c3) {
    draw_line(r1, c1, r2, c2);
    draw_line(r2, c2, r3, c3);
    draw_line(r3, c3, r1, c1);
}

int main() {
    int choice;
    int r1, c1, r2, c2, r3, c3, rad;

    init_canvas();

    printf("--- 2D Graphics Editor Part 1 ---\n");

    while(1) {
        printf("\n1. Draw Circle\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Line\n");
        printf("4. Draw Triangle\n");
        printf("5. Display Canvas\n");
        printf("6. Clear Canvas\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter center col, row and radius: ");
            scanf("%d %d %d", &c1, &r1, &rad);
            draw_circle(c1, r1, rad);
            printf("Circle drawn!\n");
        } else if (choice == 2) {
            printf("Enter r1 c1 r2 c2: ");
            scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
            draw_rectangle(r1, c1, r2, c2);
            printf("Rectangle drawn!\n");
        } else if (choice == 3) {
            printf("Enter r1 c1 r2 c2: ");
            scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
            draw_line(r1, c1, r2, c2);
            printf("Line drawn!\n");
        } else if (choice == 4) {
            printf("Enter r1 c1 r2 c2 r3 c3: ");
            scanf("%d %d %d %d %d %d", &r1, &c1, &r2, &c2, &r3, &c3);
            draw_triangle(r1, c1, r2, c2, r3, c3);
            printf("Triangle drawn!\n");
        } else if (choice == 5) {
            display_canvas();
        } else if (choice == 6) {
            init_canvas();
            printf("Canvas cleared!\n");
        } else if (choice == 7) {
            printf("Bye!\n");
            break;
        } else {
            printf("Wrong choice! Try again.\n");
        }
    }

    return 0;
}