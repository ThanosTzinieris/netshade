# Netshade

A constrained low-level image-processing pipeline built in C around the Netpbm image format family.

![Netshade Demo](img/netshade.jpg)

---

## Overview

Netshade is an academic image-processing project focused on direct manipulation of raw graphical data through grayscale conversion, binary threshold mapping, and sequential pixel-stream processing.

Unlike higher-level graphics applications relying on external imaging libraries, the project operates directly on ASCII and binary image data using manually implemented parsing and transformation logic.

The project was developed under unusually strict technical limitations designed to encourage low-level computational thinking and memory-aware programming techniques.

---

## Technical Constraints

The assignment intentionally prohibited:

- Arrays
- Strings
- Floating-point arithmetic
- Several standard helper utilities

As a result, the entire processing pipeline was implemented around:

- Sequential data handling
- Character-level parsing
- Stream-based computation
- Incremental transformation logic

---

## Supported Processing Operations

Netshade supports transformation between:

- Full-color image states
- Grayscale image states
- High-contrast binary threshold states

The application manually processes image headers, dimensions, and color values while converting between multiple Netpbm formats.

---

## About Netpbm

The Netpbm family of formats stores graphical information using intentionally simple and human-readable structures.

Because of their straightforward layout, Netpbm images are particularly useful for studying:

- Pixel representation
- Color encoding
- Image transformation
- Low-level graphical computation

---

## Processing Pipeline

Rather than separating operations into isolated utilities, the project was designed around a unified processing flow capable of:

1. Loading image data
2. Parsing graphical information
3. Transforming pixel values
4. Exporting converted image states

---

## Example Transformations

### Color → Grayscale → Binary Threshold

![Transformation Example](img/graph.jpg)

The project progressively reduces visual information through computational transformation, demonstrating how image data can be abstracted into simplified graphical states.

---

## Experimental Results

Although academically focused in scope, certain threshold-processing operations occasionally produced unexpectedly abstract or perceptual visual results.

![Threshold Example](img/don.jpg)

---

## Repository Structure

```text
main.c
convert.c
netpbm.c

convert.h
netpbm.h

test_p3.ppm
test_p6.ppm
```

---

## Educational Focus

This project became an important introduction to:

- Low-level image processing
- Constrained problem solving
- Stream-based computation
- Sequential logic
- Systems-oriented programming
- The computational foundations of digital imaging