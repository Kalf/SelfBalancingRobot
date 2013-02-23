// Robot Control System
// K-F Johansson, H. Sandström
// 2013-02-10

//Constants
const int BACKWARDS = 0;
const int FORWARDS = 1;
const int MOTOR_RIGHT = 13;
const int MOTOR_LEFT = 12;
const int BALANCED_VALUE = 517;

//Pin configuration motor
int motor_right_Speed = 11;     // sp B
int motor_left_Speed = 10;      // sp A
int motor_right_dir = 13;       // dir B
int motor_left_dir = 12;        // dir A

// Pin configuration accelerometer
int acc_x_pin = 0;
int acc_y_pin = 1;
int acc_x_value = 0;
int acc_y_value = 0;

// Acceloremeter mean value
int mean_value = 0;


void setup() {
  pinMode(motor_right_Speed, OUTPUT);
  pinMode(motor_left_Speed, OUTPUT);
  pinMode(motor_right_dir, OUTPUT);
  pinMode(motor_left_dir, OUTPUT);
 
  // Set the reference to 3.3V
  analogReference(EXTERNAL);
  //mean_value = calc_mean_value(50);
 
  //debug
  /*
  Serial.begin(9600);
  Serial.println("Init debug sequence...");
  Serial.println("=====================================");
  Serial.print("Mean value=");
  Serial.println(mean_value);
  Serial.println("=====================================");
  */
}

void loop()
{
  acc_y_value = analogRead(acc_y_pin);
  
  digitalWrite(motor_right_dir, HIGH);
  digitalWrite(motor_left_dir, HIGH);
  
  /*
  if(acc_y_value > BALANCED_VALUE)
  {
    motorspeed(MOTOR_RIGHT, 100,  FORWARDS);
    motorspeed(MOTOR_LEFT, 100, FORWARDS);
    Serial.print("BIGGER than reference!");
  }
  else if(acc_y_value < BALANCED_VALUE)
  {
    motorspeed(MOTOR_RIGHT, 100,  BACKWARDS);
    motorspeed(MOTOR_LEFT, 100, BACKWARDS);
    Serial.print("SMALLER than reference!");
  }
  else
  {
    motorspeed(MOTOR_RIGHT, 0,  BACKWARDS);
    motorspeed(MOTOR_LEFT, 0, BACKWARDS);
    Serial.print("SAME as reference.");
  }
  */
  
  Serial.println("");
  Serial.print("Y=");
  Serial.println(acc_y_value);
}

void motorspeed(int motor, int speed_percent, int dir)
{
  //Set direction
  if(dir == FORWARDS)
  {
    if(motor == MOTOR_RIGHT)
    {
      digitalWrite(motor_right_dir, HIGH);
    } 
    else
    {
      digitalWrite(motor_left_dir, HIGH);
    }
  }
  else
  {
    if(motor == MOTOR_RIGHT)
    {
      digitalWrite(motor_right_dir, LOW);
    } 
    else
    {
      digitalWrite(motor_left_dir, LOW);
    }
  }
 
  //Set speed
  //0-100 till 0-255
  int Speed = (255/100)*speed_percent;
   
  if(motor == MOTOR_RIGHT)
    {
      analogWrite(motor_right_Speed, Speed);
    } 
    else
    {
      analogWrite(motor_left_Speed, Speed);
    }
 
}

// Calculate mean value
int calc_mean_value(int max_samples)
{
  int samples = 0;
  int total_value = 0;
 
  while(samples < max_samples)
  {
    acc_x_value = analogRead(acc_x_pin);
    total_value += acc_x_value;
    samples++;
  }
 
  return (total_value / samples);
}
