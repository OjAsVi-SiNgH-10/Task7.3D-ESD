import RPi.GPIO as GPIO
import time

#Raspberry Pi's pins initialised as real numbered pins
GPIO.setmode(GPIO.BOARD)

#Varaibles for the pins numbers of LED and trig, echo pins of the HC SR04
LED = 38
TRIG = 11
ECHO = 16

////////////

MAX_SET_DISTANCE = 20

GPIO.setup(LED, GPIO.OUT)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

led = GPIO.PWM(LED, 100)
led.start(0)


def calDistance():
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    while GPIO.input(ECHO) == False:
        start = time.time()

    while GPIO.input(ECHO) == True:
        end = time.time()

    sig_time = end-start
    
    distance = sig_time / 0.000058
    return distance

////////////

try:
    while 1:
        dis = calDistance()
        print(dis)
        if dis <= MAX_SET_DISTANCE:
            #Changing the duty cycle as per the percentage calculated
            led.ChangeDutyCycle(100 - (dis/MAX_SET_DISTANCE * 100))
            time.sleep(0.1)
        else:
            led.ChangeDutyCycle(0)
            
except KeyboardInterrupt:
    print("Force Stopped")

#Reset the whole setup once exitted
led.stop()
GPIO.cleanup()
