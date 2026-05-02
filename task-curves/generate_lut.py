#!/usr/bin/env python3
import sys
from PIL import Image

def main():
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} <map.png> <output.h> <output.cpp>", file=sys.stderr)
        sys.exit(1)

    img = Image.open(sys.argv[1]).convert("RGB")
    pixels = img.load()
    w, h = img.size  # expected 256x3

    lut_r = [pixels[x, 0][0] for x in range(w)]
    lut_g = [pixels[x, 1][1] for x in range(w)]
    lut_b = [pixels[x, 2][2] for x in range(w)]

    def fmt(arr):
        return ", ".join(str(v) for v in arr)

    with open(sys.argv[2], "w") as f:
        f.write("#pragma once\n")
        f.write("#include <cstdint>\n\n")
        f.write("extern const uint8_t LUT_R[256];\n")
        f.write("extern const uint8_t LUT_G[256];\n")
        f.write("extern const uint8_t LUT_B[256];\n")

    with open(sys.argv[3], "w") as f:
        f.write('#include "lut_data.h"\n\n')
        f.write(f"const uint8_t LUT_R[256] = {{{fmt(lut_r)}}};\n")
        f.write(f"const uint8_t LUT_G[256] = {{{fmt(lut_g)}}};\n")
        f.write(f"const uint8_t LUT_B[256] = {{{fmt(lut_b)}}};\n")

if __name__ == "__main__":
    main()
