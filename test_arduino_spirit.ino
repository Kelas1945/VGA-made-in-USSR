

//**********************************
/*
пин D2   регистр Х
пин D3   регистр У
пин D5   такт
пин D6   страница
пин D7   пипетка
пин D13  пиксель
пин D11  разрешить

  *** шина ***
пин A0      0
пин A1      1
пин A2      2
пин A3      3
пин A4      4
пин A5      5
пин D12     6
пин D4      7

*/
//***********************************
int xx=0;
int yy=60;


byte Backup[12][15] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

byte Cur[12][15] = {
{ 0, 0, 0, 0, 0, 0,255,255,255, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0,255,255, 0, 0, 0,255,255, 0, 0, 0, 0},
{ 0, 0, 0,255, 0, 0, 0, 0, 0, 0, 0,255, 0, 0, 0},
{ 0, 0, 0,255, 0, 0, 0, 0, 0, 0, 0,255, 0, 0, 0},
{255,255, 0,255, 0,255,255, 0,255,255, 0,255, 0,255,255},
{255, 0,255,255, 0, 0,255, 0,255, 0, 0,255,255, 0,255},
{ 0,255, 0,255, 0, 0, 0, 0, 0, 0, 0,255, 0,255, 0},
{ 0, 0,255, 0, 0,255, 0, 0, 0,255, 0, 0,255, 0, 0},
{ 0, 0,255, 0, 0, 0,255,255,255, 0, 0, 0,255, 0, 0},
{ 0,255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,255, 0},
{ 0,255, 0,255,255, 0, 0,255,255, 0,255,255, 0,255, 0},
{255,255,255, 0, 0,255,255, 0, 0,255, 0, 0,255,255,255},
};



void setup() {
  
PinsVGA();
PAGE (1);



}

void loop() {

  for (int y2=0; y2<=11; y2++) {Locate (xx,yy+y2);for (int x2=0; x2<=14; x2++) { Backup [y2] [x2] = Drop();}} // сохраняем участок под курсором
  for (int y2=0; y2<=11; y2++) {Locate (xx,yy+y2); for (int x2=0; x2<=14; x2++) {if (Cur [y2] [x2]>0) {Locate (xx+x2,yy+y2); Pixel (Cur[y2][x2]);}}} //рисуем курсор
  
  delay (200);
  for (int y2=0; y2<=11; y2++) {
    Locate (xx,yy+y2);
    for (int x2=0; x2<=14; x2++) {Pixel (Backup[y2][x2]);}} // возвращаем  участок на место
 xx=xx+3;
 if (xx>240) xx=10;

}

void PinsVGA(){
  DDRD |= (1<<2);  // 2, out  
  DDRD |= (1<<3);  // 3, out  
  DDRB |= (1<<5);  // 13, out  
  DDRB &= ~(1<<3); // 11, in
  DDRC = 0b111111;    
  PORTC = 0b000000;
  DDRB |= (1<<4);  // 12, out   
  DDRD |= (1<<4);  // 4, out 
  DDRD |= (1<<5);  // 5, out 
  DDRD |= (1<<6);  // 6, out 
  DDRD |= (1<<7);  // 7, out 
  PORTD |= (1<<2);  //digitalWrite (2, HIGH); Х
  PORTD |= (1<<3);  //digitalWrite (3, HIGH); У
  PORTD |= (1<<5);  //digitalWrite (5, HIGH); CLK
  PORTD |= (1<<6);  //digitalWrite (6, HIGH); PAGE
  PORTD |= (1<<7);  //digitalWrite (7, HIGH); DROP
  PORTB |= (1<<5);  //digitalWrite (13, HIGH); PIXEL
}

void ClsVGA (byte c){
  //очиска экрана
  Locate (0,0);
  for (int j=0; j<128; j++){for (int i=0; i<256; i++){Pixel (c);}}
}

void Locate (byte x, byte y){
  if (x&(1<<7)) {PORTD |= (1<<4);} else {PORTD &= ~(1<<4);}  //работаем с пином 4
  if (x&(1<<6)) {PORTB |= (1<<4);} else {PORTB &= ~(1<<4);}  //работаем с пином 12
  PORTC = x; //данные
  
  PORTD &= ~(1<<2);  //digitalWrite (2, LOW); X
  PORTD &= ~(1<<5);  //digitalWrite (5, LOW); CLK
  PORTD |= (1<<5);  //digitalWrite (5, HIGH); CLK
  PORTD |= (1<<2);  //digitalWrite (2, HIGH); X

  if (y&(1<<7)) {PORTD |= (1<<4);} else {PORTD &= ~(1<<4);}  //работаем с пином 4      
  if (y&(1<<6)) {PORTB |= (1<<4);} else {PORTB &= ~(1<<4);}  //работаем с пином 12
  PORTC = y; //данные
  PORTD &= ~(1<<3);  //digitalWrite (3, LOW); Y
  PORTD &= ~(1<<5);  //digitalWrite (5, LOW); CLK
  PORTD |= (1<<5);  //digitalWrite (5, HIGH); CLK
  PORTD |= (1<<3);  //digitalWrite (3, HIGH); Y
  
}
void Pixel (byte c){
  while (digitalRead(11) == LOW){}
  if (c&(1<<7)) {PORTD |= (1<<4);} else {PORTD &= ~(1<<4);}  //работаем с пином 4
  if (c&(1<<6)) {PORTB |= (1<<4);} else {PORTB &= ~(1<<4);}  //работаем с пином 12
  PORTC = c; //данные
  PORTB &= ~(1<<5);  //digitalWrite (13, LOW); PIXEL
  PORTD &= ~(1<<5);  //digitalWrite (5, LOW); CLK
  PORTB |= (1<<5);  //digitalWrite (13, HIGH); PIXEL
  PORTD |= (1<<5);  //digitalWrite (5, HIGH); CLK
  //delayMicroseconds (1); 
}

void PAGE (byte pagge){
  Locate (pagge,0);
  PORTD &= ~(1<<6);  //digitalWrite (6, LOW); page
  PORTD &= ~(1<<5);  //digitalWrite (5, LOW); CLK
  PORTD |= (1<<5);  //digitalWrite (5, HIGH); CLK
  PORTD |= (1<<6);  //digitalWrite (6, HIGH); PAGE 
}

int Drop (){

int s=0;
int s1=0;
  //шину в input
  DDRC = 0b000000;    
  PORTC = 0b000000;
  DDRB &= ~(1<<4);  // (12, LOW);
  DDRD &= ~(1<<4);  // (4, LOW);
  
  while (digitalRead(11) == LOW){}
  PORTD &= ~(1<<7);  //digitalWrite (7, LOW);
 
  s=digitalRead (4);    //старший бит
  s=s<<1;
  s1=digitalRead (12);
  s=s+s1;
  s=s<<1;
  s1=digitalRead (19);
  s=s+s1;
  s=s<<1;
  s1=digitalRead (18);
  s=s+s1;
  s=s<<1;
  s1=digitalRead (17);
  s=s+s1;
  s=s<<1;
  s1=digitalRead (16);
  s=s+s1;
  s=s<<1;
  s1=digitalRead (15);
  s=s+s1;
  s=s<<1;
  s1=digitalRead (14);
  s=s+s1;
  
  PORTD &= ~(1<<5);  //digitalWrite (5, LOW); CLK
  PORTD |= (1<<7);  //digitalWrite (7, HIGH); DROP
  PORTD |= (1<<5);  //digitalWrite (5, HIGH); CLK
  
  PinsVGA(); //инициализируем пины *** initializing pins

return (s);
   
}


