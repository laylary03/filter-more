# Filter (More) — CS50 Problem Set 4

## Overview
This program applies multiple image filters to BMP files, including an **edge detection** filter using the Sobel operator.  
The filters implemented are:
- **Grayscale** — Convert image to shades of gray.
- **Sepia** — Apply a warm, antique-style color filter.
- **Reflect** — Flip image horizontally.
- **Blur** — Apply a box blur to smooth the image.
- **Edges** — Highlight edges in an image using the Sobel algorithm.

---

## Files
- `filter.c` — Main driver for reading/writing BMP files and invoking filters.
- `helpers.c` — Implements grayscale, sepia, reflect, blur, and edges filters.
- `helpers.h` — Header file with function prototypes.
- `bmp.h` — Defines the BMP file format structure.
- `Makefile` — For compilation.
- `README.md` — You’re reading it!

---

## Compilation
To compile:
```bash
make filter
./filter [filter] infile.bmp outfile.bmp

Where [filter] is one of:

-g — Grayscale

-s — Sepia

-r — Reflect

-b — Blur

-e — Edges

Author
Based on the CS50 Problem Set 4 specification:
https://cs50.harvard.edu/x/2025/psets/4/filter/more/
