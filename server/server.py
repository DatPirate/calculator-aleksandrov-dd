import json
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse, parse_qs
 
class CalcHandler(BaseHTTPRequestHandler):
    def do_POST(self):
    	try:
		output = "request recieved"
		self.send_response(200)
		self.send_header("Content-Type", "application/json")
		self.end_headers()
		self.wfile.write(json.dumps(output).encode("utf-8"))
	except Exception as e:
            	self.send_response(500)
            	self.send_header("Content-Type", "application/json")
            	self.end_headers()
            	self.wfile.write(json.dumps({"error": str(e)}).encode("utf-8"))
 
if __name__ == "__main__":
    server_address = ('', 8000)
    httpd = HTTPServer(server_address, CalcHandler)
    print("Starting server on port 8000...")
    httpd.serve_forever()
 
