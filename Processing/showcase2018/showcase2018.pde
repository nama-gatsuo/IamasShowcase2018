import processing.serial.*;

import netP5.*;
import oscP5.*;
Serial myPort;

OscP5 oscP5;
NetAddress myRemoteLocation;
 
 int receivePort = 12345;
 
//String mode = ;

boolean light1 = false;
boolean light2 = false;
boolean light3 = false;
boolean light4 = false;

 
void setup() {
  size(100,100);
  background(128, 168, 199);
  myPort = new Serial(this,Serial.list()[3],9600);
  
  print(Serial.list()[3]);
  oscP5 = new OscP5(this,receivePort);//ポート番号は受信側で設定したものを同じにする
  
  myRemoteLocation = new NetAddress("127.0.0.1",6230);
  
}
 
 
void draw() {

  
}
 

void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());

  theOscMessage.print();
    println(theOscMessage.get(0).intValue());
    
   //if(theOscMessage.addrPattern() == "/light/")
  
  if(theOscMessage.get(0).intValue() == 0 ){
    if (light1 == false){
        myPort.write(11);
        light1 = true;
    }else if (light1 == true){
        myPort.write(111);
        light1 = false;
    }
    print("1hoge");
}else if(theOscMessage.get(0).intValue() == 1){
    if (light2 == false){
        myPort.write(22);
        light2 = true;
    }else if (light2 == true){
        myPort.write(222);
        light2 = false;
    }
   print("2hoge");
}else if(theOscMessage.get(0).intValue() == 2){
     if (light3 == false){
        myPort.write(33);
        light3 = true;
    }else if (light3 == true){
        myPort.write(34);
        light3 = false;
    }
   print("3hoge");
}else if(theOscMessage.get(0).intValue() == 3){
     if (light4 == false){
        myPort.write(44);
        light4 = true;
    }else if (light4 == true){
        myPort.write(45);
        light4 = false;
    }
   print("4hoge");
}
}