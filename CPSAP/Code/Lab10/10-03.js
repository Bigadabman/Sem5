var WebSocket = require('ws');

const WSPort = 5000;

let wsServer = new WebSocket.Server({port: WSPort, host: 'localhost', path: '/broadcast'});

wsServer.on('connection', (ws) => {


    ws.on('message', (m) => {
        console.log('got message: ', m.toString());
    })
});

    setInterval(()=>{
        if(wsServer.clients.size > 0){
        wsServer.clients.forEach((client)=>{
            client.send(`Hello from broadcast`)
        })
        }
    }, 5000);