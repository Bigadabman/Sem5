var http = require('http');
const { stdin } = require('process');


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

process.stdin.setEncoding('utf-8');


process.stdout.write(`${appStatus}->`);
process.stdin.on('data', (data) => {
  const input = data.trim().toLowerCase();

  switch (input) {
    case 'exit':
      process.exit(0);
      break;

    case 'norm':
    case 'stop':
    case 'idle':
      console.log(`reg = ${appStatus} --> ${input}`);
      appStatus = input;
      break;

    default:
      console.log(`${input}`);
      break;
  }

  process.stdout.write(`${appStatus}->`);
});


