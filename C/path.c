#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "File does not exist\n");
        return 1;
    }

    int map_size;
    if (fscanf(file, "%d", &map_size) != 1) {
        fprintf(stderr, "Invalid map size\n");
        fclose(file);
        return 1;
    }

    int map[map_size][map_size];
    int dp[map_size][map_size];

    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            if (fscanf(file, "%d", &map[i][j]) != 1) {
                fprintf(stderr, "Invalid map element at (%d - %d)\n", i, j);
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    
    dp[0][0] = map[0][0];

    for (int i = 1; i < map_size; i++)
        dp[i][0] = dp[i - 1][0] + map[i][0];

    for (int j = 1; j < map_size; j++)
        dp[0][j] = dp[0][j - 1] + map[0][j];

    for (int i = 1; i < map_size; i++) {
        for (int j = 1; j < map_size; j++) {
            int min_prev = dp[i - 1][j] < dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
            dp[i][j] = map[i][j] + min_prev;
        }
    }

    // Ανακατασκευή μονοπατιού
    int *path = malloc((2 * map_size) * sizeof(int));
    int rows = map_size - 1, cols = map_size - 1;
    int path_size = 0;

    while (rows > 0 || cols > 0) {
        path[path_size++] = map[rows][cols];
        if (rows == 0) cols--;
        else if (cols == 0) rows--;
        else if (dp[rows - 1][cols] < dp[rows][cols - 1]) rows--;
        else cols--;
    }
    path[path_size++] = map[0][0];

    printf("Minimum Cost: %d\n", dp[map_size - 1][map_size - 1]);
    printf("Minimum Cost Path: ");

    for (int i = path_size - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");

    free(path);
    return 0;
}