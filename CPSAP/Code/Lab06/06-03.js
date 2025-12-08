var http = require('http');
var fs = require('fs')
const {parse} = require('querystring');
var {send} = require('./package/m0603');

const PORT = 5000;

let server = http.createServer(function(request, response){
    
    if(request.url=="/" && request.method=="GET"){
        response.writeHead(200, {'content-type':'text/html;charset=utf-8'});
        let html = fs.readFileSync('m0603.html');
        response.end(html);
    }
    else if(request.url=="/" && request.method=="POST"){
        let body='';
        request.on('data', chunk => {body+=chunk.toString();});
        request.on('end', ()=>{
            const { password, message} = parse(body);

            send(message, password)
                    .then(info => {
                        response.writeHead(200, { 'content-type': 'text/html;charset=utf-8' });
                        response.end("<h1>200 Mail successfully sent</h1>");
                    })
                    .catch(err => {
                        console.log(err)
                        response.writeHead(500, { 'content-type': 'text/html;charset=utf-8' });
                        response.end("<h1>500 Failed to send an email</h1>");
                    })


        })
    }
    else{
        response.writeHead(404, {'content-type':'text/html;charset=utf-8'});
        response.end('<h1>404, Not found</h1>')
    }


});

server.listen(PORT);

console.log(`Server running at http://localhost:${PORT}/`)