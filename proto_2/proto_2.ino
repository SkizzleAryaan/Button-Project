
#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"
//TMRpcm  tmrpcm;
TMRpcm  audio;
const int buttonPin = 2; //Speaker buttons
const int buttonPin2 = 4; 
const int buttonPin3 = 3; //Record buttons
const int buttonPin4 = 5;  

//Record audio
int file_number = 0;
char filePrefixname[50] = "test";
int file_number2 = 0;
char filePrefixname2[50] = "thing";

char exten[10] = ".wav";
const int mic_pin = A0;
const int sample_rate = 16000;

#define SD_CSPin 10 // defines the CS pin of the SD card.
// delay function for serial log.
void wait_sec(int sec) {
  int count = 0;
  int secs = sec;
  while (1) {
            Serial.print('.');
            delay(1000);
            count++;
            if (count == secs) {
            count = 0;
            break;
            }
  }
  Serial.println();
  return ;
}

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT);  
  pinMode(buttonPin3, INPUT); 
  pinMode(buttonPin4, INPUT); 
  pinMode(mic_pin, INPUT);
  
  Serial.println("ready");
  audio.speakerPin=9;
  Serial.println("begin");
  Serial.begin(9600);
  if(!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  }
  while (!SD.begin(SD_CSPin)) {
            Serial.print(".");
            delay(500);
  }
  audio.CSPin = SD_ChipSelectPin;
  
  audio.setVolume(6);

}

void loop() 
{
    //file_number++;
  //file_number2++;
    //Serial.println("Create file"); 
    char fileSlNum[20] = "";
    itoa(file_number, fileSlNum, 10);
    char file_name[50] = "";
    strcat(file_name, filePrefixname);
    strcat(file_name, fileSlNum);
    strcat(file_name, exten);

    char fileS2Num[20] = "";
    itoa(file_number2, fileS2Num, 10); 
    char file_name2[50] = "";
    strcat(file_name2, filePrefixname2);
    strcat(file_name2, fileS2Num);
    strcat(file_name2, exten);
    
    if (digitalRead(buttonPin3) == HIGH)
    {   
      if (digitalRead(buttonPin) == HIGH)
      {
        Serial.println("Start recording");
        audio.startRecording(file_name, sample_rate, mic_pin);
        wait_sec(5); 
        Serial.println(file_name);
        Serial.println("End recordin2g");
        audio.stopRecording(file_name);      
      }
      else if (digitalRead(buttonPin2) == HIGH)
      {
        Serial.println("Start recording2");
        audio.startRecording(file_name2, sample_rate, mic_pin);
        wait_sec(5); 
        Serial.println(file_name2);
        Serial.println("End recording2");
        audio.stopRecording(file_name2); 
      }     
    }
    
      
  
  if (digitalRead(buttonPin) == HIGH && digitalRead(buttonPin3) == LOW) 
  {   
    Serial.println("button 1 pressed");

    Serial.println(file_name);
     audio.play(file_name);
     delay(7500); 
     audio.stopPlayback();
  }
  if (digitalRead(buttonPin2) == HIGH && digitalRead(buttonPin3) == LOW)
  {
    Serial.println("button 2 pressed");
    Serial.println(file_name2);
    audio.play(file_name2);
    delay(7500); 
    audio.stopPlayback(); 
  }

}
