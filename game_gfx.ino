#define SCROLL 500
#define VSPACE 14
#define HSPACE  6
#define HEIGHT 84
#define WIDTH  48

#define BLACK 1
#define WHITE 0

int time = 0;
int score = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(52, 51, 5, 7, 3);

void initDisplay() {
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
}

void showFrame(byte *notes, int numNotes) {
  display.clearDisplay();
  display.setRotation(0);
  if (mode == MAIN_MENU) {
    showMenu();
  } else {
    if (mode == GAME) {
      showNotes(notes, numNotes, time);
      showScore();
      time++;
    }
    showBar();
    showBursts();
    showScale();
  }
  display.display();
}

void showNotes(byte *notes, int numNotes, int time) {
   display.setRotation(0);
   int next   = (time / (VSPACE)) % (numNotes + 6);
   if(next == 2) {
     score = 0;
   }
   int offset = time % (VSPACE);
   while(next >= 0 && offset < (HEIGHT)) {
     byte cur = next < numNotes ? notes[next] : 0;
     byte num = 0;
     while(cur != 0) {
       if(cur & 1 == 1) {
         display.fillRect(HEIGHT - offset, WIDTH - HSPACE * num - 5, 4, 4, BLACK);
         if (HEIGHT - offset >= 2 && HEIGHT - offset <= 5) {
           if (noteValues[num] && time - 10 > lastTimeScored[num]) {
             score++;
             lastTimeScored[num] = time;
             Serial.print("Score: ");
             Serial.println(score);
           }
         }
       }
       cur >>= 1;
       num++;
     }
     offset += VSPACE;
     next--;
   }
}

void showBar() {
  display.setRotation(0);
  display.drawLine(2, 0, 2, HEIGHT, BLACK);
}

void showScore() {
  display.setRotation(90);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.print(score);
}

char *scales[] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};

void showScale() {
  display.setRotation(90);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(65, 0);
  display.print(scales[(scale[0] - 2) % 11]);
  display.print((scale[0] - 14)/ 11);
  display.setCursor(30, 0);
  switch (scaleType) {
    case 0:
      display.print("Major"); break;
    case 1:
      display.print("Minor"); break;
    case 2:
      display.print("MajorP"); break;
    case 3:
      display.print("Blues"); break;
  }
}

void showMenu() {
  display.setRotation(90);
  display.setTextSize(1.5);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.print("C = Free Mode\nZ = Game Mode");
}

void showBursts() {
  display.setRotation(90);
  display.setCursor(0, 0);
  for(int i = 0; i < 8; i++) {
    if(noteValues[i]) {
      display.drawRect(HEIGHT - 6, HSPACE * i, 6, 6, BLACK);
    }
  }
}
