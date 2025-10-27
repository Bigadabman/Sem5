var http = require('http');
var fs = require('fs');

http.createServer(function (request, response){
    if(request.url=='/png'){


        const fname='./bobr.png';
        var png = fs.readFileSync(fname);

                  
        response.writeHead(200, {'Content-Type': 'image/png'});
        response.end(png);

    }
    else{
        response.writeHead(404, {'Content-Type': 'text/plain; charset=utf-8;'});
        response.end('Страница не найдена')
    }



}).listen(5000);


console.log('Server running at http://localhost:5000/png');