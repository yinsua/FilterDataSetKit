typedef struct ImageData{
    const int eachReadNum = 600;
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

typedef struct SaveItem{
    vector<int> countEachNum;
    int currentIterNum;
}_saveItem;

_saveItem GSaveItem;

#define _FILE_NAME ".filterDataSetKit.xml"
#define _KEY_VALUE_q 1048689
#define _KEY_VALUE_ESC 1048603