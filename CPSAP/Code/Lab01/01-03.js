var http = require('http');

function h(r){
    let rc = '';
    for(key in r.headers) rc+='<h3>' + key + ': ' + r.headers[key] + '</h3>';
    return rc;
} 


http.createServer(function (request, response){

    let b = '';
    request.on('data', str=>(b+=str, console.log('data', b)));
    response.writeHead(200, {'Content-Type': 'Text/html; charset=utf8'});
    request.on('end', ()=>response.end('<!doctype html> <html>' +
        '<body>'
        +'<h1>Структура запроса</h1>'
        +'<h2>Метод: '+ request.method +'</h2>'
        +'<h2>uri:' + request.url + '</h2>'
        +'<h2>Версия: ' + request.httpVersion + '</h2>'
        +'<h2>Заголовки: '  + '</h2>'  
        + h(request)
        + '<h2> Тело: ' + b + '</h2>'
        + '</body>'        
        + '</html>'));

}).listen(3000);
    
console.log('server running at http://localhost:3000/');