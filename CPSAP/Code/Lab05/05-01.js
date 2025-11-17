var http = require('http');
var url = require('url');
var fs = require('fs');


var data_module = require('./DB_module');
const PORT = 5000;

var db = new data_module.DB();

var serverStats = {
    start_time: null,
    finish_time: null,
    request_count: 0,
    commit_count: 0
}


db.on('GET', async(request, response) => {
    response.writeHead(200, {'Content-Type':'application/json; charset=utf-8'});
    response.end(JSON.stringify(db.select()));
})

db.on('POST', async(request, response) => {
    request.on('data', (data) => {
        let dat = JSON.parse(data);
        db.insert(dat);
        response.writeHead(200, {'Content-Type':'application/json; charset=utf-8'});
        response.end(JSON.stringify(dat));
    })
});


db.on('PUT', async(request, response) => {
    request.on('data', (data) => {
        let dat = JSON.parse(data);
        db.update(dat);
        response.writeHead(200, {'Content-Type':'application/json; charset=utf-8'});
        response.end(JSON.stringify(dat));
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

db.on('COMMIT', async()=>{
    console.log()
    serverStats.commit_count = db.commit();
})



let server = http.createServer(function(request, response){
     if (request) {
        serverStats.request_count++;
    }
    if(url.parse(request.url).pathname == '/api/db'){
        db.emit(request.method, request, response);
    }
    else if (url.parse(request.url).pathname === "/api/ss") {
        response.writeHead(200, { 'content-type': 'application/json;charset=utf-8' });
        
        response.end(JSON.stringify(serverStats));
    }
    else if(request.url=='/'){
        var html = fs.readFileSync('index.html');
        response.writeHead(200, {'Content-Type':'text/html; charset=utf-8'});
        response.end(html);
    }
    else{
        response.writeHead(404,{'Content-Type':'text/html; charset=utf-8'});
        response.end('<h1>404, Not found</h1>');
    }

});

server.listen(PORT);

console.log(`Server running at http://localhost:${PORT}/api/db`);

console.log(`Statistics collected at http://localhost:${PORT}/api/ss`);


process.stdin.setEncoding('utf-8');

process.stdout.write('$~')
process.stdin.on('data', (data)=>{
    const input = data.trim().toLowerCase();

    [command, time] = input.split(' ');
    
    switch(command){
        case 'sd':
            clearTimeout(stopTimeout);
            let duration = parseInt(time);

            if (time) {
                if (!isNaN(duration)) {
                    stopServer(parseInt(time));
                }
            }
            else {
                clearTimeout(stopTimeout);
                console.log("Server stop aborted");
            }

            break;

        case 'sc':
            clearInterval(commitInterval);
            let interval = parseInt(time);
            if (time) {
                if (!isNaN(interval)) {
                    startCommiting(interval);
                }
            }
            else {
                clearInterval(commitInterval);
                console.log("Commit execution aborted");
            }

        break;

        case 'ss':
            clearTimeout(statisticsTimeout);
            let statTimeout = parseInt(time);
            if (time) {
                if (!isNaN(statTimeout)) {
                    collectStatistics(statTimeout);
                }
            }
            else {
                clearTimeout(statTimeout);
                serverStats.finish_time = new Date(Date.now()).toLocaleString();
                console.log("Statistics collection aborted");
            }
            break;

        default:
            console.log('Invalid command')
        break;

    }

})



let stopTimeout;
const stopServer = (delay) => {
    stopTimeout = setTimeout(() => {
        console.log("Timeout passed. Exiting the application...");
        process.exit(0);

    }, delay);
    stopTimeout.unref();
}


let commitInterval;

const startCommiting = (interval) => {
    commitInterval = setInterval(() => {
        db.emit('COMMIT');
        console.log("Commit operation executed");
    }, interval);
    commitInterval.unref();
}


let statisticsTimeout;
const collectStatistics = (collDelay) => {
    serverStats.start_time = new Date(Date.now()).toLocaleString();
    statisticsTimeout = setTimeout(() => {
        serverStats.finish_time = new Date(Date.now()).toLocaleString();
        console.log("Statistic collected");
        console.log(serverStats);
    }, collDelay);

    statisticsTimeout.unref();
}

