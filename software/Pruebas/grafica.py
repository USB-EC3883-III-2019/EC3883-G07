import matplotlib
matplotlib.use('Qt4Agg')
import sys
from PyQt4 import QtGui, QtCore, uic
import matplotlib.pyplot as plt
import matplotlib.figure as Figure
import numpy as np
import time
import serial
from drawnow import drawnow
from matplotlib.backends.qt_compat import QtWidgets
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas 
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar

qtCreatorFile = "Solindar.ui" #Importo el archivo de designer

Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

s = serial.Serial('COM8')
s.baudrate = 115200


i = 1
n = 0
flag = True
fourx = np.linspace(-40, 40, 40)
foury = np.sqrt(1600-(fourx*fourx))
fourt = np.arctan2(foury,fourx)
fourr = (fourx**2 + foury**2)**(0.5)

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
		self.ang = 0
		self.distS = 0
		self.distL = 0
		self.distF = 0
		self.rdataS = np.zeros(64)
		self.rdataL = np.zeros(64)
		self.rdataF = np.zeros(64)
		self.pdata = np.zeros(64)

		#GRIDs
		self.angles=[]
		for k in range(1,31):
			self.angles.append(-106+k*7)

		self.radii=[]
		for k in range(1,9):
			self.radii.append(k*10)
		
		#Crear parametros de funcionamiento
		self.refresh=0.1 #Periodo de actualizacion de imagen
		self.buffact=0.1 #Periodo de actualizacion de buffer de datos
		self.buffready = False #Variable para indicar el fin de la lectura inicial del buffer de datos
		self.refreshcount = self.refresh*1000
		self.buffactcount = self.buffact*1000

		#Iniciar timer para la graficacion
		timergraf = QtCore.QTimer(self)
		timergraf.timeout.connect(self.grafica)
		timergraf.start(self.refreshcount)

		#Iniciar timer para actualizacion de datos
		timerbuff = QtCore.QTimer(self)
		timerbuff.timeout.connect(self.lectura)
		timerbuff.start(self.buffactcount)
		
	def grafica(self):
		self.ax = self.canvas.figure.add_subplot(111, projection='polar')
		self.ax.clear()
		if self.buffready:
			self.radar = self.ax.plot(self.rad,[80,0],'g',alpha=0.35,drawstyle='steps')
			if self.Sonar:
				self.datosS = self.ax.plot(self.pdata, self.rdataS,'ro')
			if self.Lidar:
				self.datosL = self.ax.plot(self.pdata, self.rdataL,'bo')
			if self.Fusion:
				self.datosF = self.ax.plot(self.pdata, self.rdataF,'yo')
		self.ax.set_theta_offset(np.pi/2)
		self.ax.set_thetalim(thetamin=-106,thetamax=106)
		self.ax.set_thetagrids(self.angles)
		self.ax.set_rgrids(self.radii)

		self.canvas.draw()
		self.canvas.flush_events()

	def lectura(self):
		byte1 = s.read(1) #Lee un byte
		while byte1 > b'\x80': #Si el byte comienza en 1, vuelve a leer
			byte1 = s.read(1) 
		datos = s.read(3) #Si comienza por 0, lee el resto de los datos

		# DECODIFICACION
		self.posicion = (ord(byte1) & 63)
		ang = (self.posicion-32)*3.7*np.pi/180
		self.filtro = (ord(byte1)&64)>>6
		self.distS = (((ord(datos[0]) & 127)<<2)|((ord(datos[1]) & 96)>>5))*61/58
		if self.distS > 80:
			self.distS = 80
		self.distL = ((ord(datos[1]) & 31)<<7)|(ord(datos[2]) & 127)
		if self.distL > 2300:
			self.distL = 2300
		elif self.distL < 400:
			self.distL = 400
		self.distL = 308135*self.distL**-1.382
		
		if self.distS < self.distL:
			self.distF = self.distS
		else:
			self.distF = self.distL

		if self.filtro:
			self.Filtro.setText('ON')
		else:
			self.Filtro.setText('OFF')

		if self.buffready:
			f = open('log.txt','a')
			f.writelines('Angulo: ' + str((self.posicion-32)*3.7) + ' - Dist. Sonar: ' + str(self.distS) + ' - Dist. Lidar: ' + str(self.distL) + ' - Dist. Fusion: ' + str(self.distF) + '\n')
			f.close()
		else:
			f = open('log.txt','w')
			f.writelines('Log: \nAngulo: ' + str((self.posicion-32)*3.7) + ' - Dist. Sonar: ' + str(self.distS) + ' - Dist. Lidar: ' + str(self.distL) + ' - Dist. Fusion: ' + str(self.distF) + '\n')
			f.close()

		self.rad = [ang, 0]
		self.rdataS[self.posicion] = self.distS
		self.rdataL[self.posicion] = self.distL
		self.rdataF[self.posicion] = self.distF
		self.pdata[self.posicion] = ang
		self.lcdNumber.display((self.posicion-32)*3.7)
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