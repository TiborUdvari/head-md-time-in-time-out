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

void setup() {
  size(600, 600);
  background(255);
  fill(0);
  
  rect(0,0, mm2px(30), mm2px(30));
  
  fill(255);
  textSize(10);
  textAlign(CENTER);
  text("30mm x 30mm", mm2px(15), mm2px(15));
}
