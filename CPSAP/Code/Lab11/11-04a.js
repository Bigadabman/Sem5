const { timeStamp } = require('console');
const WebSocket = require('ws');


if(process.argv.length < 3){
    console.log('usage: node Lab-04a.js <client name>');
    process.exit(1);
}

ws = new WebSocket('ws://localhost:4000/json');

ws.on('open', ()=>{
    let json = {
        client: process.argv[2], 
        timeStamp: new Date().getTime()
    }
    setInterval(()=>{ws.send(JSON.stringify(json))}, 5000);


    ws.on('message', (data)=>{
        console.log(data.toString());
    })

})