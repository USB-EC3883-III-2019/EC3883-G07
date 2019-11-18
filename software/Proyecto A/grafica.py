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

qtCreatorFile = "Solindar.ui" # Importo el archivo de designer

Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

s = serial.Serial('COM8') # Inicializa la lectura por puerto serial
s.baudrate = 116736	# Se ajusta el baudrate a la misma tasa del microcontrolador

class MyApp(QtGui.QMainWindow, Ui_MainWindow):
	def __init__(self):
		# Inicializar
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

		# Flags y Variables a usar
		self.filtro = False		# Flags para indicar que graficas se observaran y si el filtro se encuentra activo
		self.Sonar = True
		self.Lidar = False
		self.Fusion = False
		self.ang = 0	# Variables para el desentramado 
		self.distS = 0
		self.distL = 0
		self.distF = 0
		self.rdataS = np.zeros(31)	# Vectores que seran graficados
		self.rdataL = np.zeros(31)
		self.rdataF = np.zeros(31)
		self.pdata = np.zeros(31)
		self.ax = self.canvas.figure.add_subplot(111, projection='polar')	# Creacion de la grafica

		# GRIDs
		self.angles=[] # Se generan los grids de angulo y magnitud que seran usados
		for k in range(1,34):
			self.angles.append(-117+k*7)

		self.radii=[]
		for k in range(1,9):
			self.radii.append(k*10)

		# Parametros de funcionamiento
		self.refresh=0.01 # Periodo de actualizacion de imagen
		self.buffready = False # Variable para indicar el fin de la lectura inicial del buffer de datos
		self.refreshcount = self.refresh*1000
		
		# Iniciar timer para la graficacion
		timergraf = QtCore.QTimer(self)
		timergraf.timeout.connect(self.grafica)
		timergraf.start(self.refreshcount)
		
	def grafica(self):
		if s.in_waiting: # En caso de no tener datos en el buffer de entrada, no pierde tiempo rehaciendo la misma grafica
			self.lectura() # Salta a la funcion de lectura de datos
			self.ax.clear() # Limpia la grafica anterior
			if self.buffready: # Empieza a plotear una vez se realice una primera lectura
				self.ax.plot(self.rad,[80,0],'g',alpha=0.35,drawstyle='steps') # Barrido del sonar
				if self.Sonar:
					self.ax.plot(self.pdata, self.rdataS,'ro') # Plot Sonar
				if self.Lidar:
					self.ax.plot(self.pdata, self.rdataL,'bo') # Plot Lidar
				if self.Fusion:
					self.ax.plot(self.pdata, self.rdataF,'yo') # Plot Fusion
			self.ax.set_theta_offset(np.pi/2) # Se agrega un desfasaje tal que 0° se encuentren en el eje vertical
			self.ax.set_thetalim(thetamin=-117,thetamax=117) # Se limita el rango del angulo al deseado
			self.ax.set_thetagrids(self.angles) # Se agregan los grids previamente creados
			self.ax.set_rgrids(self.radii)

			self.canvas.draw() # Actualización de la grafica
			self.canvas.flush_events()

	def lectura(self):
		self.byte1 = s.read(1) #Lee un byte
		while self.byte1 > b'\x80': #Si el byte comienza en 1, vuelve a leer
			self.byte1 = s.read(1) 
		self.datos = s.read(3) #Si comienza por 0, lee el resto de los datos

		# DECODIFICACION
		self.posicion = (ord(self.byte1) & 63) # Valor n que corresponde al angulo
		self.ang = -(self.posicion-16)*7.4*np.pi/180 # Angulo en radianes
		self.filtro = (ord(self.byte1)&64)>>6 # Verificacion del bit correspondiente al filtro
		self.distS = (((ord(self.datos[0]) & 127)<<2)|((ord(self.datos[1]) & 96)>>5))*61.035/58 # Decodificacion y ajuste de la distancia leida por el Sonar
		if self.distS > 80: # Si el valor sale del rango, se ajusta al maximo del Lidar
			self.distS = 80
		self.distL = ((ord(self.datos[1]) & 31)<<7)|(ord(self.datos[2]) & 127) # Si el valor sale del rango, se ajusta a los limites previamente calculados
		if self.distL > 2300:
			self.distL = 2300
		elif self.distL < 400:
			self.distL = 400
		self.distL = 308135*self.distL**-1.382 # Conversion de la distancia del Lidar a cm
				
		# Fusion
		varL=1 + 0.5*self.distL/10 # Varianza del Lidar
		varS=3 # Varianza del Sonar
		var3=(varL**-2 + varS**-2)**-1
		self.distF = var3*(varS**(-2)*self.distS + varL**(-2)*self.distL)
		
		# Filtro
		if self.filtro: # Si el bit del filtro es 1, el filtro esta activo. En caso contrario, esta apagado
			self.Filtro.setText('ON')
		else:
			self.Filtro.setText('OFF')

		# Guardar los datos en un log
		if self.buffready: # Despues de hacer la primera lectura, los datos se van agregando al log
			self.f = open('log.txt','a')
			self.f.writelines('Angulo: ' + str(-(self.posicion-16)*7.4) + ' - Dist. Sonar: ' + str(self.distS) + ' - Dist. Lidar: ' + str(self.distL) + ' - Dist. Fusion: ' + str(self.distF) + '\n')
			self.f.close()
		else: # Si no se ha hecho una primera lectura, se crea o sobreescribi el archivo de log
			self.f = open('log.txt','w')
			self.f.writelines('Log: \nAngulo: ' + str(-(self.posicion-16)*7.4) + ' - Dist. Sonar: ' + str(self.distS) + ' - Dist. Lidar: ' + str(self.distL) + ' - Dist. Fusion: ' + str(self.distF) + '\n')
			self.f.close()

		# Actualiza los parametros a plotear
		self.rad = [self.ang, 0] # Se ajusta el angulo del barrido
		self.rdataS[self.posicion-1] = self.distS # Se actualizan los datos segun la posicion (el angulo) del motor
		self.rdataL[self.posicion-1] = self.distL
		self.rdataF[self.posicion-1] = self.distF
		self.pdata[self.posicion-1] = self.ang
		self.lcdNumber.display(-(self.posicion-16)*7.4) # Se muestran los datos leido en los display
		self.lcdNumber_2.display(self.distS)
		self.lcdNumber_3.display(self.distL)
		self.lcdNumber_4.display(self.distF)
		self.buffready = True # Una vez se lee por primera vez, se cambia el flag

	# FUNCIONES INTERFAZ
	def Msonar(self,state): # Verifica si es seleccionado el Sonar para ser graficado
		if state == QtCore.Qt.Checked:
			self.Sonar = True
		else:
			self.Sonar = False

	def Mlidar(self,state): # Verifica si es seleccionado el Lidar para ser graficado
		if state == QtCore.Qt.Checked:
			self.Lidar = True
		else:
			self.Lidar = False

	def Mfusion(self,state): # Verifica si es seleccionado la Fusion para ser graficada
		if state == QtCore.Qt.Checked:
			self.Fusion = True
		else:
			self.Fusion = False


if __name__ == "__main__":
	app = QtGui.QApplication(sys.argv)
	window = MyApp()
	window.show()
	sys.exit(app.exec_())  