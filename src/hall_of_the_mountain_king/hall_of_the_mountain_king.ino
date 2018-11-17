#define BUZZER 8

const int c4 = 261;
const int cS4 = 277;
const int d4 = 294;
const int dS4 = 311;
const int e4 = 329;
const int f4 = 349;
const int fS4 = 370;
const int g4 = 391;
const int gS4 = 415;
const int la4 = 440;
const int laS4 = 455;
const int b4 = 466;
const int c5 = 523;
const int cS5 = 554;
const int d5 = 587;
const int dS5 = 622;
const int e5 = 659;
const int f5 = 698;
const int fS5 = 740;
const int g5 = 784;
const int gS5 = 830;
const int la5 = 880; 
const int laS5 = 932;
const int d6 = 1175;
const int dS6 = 1245;
const int e6 = 1319;
const int f6 = 1397;
const int fS6 = 1480;

 
int counter = 0;
 
void setup(){
  //Setup pin modes
  pinMode(BUZZER, OUTPUT);
}

void doorbell(void){
 
  //Play first section
  firstSection();
 
  //Play second section
  secondSection();

}
 
void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(BUZZER, note, duration);

  delay(1 + duration);
 
  //Stop tone on buzzerPin
  noTone(BUZZER);
 
  //Increment counter
  counter++;
}
 
void firstSection()
{
  beep(c4, 250);
  beep(d4, 250);    
  beep(dS4, 250);
  beep(f4, 250);
  beep(g4, 250);  
  beep(dS4, 250);
  beep(g4, 500);
  beep(fS4, 250);
  beep(d4, 250);
  beep(fS4, 500);
  beep(f4, 250);
  beep(cS4, 250);
  beep(f4, 500);
  beep(c4, 250);
  beep(d4, 250);    
  beep(dS4, 250);
  beep(f4, 250);
  beep(g4, 250);
  beep(dS4, 250);
  beep(g4, 250);
  beep(c5, 250);
  beep(laS4, 250);
  beep(g4, 250);
  beep(dS4, 250);
  beep(g4, 250);
  beep(laS4, 500);
  
  delay(500);
}
 
void secondSection()
{
  beep(g4, 250);
  beep(la4, 250);    
  beep(b4, 250);
  beep(c5, 250);
  beep(d5, 250);  
  beep(b4, 250);
  beep(d5, 500);
  beep(dS5, 250);
  beep(b4, 250);
  beep(dS5, 500);
  beep(d5, 250);
  beep(b4, 250);
  beep(d5, 500);
  beep(g4, 250);
  beep(la4, 250);    
  beep(b4, 250);
  beep(c5, 250);
  beep(d5, 250);
  beep(b4, 250);
  beep(d5, 500);
  beep(dS5, 250);
  beep(b4, 250);
  beep(dS5, 500);
  beep(d5, 500);
  
  delay(500);
}

void loop(){
  doorbell();
}
