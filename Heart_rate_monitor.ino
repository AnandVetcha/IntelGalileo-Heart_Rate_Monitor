
int sensorPin = A0;    // Pin to which Heat beat Output is connected
int sensorValue = 0;   // Stores the valuse sensed by Analog input Pin
int processedValue = 0;
int Time_current = 0;
int Time_prev = 0;
int Flag1 = 1;
int Heartbeat = 0;
int Avg_Heartbeat = 0;
int LedRange = 0;

int SampleArray[5] = {0,0,0,0,0}; // Stores previous 5 heart beat measurments

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // initialize the led pin as an output.
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);   
  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  processedValue = constrain(sensorValue, 100, 800);
  
  if (processedValue == 800 && Flag1 == 1) {
    Time_prev = Time_current;
    Time_current = millis();
    Flag1 = 0;
    Heartbeat = 60*1000/(Time_current - Time_prev);
    Update_array(SampleArray,Heartbeat);
    Avg_Heartbeat = Avg_array(SampleArray);
        
    Serial.print("Avg Heat beat value:");
    Serial.println(Avg_Heartbeat);
    
    LedRange = constrain(map(Avg_Heartbeat,70,150,3,7),1,7);
    LedIndicator(LedRange);
  }
  if (processedValue == 100 && Flag1 == 0) {
    Flag1 = 1;
  }  
}

//Led Indicator
void LedIndicator(int value) {
  switch (value) {
      case 1:
        digitalWrite(1, HIGH);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 2:
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 3:
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 4:
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 5:
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        break;
      case 6:
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
        break;
      case 7:
        digitalWrite(1, HIGH);
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        break;
      default:
        digitalWrite(1, LOW);
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
  }
}

//Update Sample Array
void Update_array(int* array,int Value) {
  int i;
  for (i = 4 ; i > 0; i = i - 1) {
    array[i] = array[i-1];
  }
  array[0] = Value;  
}

// Function to return the avg of the contents of the array
int Avg_array(int* array){
  int i;
  int sum = 0;
  int avg = 0;
  for (i = 0; i < 5; i = i + 1) {
    sum = sum + array[i];
  }
  avg = sum/5;
  return avg;
} 
