

class video_effect:
	def __init__(self, _name, midi_channel, _oscAdress, _valueMin, _valueMax):
		self.name = _name
		self.midiChannel = _midiChannel
		self.oscAdress = _oscAdress
		self.currentValue = 63
		self.valueMin = _valueMin
		self.valueMax = _valueMax

	def printResult(self):
		print self.name + " : "+str(self.currentValue)

	def setValue(self, newVal):
		if(newVal>0 and newVal<127):
			self.currentValue = newVal

	def update(self):
		#l'idée serait de faire un smooth ici, histoire ne pas avoir des changements trop
		#violent, lorsque les potars sont modifiés entre 2 changements
