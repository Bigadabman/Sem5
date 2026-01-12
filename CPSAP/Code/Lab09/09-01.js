var http = require('http');



const PORT = 5000;

http.get(`http://localhost:${PORT}/09-01`, (res) => {
    console.log('09-01');
    console.log('code: ', res.statusCode);
    console.log('message: ', res.statusMessage);

    let socket = res.socket;

    console.log('IP: ', socket.remoteAddress);
    console.log('port: ', socket.remotePort);

    let body = '';
    res.setEncoding('utf-8');
    res.on('data', (chunk) => {
        body += chunk;
    });


    res.on('end', () => {
        console.log('body: ', body);
    });

});