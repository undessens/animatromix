import mido
import serial
import os
import sys
import glob
import time
from channel import channel
from video_effect import video_effect
from transport_effect import transport_effect
from OSC import OSCClient, OSCMessage

########################################
# 3 differenciation importante : motor, led, video, et commande arduino
# motor, led et video sont controlle par le meme controlleur midi
# mais depuis des "modes" differents ...
# led et motor sont controlles depuis des "channel", il est donc possible
#d'enregistrer et de lire une boucle d'automation.
# la video est juste controllable.
#Depuis un meme valeur modifiee depuis le controlleur midi, le veritable control se fera 
#en fonction du mode en question.
# Il est possible d'avoir un mode "vide" pour bouger les potars sans que rien de soit affecte


##########################################
#Todo . Si on en enregistre mais que l'on 
# ne bouge pas les potars, peut on considerer que cest un stop
#
#



def receive_midi_msg(msg):
	#print msg
	for c in list_of_all['motor']:
		if (c.midiChannel == msg.control):
			c.setValue(msg.value)
			c.printResult()
		if (c.recordButton == msg.control):
			if( msg.value):
				print ( c.name+" : record")
				c.startRecording()
			else :
				print ( c.name+" : stop record")
				c.stopRecording()

	for c in list_of_all['led']:
		if (c.midiChannel == msg.control):
			c.setValue(msg.value)
			c.printResult()
		if (c.recordButton == msg.control):
			if( msg.value):
				print ( c.name+" : record")
				c.startRecording()
			else :
				print ( c.name+" : stop record")
				c.stopRecording()

	for c in list_of_all['videoFx']:
		if (c.midiChannel == msg.control):
			c.setValue(msg.value)
			c.printResult()

	for c in list_of_all['transport']:
		if (c.midiChannel == msg.control):
			c.setValue(msg.value)
			c.printResult()


def update_channel( channel):
	result = channel.update()
	if result != None  :
		#print result
		send_serial(result, channel.arduinoID)

def update_transport( transp):
	result = transp.update()
	if result :
		#print result
		send_serial(100, transp.arduinoID)

def update_videoFx( vidFx):
	result = vidFx.update()
	if result != None :
		#print result
		send_osc ( vidFx.oscAddress, result)

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
	msg = ""
	msg = str(chr(id))+str(chr(val))
	if(ser):
		ser.write(msg)

def send_osc(address, value):
	oscMsg = OSCMessage()
	oscMsg.setAddress(address)
	oscMsg.append(int(value))
	try:
		oscClient.send(oscMsg)
	except Exception, e:
		print e

def main():
	#channel listing
	global list_of_motor
	list_of_motor= []
	list_of_motor.append( channel( "servomoteur2", 17, 4 , 33) )
	list_of_motor.append( channel( "servomoteur1", 16, 7 , 32) )
	list_of_motor.append( channel( "stepper motor1",18, 13, 34) )
	list_of_motor.append( channel( "stepper motor2",19, 14, 35) )
	#list_of_motor.append( channel( "channel4", 36, 4, 0) )
	global list_of_leds
	list_of_leds = []
	list_of_leds.append( channel( "ledRouge", 0, 2, 64))
	list_of_leds.append( channel( "ledRGBr", 1, 10, 65))
	list_of_leds.append( channel( "ledRGBg", 2, 11, 66))
	list_of_leds.append( channel( "ledRGBb", 3, 12, 67))
	#list_of_leds.append( channel( "ledSide2", 12, 34, 0))
	global list_of_videoFx 
	list_of_videoFx = []
	list_of_videoFx.append ( video_effect("sharpness", 5 , "enhancement/sharpness"))
	list_of_videoFx.append ( video_effect("Constrate", 4 , "enhancement/contrast"))
	list_of_videoFx.append ( video_effect("Saturation", 6, "enhancement/saturation"))
	list_of_videoFx.append ( video_effect("Brightness", 7, "enhancement/brightness"))
	list_of_videoFx.append ( video_effect("Filter +", 62, "filters/nextFilter"))
	list_of_videoFx.append ( video_effect("Filter -", 61, "filters/previousFilter"))
	list_of_videoFx.append ( video_effect("init Filter", 60, "filters/initFilter"))
	list_of_videoFx.append ( video_effect("zoom", 21, "zoomCrop/topMargin"))
	list_of_videoFx.append ( video_effect("zoom", 22, "zoomCrop/leftMargin"))
	list_of_videoFx.append ( video_effect("zoom", 23, "zoomCrop/zoomLevel"))
	global list_of_transport
	list_of_transport = []
	list_of_transport.append( transport_effect("release Stepper", 42, 21))
	list_of_transport.append( transport_effect("hold Stepper", 41, 20))
	list_of_transport.append( transport_effect("init stepper pos", 43, 22))
	global list_of_all 
	list_of_all = dict()
	list_of_all['motor'] = list_of_motor
	list_of_all['led'] = list_of_leds
	list_of_all['videoFx'] = list_of_videoFx
	list_of_all['transport'] = list_of_transport
	# TODO delete current mode, not used anymore
	# currentMode, "motor" or "led" or "videoFx"
	currentMode = "motor"

	# OSC connect
	global oscClient
	oscClient = OSCClient()
	oscClient.connect( ("localhost",12345 ))

	
	# Midi connect						
	try:
		if sys.platform.startswith('darwin'):
			inport = mido.open_input('nanoKONTROL2 SLIDER/KNOB')
		elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
			inport = mido.open_input('nanoKONTROL2 MIDI 1')
		else:
			inport = None
	except :
		print "Impossible to connect to Midi device"
		inport = None	

	if(inport):
		inport.callback = receive_midi_msg

	#Serial connect
	try:
		global ser
		if sys.platform.startswith('darwin'):
			ser = serial.Serial('/dev/tty.usbmodem1a151',115200)
			print "Serial connected"
		elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
			try:
				ser = serial.Serial('/dev/ttyACM0',115200)
				print "ACM0"
			except :
				ser = serial.Serial('/dev/ttyACM1', 115200)
				print "ACM1"
			
		else:
			ser = None
	except :
		print "Impossible to connect to Serial"
		ser = None	


	while True:
		#Main update
		#Frequency update 20Hz
		time.sleep(0.05)
		for c in list_of_all['motor']:
			update_channel(c)
		for c in list_of_all['led']:
			update_channel(c)
		for c in list_of_all['videoFx']:
			update_videoFx(c)
		for c in list_of_all['transport']:
			update_transport(c)




if __name__ == "__main__":
    main()
