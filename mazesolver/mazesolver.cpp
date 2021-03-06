#include "opencv2/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"


// #include "implementation.cpp"
#include "hjk_astar.c"
using namespace cv;
using namespace std;

enum STATUS_T
{
    INIT,
    CAM_SHOW,
    CAM_PAUSE,
    SELECT_ROI,
    SELECT_POINT,
    SOLVE,
    SAVE,
    EXIT
};

typedef struct 
{
    Mat src;
    Mat dst;
}MAT_IO_t;


Mat webcam_frame;
Mat pause_img;
int key_input;
STATUS_T myStatus=INIT;
STATUS_T selectStatus = SELECT_ROI;
std::vector<Point> point_v;
std::vector<Point> startAndend_v;

bool imshow_flag = false;

void COLOR2BIN(Mat src, Mat& dst, int threshold_value);
void COLOR2BIN_cb(int, void*);
void mouse_cb(int event, int x, int y, int flags, void* userdata);

void COLOR2BIN_cb(int threshold, void* userdata){
    MAT_IO_t temp = *((MAT_IO_t*)userdata);
    COLOR2BIN(temp.src, temp.dst, threshold);
}


void COLOR2BIN(Mat src, Mat& dst, int threshold_value)
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
     threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)
   */
    Mat temp;
    cvtColor(src, temp, COLOR_BGR2GRAY);
    threshold(temp, dst, threshold_value, 255,0);
}

template <class T>
void update_state(T current_state){
    static T last_state = current_state;
    if (current_state != last_state){
        cout<<"Now in "<<current_state<<" state."<<endl;
        last_state = current_state;
    }
}

void mouse_cb(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) { // Left mouse button pressed
        if (selectStatus == SELECT_ROI){
            point_v.push_back(Point(x,y));
            cout<<"Added new ROI point"<<endl;
            imshow_flag = false;
            // cout<<"There are: "<<point_v.size()<<" points in point_v"<<endl;
        }else if(selectStatus == SELECT_POINT && startAndend_v.size()<2){
            startAndend_v.push_back(Point(x,y));
            cout<<"Added new start/end point"<<endl;
            imshow_flag = false;
        }
        // square[imark%4] = Point(x,y);
        // if (imark>0 && (imark+1) %4 ==0){
        //     int npts[] = {4};
        //     square_v.push_back(square);
        //     polylines(img, &square, npts, 1, true, Scalar(0,0,0));
        // }
        // circle(img, Point(x, y), 4, Scalar(0,0,255), 2);
        // imark++;// Increment the number of marks
        // sprintf(textm, "mark %d", imark);// Set the mark text
        // putText(img, textm, Point(x+6, y), FONT_HERSHEY_PLAIN,
        //                 1, Scalar(0,0,0),2);
        // imshow(IN_WIN, img); // Show final image
    }
    return;
}

void solve_maze(Mat& in_img, Point in_start, Point in_stop, std::vector<Point> POI){
    Size imgsize = in_img.size();

    int i=0,j=0,count=0;

    // find boundary of POI
    int left_x=imgsize.width, right_x=0, up_y=imgsize.height, down_y=0;
    for (i=0;i<POI.size();i++){
        if (POI[i].x<left_x){
            left_x = POI[i].x;
        }
        if (POI[i].x>right_x){
            right_x = POI[i].x;
        }
        if (POI[i].y<up_y){
            up_y = POI[i].y;
        }
        if (POI[i].y>down_y){
            down_y = POI[i].y;
        }
    }

    printf("The boundary is: (%d, %d), (%d, %d)\n", left_x, up_y, right_x, down_y);
    printf("The type of Mat is: %d\n", in_img.type()==CV_8U? 1:0 );
    int map[(right_x-left_x)*(down_y-up_y)];
    for(j=up_y;j<down_y;j++){
        for (i=left_x;i<right_x;i++){
            map[count] = (int)in_img.at<uint8_t>(j,i);
            printf("%d ", map[count]);
            count++;
        }
        // printf("\n");
        
    }

    Location2D_t route[(right_x-left_x)*(down_y-up_y)];
    int route_len=0;

    Location2D_t start;
    start.x = in_start.x-left_x+1;
    start.y = in_start.y-up_y+1;
    Location2D_t stop;
    stop.x = in_stop.x-left_x-1;
    stop.y = in_stop.y-up_y-1;

    printf("The sent mat size is %d*%d\n",right_x-left_x, down_y-up_y );
    A_star(map, right_x-left_x, down_y-up_y, route, &route_len, start, stop);

    i=0;
    for (i=route_len-1;i>=0;i--){
        // printf("(%d,%d)->", route[i].x, route[i].y);
        circle(in_img, Point(route[i].x+left_x, route[i].y+up_y), 1, Scalar(0,0,0), 1);
    }


    // vector<Point> tempptr;
    // vector<vector<Point> > temp_ptrptr;
    // int _x, _y;
    // for(int i=0;i<path.size()-1;i++){
    //     tie (_x,_y) = path[i];
    //     tempptr.push_back(Point(_x,_y));
    // }
    // temp_ptrptr.clear();
    // temp_ptrptr.push_back(tempptr);
    // polylines(in_img, temp_ptrptr, true, Scalar(0,255,0),5);

}

int main(int, char**)
{
    int cam_num=0;
    VideoCapture cap(cam_num); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow("MazeSolver",WINDOW_AUTOSIZE);



    int default_threshold = 100;
    char dummyText[]="dummyText";
    int last_track = default_threshold;
    vector<vector<Point> > point_ptr;
    


    cap>>webcam_frame;
    cout<<"The depth of webcam_frame is: "<<webcam_frame.depth()<<endl;
    cout<<"The type of webcam_frame is: "<<webcam_frame.type()<<endl;

    for(;;)
    {
        switch(myStatus){
            case INIT:
                myStatus = CAM_SHOW;
                break;
            case CAM_SHOW:
                // cout<<"Im at CAM_SHOW"<<endl;
                cap >> webcam_frame;
                imshow("MazeSolver", webcam_frame);
                key_input = waitKey(30);
                switch (key_input){
                    case 'q':
                        myStatus = EXIT;
                        break;
                    case 32:
                        // space key
                        myStatus = CAM_PAUSE;
                        break;
                    default:
                        break;
                }
                break;
            case CAM_PAUSE:
                // cout<<"Im at CAM_PAUSE"<<endl;
                if (!imshow_flag){
                    // if no change, just jump over, to save power
                    if (!imshow_flag){
                    setMouseCallback("MazeSolver", mouse_cb, NULL);
                    COLOR2BIN(webcam_frame, pause_img, default_threshold);
                    imshow("MazeSolver", pause_img);
                    createTrackbar("Threashold", "MazeSolver", &default_threshold, 255);
                    imshow_flag = true;
                    }

                    COLOR2BIN(webcam_frame, pause_img, last_track);
                    // cvtColor(webcam_frame, pause_img, COLOR_BGR2GRAY);


                    point_ptr.clear();
                    point_ptr.push_back(point_v); 
                    if (point_v.size()>1){
                        polylines(pause_img, point_ptr, true, Scalar(0,0,0),10);
                    }

                    if(startAndend_v.size()>0){
                        circle(pause_img, startAndend_v[0], 1, Scalar(0,0,0), 1);
                        sprintf(dummyText, "Start");// Set the mark text
                        putText(pause_img, dummyText, Point(startAndend_v[0].x+6, startAndend_v[0].y), FONT_HERSHEY_PLAIN,
                            1, Scalar(0,0,0),2);
                    }
                    if(startAndend_v.size()>1){
                        circle(pause_img, startAndend_v[1], 1, Scalar(0,0,0), 1);
                        sprintf(dummyText, "END");// Set the mark text
                        putText(pause_img, dummyText, Point(startAndend_v[1].x+6, startAndend_v[1].y), FONT_HERSHEY_PLAIN,
                            1, Scalar(0,0,0),2);
                    }

                    imshow("MazeSolver", pause_img);
                }

                if (last_track != getTrackbarPos("Threashold", "MazeSolver")){
                    imshow_flag = false;
                    last_track = getTrackbarPos("Threashold", "MazeSolver");
                }
                
            
                key_input = waitKey(30);
                switch (key_input){
                    case 'q':
                        myStatus = EXIT;
                        break;
                    case 32:
                        // space key
                        point_v.clear();
                        startAndend_v.clear();
                        destroyWindow("MazeSolver");
                        imshow_flag = false;
                        myStatus = CAM_SHOW;
                        break;
                    case 'r':
                        point_v.clear();
                        startAndend_v.clear();
                        imshow_flag = false;
                        selectStatus = SELECT_ROI;
                        cout<<"selectStatus changed to SELECT_ROI"<<endl;
                        break;
                    case 's':
                        // selectmode toggle key
                        if (selectStatus == SELECT_POINT){
                            selectStatus = SELECT_ROI;
                        }else{
                            selectStatus = SELECT_POINT;
                        }
                        cout<<"selectStatus changed to SELECT_POINT"<<endl;
                        imshow_flag = false;
                        break;
                    case 13:
                        // enter key, to slove the maze
                        myStatus = SOLVE;
                        break;

                    default:
                        myStatus = CAM_PAUSE;
                }
                // goto select_roi

            case SELECT_ROI:
                break;
            case SELECT_POINT:
                break;
            case SOLVE:
                // print mat
                solve_maze(pause_img, startAndend_v[0], startAndend_v[1], point_v);
                imshow("MazeSolver", pause_img);
                selectStatus = SELECT_ROI;
                myStatus = CAM_PAUSE;
                break;
            case SAVE:
                break;
            case EXIT:
                cap.release();
                return 0;
                break;
            default:
                break;
            }
            update_state(myStatus);

    }


    // for(;;)
    // {
    //     Mat frame;
    //     cap >> frame; // get a new frame from camera
    //     cvtColor(frame, edges, COLOR_BGR2GRAY);
    //     imshow("Raw", frame);
    //     GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    //     Canny(edges, edges, 0, 30, 3);
    //     imshow("edges", edges);
    //     if(waitKey(30) >= 0) break;
    // }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}