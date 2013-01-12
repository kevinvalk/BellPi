cmake_minimum_required(VERSION 2.8.4)

project(wiringPi)
 
# Version info
set(WIRINGPI_VERSION_MAJOR 1)
set(WIRINGPI_VERSION_MINOR 0)
set(WIRINGPI_VERSION ${WIRINGPI_VERSION_MAJOR}.${WIRINGPI_VERSION_MINOR})

# WirePi source files
set(WIRINGPI_SRCS wiringPi.c wiringPiFace.c wiringSerial.c wiringShift.c gertboard.c piNes.c lcd.c piHiPri.c piThread.c wiringPiSPI.c softPwm.c softServo.c softTone.c)

# Add the library
add_library(wiringPi ${WIRINGPI_SRCS})