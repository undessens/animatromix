import mido
import time
from channel import channel

list_of_channel= []
list_of_channel.append( channel( "servo1", 18, 4) )
list_of_channel.append( channel( "servomoteur", 24, 7) )
list_of_channel.append( channel( "channel4", 36, 4) )


def receive_midi_msg(msg):
	for c in list_of_channel:
		if (c.midiChannel == msg.control):
			c.setValue(msg.value)
			c.printResult()

inport = mido.open_input('nanoKONTROL2 MIDI 1')
inport.callback = receive_midi_msg

while True:
	time.sleep(1)

