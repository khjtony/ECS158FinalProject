#include "stdio.h"
#include "stdlib.h"
#include "math.h"



#define DEBUG

// REMEMBER THE X,Y MEANING
// WHICH IS DIFFERNET THAN MATRIX
// This A star path finder does not have weight feather

typedef struct
{
    int x;
    int y;
}Location2D_t;

typedef struct 
{
    int pass;
    Location2D_t pos;
    int frontier;
    float current_cost;
    float priority;
    Location2D_t came_from;

}pix_t;



void update_pix(pix_t* map_mask, Location2D_t previous,  Location2D_t current, int width, int height, Location2D_t start, Location2D_t stop){
    // if it is wall
    if (map_mask[current.x+current.y*width].pass == 0){
        map_mask[current.x+current.y*width].frontier=0;
        return ;
    }
    // int distance = sqrt(pow((current.x-start.x),2)+pow((current.y-start.y),2));
    int distance = map_mask[previous.x+previous.y*width].current_cost+1;
    // printf("Updated pix: now update pix (%d, %d):%d \n", current.x ,current.y,map_mask[current.x+current.y*width].current_cost);
    if (map_mask[current.x+current.y*width].current_cost==-1 ||
        distance< map_mask[current.x+current.y*width].current_cost){
        // printf("Updated pix: update pix (%d,%d)!\n", current.x, current.y);
        map_mask[current.x+current.y*width].current_cost = distance;
        map_mask[current.x+current.y*width].frontier=1;
        // map_mask[current.x+current.y*width].priority=distance+abs(current.x-stop.x)+abs(current.y-stop.y);
        map_mask[current.x+current.y*width].priority=distance+sqrt(pow((stop.x-current.x),2)+pow((stop.y-current.y),2));
        map_mask[current.x+current.y*width].came_from = previous;
        return;
    }
    return;

}

Location2D_t find_priority_frontier(pix_t* map_mask, int width, int height){

    Location2D_t front;
    float priority=2*((width+height));
    int x=0;
    int y=0;
    for (x=0;x<width;x++){
        for (y=0;y<height;y++){
            if (map_mask[x+y*width].pass==0){
                map_mask[x+y*width].frontier=0;
                continue;
            }


            if (map_mask[x+y*width].frontier==1 &&
                map_mask[x+y*width].priority<priority){
                // if (map_mask[x+y*width].priority==0){
                //     printf("Now check (%d,%d), priority is: %d\n", 
                //     x, y, map_mask[x+y*width].priority);
                // }
                priority = map_mask[x+y*width].priority;
                front = map_mask[x+y*width].pos;
            }
        }
    }
    // deassert frontier attribution
    #ifdef DEBUG
    printf("Found priority at (%d,%d)\n", front.x, front.y);
    #endif 
    map_mask[front.x+front.y*width].frontier=0;
    return front;
}

void print_mask(pix_t* map_mask, int width, int height){
    int x=0, y=0;
    for (y=0;y<height;y++){
        for(x=0;x<width;x++){
            if (map_mask[x+y*width].pass==0){
                printf("#\t");
            }else{
                printf("%.1f(%d)\t",map_mask[x+y*width].priority,map_mask[x+y*width].frontier);
            }
        }
        printf("\n");
    }
}

void A_star(int* map, int width, int height, Location2D_t* route, int* route_len,
    Location2D_t start, Location2D_t stop){
    printf("The vertex are: (%d, %d), (%d, %d)\n", start.x, start.y, stop.x, stop.y);
    printf("The received mat size is %d*%d\n",width, height );
    pix_t* map_mask = (pix_t*)malloc(width*height*sizeof(pix_t));
    // drift from start point
    start.x = start.x;
    start.y= start.y;
    // init map_mask
    int x=0;
    int y=0;
    Location2D_t zero_pos;
    zero_pos.x=0;
    zero_pos.y=0;
    for (y=0;y<height;y++){
        for(x=0;x<width;x++){
            // pos
            map_mask[x+y*width].pos.x=x;
            map_mask[x+y*width].pos.y=y;
            // pass
            if (map[x+y*width]==0){
               map_mask[x+y*width].pass = 0; 
            }else{
               map_mask[x+y*width].pass = 1;  
            }
            // frontier
            map_mask[x+y*width].frontier = 0;
            // current_cost
            map_mask[x+y*width].current_cost = -1;
            // priority
            map_mask[x+y*width].priority = -1;
            // came_from
            map_mask[x+y*width].came_from = zero_pos;

        }
    }
    map_mask[start.x+start.y*width].pass = 1;
    map_mask[start.x+start.y*width].frontier=1;
    map_mask[start.x+start.y*width].current_cost=0;
    map_mask[start.x+start.y*width].priority=0;
    // add start 
    Location2D_t current;
    current.x = start.x;
    current.y = start.y;
    Location2D_t temp_current;
    while(!(abs(current.x - stop.x)==0 && abs(current.y - stop.y)==0)){
        // find priority
        current = find_priority_frontier(map_mask, width, height);
        x = current.x;
        y = current.y;
        // up
        if (y-1>=0){
            // printf("Test up\n");
            temp_current.x = x;
            temp_current.y = y-1;
            update_pix(map_mask, current, temp_current, width, height, start, stop);
        }
        // down
        if (y+1<height){
            // printf("Test down\n");
            temp_current.x = x;
            temp_current.y = y+1;
            update_pix(map_mask, current, temp_current, width, height, start, stop);
        }
        // left
        if (x-1>=0){
            // printf("Test right\n");
            temp_current.x = x-1;
            temp_current.y = y;
            update_pix(map_mask, current, temp_current, width, height, start, stop);
        }
        // right
        if (x+1<width){
            // printf("Test right\n");
            temp_current.x = x+1;
            temp_current.y = y;
            update_pix(map_mask, current, temp_current, width, height, start, stop);
        }
        // left up
        if (y-1>=0 && x-1>0){
            temp_current.x = x-1;
            temp_current.y = y-1;
            update_pix(map_mask, current, temp_current, width, height, start, stop);
        }
        // left down
        if (y+1<height && x-1>0){
            temp_current.x = x-1;
            temp_current.y = y+1;
            update_pix(map_mask, current, temp_current, width, height, start, stop);
        }
        // right up
        if (x+1<width && y-1>0){
            temp_current.x = x+1;
            temp_current.y = y-1;
            update_pix(map_mask, current, temp_current, width, height, start, stop);
        }
        // right down
        if (x+1<width && y+1<height){
            temp_current.x = x+1;
            temp_current.y = y+1;
            update_pix(map_mask, current, temp_current, width, height, start, stop);
        }
        // print_mask(map_mask, width, height);

    }
    printf("Reached stop! (%d,%d)\n", current.x, current.y);

    // find back
    stop.x=current.x;
    stop.y=current.y;
    current.x = stop.x;
    current.y = stop.y;

    int i=0;
    while (!(current.x == start.x && current.y == start.y)){
        route[i].x = current.x;
        route[i].y =current.y;

        printf("Now is: (%d, %d), ", current.x, current.y);
        current = map_mask[current.x+current.y*width].came_from;
        printf("Found previous (%d, %d) \n", current.x, current.y);

        i++;
    }
    *route_len = i;
    return;
}




// int main(int argc, char const *argv[])
// {
//     // dummy map
//     int width = 7;
//     int height=7;
//     int map[]={1,1,1,1,1,1,1,
//                 1,0,0,1,1,1,1,
//                 1,0,0,0,1,1,1,
//                 1,1,0,0,0,1,1,
//                 1,1,1,0,0,0,1,
//                 1,1,1,1,0,0,1,
//                 1,1,1,1,1,1,1};
//     Location2D_t route[width*height];
//     int route_len=0;

//     // read from file
//     // printf("Width and height is: (%d, %d)\n",width, height );

//     //create map
//     // int map[width*height];
//     // while(getline(&line, &len, fptr)!=-1){
//     //     sscanf(line, "%d", &value);
//     //     map[count]=value;
//     //     count++;
//     // }
//     // fclose(fptr);


//     Location2D_t start;
//     start.x=0;
//     start.y=0;
//     Location2D_t stop;
//     stop.x=6;
//     stop.y=6;
//     // put into astar solver
//     printf("Start to solve\n");
//     A_star(map, width, height, route, &route_len, start, stop);
//     // get back route
//     int i=0;
//     for (i=route_len-1;i>=0;i--){
//         printf("(%d,%d)->", route[i].x, route[i].y);
//     }
//     return 0;
// }