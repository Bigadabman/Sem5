const fs = require('fs');
const WebSocket = require('ws');

let wss = new WebSocket.Server({port: 4000, host: 'localhost', path: '/download'});

wss.on('connection', (ws)=>{
    let duplex = WebSocket.createWebSocketStream(ws, {encoding:'utf8'});
    let rfile = fs.createReadStream('./download/MyFile.txt');
    rfile.pipe(duplex);
})