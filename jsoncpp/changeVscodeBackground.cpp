#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include "json/json.h"
#include "jsoncpp.cpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::to_string;

string jsonPath="C://Users//Administrator.USER-20200927FP//AppData//Roaming//Code//User//settings.json";//vscode的全局settings.json的位置

void parseJson(int &i){
    Json::CharReaderBuilder b;
    b["collectComments"] = true;
    Json::Value root;
    JSONCPP_STRING errs;

    ifstream ifs(jsonPath);
    if(!ifs.good()){
        cout << "open failed" << endl;
    }

    if(!Json::parseFromStream(b,ifs,&root,&errs)){
        cout << errs << endl;
        return;
    }

    if(i<=0||i>=36){//一轮图片循环完了
        i = 1;
    }

    string picPath = root["background.customImages"][0].asString();
    cout << "picPath = " << picPath << endl;
    char newPath[64]={0};
    ::sprintf(newPath, "file:///F:/vscodebackground/%d.png", i);//拼接图片路径字符串，具体看settings.json里的格式
    i++;//转到下一张
    cout << "newPath = " << newPath << " , i = " << i << endl;
    root["background.customImages"][0] = newPath;

    ofstream ofs(jsonPath);
    Json::StreamWriterBuilder writerBuilder;
    Json::StreamWriter *writer(writerBuilder.newStreamWriter());
    writer->write(root,&ofs);

    ifs.close();
    ofs.close();
}


int main(int argc,char **argv){
    int startNum=1, sleepSecond=10;//默认从1开始，间隔10秒切换一次
    if(argc!=3){
        cout<<"error : changeVscodeBackground.exe   开始的图片id    刷新时间"<<endl;
    }else{
        startNum = atoi(argv[1]);
        sleepSecond = atoi(argv[2]);
    }

    while(1){
        parseJson(startNum);
        cout << "change successful" << endl;
        ::_sleep(1000 * sleepSecond); //每sleepsecond秒更换一次
    }
    return 0;
}