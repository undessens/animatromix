#################
# Comment s'organise la classe channel ?
# Chaque channel correspond a un objet.
# On peut le modifier en changeant directement en midi le potentiometre correspondant.
# Quand on appuie sur le bouton d'enregistrement, la sequence s'enregistre telle qu'elle.
# Pas de syncro. Pas de tempo .
# Quel est le lien entre le potentiometre et le fadeur. Est ce que le fadeur est un maximum
# non enregistrable, qui permet d'agir comme un master ?
# 8 channel pour l'electronique
# 8 channel pour les lumieres
# 8 channel pour les parametres videos, qui ne seront pas enregistrable.
###################################################################




class channel:
	def __init__(self, _name, _midiChannel, _arduinoID):
		self.name = _name
		self.midiChannel = _midiChannel
		self.arduinoID = _arduinoID
		self.currentValue = 63
		#Recording
		self.isRecording = False
		self.isPlaying = False
		self.list_of_value = []
		self.currentIndex = 0
		self.recordingStart = 0.0  #msec


	def printResult(self):
		print self.name + " : "+str(self.currentValue)

	def setValue(self, newVal):
		if(newVal>0 and newVal<127):
			self.currentValue = newVal

	def update( self):
		if isRecording :
			list_of_value.append(self.currentValue)

		if self.isPlaying :
			self.currentIndex+=1
			if(self.currentIndex >= len(self.list_of_value):
				self.currentIndex = 0
			return self.list_of_value[self.currentIndex]
		else :
			return self.currentValue
			
	def playStop( self, isPlay ):
		if isPlay and len(self.list_of_value)>0 :
			self.currentIndex = 0
			self.isPlaying = True
			print self.name+" play "
		else
			self.isPlaying = False
			print self.name+" stop"

	def startRecording( self):
		del list_of_value[:]
		self.isRecording = True

	def stopRecording (self):
		self.isRecording = False











