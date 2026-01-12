const WebSocket = require('ws');

let wss = new WebSocket.Server({port: 4000, host: 'localhost', path: '/ping-pong'});



wss.on('connection', (ws) => {
    
    ws.on('pong', (data) => {
            console.log(`Got client${++ClientCount}: ${data}`);
    })
    

})


let ClientCount = 0;
let n = 0;

    setInterval(()=>{
        if(wss.clients.size > 0){
        wss.clients.forEach((client)=>{
            client.send(`11-03-server: ${n++}`)
        })
        }
    }, 15000);


    setInterval(()=>{

        if(wss.clients.size >0){
            wss.clients.forEach((client) =>{
                client.ping('check alive');   
            })
        }
        console.log('Client amount: ', ClientCount);

        ClientCount = 0;
    }, 5000);
    