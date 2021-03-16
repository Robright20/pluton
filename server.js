const log = console.log;
HTTP_PORT = 3000;
SOCK_PORT = 8000;

'use strict';
const fs = require('fs');
const net = require('net');
const http = require('http');
const WebSocket = require('ws');
const wss = new WebSocket.Server({ noServer: true });
const getLine = require('./src/getLine');
let client = {connected: false};

const MIMETypes = {
	'html': 'text/html',
	'css': 'text/css',
	'js': 'text/javascript; charset=utf-8',
	'svg': 'image/svg+xml',
	'ico': 'image/x-icon'
};

const httpServer = http.createServer((req, res) => {
	const url = (req.url === '/') ? '/index.html': req.url;
	const ext = url.match(/\.([a-zA-Z0-9]*)$/)?.[1];
	const type = MIMETypes[ext];
	const path = ['html', 'css'].includes(ext) ? './public' + url : '.' + url;
	fs.readFile(path, null, (err, data) => {
		if (err)
			res.writeHead(404);
		else {
			res.writeHead(200, {'Content-Type': type});
			res.write(data);
		}
		res.end();
	});
});

httpServer.on('upgrade', (req, sock, head) => {
	wss.handleUpgrade(req, sock, head, (ws) => {
		wss.emit('connection', ws, req);
	});
});

wss.on('connection', (ws) => {
	ws.send("connected to the server\n");
	client.connected = true;
	client.sock = ws;
	ws.on('message', (msg) => log('received: %s', msg));
});

const socketServer = net.createServer((sock) => {
	sock.on('error', (err) => log(err));
	sock.setEncoding('utf-8');

	sock.on('data', data => {
		let line = getLine(sock, data);
		if (!client.connected)
			return sock.write("NO_HTTP_CLIENT: data sent will be lost.\n");
    do {
      if (line) {
        sendLine(sock, client, line);
      }
      log(line);
    } while ((line = getLine(sock)));
	});
});

const sendLine = (sock, client, line) => {
	if (!/^##check-client/.test(line))
		client.sock.send(line + '\n');
	else
		sock.write("200: client connected.\n");
}

httpServer.listen(HTTP_PORT, () => log(`[http] listening on port: ${HTTP_PORT}`));
socketServer.listen(SOCK_PORT, () => log(`[socket] listening on port: ${SOCK_PORT}`));

process.on('SIGINT', function() {
	console.log("Stopping the server...\n");

	httpServer.close();
	socketServer.close();
	process.exit();
});
