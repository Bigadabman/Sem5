var WebSocket = require('ws');

const WSPort = 5000;

let wsServer = new WebSocket.Server({port: WSPort, host: 'localhost', path: '/broadcast'});

wsServer.on('connection', (ws) => {
    ws.on('message', (m) => {
        console.log('got message: ', m.toString());
        wsServer.clients.forEach((client) => {
            if(client.readyState == WebSocket.OPEN) client.send(`message: ${m}`);
        })
    })
});