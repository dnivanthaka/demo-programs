import sys
#import http
#from http import server
import BaseHTTPServer
from SimpleHTTPServer import SimpleHTTPRequestHandler
import os
import glob
import time
import datetime
#import tea5767


class RequestHandler(SimpleHTTPRequestHandler):
	#tea5767 = None

    def __init__(self, request, address, server):
		#self.tea5767 = tea5767.TEA5767()
        SimpleHTTPRequestHandler.__init__(self, request, address, server)

    def do_GET(self):
        if self.path == '/':
            self.path = 'www/index.html'
		if self.path == '/tune'
			self.path = 'www/index.html'
		if self.path == '/info'
			self.path = 'www/index.html'
		if self.path == '/search'
			self.path = 'www/index.html'

        return SimpleHTTPRequestHandler.do_GET(self)


HandlerClass = RequestHandler
ServerClass = BaseHTTPServer.HTTPServer
Protocol = "HTTP/1.0"

if sys.argv[1:]:
    port = int(sys.argv[1])
else:
    port = 10005

server_address = ('0.0.0.0', port)

HandlerClass.protocol_version = Protocol
httpd = ServerClass(server_address, HandlerClass)

sa = httpd.socket.getsockname()
print("Serving HTTP on ", sa[0], "port ", sa[1])
httpd.serve_forever()
