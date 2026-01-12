var http = require('http');
var query = require('querystring');

const PORT = 5000;

let body = query.stringify({ x: 1, y: 2, s: 'xxx' });

let options = {
    host: 'localhost',
    port: PORT,
    path: '/09-03',
    method: 'POST',
    headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
        'Content-Length': Buffer.byteLength(body)
    }
};

let req = http.request(options, (res) => {

    console.log('09-03');
    console.log('code:', res.statusCode);

    let responseBody = '';
    res.setEncoding('utf-8');

    res.on('data', chunk => {
        responseBody += chunk;
    });

    res.on('end', () => {
        console.log('body:', responseBody);
    });
});

req.on('error', (e) => {
    console.log('request error:', e.message);
});

req.end(body);
