import matplotlib
matplotlib.use('Qt4Agg')
import sys
from PyQt4 import QtGui, QtCore, uic
import matplotlib.pyplot as plt
import matplotlib.figure as Figure
import numpy as np
import time
import serial
from matplotlib.backends.qt_compat import QtWidgets
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas 
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar

qtCreatorFile = "Solindar.ui" #Importo el archivo de designer

Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

s = serial.Serial('COM8')
s.baudrate = 116736

class MyApp(QtGui.QMainWindow, Ui_MainWindow):
	def __init__(self):
		#Inicializar
		QtGui.QMainWindow.__init__(self)
		Ui_MainWindow.__init__(self)
		self.setupUi(self)
		self.navigation = NavigationToolbar(self.canvas,self)
		self.hlayout.addWidget(self.navigation)

		self.sonar.stateChanged.connect(self.Msonar)
		self.sonar.setStatusTip("Sonar")
		self.lidar.stateChanged.connect(self.Mlidar)
		self.lidar.setStatusTip("Lidar")
		self.fusion.stateChanged.connect(self.Mfusion)
		self.fusion.setStatusTip("Fusion")

		#Flags y Variables
		self.filtro = False
		self.Sonar = True
		self.Lidar = False
		self.Fusion = False
		self.rep = 0
		self.ang = 0
		self.distS = 0
		self.distL = 0
		self.distF = 0
		self.rdataS = np.zeros(31)
		self.rdataL = np.zeros(31)
		self.rdataF = np.zeros(31)
		self.pdata = np.zeros(31)
		self.ax = self.canvas.figure.add_subplot(111, projection='polar')

		#GRIDs
		self.angles=[]
		for k in range(1,34):
			self.angles.append(-117+k*7)

		self.radii=[]
		for k in range(1,9):
			self.radii.append(k*10)

		#Crear parametros de funcionamiento
		self.refresh=0.01 #Periodo de actualizacion de imagen
		#self.buffact=0.09 #Periodo de actualizacion de buffer de datos
		self.buffready = False #Variable para indicar el fin de la lectura inicial del buffer de datos
		self.refreshcount = self.refresh*1000
		#self.buffactcount = self.buffact*1000

		#Iniciar timer para la graficacion
		timergraf = QtCore.QTimer(self)
		timergraf.timeout.connect(self.grafica)
		timergraf.start(self.refreshcount)

		#Iniciar timer para actualizacion de datos
		#timerbuff = QtCore.QTimer(self)
		#timerbuff.timeout.connect(self.lectura)
		#timerbuff.start(self.buffactcount)
		
	def grafica(self):
		print(s.in_waiting)
		if s.in_waiting:
			self.lectura()
			self.ax.clear()
			if self.buffready: # Empieza a plotear una vez se realice una primera lectura
				self.ax.plot(self.rad,[80,0],'g',alpha=0.35,drawstyle='steps') # Barrido del sonar
				if self.Sonar:
					self.ax.plot(self.pdata, self.rdataS,'ro') # Plot Sonar
				if self.Lidar:
					self.ax.plot(self.pdata, self.rdataL,'bo') # Plot Lidar
				if self.Fusion:
					self.ax.plot(self.pdata, self.rdataF,'yo') # Plot Fusion
			self.ax.set_theta_offset(np.pi/2)
			self.ax.set_thetalim(thetamin=-117,thetamax=117)
			self.ax.set_thetagrids(self.angles)
			self.ax.set_rgrids(self.radii)

			self.canvas.draw()
			self.canvas.flush_events()
			#if(s.in_waiting>=8):
			#	s.reset_input_buffer()

	def lectura(self):
		byte1 = s.read(1) #Lee un byte
		while byte1 > b'\x80': #Si el byte comienza en 1, vuelve a leer
			byte1 = s.read(1) 
		datos = s.read(3) #Si comienza por 0, lee el resto de los datos

		# DECODIFICACION
		self.posicion = (ord(byte1) & 63) # Valor n que corresponde al angulo
		ang = -(self.posicion-16)*7.4*np.pi/180 # Angulo en radianes
		self.filtro = (ord(byte1)&64)>>6
		self.distS = (((ord(datos[0]) & 127)<<2)|((ord(datos[1]) & 96)>>5))*61.035/58 # Si el valor sale del rango, se ajusta al maximo del Lidar
		if self.distS > 80:
			self.distS = 80
		self.distL = ((ord(datos[1]) & 31)<<7)|(ord(datos[2]) & 127) # Si el valor sale del rango, se ajusta a los limites
		if self.distL > 2300:
			self.distL = 2300
		elif self.distL < 400:
			self.distL = 400
		self.distL = 308135*self.distL**-1.382 # Conversion a cm
		#print(self.distL,self.distS)
		
		# Fusion
		if self.distS < self.distL:
			if self.distF == self.distS:
				self.rep = self.rep+1
			else:
				self.rep = 0
			self.distF = self.distS
			if self.rep > 2:
				self.distF = self.distL
				self.rep = 0
		else:
			self.distF = self.distL

		# Filtro
		if self.filtro:
			self.Filtro.setText('ON')
		else:
			self.Filtro.setText('OFF')

		# Guardar los datos en un log
		if self.buffready:
			f = open('log.txt','a')
			f.writelines('Angulo: ' + str(-(self.posicion-16)*7.4) + ' - Dist. Sonar: ' + str(self.distS) + ' - Dist. Lidar: ' + str(self.distL) + ' - Dist. Fusion: ' + str(self.distF) + '\n')
			f.close()
		else:
			f = open('log.txt','w')
			f.writelines('Log: \nAngulo: ' + str(-(self.posicion-16)*7.4) + ' - Dist. Sonar: ' + str(self.distS) + ' - Dist. Lidar: ' + str(self.distL) + ' - Dist. Fusion: ' + str(self.distF) + '\n')
			f.close()

		# Actualiza los parametros a plotear
		self.rad = [ang, 0]
		self.rdataS[self.posicion-1] = self.distS
		self.rdataL[self.posicion-1] = self.distL
		self.rdataF[self.posicion-1] = self.distF
		self.pdata[self.posicion-1] = ang
		self.lcdNumber.display(-(self.posicion-16)*7.4)
		self.lcdNumber_2.display(self.distS)
		self.lcdNumber_3.display(self.distL)
		self.lcdNumber_4.display(self.distF)
		self.buffready = True

	# FUNCIONES INTERFAZ
	def Msonar(self,state):
		if state == QtCore.Qt.Checked:
			self.Sonar = True
		else:
			self.Sonar = False

	def Mlidar(self,state):
		if state == QtCore.Qt.Checked:
			self.Lidar = True
		else:
			self.Lidar = False

	def Mfusion(self,state):
		if state == QtCore.Qt.Checked:
			self.Fusion = True
		else:
			self.Fusion = False


if __name__ == "__main__":
	app = QtGui.QApplication(sys.argv)
	window = MyApp()
	window.show()
	sys.exit(app.exec_())  