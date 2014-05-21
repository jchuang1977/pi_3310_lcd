# Makefile for Nokia 5110 Drivers running on a Raspberry Pi
#
# http://binerry.de/post/25787954149/pcd8544-library-for-raspberry-pi 
# 

CC = /usr/bin/gcc
DIR=samples
INSTALL = @install


all: pcd8544_rpi pcd8544_test2 pcd8544_test nokia5110

nokia5110: nokia5110.c 
	${CC} -o nokia5110 nokia5110.c PCD8544.c  -L/usr/local/lib -lwiringPi

pcd8544_rpi: $(DIR)/pcd8544_rpi.c
	${CC} -o pcd8544_rpi $(DIR)/pcd8544_rpi.c PCD8544.c  -L/usr/local/lib -lwiringPi

pcd8544_alljoyn: $(DIR)/pcd8544_alljoyn.c
	${CC} -o pcd8544_alljoyn $(DIR)/pcd8544_alljoyn.c PCD8544.c  -L/usr/local/lib -lwiringPi


pcd8544_test: $(DIR)/pcd8544_test.c
	${CC} -o pcd8544_test $(DIR)/pcd8544_test.c PCD8544.c  -L/usr/local/lib -lwiringPi

pcd8544_test2: $(DIR)/pcd8544_test2.c
	${CC} -o pcd8544_test2 $(DIR)/pcd8544_test2.c PCD8544.c  -L/usr/local/lib -lwiringPi

install: pcd8544_rpi
	$(INSTALL) -m 0655 pcd8544_rpi /usr/sbin
	$(INSTALL) -m 0755 3310_lcd /etc/init.d
	update-rc.d -f 3310_lcd start 80 2 3 4 5 . stop 30 0 1 6

clean:
	rm -rf pcd8544_rpi pcd8544_test2 pcd8544_test nokia5110
