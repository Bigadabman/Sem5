const rpcWSS = require('rpc-websockets').Server;

const server = new rpcWSS({port: 4000, host: 'localhost'});

server.event('A');
server.event('B');
server.event('C');

process.stdin.setEncoding('utf8');

process.stdin.on('data', (data)=>{
    let event = data.toString().toUpperCase().trim();

    if(event == 'A' || event == 'B' || event == 'C'){
        console.log(`emit event: ${event}`);
        server.emit(event);
    }
})