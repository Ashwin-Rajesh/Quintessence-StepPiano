// { -1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1}
// { 0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0}
const int stepPins[8] = {3,4,5,6,7,8,9,10};
const int speakerPin  = 2;

unsigned long x,y;
int n=0,pos=1,count=40;

// Variables storing values retreived from step inputs
bool prevStep[8]              = {1,1,1,1,1,1,1,1};
bool currentStep[8]           = {1,1,1,1,1,1,1,1};

// Frequency for each step
int frequency[8]              = {240,270,300,320,360,400,450,480};

// Variables for waiting music
const int waitDelay           = 1000;
int waitTimer                 = 0;
int noteTimer                 = 0;
const int musicNum            = 2;
int music[musicNum][50]       = {{ 0  ,1  ,2  ,3  ,4  ,5  ,6  ,7  ,6  ,5  ,4  ,3  ,2  ,1  ,0  ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1},
                                 { 1  ,2  ,1  ,2  ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1}};
int musicDelay[musicNum][50]  = {{ 200,200,200,200,200,200,200,200,200,200,200,200,200,200,200,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0},
                                 { 200,200,200,200,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0}};
int musicIndex                = 0;
int musicCurrent;         

void setup()   
{
  Serial.begin(9600);

  pinMode(speakerPin,OUTPUT);
  
  for(int i = 0; i < 8; i++)
    pinMode(stepPins[i],INPUT_PULLUP); 
}

void loop() 
{  
  piano();
  delay(50);
  playMusic();
}

// Sample input from comparators and save in currentStep, and shift currentStep to prevStep
void piano()
{
  for(int i = 0; i < 8; i++)
    prevStep[i] = currentStep[i];
    
  for(int i = 0; i < 8; i++)
    currentStep[i] = digitalRead(stepPins[i]);
    
  for(int i = 0; i < 8; i++)
    if(prevStep[i] && !currentStep[i])
    {
      musicIndex = 0;
      waitTimer = millis();
      tone(speakerPin,frequency[i],2000);
      break;
    }
}

void playMusic()
{
  if(millis() <= waitTimer + waitDelay)
    return;
    
  if(millis() <= noteTimer + musicDelay[musicCurrent][musicIndex])
    return; 
  
  if(getNote() == -1)
  {
    newMusic();
    noTone(speakerPin);
  }
  else
  {
    noteTimer = millis();
    tone(speakerPin,frequency[getNote()],1000);
    musicIndex++;
  }
}

int getNote()
{
  return music[musicCurrent][musicIndex];
}

// Resets timer(waitTime), resets music counter(musicIndex) and sets a random music as next in line
void newMusic()
{
  Serial.print("a");
  musicIndex = 0;
  waitTimer = millis();
  musicCurrent = random(musicNum);
}

/*void ran()
{
  if(millis()-x>=8000)
  {
    if(millis()-y>=100)
    {
    y=millis();
    Serial.println(n);
    tone(speakerPin,frequency[n],count);
    
    if(n>=7)
    {
      count=30;
      pos=-1;
    }
    else if(n<=0)
    {
      pos=1;
      count=90;
    }
    
    n=n+pos;
    }
  }
}*/
