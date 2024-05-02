x = 0x0f1e2d3c4b5a69788796a5b4c3d2e1f0

a = x & 0x1FFFFFFFFFFFFFFF
print(hex(a))
b = x >> 66
print(hex(b))

print( hex((a << 66) | b) )