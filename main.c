#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define INF 100000

void table(int M, int dists[M][M]){
    printf("    ");
    for (int i = 0; i < M; i++){
            printf("%4d", i+1);
    }
    printf("\n");

    for (int i = 0; i < M; i++){
        printf("%4d", i+1);
        for (int j = 0; j < M; j++){
            if (dists[i][j] == INF){
                printf("%4s", "INF");
            }else{
            printf("%4d", dists[i][j]);
            }
        }
        printf("\n");
    }
}


void floyd(int M, int dists[M][M]){
    for (int k = 0; k < M; k++){
        for (int i = 0; i < M; i++){
            for (int j = 0; j < M; j++){
                if (dists[i][k] + dists[k][j] < dists[i][j] && dists[i][k] != INF && dists[k][j] != INF){
                    dists[i][j] = dists[i][k] + dists[k][j];
                }
            }
        }
    }
}

void greedy_method(int M, int dists[M][M], int visit_time[M], int N) {
    int visited[M];
    for (int i = 0; i < M; i++) {
        visited[i] = 0;
    }

    int plan[M];
    int plan_count = 0, total_time = 0, current_place = 0;


    printf("\nVISITED PLACES:\n");
    while (total_time < N) {
        int next = -1;
        int smallest_time = INF;

        if (plan_count == 0) {
            next = 0;
            smallest_time = visit_time[0];
        } else {
            for (int j = 0; j < M; j++) {
                if (!visited[j] && dists[current_place][j] != INF) {
                    int time_needed = visit_time[j] + dists[current_place][j];
                    if (time_needed < smallest_time && total_time + time_needed <= N) {
                        smallest_time = time_needed;
                        next = j;
                    }
                }
            }
            if (next == -1) {
                for (int i = 0; i < M; i++) {
                    if (!visited[i] && total_time + visit_time[i] <= N) {
                        next = i;
                        smallest_time = visit_time[i];
                        break;
                    }
                }
            }
        }
        if (next == -1) break;

        visited[next] = 1;
        plan[plan_count] = next + 1;
        total_time += smallest_time;
        plan_count++;
        printf("place %d, visit time's %d and total time's %d\n", next + 1, visit_time[next], total_time);
        current_place = next;
    }

    printf("FINAL MAP:\n");
    for (int i = 0; i < plan_count; i++) {
        printf("%d", plan[i]);
        if (i < plan_count - 1) printf(" -> ");
    }
    printf("\ntotal time: %d minutes\n", total_time);
    printf("VISITED PLACES: %d\n", plan_count);
}

int main(){
    srand(time(NULL));
    int N, M;
    int option;

    printf("How much time do you have?\n");
    scanf("%d", &N);

    if (N < 0){
        printf("please enter a positive number.");
    }

    printf("enter the places you want:\n");
    scanf("%d", &M);
    
    if (M < 1 || M > 100){
        printf("due to overflow, you must choose a number between 1 to 100 :)");
        return 1;
    }

    printf("Do you want to use infinity (INF) in some paths?:(1=yes, 0=no)\n");
    scanf("%d", &option);

    if (option != 1 && option != 0){
        printf("what you doing man? 1 or 0. it's simple.");
    }

    int visit_time[M];
    int dists[M][M];

    for (int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            if (i == j){
                dists[i][j] = 0;
            }else if (option == 1){
                if (rand() % 100 < 20){
                    dists[i][j] = INF;
                    dists[j][i] = INF;
                }else{
                    dists[i][j] = rand() % 41 + 10;
                    dists[j][i] = dists[i][j];
                }
            }else{
                dists[i][j] = rand() % 41 + 10;
                dists[j][i] = dists[i][j];
            }
        }
    }

    for (int x = 0; x < M; x++){
        visit_time[x] = rand() % 71 + 30;
        printf("place %d visit time: %d minutes\n", x+1, visit_time[x]);
    }

    table(M, dists);
    floyd(M, dists);
    printf("\n");
    table(M, dists);

    greedy_method(M, dists, visit_time, N);

    return 0;

}

