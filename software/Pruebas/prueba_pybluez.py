import bluetooth

print "Buscando..."
nearby_devices = bluetooth.discover_devices(lookup_names = True)
print "Se encontraron %d dispositivos" %len(nearby_devices)

for name, addr in nearby_devices:
	print "%s - %s" %(addr,name)