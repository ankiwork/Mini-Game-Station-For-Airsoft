#include <Keypad.h>
#include <LiquidCrystal_I2C.h>



//==========================================================================
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Создание объекта LiquidCrystal_I2C
//==========================================================================



//=======================================================================================================================================
const byte ROWS = 4;                                                                           // Количество строк клавиатуры
const byte COLS = 3;                                                                           // Количество столбцов клавиатуры
//---------------------------------------------------------------------------------------------------------------------------------------
char keys[ROWS][COLS] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};  // Определение символов клавиатуры
//---------------------------------------------------------------------------------------------------------------------------------------
byte rowPins[ROWS] = {7, 2, 3, 5};                                                             // Определение пинов строк клавиатуры
byte colPins[COLS] = {6, 8, 4};                                                                // Определение пинов столбцов клавиатуры
//---------------------------------------------------------------------------------------------------------------------------------------
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);                        // Создание объекта Keypad
//=======================================================================================================================================


//======================================================================================================================================
unsigned long lastTimerUpdate = 0;  // Отслеживание времени
//--------------------------------------------------------------------------------------------------------------------------------------
int value = 0;                      // Отслеживание количества нажатых кнопокна матричной панели, рекомендуется обнулять в конце цикла
//--------------------------------------------------------------------------------------------------------------------------------------
int bombCode[6];                    // Хранение введённого кода от бомбы
//--------------------------------------------------------------------------------------------------------------------------------------
int bombTime[2];                    // Хранение времени бомбы до взрыва
//======================================================================================================================================



// Предустановки 
void setup() {
  //============================================
  lcd.init();       // Инициализация дисплея
  //--------------------------------------------
  lcd.backlight();  // Инициализация подсветки 
  //============================================



  //=================================================
  loadingTheSystem();  // Отображение разработчиков
  //-------------------------------------------------
  setGameMode();       // Выбор игрового режима
  //=================================================
}



// Бесконечный цикл
void loop() {
  
}



// Код для игрового режима 1
void gameMode1() {
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("SELECT");

  lcd.setCursor(2, 1);
  lcd.print("BOMB && CODE");

  delay(2000);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("SET THE TIME");

  lcd.setCursor(7, 1);
  lcd.print("**");

  while (true) {
    if (value == 2) {
      break;
    }

    char key = keypad.getKey();
    if (key) {
      if (key >= '0' && key <= '9') {
        int digit = key - '0';

        bombTime[value] = digit;

        lcd.setCursor(7 + value, 1);
        lcd.print(digit);

        value++;
      }
    }
  } value = 0;  // Обнуление, после завершения работы с циклом
  
  delay(2000);

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("******");

  lcd.setCursor(7, 1);
  lcd.print(":: 00");

  for (int i = 0; i < 2; i++) {
    lcd.setCursor(4 + i, 1);
    lcd.print(bombTime[i]);
  }
  
  while (true) {
    if (value == 6) {
      break;
    }

    char key = keypad.getKey();
    if (key) {
      if (key >= '1' && key <= '9') {
        int digit = key - '0';

        bombCode[value] = digit;

        lcd.setCursor(5 + value, 0);
        lcd.print(digit);

        value++;
      }
    }
  } value = 0;  // Обнуление, после завершения работы с циклом

  delay(2000);

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("******");

  lcd.setCursor(7, 1);
  lcd.print(":: 00");

  for (int i = 0; i < 2; i++) {
    lcd.setCursor(4 + i, 1);
    lcd.print(bombTime[i]);
  }

  int minutes = bombTime[0] * 10 + bombTime[1];
  int seconds = 59;
  while (true) {
    if (value == 6) {
      break;
    }

    if (millis() - lastTimerUpdate >= 1000) {
      lastTimerUpdate = millis();

      lcd.setCursor(4, 1);

      lcd.print(minutes <= 10 ? "0" : "");
      lcd.print(minutes - 1);

      lcd.print(" :: ");

      lcd.print(seconds < 10 ? "0" : "");
      lcd.print(seconds);

      seconds--;

      if (seconds < 0) {
        seconds = 59;
        minutes--;
      }
    }

    char key = keypad.getKey();
    if (key) {
      if (key >= '0' && key <= '9') {
        int digit = key - '0';
        if (digit == bombCode[value]) {
          lcd.setCursor(5 + value, 0);
          lcd.print(digit);
          value++;
        }
      }
    }
    delay(50); // Уменьшаем задержку для более быстрой реакции на ввод
  }
  value = 0; // Обнуление, после завершения работы с циклом
}



// Код для игрового режима 2
void gameMode2() {

}



// Код для игрового режима 3
void gameMode3() {

}



// Код для игрового режима 4
void gameMode4() {

}



// Установка игрового режима на стадии запуска станции
void setGameMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Game Mode");

  lcd.setCursor(3, 1);
  lcd.print("1  2  3  4");

  while (true) {
    char key = keypad.getKey();
    if (key) {
      if (key >= '1' && key <= '4') {
        int digit = key - '0';
        switch (digit) {
          case 1: {  // Код для игрового режима 1
            gameMode1();

            break;
          }

          case 2: {  // Код для игрового режима 2

            // gameMode2();

            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("In Development");

            delay(2000);

            lcd.clear();
            setGameMode();

            break;
          }

          case 3: {  // Код для игрового режима 3

            // gameMode3();

            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("In Development");

            delay(2000);

            lcd.clear();
            setGameMode();

            break;
          }

          case 4: {  // Код для игрового режима 4

            // gameMode4();

            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("In Development");

            delay(2000);

            lcd.clear();
            setGameMode();

            break;
          }
        }
        break;
      }
    }
  }
}



// Отображение разработчиков при первом включении
void loadingTheSystem() {
  lcd.setCursor(3, 0);
  lcd.print("DEVELOPERS");

  lcd.setCursor(0, 1);
  lcd.print("BASTARD && ARCHI");

  delay(2000);
}