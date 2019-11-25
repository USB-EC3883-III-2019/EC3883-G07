import sys
from PyQt4 import QtGui, QtCore, uic
import numpy as np
import time
import serial

qtCreatorFile = "Torre.ui" # Importo el archivo de designer

Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

s = serial.Serial('COM8') # Inicializa la lectura por puerto serial
s.baudrate = 116736	# Se ajusta el baudrate a la misma tasa del microcontrolador

class MyApp(QtGui.QMainWindow, Ui_MainWindow):
	def __init__(self):
		# Inicializar
		QtGui.QMainWindow.__init__(self)
		Ui_MainWindow.__init__(self)
		self.setupUi(self)
		
		# Variables y Flags 
		self.mode = False
		self.env = False
		self.Z0 = 0
		self.Z1 = 0
		self.Z2 = 0
		self.Z3 = 0
		self.Z4 = 0
		self.msg = " "
		self.msgr = " "
		self.datos = np.array([0, 0, 0 ,0],dtype=np.uint8)
		
		# Funciones
		self.Modo.setStatusTip("Maestro/Esclavo")
		self.Modo.activated[str].connect(self.Mode)

		self.Enviar.clicked.connect(self.Env)

		# Parametros de funcionamiento
		self.refresh=1 # Periodo de actualizacion de imagen
		self.buffready = False # Variable para indicar el fin de la lectura inicial del buffer de datos
		self.refreshcount = self.refresh*1000
		
		# Iniciar timer para la graficacion
		timergraf = QtCore.QTimer(self)
		timergraf.timeout.connect(self.Torre)
		timergraf.start(self.refreshcount)

	def Torre(self):
		if self.mode:
			#print('Maestro')
			if self.env:
				self.MsgR.clear()
				self.Z0 = self.Zona0.value()
				self.Z1 = self.Zona1.value()
				self.Z2 = self.Zona2.value()
				self.Z3 = self.Zona3.value()
				self.Z4 = self.Zona4.value()
				if self.Nsaltos.value()==1:
					self.Z2 = self.Z3 = self.Z4 = 0
				elif self.Nsaltos.value()==2:
					self.Z3 = self.Z4 = 0
				elif self.Nsaltos.value()==3:
					self.Z4 = 0

				#print('Zona 1: '+str(self.Z1)+', Zona 2: '+str(self.Z2)+', Zona 3: '+str(self.Z3)+', Zona 4: '+str(self.Z4))
				self.msg = self.Msg.toPlainText()
				self.env = False
				if len(self.msg)==1:
					# Entramado
					self.msg = self.msg.toUtf8().data() #Si se usa una version distinta de Python 2.7, ignorar esta linea
					
					self.datos[0] = 128|((ord(self.msg)&240)>>4)
					self.datos[1] = ord(self.msg)&15 | self.Z0<<4
					self.datos[2] = (self.Z1<<3) | self.Z2
					self.datos[3] = (self.Z3<<3) | self.Z4
					
					#for i in range(0,4):
					#	print(self.datos[i])
					s.write(self.datos)

				else:
					self.Msg.setPlainText("Ingrese UN caracter")

			#print(str(s.in_waiting) + "\n")
			if s.in_waiting:
				self.msgr = s.read(1)
				self.MsgR.setPlainText(self.msgr)

		else:
			#print('Esclavo \n')
			if self.env:
				self.Msg.setPlainText("NO PUEDES HACER NADA COMO ESCLAVO")
				#Entramado Esclavo
				self.datos[0] = 128|(1<<5)
				self.datos[1] = 0
				self.datos[2] = 0
				self.datos[3] = 0
				s.write(self.datos)

	def Env(self):
		self.env = True

	def Mode(self,text):
		if text == "Esclavo":
			self.mode = False

		elif text == "Maestro":
			self.mode = True		

if __name__ == "__main__":
	app = QtGui.QApplication(sys.argv)
	window = MyApp()
	window.show()
	sys.exit(app.exec_())  