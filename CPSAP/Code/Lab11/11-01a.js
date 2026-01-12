const fs = require('fs');
const WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:4000/upload');

ws.on('open', ()=>{
    let duplex = WebSocket.createWebSocketStream(ws, {encoding: 'utf8'});
    let rfile = fs.createReadStream('./MyFile.txt');
    rfile.pipe(duplex);

})