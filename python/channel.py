class channel:
	def __init__(self, _name, _midiChannel, _arduinoID):
		self.name = _name
		self.midiChannel = _midiChannel
		self.arduinoID = _arduinoID
		self.currentValue = 22

	def printResult(self):
		print self.name + " : "+str(self.currentValue)

	def setValue(self, newVal):
		if(newVal>0 and newVal<127):
			self.currentValue = newVal
