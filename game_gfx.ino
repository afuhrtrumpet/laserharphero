#define SCROLL 500
#define VSPACE 14
#define HSPACE  6
#define HEIGHT 84
#define WIDTH  48

#define BLACK 1
#define WHITE 0

Adafruit_PCD8544 display = Adafruit_PCD8544(52, 51, 5, 7, 3);

int time;

void showNotes(byte *notes, int numNotes, int time) {
   int next   = (time / (VSPACE)) % (numNotes + 6);
   int offset = time % (VSPACE);
   while(next >= 0 && offset < (HEIGHT)) {
     byte cur = next < numNotes ? notes[next] : 0;
     byte num = 0;
     while(cur != 0) {
       if(cur & 1 == 1) {
         display.fillRect(HEIGHT - offset, WIDTH - HSPACE * num - 5, 4, 4, BLACK);
       }
       cur >>= 1;
       num++;
     }
     offset += VSPACE;
     next--;
   }
}

void showBar() {
  display.drawLine(2, 0, 2, HEIGHT, BLACK);
}
