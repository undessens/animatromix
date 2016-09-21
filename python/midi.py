import mido
import serial
import os
import sys
import glob
import time
from channel import channel

########################################
# 3 différenciation importante : motor, led, video
# motor, led et video sont controllé par le meme controlleur midi
# mais depuis des "modes" différents ...
# led et motor sont controlles depuis des "channel", il est donc possible
#d'enregistrer et de lire une boucle d'automation.
# la video est juste controllable.
#Depuis un meme valeur modifiee depuis le controlleur midi, le veritable control se fera 
#en fonction du mode en question.
# Il est possible d'avoir un mode "vide" pour bouger les potars sans que rien de soit affecté



def receive_midi_msg(msg):
	for c in list_of_channel:
		if (c.midiChannel == msg.control):
			c.setValue(msg.value)
			c.printResult()

def update_channel( channel):
	result = channel.update()
	if result != None  :
		send_serial(result, channel.arduinoID)

def changeMode( newMode):
	if(newMode =="motor") :
		currentMode = "motor"
	elif(newMode == "led") :
		currentMode = "led"
	elif(newMode == "videoFx"):
		currentMode = "videoFx"
	else :
		print "wrong mode choosen"

def send_serial(val, id):
	#send serial TODO
	a=1

def main():
	#channel listing
	list_of_motor= []
	list_of_motor.append( channel( "servo1", 18, 4) )
	list_of_motor.append( channel( "servomoteur", 24, 7) )
	list_of_motor.append( channel( "channel4", 36, 4) )
	list_of_leds = []
	list_of_leds.append( channel( "ledSide1", 18, 13))
	list_of_leds.append( channel( "ledSide2", 12, 34))
	list_of_videoFx = []
	list_of_videoFx.append ( video_effect("Constrate", 13 , "/video/constrate", 12, 255))
	list_of_all = dict()
	list_of_all['motor'] = list_of_motor
	list_of_all['led'] = list_of_leds
	list_of_all['videoFx'] = list_of_videoFx
	# currentMode, "motor" or "led" or "videoFx"
	currentMode = "motor"

	#channel
	inport = mido.open_input('nanoKONTROL2 MIDI 1')
	inport.callback = receive_midi_msg

	#Serial connect
	try:
		if sys.platform.startswith('darwin'):
			ser = serial.Serial('/dev/tty.usbmodem1a131',115200)
		elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
			ser = serial.Serial('/dev/ttyACM0',115200)
			#ser = serial.Serial('/dev/ttyACM1', 115200)
		else:
			ser = None
	except :
		print "Impossible to connect to Serial"
		ser = None	


	while True:
		#Main update
		#Frequency update 20Hz
		time.sleep(0.05)
		for c in list_of_channel:
			v = update_channel(c)
			if(v != None):
				send_serial(v, c.arduinoID)


if __name__ == "__main__":
    main()
