import json
import subprocess
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse, parse_qs
 
CALCULATOR_EXECUTABLE = "../build/app.exe"
 
class CalcHandler(BaseHTTPRequestHandler):
	def do_POST(self):
		parsed_url = urlparse(self.path)
		if parsed_url.path != "/calc":
			self.send_error(404, "Not Found")
		return
 
		content_length = int(self.headers.get('Content-Length', 0))
		body = self.rfile.read(content_length).decode('utf-8')
 
		try:
			try:
				data = json.loads(body)
			except Exception as e:
		    		self.send_response(400)
		    		self.send_header("Content-Type", "application/json")
		    		self.end_headers()
		    		self.wfile.write(json.dumps({"error": "Invalid JSON"}).encode("utf-8"))
		    		return
			expression = data if isinstance(data, str) else ""
			query_params = parse_qs(parsed_url.query)
			float_mode = query_params.get("float", ["false"])[0].lower() == "true"
			command = [CALCULATOR_EXECUTABLE, expression]
			result = subprocess.run(command, capture_output=True, text=True)


			if result.returncode == 0:
				output = result.stdout.strip()
				if not float_mode and "." in output:
					output = str(int(float(output)))
				self.send_response(200)
				self.send_header("Content-Type", "application/json")
				self.end_headers()
				self.wfile.write(json.dumps(output).encode("utf-8"))
			else:
				raise Exception(result.stderr.strip())
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
 
 
