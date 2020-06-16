
//#include <ArduinoSTL.h>
//#include <vector>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/Int16MultiArray.h>

#define LED 13
#define BUZZER 9

ros::NodeHandle nh;

void messageHandler(const std_msgs::Int16MultiArray& array){
    
    int num = array.data_length;
    int frequency = 300;

    char result[2];
    sprintf(result,"%d",num);
    nh.loginfo(result);
   
    for (int i=0;i<num;i++){
         char test[2];
    sprintf(test,"%d",array.data[i]);
    nh.loginfo(test);
        switch(array.data[i]){
            case 2:
            delay(200);
            break;
            case 0:
            digitalWrite(LED,HIGH);
            tone(BUZZER,frequency);
            delay(100);
            break;
            case 1:
            digitalWrite(LED,HIGH);
            tone(BUZZER,frequency);
            delay(300);
            break;
        
        }
        digitalWrite(LED,LOW);
       noTone(BUZZER);
        delay(100);
    }
    
}

ros::Subscriber<std_msgs::Int16MultiArray> sub("morse",&messageHandler);

void setup(){
    pinMode(LED,OUTPUT);
    pinMode(BUZZER,OUTPUT);

    //digitalWrite(LED,HIGH);
    nh.initNode();
    nh.subscribe(sub);
    //Serial.begin(57600);
}
void loop(){
    nh.spinOnce();
}