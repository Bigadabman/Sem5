var http = require('http');

http.createServer(function (request, response){
    if(request.url=='/api/name'){

        response.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8;'});
        response.end('Коробов Егор Олегович');

    }
    else{
        response.writeHead(404, {'Content-Type': 'text/plain; charset=utf-8;'});
        response.end('Страница не найдена');
    }
}).listen(5000);

console.log('Server running at http://localhost:5000/api/name');