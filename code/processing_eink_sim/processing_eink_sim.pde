// My macbook display size 16-inch (3072 × 1920)
// 16‑inch (diagonal) LED‑backlit display with IPS technology; 
// 3072‑by‑1920 native resolution at 226 pixels per inch with support for millions of colors

// Identify the model
// https://support.apple.com/fr-fr/HT201300

// Specs
// https://support.apple.com/kb/SP809?viewlocale=en_US&locale=fr_FR

// My resolution 1536 x 960 - pixel density 2. Compared to 3072 x 1920.

// for printing


/*
// Screen
float ppi = 226;
float pixelDensity = 2;
*/

/*
// Printing test
// Still need to resize this in indesign
float ppi = 72;
float pixelDensity = 1;
*/



float ppi = 72;
float pixelDensity = 1;

float inch2mm = 25.4;
float ppmm = ppi / inch2mm;

float hackRatio = 1;
//71.0 / 31;

float mm2px(float mm) {
  return mm * ppmm / pixelDensity * hackRatio;
}

int fontIndex = 0;
int sizeIndex = 0;
int screenIndex = 0;

String displayText = "Hello \ne-ink";

PFont customFont;

String[] fontNames = { 
  "FreeMono",
  "FreeSans",
  "FreeSerif",
  "FreeMonoBold",
  "FreeSansBold",
  "FreeSerifBold",
  "FreeMonoBoldOblique",
  "FreeSansBoldOblique",
  "FreeSerifBoldItalic",
  "FreeMonoOblique",
  "FreeSansOblique",
  "FreeSerifItalic"
};

String brownFox = "The quick brown fox jumps over the lazy dog";
int[] fontSizes = { 9, 12, 18, 24 };

JSONArray einkScreens;
PGraphics einkGraphics;

boolean toggleScreenName = true;

void updateCurrentFont() {
  println("Current font is " + fontNames[fontIndex] + " at size " + fontSizes[sizeIndex]);
  customFont = createFont(fontNames[fontIndex], fontSizes[sizeIndex], false);
  textFont(customFont);
  
}

void updateScreenSize() {
  println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  JSONObject screen = einkScreens.getJSONObject(screenIndex); 
  
  int wpx = (int) screen.getInt("w px");
  int hpx = (int) screen.getInt("h px");
  
  einkGraphics = createGraphics(wpx, hpx);
  
  float wmm = screen.getFloat("w (mm)");
  float hmm = screen.getFloat("h (mm)");
  
  int w = (int) mm2px(wmm);
  int h = (int) mm2px(hmm);
  
  
  // 200x200 1.54inch Schwarz / Weiss E-Ink Display
  String name = screen.getString("Name");
  displayText = toggleScreenName ? name : brownFox;
  
  println(name);
  println("Size mm " + wmm + " mm x " + hmm + " mm");
  println("Size px be " + wpx + " px x " + hpx + " px");

  surface.setSize(w, h);
}

void setup() {
  size(600, 600, P2D);
  updateCurrentFont();
  
  einkGraphics = createGraphics(600, 600);

  einkScreens = loadJSONArray("einkdata.json");
  
  var list = PFont.list();
  for (int i = 0; i < 360; i++) {
    println(list[i]);
  }
}

void draw(){
  einkGraphics.beginDraw();
  einkGraphics.background(255);
  
  einkGraphics.fill(0);
  einkGraphics.stroke(0);

  einkGraphics.textSize(fontSizes[sizeIndex]);
  einkGraphics.textAlign(LEFT, TOP);
  
  einkGraphics.textFont(customFont);

  //text("30mm x 30mm", mm2px(15), mm2px(15));
  float pp = 0.05;
  
  
  einkGraphics.text(displayText, einkGraphics.width * pp, einkGraphics.height * pp, einkGraphics.width * (1-pp), einkGraphics.height * (1-pp));
  einkGraphics.endDraw();

  image(einkGraphics, 0, 0, width, height);
}

void keyPressed() {
  if (key == ' ') {
    screenIndex = (screenIndex + 1) % einkScreens.size();
  }

  if (key == 'f') {
    toggleScreenName = !toggleScreenName;
  }
  
  if (key == 's') {
    println("Save frame");
    
    JSONObject screen = einkScreens.getJSONObject(screenIndex); 
  
    int wpx = (int) screen.getInt("w px");
    int hpx = (int) screen.getInt("h px");
    
    float wmm = screen.getFloat("w (mm)");
    float hmm = screen.getFloat("h (mm)");
    
    int w = (int) mm2px(wmm);
    int h = (int) mm2px(hmm);
    
    // 200x200 1.54inch Schwarz / Weiss E-Ink Display
    String name = screen.getString("Name");
    displayText = toggleScreenName ? name : brownFox;
    

    String fn = pixelDensity * ppi + "ppi-"+ wmm + "mm-" + hmm + "mm_" + wpx + "px-" + hpx + "px_" + slugify(name) + ".png";
    saveFrame(fn); 
  }
  
  /*
  if (key != CODED) {
    return;
  }*/
  
  //println("key pressed");
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
