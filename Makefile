# final executable to build:
TARGET = encoder
# .o files to link in (for all .c files)
OBJS = encoder.o

# Add support for pthread and real-time clock here:
CXXFLAGS  = -Wall -Werror -Wextra

# You should not need to change any of this:
CC = g++

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f outFile.txt
	rm -f out.brr
	rm -f decOUT.raw
	rm -f psnr