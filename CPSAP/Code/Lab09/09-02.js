var http = require('http');
var query = require('querystring');
var url = require("url");


const PORT = 5000;


let parms = query.stringify({ x: 1, y: 2 });
http.get(`http://localhost:${PORT}/09-02?${parms}`, (res) => {

    console.log('09-02');
    console.log('code: ', res.statusCode);

    let body = '';
    res.setEncoding('utf-8');
    res.on('data', (chunk) => {
        body += chunk;
    });

    res.on('end', () => {
        console.log('body: ', body);
    })

});