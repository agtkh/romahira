CC = cc
CFLAGS = -Wall -Wextra -O2
TARGET = romahira

$(TARGET): romahira.c
	$(CC) $(CFLAGS) -o $(TARGET) romahira.c

install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/

clean:
	rm -f $(TARGET)

.PHONY: install clean
