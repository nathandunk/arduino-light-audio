//Libraries
#include <Adafruit_NeoPixel.h>  //Library to simplify interacting with the LED strand
#include <math.h>
#ifdef __AVR__
#include <avr/power.h>   //Includes the library for power reduction registers if your chip supports them. 
#endif                   //More info: http://www.nongnu.org/avr-libc/user-manual/group__avr__power.htlm

//Constants (change these as necessary)
#define LED_PIN        6  //Pin for the pixel strand. Does not have to be analog.
#define LED_TOTAL      50  //Change this to the number of LEDs in your strand.
#define AUDIO_PIN      A1  //Pin for the envelope of the sound detector
#define KNOB_PIN       A0  //Pin for the trimpot 10K
#define SCALE_LOW_PIN  A2 // pin for trimpot
#define SCALE_HIGH_PIN A3 // Pin for 

//Low pass butterworth filter order=1 alpha1=0.033333333333333 
class  FilterBuLp1
{
  public:
    FilterBuLp1()
    {
      v[0]=v[1]=0.0;
    }
  private:
    float v[2];
  public:
    float step(float x) //class II 
    {
      v[0] = v[1];
      v[1] = (9.510798340249641825e-2 * x)
         + (0.80978403319500713575 * v[0]);
      return 
         (v[0] + v[1]);
    }
};

Adafruit_NeoPixel strand = Adafruit_NeoPixel(LED_TOTAL, LED_PIN, NEO_RBG + NEO_KHZ800);  //LED strand objetc

int gradient = 0; //Used to iterate and loop through each color palette gradually

int num_values = 3;

int recent_volumes[] = {0, 0, 0};
int max_val = 0;

int num_samples = 0;

int volume = 0;    //Holds the volume level read from the sound detector.
int last = 0;      //Holds the value of volume from the previous loop() pass.

double maxVol = 15;     //Holds the largest volume recorded thus far to proportionally adjust the visual's responsiveness.
double knob = 1023.0;   //Holds the percentage of how twisted the trimpot is. Used for adjusting the max brightness.
float avgVol = 0;      //Holds the "average" volume-level to proportionally adjust the visual experience.
float avgBump = 0;     //Holds the "average" volume-change to trigger a "bump."

bool bump = false;     //Used to pass if there was a "bump" in volume

bool switch_order = false;

double curr_t_sec;
double curr_t_sec_last;

double scaled_volume = 0;
double scaled_volume_last = 0;

long long int last_t = 0;
long long int curr_t = 0;
long long int period = 0;

int total_colors = 0;

double time_scale = 20.0;
const int num_colors = 4;

int colors[num_colors][3] = {{255, 30, 30}, // Red
                             { 51,204,255}, // Blue
                             {  0,255, 30}, // Green
                             {255,255,255}};// White

//int colors[num_colors][3] = {{249,110, 70}, // orange
//                             { 77,170, 87}, // green
//                             {249,200, 70},  // yellow
//                             {118,190,208}};// blue

//int colors[num_colors][3] = {{249, 65, 68}, 
//                             {243,114, 44}, 
//                             {244,150, 30}, 
//                             {249,199, 79},
//                             {144,190,109},
//                             { 67,170,139},
//                             { 87,117,144}};

int last_color[3];
int current_color[3];

int use_color[3];

FilterBuLp1 filter;

void setup() {    //Like it's named, this gets ran before any other function.

  memcpy(last_color, colors[num_colors-1], sizeof(last_color));
  memcpy(current_color, colors[0], sizeof(last_color));

  Serial.begin(115200); //Sets data rate for serial data transmission.

  strand.begin(); //Initialize the LED strand object.
  strand.fill(strand.Color(255.0,0.0,0.0));
  strand.show();  //Show a blank strand, just to get the LED's ready for use.  
}


void loop() {  //This is where the magic happens. This loop produces each frame of the visual.
  double scale_low  = (double)analogRead(SCALE_LOW_PIN)/1023.0;
  double scale_high = (double)analogRead(SCALE_HIGH_PIN)/1023.0;
  
  int raw_volume = analogRead(AUDIO_PIN);       //Record the volume level from the sound detector
  raw_volume = abs(raw_volume-503);

  // poor mans envelope filter - tried to put this in a function but it was really weird
  recent_volumes[num_samples%num_values] = raw_volume;
  max_val = 0;
  for(int i; i < num_values; i++){
    if (max_val < recent_volumes[i]){
       max_val = recent_volumes[i];
    }
  }
  volume = max_val;
  num_samples++;
  // end poor mans envelope filter

  //Record how far the trimpot is twisted on range (0,1) and scale the volume
  double new_reading = (double)analogRead(KNOB_PIN) / 1023.0;
  knob = abs(new_reading - knob) > 0.02 ? new_reading : knob; 
  avgVol = volume*knob; 

  // store last volume to deal with slowly dimming
  scaled_volume_last = scaled_volume;

  // scaled volume
  scaled_volume = avgVol*avgVol;
  Serial.print(scaled_volume);
  Serial.print(" ");
  scaled_volume = max(100*knob,scaled_volume);
//  scaled_volume = constrain(scaled_volume,200*knob*scale_low,300*knob*scale_high);
  Serial.print(scaled_volume);
  Serial.print(" ");
  scaled_volume = filter.step(scaled_volume);
  
  // slowly dim instead of imediately going back to 0
  if (scaled_volume < scaled_volume_last){
    scaled_volume = scaled_volume_last * 0.99;
  }

//  Serial.println(scaled_volume);

  curr_t_sec_last = curr_t_sec;
  
  // get position in current cycle on range (0,1)
  curr_t_sec = fmod(((double)curr_t/1000000.0),time_scale)/time_scale;

  // if we are restarting a cycle, update the previous and next color
  if(curr_t_sec < curr_t_sec_last) {
    memcpy(last_color, current_color, sizeof(last_color));
    total_colors++;
    memcpy(current_color, colors[total_colors%num_colors], sizeof(current_color));
  }

  mj(last_color,current_color,curr_t_sec);
  
  strand.fill(strand.Color(scaled_volume/255.0*use_color[0],scaled_volume/255.0*use_color[1],scaled_volume/255.0*use_color[2]));
  strand.show();

  while(micros()-curr_t < 3000){}
  last_t = curr_t;
  curr_t = micros();

  Serial.print(scaled_volume/255.0*use_color[0]);
  Serial.print(" ");
  Serial.print(scaled_volume/255.0*use_color[1]);
  Serial.print(" ");
  Serial.println(scaled_volume/255.0*use_color[2]);
  
//  if (!(num_samples % 1000)) {
//    last_t = curr_t;
//    curr_t = micros();
//    period = curr_t-last_t;
//    Serial.println((int)(period/1000));
//  }
}

//////////</Standard Functions>

//////////<Helper Functions>

// 10hz Single Pole Lowpass IIR Filter
float envelopeFilter(float sample) { //10hz low pass
    static float xv[2] = {0,0}, yv[2] = {0,0};
    xv[0] = xv[1]; 
    xv[1] = sample / 50.f;
    yv[0] = yv[1]; 
    yv[1] = (xv[0] + xv[1]) + (0.9875119299f * yv[0]);
    return yv[1];
}

void mj(int last_color[],int current_color[],double t){
  double mj_traj = t*t*(10*t-15*t*t + 6*t*t*t);

  double R = (last_color[0] + (current_color[0] - last_color[0]) * mj_traj);
  double G = (last_color[1] + (current_color[1] - last_color[1]) * mj_traj);
  double B = (last_color[2] + (current_color[2] - last_color[2]) * mj_traj);

//  Serial.print(R);
//  Serial.print(" ");
//  Serial.print(G);
//  Serial.print(" ");
//  Serial.println(B);
//  Serial.print(" ");

  use_color[0] = R;
  use_color[1] = B;
  use_color[2] = G;
}
