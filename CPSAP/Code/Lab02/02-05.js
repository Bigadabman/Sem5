var http = require('http');
var fs = require('fs');

http.createServer(function (request, response){
    if (request.url == "/fetch"){
        let html = fs.readFileSync('./fetch.html');
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.end(html);
    }
    else if (request.url == "/api/name"){
        response.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
        response.end("Коробов Егор Олегович");
    }
    else {
        response.writeHead(404, { 'content-type': 'text/plain; charset=utf-8' })
        response.end('404. Страница не найдена');
    }
}).listen(5000);

console.log('Server running at http://localhost:5000/fetch');

