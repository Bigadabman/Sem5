var http = require('http');
var fs = require('fs');

http.createServer(function (request, response) {
    if (request.url == "/xmlhttprequest") {
        let xmlhttprequest = fs.readFileSync('./xmlhttprequest.html');
        response.writeHead(200, { 'content-type': 'text-html;charset=utf-8' });
        response.end(xmlhttprequest);
    }
    else if (request.url == "/api/name") {
        response.writeHead(200, {'content-type': 'text/plain; charset=utf-8' });
        response.end('Коробов Егор Олегович');
    }
    else {
        response.writeHead(404, { 'content-type': 'text/plain; charset=utf-8' })
        response.end('404. Страница не найдена');
    }
}).listen(5000);

console.log("Server running at http://localhost:5000/xmlhttprequest");