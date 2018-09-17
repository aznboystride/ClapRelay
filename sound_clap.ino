#define sound_sensor 3;
#define led 7;

int num_of_clap = 0;

long detection_range_start = 0;
long detection_range = 0;

boolean status_lights = false;

void setup() {
  Serial.begin(9600);
  pinMode(sound_sensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int status_sensor = digitalRead(sound_sensor);
  if (status_sensor == 0)
  {
      if(num_of_clap == 0)
      {
         detection_range_start = detection_range = millis();
         num_of_clap++;
      }
      else if(num_of_clap > 0 && millis() - detection_range >= 50)
      {
        detection_range = millis();
        num_of_clap++;
      }
  }
  if(millis() - detection_range_start >= 400)
  {
    if(num_of_clap == 2)
    {
      if(!status_lights)
      {
        status_lights = true;
        digitalWrite(led, HIGH);
      }
      else if(status_lights)
      {
        status_lights = false;
        digitalWrite(led, LOW);
      }
    }
    num_of_clap = 0;
  }
  Serial.println(num_of_clap);
}
