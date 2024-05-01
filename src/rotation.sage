def rotate_right_128bit(x, n, width=128):
    """Rotate `x` right `n` positions in a `width`-bit integer."""
    n %= width  # Ensure n is within the bounds of 0 to width-1
    return ((x >> n) | (x << (width - n))) & ((1 << width) - 1)

# Example 128-bit integer, you might typically have this in hex or similar
x = 0x2a21c14191eff1010bff1c22abcd1f11  # Just a placeholder example

# Number of positions to rotate
n = 61

# Perform the rotation
rotated_value = rotate_right_128bit(x, n)

# Print the original and rotated values in hexadecimal form for clarity
print("Original:", format(x, '032x'))  # 32 hexadecimal digits for 128 bits
print("Rotated :", format(rotated_value, '032x'))