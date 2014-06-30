#! /usr/bin/python
import socket
from datetime import datetime

class Status():
	def netStatus():
		ip = [(s.connect(('8.8.8.8', 80)), s.getsockname()[0], s.close()) for s in [socket.socket(socket.AF_INET, socket.SOCK_DGRAM)]][0][1];
		connected = str(not(ip[:ip.find('.',3)] in ["169.254", "127.0", "0.0"]));
		print('"net":{"ip":"' + ip + '", "connected":"' + connected + '"}', end='');

print("Content-type: text/json\r\n");

print("{");
for module in Status.__dict__.values() :
	try:
		module();
		print(",");
	except TypeError:
		pass;

print('"generated":"' + str(datetime.now()) + '"\n}');