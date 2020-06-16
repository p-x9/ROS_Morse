#include <iostream>
#include <vector>
#include <cstdio>

#include "ros/ros.h"
#include "std_msgs/Int16MultiArray.h"

std::vector<std::vector<int>> codes = {
    // A -- Z
    {0, 1},       {1, 0, 0, 0}, {1, 0, 1, 0}, {1, 0, 0},    {0},
    {0, 0, 1, 0}, {1, 1, 0},    {0, 0, 0, 0}, {0, 0},       {0, 1, 1, 1},
    {1, 0, 1},    {0, 1, 0, 0}, {1, 1},       {1, 0},       {1, 1, 1},
    {0, 1, 1, 0}, {1, 1, 0, 1}, {0, 1, 0},    {0, 0, 0},    {1},
    {0, 0, 1},    {0, 0, 0, 1}, {0, 1, 1},    {1, 0, 0, 1}, {1, 0, 1, 1},
    {1, 1, 0, 0}, 

    // 0 -- 9
    {0, 1, 1, 1, 1}, {0, 0, 1, 1, 1}, {0, 0, 0, 1, 1}, {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 1, 0, 0, 0}, {1, 1, 1, 0, 0}, 
    {1, 1, 1, 1, 0}, {1, 1, 1, 1, 1}, 
 };

std::vector<int> converToMorse(int ch){
    int c = std::tolower(ch);
    int index = -1;
    if ('a' <= c && c <= 'z') {
      index = c - 'a';
    } else if ('0' <= c && c <= '9') {
      index = c - '0' + 26;
    } else if (' ' == c) {
        std::vector<int> vec{0};
      return vec;
    }
    return codes[index];
}



int main(int argc,char **argv){
    ros::init(argc,argv,"morse_publisher");
    ros::NodeHandle nh;

    ros::Publisher morse_pub = nh.advertise<std_msgs::Int16MultiArray>("morse",200);

    ros::Rate loop_rate(10);

    std_msgs::Int16MultiArray msg;

    while(ros::ok()){
        int c;
        msg.data.resize(0);
        while((c = std::getchar()) != 10) {
            std::vector<int> newnums;

        c = std::tolower(c);
        int index = -1;
        if ('a' <= c && c <= 'z') {
        index = c - 'a';
        } else if ('0' <= c && c <= '9') {
            index = c - '0' + 26;
         } else if (' ' == c) {
            std::vector<int> vec{0};
              newnums = vec;
         }
        // if(index <= 0)continue;
        newnums = codes[index];

           //std::copy(newnums.begin(),newnums.end(),std::back_inserter(msg.data));
           
           msg.data.insert(msg.data.end(),newnums.begin(),newnums.end());
           std::vector<int> vec{2};
            msg.data.insert(msg.data.end(),vec.begin(),vec.end());
           //msg.data.resize(newnums.size());
           
           /*for(int i=0;i<newnums.size();i++){
               msg.data[i] = newnums[i];
           }*/
           
        }
        morse_pub.publish(msg);
    }
    return 0;
}

