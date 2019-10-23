import sys
import os
import struct
import io
import math

refTable = {0:1, 1:2, 2:4, 3:8, 4:16, 5:32, 6:64, 7:128, 8:256, 9:512, 10:1024, 11:2048, 12:4096}

def main():
	stepSize = 0
	am = 16;
	outFile = open("deOut.raw", "w+b")
	headFlag = 8 
	with open("out.brr","rb") as f:
		while True:
			if headFlag == 8:
				nextByte = f.read(1)
				if not nextByte:
					break
				head = (int) (struct.unpack("<B",nextByte)[0]  / pow(2,4))
				stepSize = refTable[head]
				headFlag = 0
			nextByte = f.read(1)
			headFlag += 1
			if not nextByte:
				break

			am = am + 4
			b0 = struct.unpack("<B",nextByte)[0] 
			b1 = (int) (b0 / pow(2,4) * stepSize)
			b1b = struct.pack(">H", b1)
			outFile.write(b1b)

			b2 = (int) (b0 % pow(2,4) * stepSize)
			b2b = struct.pack(">H", b2)
			outFile.write(b2b)

if __name__ == "__main__":
    main()