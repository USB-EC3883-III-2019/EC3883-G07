import matplotlib
matplotlib.use('Qt4Agg')
import sys
from PyQt4 import QtGui, QtCore, uic
import matplotlib.pyplot as plt
import matplotlib.figure as Figure
import numpy as np
import time
from drawnow import drawnow
from matplotlib.backends.qt_compat import QtWidgets
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas 
from matplotlib.backends.backend_qt4agg import NavigationToolbar2QT as NavigationToolbar

qtCreatorFile = "Solindar.ui" #Importo el archivo de designer

Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

i = 1
n = 0
flag = True

fourx = np.linspace(-40, 40, 40)
foury = np.sqrt(1600-(fourx*fourx))
fourt = np.arctan2(foury,fourx)
fourr = (fourx**2 + foury**2)**(0.5)

#GRIDs
angles=[]
for k in range(1,34):
	angles.append(-136+k*8)

radii=[]
for k in range(1,9):
	radii.append(k*10)

#class Canvas(FigureCanvas):
#    def __init__(self, parent=None):
#        self.canvas = plt.figure()
#        FigureCanvas.__init__(self, self.canvas)
#        self.setParent(parent)

class MyApp(QtGui.QMainWindow, Ui_MainWindow):
	def __init__(self):
		#Inicializar
		QtGui.QMainWindow.__init__(self)
		Ui_MainWindow.__init__(self)
		self.setupUi(self)
		self.navigation = NavigationToolbar(self.canvas,self)
		self.hlayout.addWidget(self.navigation)
		
		#Crear parametros de funcionamiento
		self.refresh=1 #Periodo de actualizacion de imagen
		self.buffact=1/40 #Periodo de actualizacion de buffer de datos
		self.buffready = 0 #Variable para indicar el fin de la lectura inicial del buffer de datos
		self.refreshcount = self.refresh*1000
		self.buffactcount = self.buffact*1000

		#Iniciar timer para la graficacion
		timergraf = QtCore.QTimer(self)
		timergraf.timeout.connect(self.grafica)
		timergraf.start(self.refreshcount)

		#Iniciar timer para actualizacion de datos
		#timerbuff = QtCore.QTimer(self)
		#timerbuff.timeout.connect(self.tickbuff)
		#timerbuff.start(self.buffactcount)
		
	def grafica(self):
		global n, flag
		self.rad = [n*8*np.pi/180, 0]
		self.ax = self.canvas.figure.add_subplot(111, projection='polar')
		self.ax.clear()
		self.radar = self.ax.plot(self.rad,[80,0],'g',alpha=0.35,drawstyle='steps')
		self.datos = self.ax.plot(fourt, fourr,'ro')
		self.ax.set_theta_offset(np.pi/2)
		self.ax.set_thetalim(thetamin=-135,thetamax=135)
		self.ax.set_thetagrids(angles)
		self.ax.set_rgrids(radii)

		if flag:
			n=n+1
			if n>17:
				n=n-2
				flag = False
		else:
			n=n-1
			if n<-17:
				n=n+2
				flag = True
		
		self.canvas.draw()
		self.canvas.flush_events()
	
if __name__ == "__main__":
	app = QtGui.QApplication(sys.argv)
	window = MyApp()
	window.show()
	sys.exit(app.exec_())  