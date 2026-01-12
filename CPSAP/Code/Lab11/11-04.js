const WebSocket = require('ws');

let wss = new WebSocket.Server({port: 4000, host: 'localhost', path:'/json'});


let n = 0;
wss.on('connection', (ws)=>{

    ws.on('message', (data)=>{
        console.log(data.toString());

        let clientJSON = JSON.parse(data);

        jsonResponse = {
            server: n++,
            client: clientJSON.client,
            timestamp: Date.now()
        }

        ws.send(JSON.stringify(jsonResponse));
    });

})