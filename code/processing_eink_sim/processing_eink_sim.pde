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
int screenIndex = 0;
String displayText = "Hello e-ink";

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

JSONArray einkScreens;

void updateCurrentFont() {
  println("Current font is " + fontNames[fontIndex] + " at size " + fontSizes[sizeIndex]);
  customFont = createFont(fontNames[fontIndex], fontSizes[sizeIndex]);
  textFont(customFont);
}

void updateScreenSize() {
  JSONObject screen = einkScreens.getJSONObject(screenIndex); 
  
  int w = (int) mm2px(screen.getFloat("w (mm)"));
  int h = (int) mm2px(screen.getFloat("h (mm)"));
  
  // 200x200 1.54inch Schwarz / Weiss E-Ink Display
  String name = screen.getString("Name");
  displayText = name;
  println(name);
  surface.setSize(w, h);

}

void setup() {
  size(600, 600);
  updateCurrentFont();
  einkScreens = loadJSONArray("einkdata.json");
}

void draw(){
  background(255);
  
  
  fill(0);
  
  textSize(fontSizes[sizeIndex]);
  textAlign(LEFT, TOP);
  //text("30mm x 30mm", mm2px(15), mm2px(15));
  text(displayText, 0, 0);
}

void keyPressed() {
  println(key);
  if (key == ' ') {
    screenIndex = (screenIndex + 1) % einkScreens.size();
  }
  
  /*
  if (key != CODED) {
    return;
  }*/
  
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
  
  
  updateScreenSize();
  updateCurrentFont();
}
