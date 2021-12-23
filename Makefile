
backlight: backlight.o

install: backlight
	install -m 4755 -o root -g root backlight /usr/bin
