
// the setup function runs once when you press reset or power the board

  bool light01 = false;
  bool light02 = false;
  bool light03 = false;
  bool light04 = false;

  //直前までの値を入れる,それと変化したらokしてあげる
  int beforeNum = 0;
  int nowtimeNum = 0;

void setup() {
  Serial.begin(9600);
  
  // initialize digital pin 4-13 as an output.
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);


}

// the loop function runs over and over again forever
void loop() {
  int i=0;

  //processingから受け取った値に沿って光をつけるようにする
Serial.print(Serial.read());
Serial.print("\n");

  if(Serial.available()>0){
Serial.print("------------");

nowtimeNum = Serial.read();

   if(nowtimeNum != beforeNum){
      switch(nowtimeNum){
      
      case 11:
        if(light01 == false){
          digitalWrite(4, HIGH);
          light01 = true;
        }
        break;
      case 111:
        if(light01 == true){
          digitalWrite(4, LOW);
          light01 = false;
        }
        break;
        
      case 22:
        if(light02 == false){
          digitalWrite(5, HIGH);
          light02 = true;
        }
        break;
      case 222:
        if(light02 == true){
          digitalWrite(5, LOW);
          light02 = false;
        }
        break;

      case 33:
        if(light03 == false){
          digitalWrite(6, HIGH);
          light03 = true;
        }
        break;
      case 34:
        if(light03 == true){
          digitalWrite(6, LOW);
          light03 = false;
        }
        break;

      case 44:
        if(light04 == false){
          digitalWrite(7, HIGH);
          light04 = true;
        }
        break;
      case 45:
        if(light04 == true){
          digitalWrite(7, LOW);
          light04 = false;
        }
        break;
        
        default:
        Serial.print("----------");
        Serial.print(light01);
        Serial.print(light02);
        Serial.print(light03);
        Serial.print(light04);
        Serial.print("----------");
        break;
        beforeNum = nowtimeNum;
    }
    
  }
    
  }

//  //1つずつ順番に点灯
//  singleOn();
//  
//  //2つずつ順番に点灯
//  doubleOn();
//  
//  //1つずつ増やして減らす
//  wave();
//
//  //3つずつ光らせる
//  tripleOn();
//  tripleOn();
//  tripleOn();
//
//  //半分ずつ光らせる
//  halfOn();

  //全体点滅
//  blinkAll(2000);

//  //caution!
//  blinkAll(500);
//  blinkAll(500);
//
//  //danger!
//  blinkAll(250);
//  blinkAll(250);
//  blinkAll(250);
//  blinkAll(250);
//
//  blinkAll(125);
//  blinkAll(125);
//  blinkAll(125);
//  blinkAll(125);
//  
//  blinkAll(50);
//  blinkAll(50);
//  blinkAll(50);
//  blinkAll(50);
  
}


void singleOn() {
  for(int i=4;i<14;i++){
    if(i>4){
      digitalWrite(i-1, LOW);
    }
    digitalWrite(i, HIGH);
    Serial.println(i);
    delay(1000);
  }
  digitalWrite(13, LOW);
}

void doubleOn() {
  for(int i=4;i<14-1;i+=2){
    if(i>5){
      digitalWrite(i-1, LOW);
      digitalWrite(i-2, LOW);
    }
    digitalWrite(i, HIGH);
    digitalWrite(i+1, HIGH);
    Serial.print(i);
    Serial.print(",");
    Serial.println(i+1);
    delay(1000);
  }
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void tripleOn(){
  for(int i=4;i<14-2;i+=3){
    if(i>6){
      digitalWrite(i-1, LOW);
      digitalWrite(i-2, LOW);
      digitalWrite(i-3, LOW);
    }
    digitalWrite(i, HIGH);
    digitalWrite(i+1, HIGH);
    digitalWrite(i+2, HIGH);
    Serial.print(i);
    Serial.print(",");
    Serial.print(i+1);
    Serial.print(",");
    Serial.println(i+2);
    delay(1000);
  }
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void wave() {
  for(int i=4;i<14;i++){
    digitalWrite(i, HIGH);
    Serial.print(i);
    if(i<13){
      Serial.print(",");
    } else {
      Serial.println("");
    }
    delay(1000);
  }
  for(int i=4;i<14;i++){
    digitalWrite(i, LOW);
    Serial.print(i);
    if(i<13){
      Serial.print(",");
    } else {
      Serial.println("");
    }
    delay(1000);
  }
}

void halfOn() {
  for(int i=0; i<5; i++){
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    Serial.println("left");
    delay(1000);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);

    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    Serial.println("right");
    delay(1000);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
}

void blinkAll(int delayTime){
  for(int i=0; i<5; i++){
    for(int j=4; j<14; j++){
      digitalWrite(j, HIGH);
    }
    Serial.println("All on");
    delay(delayTime);
    for(int j=4; j<14; j++){
      digitalWrite(j, LOW);
    }
    Serial.println("All off");
    delay(delayTime);
  }
}

