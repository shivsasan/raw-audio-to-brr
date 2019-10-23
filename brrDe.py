import sys
import os
import struct
import io
import math

refTable = {0:1, 1:2, 2:4, 3:8, 4:16, 5:32, 6:64, 7:128, 8:256, 9:512, 10:1024, 11:2048, 12:4096}

def main():
	stepSize = 0
	outFile = open("decOUT.raw", "w+b")
	headerFlag = 8 
	with open("EnOUT.raw","rb") as f:
		while True:
			if headerFlag == 8:
				nextByte = f.read(1)
				if not nextByte:
					break
				head = (int) (struct.unpack("<B",nextByte)[0]  / pow(2,4))
				stepSize = refTable[head]
				headerFlag = 0
			# read 32 byte
			nextByte = f.read(1)
			headerFlag += 1
			if not nextByte:
				break

			b0 = struct.unpack("<B",nextByte)[0] 
			#print (b0)
			b1 = (int) (b0 / pow(2,4) * stepSize)
			#print (b1)
			b1b = struct.pack(">H", b1)
			#print (b1b)
			outFile.write(b1b)

			b2 = (int) (b0 % pow(2,4) * stepSize)
			#print (b2)
			b2b = struct.pack(">H", b2)
			#print (b1b)
			outFile.write(b2b)

if __name__ == "__main__":
    main()