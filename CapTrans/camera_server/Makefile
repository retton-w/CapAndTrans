COMPILE=/opt/develop/davinci/CodeSourcery/Sourcery_G++_Lite/bin/arm-none-linux-gnueabi-gcc
camera: main.o send_file.o capture.o
	$(COMPILE) -o camera main.o send_file.o capture.o -lpthread
main.o: main.c camera.h
	$(COMPILE) -c main.c
send_file.o: send_file.c camera.h
	$(COMPILE) -c send_file.c
capture.o: capture.c davinci_vpfe.h ccdc_davinci.h sensor.h camera.h
	$(COMPILE) -c capture.c 
.PHONY:
	clean
clean:
	rm -f *.o
