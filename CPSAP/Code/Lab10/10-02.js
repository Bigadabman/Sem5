var WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:5000/ws');

ws.on('open', ()=>{

    let k = 0;

    console.log('socket.open');
    let SendInterval = setInterval(()=>{ws.send(`10-01-client: ${++k}`)}, 3000);

    SendInterval .unref();

    setTimeout(() => {
        ws.send('client closes socket');
        ws.close()
       }, 25000);

    ws.on('message', (message) => {console.log('got message: ', message.toString());});

    ws.on('close', (m) =>{ console.log('socket.close',m);
        
    });

    ws.on('error', (error) => { console.log('Error: ', error.message); })
    

    
})