var http = require('http');
var fs = require('fs');


const PORT = 5000;


options = {
    host: 'localhost',
    port: PORT,
    path: '/09-06',
    method: 'POST',
    headers: {
        'Content-Type': 'text/plain'
    }
};

req = http.request(options, (response) => {
    response.on('data', chunk => console.log(chunk.toString()));
});

fs.createReadStream('MyFile.txt').pipe(req);
