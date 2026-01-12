var http = require('http');
var fs = require('fs');


const PORT = 5000;


options = {
    host: 'localhost',
    port: PORT,
    path: '/09-07',
    method: 'POST',
    headers: {
        'Content-Type': 'image/png'
    }
};

req = http.request(options, (response) => {
    response.on('data', chunk => console.log(chunk.toString()));
});

fs.createReadStream('MyFile.png').pipe(req);