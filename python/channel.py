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
	def __init__(self, _name, _midiChannel, _arduinoID, _recordButton):
		self.name = _name
		self.midiChannel = _midiChannel
		self.recordButton = _recordButton
		self.arduinoID = _arduinoID
		self.currentValue = 63
		self.isModified = True
		#Recording
		self.isRecording = False
		self.isOverdubbing = False
		self.isInvisiblePlay = True
		self.isPlaying = False
		self.list_of_value = []
		self.currentIndex = 0
		self.recordingStart = 0.0  #msec


	def printResult(self):
		print self.name + " : "+str(self.currentValue)

	def setValue(self, newVal):
		if(newVal>0 and newVal<127):
			self.currentValue = newVal
			self.isModified = True

	def update( self):
		#only recording
		if self.isRecording and not(self.isPlaying):
			self.list_of_value.append(self.currentValue)
			if self.isModified :
				self.isModified = False
				return self.currentValue
			else :
				return None


		#playing and recording ( overdub )	
		if self.isRecording and self.isPlaying:	
			self.currentIndex+=1
			#go to 0 if needed
			if self.currentIndex >= len(self.list_of_value):
				self.currentIndex = 0
			#overdub
			if self.isModified or self.isOverdubbing:
				self.list_of_value[self.currentIndex]=self.currentValue
				self.isModified = False
				self.isOverdubbing = True
				return self.currentValue
			#return the value
			elif self.list_of_value[self.currentIndex] != self.currentValue :
				self.currentValue = self.list_of_value[self.currentIndex]
				return self.currentValue
			else :
				return None	

		#only playing
		if self.isPlaying and not(self.isRecording) :
			self.currentIndex+=1
			if self.isModified :
				#stop playing but let index goes on
				self.isInvisiblePlay = True
				self.isModified = False
				return self.currentValue
			if self.currentIndex >= len(self.list_of_value):
				self.currentIndex = 0
			if self.isInvisiblePlay :
				return self.currentValue
			elif self.list_of_value[self.currentIndex] != self.currentValue :
				self.currentValue = self.list_of_value[self.currentIndex]
				return self.currentValue
			else :
				return None
		
		#if nothing is playing or recording 
		if not(self.isPlaying) and not(self.isRecording) :
			if self.isModified :
				self.isModified = False
				return self.currentValue
			else :
				return None

			
	def playStop( self, isPlay ):
		if isPlay and len(self.list_of_value)>0 :
			self.currentIndex = 0
			self.isPlaying = True
			self.isInvisiblePlay = False
			#print self.name+" play "
		else :
			self.isPlaying = False
			#print self.name+" stop"

	def startRecording( self):
		#if not playing, delete the previous recording
		if not(self.isPlaying):
			del self.list_of_value[:]
		self.isRecording = True
		self.isOverdubbing = False

	def stopRecording (self):
		self.isRecording = False
		self.isOverdubbing = False











