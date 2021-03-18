const log = console.log;
HTTP_PORT = 3000;
SOCK_PORT = 8000;

'use strict';
const fs = require('fs');
const net = require('net');
const http = require('http');
const WebSocket = require('ws');
const {MIMETypes, client, getLine} = require('./src/lib');
const wss = new WebSocket.Server({ noServer: true });

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
	ws.on('message', (msg) => {
		let line = getLine(ws, msg);

    do {
      if (line) {
        sendLine(line, client.sock_to);
      }
      log(`[msg] [ws] ${line}`);
    } while ((line = getLine(ws)));
  });
});

const socketServer = net.createServer((sock) => {
	sock.setEncoding('utf-8');
	client.sock_to = sock;

  sock.on("error", (e) => {
    if (e.code === "EPIPE")
      log('[socket] closed.');
  });

	sock.on('data', data => {
		let line = getLine(sock, data);
		if (!client.connected)
			return sock.write("ERR: NO_HTTP_CLIENT\n");
    do {
      if (line) {
        sendLine(line, client.sock);
      }
      log(`[msg] [socket] ${line}`);
    } while ((line = getLine(sock)));
	});
});

const sendLine = (line, sock) => {
	if (sock instanceof WebSocket)
			return sock.send(line + '\n');
	return sock?.write(line + '\n');
}

socketServer.on('error', (err) => {
  if (err.code === 'EADDRINUSE') {
    console.log('Address in use, retrying...');
    setTimeout(() => {
      socketServer.close();
      socketServer.listen(HTTP_PORT);
    }, 1000);
  }
  // log(err);
});

httpServer.on('error', (err) => {
  if (err.code === 'EADDRINUSE') {
    console.log('Address in use, retrying...');
    setTimeout(() => {
      socketServer.close();
      socketServer.listen(HTTP_PORT);
    }, 1000);
  }
  // log(err);
});

httpServer.listen(HTTP_PORT, () => log(`[http] listening on port: ${HTTP_PORT}`));
socketServer.listen(SOCK_PORT, () => log(`[socket] listening on port: ${SOCK_PORT}`));

process.on('SIGINT', function() {
	console.log("Stopping the server...\n");

	httpServer.close();
	socketServer.close();
	process.exit();
});
