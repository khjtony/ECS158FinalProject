#include "implementation.cpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
  ifstream fptr;
  if (argc>1){
    string fname(argv[1]);
    fptr.open("binaryMaze.txt", ifstream::in);
  }
  int width, height, value,count;
  count=0;
  fptr>> width >> height;
  cout<<"The (width, height) of this picture is: "<<width<<","<<height<<endl;

  //create map
  GridWithWeights grid(width, height);
  while(fptr>>value){
    if (value==0){
      //add wall
      grid.walls.insert(SquareGrid::Location {count%width, count/width});
    }
    count++;
  }
  fptr.close();

  // GridWithWeights grid = make_diagram4();
  SquareGrid::Location start{150, 10};
  SquareGrid::Location goal{180, 310};
  unordered_map<SquareGrid::Location, SquareGrid::Location> came_from;
  unordered_map<SquareGrid::Location, double> cost_so_far;
  a_star_search(grid, start, goal, came_from, cost_so_far);
  // draw_grid(grid, 2, nullptr, &came_from);
  // std::cout << std::endl;
  // draw_grid(grid, 3, &cost_so_far, nullptr);
  // std::cout << std::endl;
  vector<SquareGrid::Location> path = reconstruct_path(start, goal, came_from);
  draw_grid(grid, 3, nullptr, nullptr, &path);
  return 0;
}
