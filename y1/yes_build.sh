#!/bin/bash

# Name of the output shared library
OUTPUT="y1.so"

# Source files (you can add more here)
SRC_FILES=" yespower.c yespower-module.c "
SRC_FILES+=" ../algo/yespower/yespower-ref.c "
SRC_FILES+=" ../algo/yespower/yespower-opt.c "
SRC_FILES+=" ../algo/yespower/yespower-blake2b.c "
SRC_FILES+=" ../algo/yespower/yespower-blake2b-ref.c "
SRC_FILES+=" ../algo/sha/hmac-sha256-hash.c "
SRC_FILES+=" ../algo/sha/sha256-hash.c "
SRC_FILES+=" ../algo/blake/sph_blake2b.c "
SRC_FILES+=" ../algo/yespower/crypto/hmac-blake2b.c "
SRC_FILES+=" ../simd-utils/simd-constants.c "

# Include directory (optional)
INCLUDE_DIR="-I../ "
INCLUDE_DIR+="-I../algo " 
INCLUDE_DIR+="-I../algo/yespower "
INCLUDE_DIR+="-I../algo/blake2b "
INCLUDE_DIR+="-I/usr/include/python3.12 "

CFLAGS="-O3 -maes -mavx -msha -mvaes -Wall -Wno-unused-function"
# Compile into shared object
gcc -fPIC -shared $INCLUDE_DIR $CFLAGS $SRC_FILES -o "$OUTPUT"
strip -s $OUTPUT

# Check result
if [ $? -eq 0 ]; then
    echo "✅ Build successful: $OUTPUT"
else
    echo "❌ Build failed."
fi