/*
*   Filter Data Set Kit
*   yinsua -- 20170609
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <assert.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>

using namespace std;
using namespace cv;

typedef struct ImageData{
    const int eachReadNum = 60;
    vector<Mat> currentGroupImage;    
    Mat cellImage;
    int colsNum = 30;
    int gap = 5;
    int read_Offset = 0;
}_imageData;

_imageData GImageData;

typedef struct ImagesFileName{
    vector<string> currentImageName;
    map<string,Mat> tempBuf;
    vector<string> displayContent;
}_imagesFileName;

_imagesFileName GImageName;

int 
getOrderByMousePoint(int x,int y){
    assert(x>=0 && y>=0);
    int returnValue = -1;
    int row=0,col=0;
    row = y%(GImageData.cellImage.rows+GImageData.gap) <= GImageData.cellImage.rows
            ? y/(GImageData.cellImage.rows+GImageData.gap)
            : -1
            ;
    col = x%(GImageData.cellImage.cols+GImageData.gap) <= GImageData.cellImage.cols
            ? x/(GImageData.cellImage.cols+GImageData.gap)
            : -1
            ;
    if(row >= 0 && col >= 0){
        returnValue = GImageData.colsNum*row+col;
        #if 0
        cout<< "row : " <<row<< " \t"
            << "col : " <<col<< " \t"
            << "Order : "<<returnValue<<endl;
        #endif
        
    }
    else cout<<"Error Mouse Point,Get No Image!"<<endl;
    return returnValue;
}

void 
on_mouse(int event,int x,int y,int flags,void *ustc)
{
    static Point pre_pt ;//初始坐标  
    static Point cur_pt ;//实时坐标  
    char temp[16];
    int win = *(int*)ustc;
    if (event == CV_EVENT_LBUTTONDOWN)
    {  
        // Currently only handles win == 1
        if(win != 1) return;

        sprintf(temp,"(%d,%d)",x,y);
        pre_pt = Point(x,y);
        int order = getOrderByMousePoint(x,y);
        int maxNum = win==1 ? GImageData.currentGroupImage.size() : GImageName.tempBuf.size();
        
        if(order>=0 && order< maxNum){
            
            string fileName_Order = GImageName.currentImageName.at(order);
            if(GImageName.tempBuf.find(fileName_Order) != GImageName.tempBuf.end()){
                
                return;
            }
            Mat &imgData_Order = GImageData.currentGroupImage.at(order);            
            GImageName.tempBuf[fileName_Order] = imgData_Order.clone();

            #if 0
                vector<Mat>::iterator pos = GImageData.currentGroupImage.begin()+order;
                GImageData.currentGroupImage.erase(pos);
            #else
                imgData_Order = Mat(imgData_Order.size(),imgData_Order.depth(),Scalar::all(255));
            #endif
        }
        
    }
    else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))
    {
        sprintf(temp,"(%d,%d)",x,y);  
        cur_pt = Point(x,y);
        //cout<<"X: "<<x<<"\t Y: "<<y<<endl;
    }
    else if (event == CV_EVENT_RBUTTONDOWN){
        sprintf(temp,"(%d,%d)",x,y);
        pre_pt = Point(x,y);
        int order = getOrderByMousePoint(x,y);
        int maxNum = win==1 ? GImageData.currentGroupImage.size() : GImageName.tempBuf.size();
        
        if(order>=0 && order< maxNum){
            if(win == 1){
                string fileName_Order = GImageName.currentImageName.at(order);
                if(GImageName.tempBuf.find(fileName_Order) != GImageName.tempBuf.end()){
                    // resume image from selected
                    GImageData.currentGroupImage.at(order) = GImageName.tempBuf[fileName_Order].clone();
                    GImageName.tempBuf.erase(fileName_Order);
                }
            }
            else if(win == 2){
                string selected = GImageName.displayContent.at(order);
                vector<string>::iterator it = find(
                        GImageName.currentImageName.begin(),
                        GImageName.currentImageName.end(),
                        selected
                    );
                int order1 = it-GImageName.currentImageName.begin();
                if(order1 >=0 && order1<GImageName.currentImageName.size()){
                    GImageData.currentGroupImage.at(order1) = GImageName.tempBuf[selected];
                    GImageName.tempBuf.erase(selected);
                }
                else cerr<<order1<<endl;
            }
        }
    }
}

Mat 
groupEachImage(string win_name,vector<Mat> src){
    if(src.empty()) {
        //cerr<<"Image Group Empty!"<<endl;
        destroyWindow(win_name);
        return Mat();
    }
    // TODO: Only support Gray Image
    assert(src.back().channels()==1);    
    int gap = GImageData.gap, colsNum = GImageData.colsNum;
    Mat totalImage = Mat(        
        (src.size()/colsNum+1)*(src.back().rows+gap)-gap,
        colsNum*(src.back().cols+gap)-gap,
        CV_8UC1,
        Scalar::all(255)
    );

    int currentCols=0;
    int currentRows=0;
    int num = 0;
    for( auto i : src){
        
        Rect roi(num*(i.cols+gap),currentRows*(i.rows+gap),i.cols,i.rows);
        Mat roiImage = totalImage(roi);
        i.copyTo(roiImage);
        num++;
        if(num%colsNum==0){
            currentRows++;
            num=0;
        }
    }    
    imshow(win_name,totalImage);
    return totalImage;
}

vector<Mat>
getData4Map(map<string,Mat> data){
    vector<Mat> temp;
    vector<string> temp1;
    for( auto i : data ){
        temp.push_back(i.second);
        temp1.push_back(i.first);
    }
    GImageName.displayContent=temp1;
    return temp;
}

vector<string> 
read_Filename(string path){
    assert(path.size()>2);
    
    Directory dir;
    vector<string> filenames = dir.GetListFiles(path);
    return filenames;
}

vector<Mat>
read_Data(string path,vector<string> filenames){
    assert(!filenames.empty());
    GImageName.currentImageName = filenames;
    vector<Mat> imgData;
    if(path[path.size()-2] != '/'){
        path += "/";
    }
    for ( auto i : filenames ){
        Mat temp=imread(path+i,CV_LOAD_IMAGE_GRAYSCALE);
        imgData.push_back(temp);
    }
    assert(!imgData.back().empty());
    return imgData;
}

void
keyValueHandle(int key){
    if(key != -1) return;
    map<int,int> numArray = {
                                {1114032,0},{1114033,1},
                                {1114034,2},{1114035,3},
                                {1114036,4},{1114037,5},
                                {1114038,6},{1114039,7},
                                {1114040,8},{1114041,9}
                            };
    if(numArray.find(key) != numArray.end()){
        //cout<<"Key Value : "<<numArray[key]<<endl;

    }
}

int 
main(int argc,char** argv){
    if (argc != 2) {
        cerr << "Usage: " << argv[0]                
                << "<image/data/set/path>" << std::endl;
        return 1;
    }
    string imgsPath = argv[1];

    string win_name = "imgVector";
    string selectedImageWinName = "Selected Image";
    
    vector<string> filenames = read_Filename(imgsPath);

    const int a=1,b=2;
    vector<string>::iterator it;
    it = filenames.begin();
    while(1)
    {        
        vector<string> temp;
        if(filenames.end()-it <= 0){
            break;
        }
        else if(filenames.end()-it<GImageData.eachReadNum){
            temp.assign(it,filenames.end());
            it = filenames.end();
        }
        else{
            temp.assign(it,it+GImageData.eachReadNum);
            it += GImageData.eachReadNum;
        }
        vector<Mat> imgVector = read_Data(imgsPath,temp);
        assert(!imgVector.empty());
        GImageData.currentGroupImage=imgVector;
        GImageData.cellImage=imgVector.back();
        while (1){
            setMouseCallback(win_name,on_mouse,(void*)&a);
            setMouseCallback(selectedImageWinName,on_mouse,(void*)&b);
            groupEachImage(win_name,GImageData.currentGroupImage);            
            groupEachImage(selectedImageWinName,getData4Map(GImageName.tempBuf));
            int k = waitKey(33);
            if(k == 1048603/*<ESC>*/) break;
            else if(k == 1048689/*q*/) exit(1);
            else keyValueHandle(k);
        }
    }

    return 0;
}