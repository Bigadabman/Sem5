var http = require('http');
const { stdin } = require('process');
var readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
})


var appStatus = "norm";

http.createServer(function(request, response){

    if(request.url == "/"){
        response.writeHead(200, {"Content-Type": "text/html; charset=utf-8"});
        response.end(`<h1>${appStatus}</h1>`)
    }
    else{
        response.writeHead(404, {'Content-type': 'text/html;charset=utf-8'});
        response.end('<h1>404. Страница не найдена</h1>')
    }


}).listen(5000);

console.log('Server running at http://localhost:5000/')



const changeState = () => {

    rl.question(`${appStatus}-> `, (input)=>{

         input = input.trim().toLowerCase();

        if(input=='exit'){
            console.log('Now exiting')

            rl.close();
            process.exit(0);

        }
        else if(['norm', 'stop', 'test', 'idle'].includes(input)){
            console.log(`reg = ${appStatus}--> ${input}`);
            appStatus=input;
        }
        else{
            console.log(`${appStatus}--> ${input}`);
        }

   changeState();
    });

 
}

changeState();

