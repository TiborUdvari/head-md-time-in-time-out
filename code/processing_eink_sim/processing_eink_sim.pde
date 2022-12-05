// My macbook display size 16-inch (3072 × 1920)
// 16‑inch (diagonal) LED‑backlit display with IPS technology; 
// 3072‑by‑1920 native resolution at 226 pixels per inch with support for millions of colors

// Identify the model
// https://support.apple.com/fr-fr/HT201300

// Specs
// https://support.apple.com/kb/SP809?viewlocale=en_US&locale=fr_FR

// My resolution 1536 x 960 - pixel density 2. Compared to 3072 x 1920.

float ppi = 226;
float inch2mm = 25.4;
float ppmm = ppi / inch2mm;
float pixelDensity = 2;

float mm2px(float mm) {
  return mm * ppmm / pixelDensity;
}

int fontIndex = 0;
int sizeIndex = 0;

PFont customFont;

String[] fontNames = { 
  "FreeMono.ttf",
  "FreeSans.ttf",
  "FreeSerif.ttf",
  "FreeMonoBold.ttf",
  "FreeSansBold.ttf",
  "FreeSerifBold.ttf",
  "FreeMonoBoldOblique.ttf",
  "FreeSansBoldOblique.ttf",
  "FreeSerifBoldItalic.ttf",
  "FreeMonoOblique.ttf",
  "FreeSansOblique.ttf",
  "FreeSerifItalic.ttf"
};

int[] fontSizes = { 9, 12, 18, 24 };

void updateCurrentFont() {
  println("Current font is " + fontNames[fontIndex] + " at size " + fontSizes[sizeIndex]);
  customFont = createFont(fontNames[fontIndex], fontSizes[sizeIndex]);
  textFont(customFont);
}

void setup() {
  size(600, 600);
  updateCurrentFont();
}

void draw(){
  background(255);
  fill(0);
  
  rect(0,0, mm2px(30), mm2px(30));
  
  fill(255);
  textSize(fontSizes[sizeIndex]);
  textAlign(LEFT, TOP);
  //text("30mm x 30mm", mm2px(15), mm2px(15));
  text("30mm x 30mm", 0, 0);

}

void keyPressed() {
  if (key != CODED) {
    return;
  }
  
  println("key pressed");
  if (keyCode == UP) {
    sizeIndex = (sizeIndex + 1) % fontSizes.length;
  }
  
  if (keyCode == DOWN) {
    sizeIndex = (fontSizes.length + sizeIndex - 1) % fontSizes.length;
  }
  
  if (keyCode == LEFT) {
    fontIndex = (fontIndex + 1) % fontNames.length; 
  }
  
  if (keyCode == RIGHT) {
    fontIndex = (fontNames.length + fontIndex - 1) % fontSizes.length; 
  }
  
  updateCurrentFont();
}
