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
#include <fstream>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/contrib/contrib.hpp>

#include "main.hpp"

using namespace std;
using namespace cv;

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
    // TODO : if the file of in <path> dir don't change, so the vector of files is same 
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
write_saveItem(int num,vector<int> countNum,string filename = _FILE_NAME){
    FileStorage fs(filename, FileStorage::WRITE);
    fs << "IterNum" << num;
    fs << "CountNum" << countNum;
    fs.release();
}

void
read_saveItem(string filename = _FILE_NAME){
    int iterNum=0;
    vector<int> countNum(10,0);
    FileStorage fs;
    fs.open(filename, FileStorage::READ);
    if(fs.isOpened()){
        fs["IterNum"] >> iterNum;
        vector<int> temp;
        fs["CountNum"] >> temp;
        if(temp.empty()){            
            write_saveItem(iterNum,countNum);
        }
        else{
            countNum = temp;
        }   
        fs.release();
    }
    else{
        write_saveItem(iterNum,countNum);
    }
    GSaveItem.currentIterNum = iterNum;
    GSaveItem.countEachNum = countNum;
}

void
keyValueHandle(string path,int key){
    // combine two file shell (cover dst file) : 
    // cat src1.txt src2.txt > dst.txt
    // combine two file shell (add to end of dst file) : 
    // cat src1.txt src2.txt >> dst.txt
    if(key == -1) return;
    static vector<string> tempSave;    

    map<int,string> numArray = {
                                {1114032,"0"},{1114033,"1"},
                                {1114034,"2"},{1114035,"3"},
                                {1114036,"4"},{1114037,"5"},
                                {1114038,"6"},{1114039,"7"},
                                {1114040,"8"},{1114041,"9"}
                            };
    if(numArray.find(key) != numArray.end()){
        //cout<<"Key Value : "<<numArray[key]<<endl;
        for( auto i : GImageName.tempBuf){
            string temp = i.first + " " + numArray[key] + "\n";
            tempSave.push_back(temp);
        }
        int num = (int)(numArray[key][0])-48;
        GSaveItem.countEachNum.at(num) += GImageName.tempBuf.size();
        GImageName.tempBuf.clear();
        // print
        {
            vector<int> x = GSaveItem.countEachNum;
            printf("Count : \n\t0: %d\n\t1: %d\n\t2: %d\n\t3: %d\n\t4: %d\n\t5: %d\n\t6: %d\n\t7: %d\n\t8: %d\n\t9: %d\n",
                    x.at(0),x.at(1),x.at(2),x.at(3),
                    x.at(4),x.at(5),x.at(6),x.at(7),
                    x.at(8),x.at(9)
                    );
        }        
    }
    else if(key == _KEY_VALUE_ESC/*<ESC>*/){
        // 1. save image name and the num of image what is called
        ofstream out(path,ios::out | ios::app);
        if(out.is_open()){
            for( auto i : tempSave){                
                out << i;
            }
            tempSave.clear();
            out.close();
        }
        else{
            cerr<<"Output TXT Open Failed!"<<endl;
            exit(1);
        }

        // 2. save count num and iter num
        GSaveItem.currentIterNum++;
        write_saveItem(GSaveItem.currentIterNum,GSaveItem.countEachNum);

    }
    else cerr<<"Unknow Key!"<<endl;
}

int 
main(int argc,char** argv){
    if (argc != 3) {
        cerr << "Usage: " << argv[0]
                << " <image/data/set/path>"
                << " <output/txt/file>" << std::endl;
        return 1;
    }
    string usageInfo =  "Key Map : \n"
                        "\t<ESC> : Next Page \n" 
                        "\t<q>   : Exit \n"
                        "\t[0~9] : Selected Image what is called \n"
                        ;
    cout<<usageInfo<<endl;
    string imgsPath = argv[1];
    string outputTxt = argv[2];

    vector<string> filenames = read_Filename(imgsPath);

    read_saveItem();

    string win_name = "imgVector (" + 
            to_string(GSaveItem.currentIterNum+1) + 
            "/" +
            to_string(filenames.size() / GImageData.eachReadNum + 1) +
            ")";
    string selectedImageWinName = "Selected Image";

    const int a=1,b=2;
    vector<string>::iterator it;
    it = filenames.begin();
    it += GSaveItem.currentIterNum*GImageData.eachReadNum;
    while(1)
    {
        vector<string> temp;
        if(filenames.end()-it <= 0){
            cout<<"IterNum : "<<GSaveItem.currentIterNum<<endl;
            cout<<"Finish!"<<endl;
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

        win_name = "imgVector (" + 
            to_string(GSaveItem.currentIterNum+1) + 
            "/" +
            to_string(filenames.size() / GImageData.eachReadNum + 1) +
            ")";

        destroyAllWindows();

        while (1){
            setMouseCallback(win_name,on_mouse,(void*)&a);
            setMouseCallback(selectedImageWinName,on_mouse,(void*)&b);
            groupEachImage(win_name,GImageData.currentGroupImage);            
            groupEachImage(selectedImageWinName,getData4Map(GImageName.tempBuf));
            int k = waitKey(33);
            if(k == _KEY_VALUE_q/*q*/) exit(1);
            else{
                keyValueHandle(outputTxt,k);
                if(k == _KEY_VALUE_ESC/*<ESC>*/) break;
            }
        }        
    }

    // clean up
    {        
        vector<int> temp(10,0);
        write_saveItem(0,temp);
    }
    
    return 0;
}