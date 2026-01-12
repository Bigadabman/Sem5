const fs = require('fs');
const WebSocket = require('ws');

let wsServer = new WebSocket.Server({port: 4000, host: 'localhost', path:'/upload'});

let k = 0;
wsServer.on('connection', (ws)=>{
    let duplex = WebSocket.createWebSocketStream(ws, {encoding:'utf8'});
    let wfile = fs.createWriteStream(`./upload/GotFile${k++}.txt`);
    duplex.pipe(wfile);
})