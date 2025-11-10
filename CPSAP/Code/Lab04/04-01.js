var http = require('http');
var url = require('url');
var data_module = require('./DB_module');
const PORT = 5000;

var db = new data_module.DB();

db.on('GET', async(request, response) => {
    response.writeHead(200, {'Content-Type':'application/json; charset=utf-8'});
    response.end(JSON.stringify(db.select()));
})

db.on('POST', async(request, response) => {
    request.on('data', (data) => {
        let dat = JSON.parse(data);
        db.insert(dat);
        response.writeHead(200, {'Content-Type':'application/json; charset=utf-8'});
        response.end(JSON.stringify(db.select()));
    })
});


db.on('PUT', async(request, response) => {
    request.on('data', (data) => {
        let dat = JSON.parse(data);
        db.update(dat);
        response.writeHead(200, {'Content-Type':'application/json; charset=utf-8'});
        response.end(JSON.stringify(db.select()));
    })
});



db.on('DELETE',async(request,response)=>{
    let parsedURL = url.parse(request.url,true);
    const id = parsedURL.query.id;
    if(!id){
        response.writeHead(400,{'content-type':'text/html;charset=utf-8'});
        response.end('<h1>400 Bad request</h1>')
    }
    const deletedRow = db.delete(id);
    response.writeHead(200,{'content-type':'application/json;charset=utf-8'});
    response.end(JSON.stringify(deletedRow));
});



let server = http.createServer(function(request, response){
    if(url.parse(request.url).pathname == '/api/db'){
        db.emit(request.method, request, response);
    }
    else{
        response.writeHead(404,{'Content-Type':'text/html; charset=utf-8'});
        response.end('<h1>404, Not found</h1>');
    }

});

server.listen(PORT);

console.log(`Server running at http://localhost:${PORT}/api/db`);
