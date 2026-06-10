#include <stdio.h>
#include <math.h>

#define ROWS 40
#define COLS 80
#define MAX_OBJ 20

char canvas[ROWS][COLS];

// object storage
int obj_type[MAX_OBJ];   // 1=circle 2=rect 3=line 4=triangle
int obj_x1[MAX_OBJ], obj_y1[MAX_OBJ];
int obj_x2[MAX_OBJ], obj_y2[MAX_OBJ];
int obj_x3[MAX_OBJ], obj_y3[MAX_OBJ];
int obj_r[MAX_OBJ];
int obj_count = 0;

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
    for (j = c1; j <= c2; j++) {
        canvas[r1][j] = '*';
        canvas[r2][j] = '*';
    }
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

// redraws everything from object list
void redraw_all() {
    int i;
    init_canvas();
    for (i = 0; i < obj_count; i++) {
        if (obj_type[i] == 0) continue; // deleted
        if (obj_type[i] == 1)
            draw_circle(obj_x1[i], obj_y1[i], obj_r[i]);
        else if (obj_type[i] == 2)
            draw_rectangle(obj_y1[i], obj_x1[i], obj_y2[i], obj_x2[i]);
        else if (obj_type[i] == 3)
            draw_line(obj_y1[i], obj_x1[i], obj_y2[i], obj_x2[i]);
        else if (obj_type[i] == 4)
            draw_triangle(obj_y1[i], obj_x1[i], obj_y2[i], obj_x2[i], obj_y3[i], obj_x3[i]);
    }
}

void list_objects() {
    int i;
    char *names[] = {"", "Circle", "Rectangle", "Line", "Triangle"};
    printf("\n--- Object List ---\n");
    for (i = 0; i < obj_count; i++) {
        if (obj_type[i] == 0) continue;
        printf("ID %d: %s\n", i+1, names[obj_type[i]]);
    }
    printf("-------------------\n");
}

void delete_object() {
    int id;
    list_objects();
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    id--;
    if (id < 0 || id >= obj_count || obj_type[id] == 0) {
        printf("Invalid ID!\n");
        return;
    }
    obj_type[id] = 0;
    redraw_all();
    printf("Object deleted!\n");
}

void modify_object() {
    int id;
    list_objects();
    printf("Enter ID to modify: ");
    scanf("%d", &id);
    id--;
    if (id < 0 || id >= obj_count || obj_type[id] == 0) {
        printf("Invalid ID!\n");
        return;
    }
    int t = obj_type[id];
    if (t == 1) {
        printf("Enter new col row radius: ");
        scanf("%d %d %d", &obj_x1[id], &obj_y1[id], &obj_r[id]);
    } else if (t == 2 || t == 3) {
        printf("Enter new r1 c1 r2 c2: ");
        scanf("%d %d %d %d", &obj_y1[id], &obj_x1[id], &obj_y2[id], &obj_x2[id]);
    } else if (t == 4) {
        printf("Enter new r1 c1 r2 c2 r3 c3: ");
        scanf("%d %d %d %d %d %d", &obj_y1[id], &obj_x1[id], &obj_y2[id], &obj_x2[id], &obj_y3[id], &obj_x3[id]);
    }
    redraw_all();
    printf("Object modified!\n");
}

int main() {
    int choice;
    init_canvas();

    printf("--- 2D Graphics Editor Part 2 ---\n");

    while(1) {
        printf("\n1. Draw Circle\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Line\n");
        printf("4. Draw Triangle\n");
        printf("5. Display Canvas\n");
        printf("6. List Objects\n");
        printf("7. Delete Object\n");
        printf("8. Modify Object\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter col row radius: ");
            scanf("%d %d %d", &obj_x1[obj_count], &obj_y1[obj_count], &obj_r[obj_count]);
            obj_type[obj_count] = 1;
            draw_circle(obj_x1[obj_count], obj_y1[obj_count], obj_r[obj_count]);
            obj_count++;
            printf("Circle added! ID: %d\n", obj_count);
        } else if (choice == 2) {
            printf("Enter r1 c1 r2 c2: ");
            scanf("%d %d %d %d", &obj_y1[obj_count], &obj_x1[obj_count], &obj_y2[obj_count], &obj_x2[obj_count]);
            obj_type[obj_count] = 2;
            draw_rectangle(obj_y1[obj_count], obj_x1[obj_count], obj_y2[obj_count], obj_x2[obj_count]);
            obj_count++;
            printf("Rectangle added! ID: %d\n", obj_count);
        } else if (choice == 3) {
            printf("Enter r1 c1 r2 c2: ");
            scanf("%d %d %d %d", &obj_y1[obj_count], &obj_x1[obj_count], &obj_y2[obj_count], &obj_x2[obj_count]);
            obj_type[obj_count] = 3;
            draw_line(obj_y1[obj_count], obj_x1[obj_count], obj_y2[obj_count], obj_x2[obj_count]);
            obj_count++;
            printf("Line added! ID: %d\n", obj_count);
        } else if (choice == 4) {
            printf("Enter r1 c1 r2 c2 r3 c3: ");
            scanf("%d %d %d %d %d %d", &obj_y1[obj_count], &obj_x1[obj_count], &obj_y2[obj_count], &obj_x2[obj_count], &obj_y3[obj_count], &obj_x3[obj_count]);
            obj_type[obj_count] = 4;
            draw_triangle(obj_y1[obj_count], obj_x1[obj_count], obj_y2[obj_count], obj_x2[obj_count], obj_y3[obj_count], obj_x3[obj_count]);
            obj_count++;
            printf("Triangle added! ID: %d\n", obj_count);
        } else if (choice == 5) {
            display_canvas();
        } else if (choice == 6) {
            list_objects();
        } else if (choice == 7) {
            delete_object();
        } else if (choice == 8) {
            modify_object();
        } else if (choice == 9) {
            printf("Bye!\n");
            break;
        } else {
            printf("Wrong choice! Try again.\n");
        }
    }

    return 0;
}