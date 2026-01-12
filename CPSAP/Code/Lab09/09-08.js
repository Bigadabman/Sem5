var http = require('http');
var fs = require('fs');


const PORT = 5000;


file = fs.createWriteStream('Downloaded-ServerFile.txt');

options = {
    host: 'localhost',
    port: PORT,
    path: '/09-08',
    method: 'GET'
};

const request = http.request(options, (response) => {
    response.pipe(file);
});

request.on('error', err => {
    console.log('Error:', err);
});

request.end();