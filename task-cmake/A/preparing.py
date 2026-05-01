#!/usr/bin/env python3
import os

output_file = os.path.join(os.path.dirname(os.path.abspath(__file__)), "index.h")
FIBONACCI = [1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
nums = ", ".join(str(x) for x in FIBONACCI)

with open(output_file, "w") as f:
    f.write("#pragma once\n\n")
    f.write('#define PROJECT_NAME "IndustrialProg"\n')
    f.write('#define PROJECT_VERSION "1.0.0"\n\n')
    f.write("static const int MAGIC_COUNT = %d;\n" % len(FIBONACCI))
    f.write("static const int MAGIC_NUMBERS[%d] = {%s};\n" % (len(FIBONACCI), nums))

print("Generated: " + output_file)
