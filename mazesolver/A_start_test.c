#include <stdio.h>
#include <stdlib.h>

struct point_t
{
    int x;      //coordinate x
    int y;      //coordinate y
    int G;      //distance to target
    int S;      //distance to source
    int T;      //total distance
    int dir;    //direction of next step 0:up 1:down 2:left 3:right
    int boundary;
};

void A_star_calcDistance(struct point_t* current, struct point_t* start, struct point_t end*);
void A_star(int* A, int r, int c, struct point_t* path, int* path_len,struct point_t start, struct point_t end);
void A_star_shadow_init(struct point_t* shadow_A, int r, int c);

void A_star_shadow_init(struct point_t* shadow_A, int r, int c){
    int i=0;
    int j=0;
    for (i=0;i<r;i++){
        for (j=0;j<c;j++){
            shadow_A[i*c+j]->x=i;
            shadow_A[i*c+j]->y=j;
            shadow_A[i*c+j]->G=0;
            shadow_A[i*c+j]->boundary=0;
        }
    }
}

void A_star_calcDistance(struct point_t* current, struct point_t* start, struct point_t end*){
    int delta_x;
    int delta_y;
    //calculate S
    delta_x = abs(current->x - start->x);
    delta_y = abs(current->y - start->y);
    current->S = (int)floor(sqrt(pow(delta_x,2)+pow(delta_y,2)));
    //calcuate G
    delta_x = abs(current->x - end->x);
    delta_y = abs(current->y - end->y);
    current->G = (int)floor(sqrt(pow(delta_x,2)+pow(delta_y,2)));
    //calcuate T
    current->T = current->S+current->G;
    //
}

void A_star_click(struct point_t *ptr, int *A, struct *point_t shadow_A, struct point_t** path_buffer, int* path_bugger_len, int n){
    int x=0;
    int y=0;
    struct point_t tmp;
    // check up
    temp.x=ptr->x;
    temp.y=ptr->y-1;
    if ((temp.y)<n && (temp.y)>0){
        A_star_calcDistance(temp)
    }
}


void A_star(int* A, int r, int c, struct point_t* path, int* path_len,struct point_t start, struct point_t end){
    // create buffer
    struct point_t shadow_A[n*n];
    A_star_shadow_init(shadow_A, n);
    // create path_buffer
    struct point_t *path_buffer[n*n];
    int path_buffer_len=0;
    struct point_t ptr = {.x=start->x, .y=start->x};
    //ptr boundary is 0

    //click up down left right


}

int main(int argc, char const *argv[])
{
    int i=0;
    int n = 5;
    int A[]={1,1,0,0,1,
            0,1,0,0,1,
            1,1,0,1,1,
            1,0,1,0,0,
            1,1,1,1,1};
    struct point_t path[n*n];
    struct point_t start = {.x=0, .y=0, .G=0, .S=0, .T=0};
    struct point_t end= {.x=4, .y=4, .G=0, .S=0, .T=0};
    int path_len=0;
    A_star(A, n, n, path, &path_len);
    for (i=0;i<path_len;i++){
        printf("(%d,%d) ->", path[i].x, path[i].y);
    }
    printf("\n");

    return 0;
}