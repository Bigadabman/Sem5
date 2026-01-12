const WebSocket = require('ws');

let ws = new WebSocket('ws://localhost:4000/ping-pong');

ws.on('open', () => {
    ws.on('ping', (data)=>{
        console.log(`ping: ${data}`);
    });

    ws.on('message', (data)=>{
        console.log('got message: ', data.toString());
    })

})