var WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:5000/broadcast');

if(process.argv.length < 3){
    console.log('Usage node 10-03a.js <clientId>');
    process.exit(1);
}


const clientId = process.argv[2];

ws.on('open', () => {
    ws.send(`client ${clientId} connected`);

    ws.on('message', (m) => {
        console.log('got message: ', m.toString());
    })
})