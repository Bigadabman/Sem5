var http = require('http');
var WebSocket = require('ws');
var fs = require('fs');

const HTTPPort = 3000;
const WSPort = 5000;


let httpServer = http.createServer((request, response) => {
    if(request.method == 'GET' && request.url == '/start'){
        let html = fs.readFileSync('10-01.html')

        response.writeHead(200, {'content-type':'text/html;charset=utf-8'});
        response.end(html);
    }
    else{
        response.writeHead(400, {'content-type':'text/html;charset=utf-8'});
        response.end('<h1>400, Bad request');
    }

});

httpServer.listen(HTTPPort, () =>{
    console.log(`http server running at http://localhost:${HTTPPort}/start`);
})




let wsServer = new WebSocket.Server({port: WSPort, host: 'localhost', path:'/ws'});



wsServer.on('connection', (ws) => {

    let ClientMessageNumber = '';
    let socketCounter = 0;

    setInterval(()=>{
        socketCounter++;

        ws.send(`10-01-server: ${ClientMessageNumber}->${socketCounter}`);
    }, 5000)

    ws.on('message', (m) => {

        console.log('message from client: ', m.toString());

        ClientMessageNumber = m.slice('10-01-client: '.length, m.length).toString();

    });

    ws.on('error', (e) => {
        console.log('Error: ', e);
    })

});

console.log(`ws server:  host:${wsServer.options.host}, port: ${wsServer.options.port}, path: ${wsServer.options.path}`);