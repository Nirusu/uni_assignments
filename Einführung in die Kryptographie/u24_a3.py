c = [0b10101010, None, None, None, None, None, None, None, None, None]
x = [None, ord("K"), ord("i"), ord("n"), ord("o"), ord("s"), ord("a"), ord("a"), ord("l"), ord("?")]



for i in range(1, 10):
	c[i] = c[i-1] ^ x[i]
	print(bin(c[i-1]) + " xor " + bin(x[i]) + " = " + bin(c[i]))

print("---MAC BRUTEFORCE:---")

for i in range(1, 9):
	cz = c[0] ^  ord(str(i))
	print(bin(cz) +  " = " + str(cz))
	bruteforce_result = (cz + 194) % 256
	print(bin(bruteforce_result))
	if bruteforce_result == 0b01011011:
		print("MATCH! i = " + str(i))
	else:
		print("No match found with i = " + str(i))