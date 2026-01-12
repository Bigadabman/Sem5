const fs = require('fs');
const WebSocket = require('ws');


let ws = new WebSocket('ws://localhost:4000/download');
let k = 0;
ws.on('open', ()=>{
    let duplex = WebSocket.createWebSocketStream(ws, {encoding:'utf8'});
    let wfile = fs.createWriteStream(`./ClientGet/ServFile${k++}.txt`);
    duplex.pipe(wfile);
})