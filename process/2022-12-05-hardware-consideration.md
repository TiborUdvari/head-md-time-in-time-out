# Hardware considerations
![Font](https://cdn-learn.adafruit.com/guides/cropped_images/000/000/071/medium640/char.png?1534965453)

I'm looking at [these](https://www.bastelgarage.ch/bauteile/displays/e-ink-epapers-display?limit=100) e-ink screens and other hardware available in Switzerland. I created an [Airtable spreadsheet](https://airtable.com/shr6Nev4DOkmD801Z) to use it and a [CSV export](./object/2022-eink-shopping.csv).

They function with the [Adafruit GFX library](https://learn.adafruit.com/adafruit-gfx-graphics-library), which uses [GNU Freefonts](https://www.gnu.org/software/freefont/) encoded into a bitmap format. This has memory implications, as noted [here](https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts).

