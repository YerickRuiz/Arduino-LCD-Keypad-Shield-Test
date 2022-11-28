#include <LiquidCrystal.h>

int row = 0;
int col = 0;
int a0_value = 0;

bool alive = true;

const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;

LiquidCrystal lcd(pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);

byte among_us[] = {
  B00000,
  B01111,
  B11000,
  B11000,
  B11111,
  B01111,
  B01010,
  B01010
};

byte among_us_dead[] = {
  B00000,
  B00000,
  B01110,
  B00100,
  B11111,
  B01111,
  B01010,
  B01010
};

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  print_info_serial();
  update_lcd();
  
  lcd.createChar(0, among_us);
  lcd.createChar(1, among_us_dead);
}

void print_info_serial() {
  Serial.print("a0_value: ");
  Serial.print(a0_value);
  Serial.print(", col: ");
  Serial.print(col);
  Serial.print(", row: ");
  Serial.println(row);
}

void update_lcd() {
  lcd.clear();
  lcd.setCursor(col, row);
  int i = 0;
  if(alive == true){
   i = 0;
  }else{
   i = 1;
  }
  lcd.write(i);
  delay(200);
}


void loop() {
  a0_value = analogRead(0);
  // RIGHT
  if ((a0_value >= 0 && a0_value < 60) && (col < 15)) {
    col++;
    print_info_serial();
    update_lcd();
  }
  // UP
  else if ((a0_value > 60 && a0_value < 200 ) && row > 0) {
    row--;
    print_info_serial();
    update_lcd();
  }
  //DOWN
  else if ((a0_value > 200 && a0_value < 400 ) && row < 1) {
    row++;
    print_info_serial();
    update_lcd();
  }
  //LEFT
  else if ((a0_value > 400) && (a0_value < 600) && (col > 0)) {
    col--;
    print_info_serial();
    update_lcd();
  }
  //SELECT
  else if ((a0_value > 600) && (a0_value < 800) && (col > 0)) {
    alive = !alive;
    print_info_serial();
    update_lcd();
  }
}