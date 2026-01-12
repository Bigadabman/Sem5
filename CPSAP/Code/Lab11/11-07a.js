let rpcWSS = require('rpc-websockets').Client;

let ws = new rpcWSS('ws://localhost:4000');


ws.on('open', () =>{

    process.stdin.setEncoding('utf8');

    process.stdin.on('data', (data) =>{
        let note = data.toString().toUpperCase().trim();

        if(note == 'A' || note == 'B' || note == 'C'){
            console.log(`notify: ${note}`);
            ws.notify(note);
        }
    })
})