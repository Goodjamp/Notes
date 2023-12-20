#print format data (hex), minimal case
val1 = 0x12
val2 = 0x14

print("data = {:x}".format(val1))
print("data = {:x}{:x}".format(val1, val2))

#variation: correct hex view
print("data = 0x{0:02x}, 0x{0:02x}".format(val1, val2))