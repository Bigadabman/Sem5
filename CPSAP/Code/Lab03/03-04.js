var http = require('http');
var url = require('url');
var fs = require('fs');

http.createServer(function(request, response){

    if(url.parse(request.url).pathname == '/fact'){
        const parsedUrl = url.parse(request.url, true);
        const k = parseInt(parsedUrl.query.k);

       


        if(request.method=='GET' && parsedUrl.pathname == '/fact' && !isNaN(k)){

            const fact = factorial(k, (fact)=>{
            
            if(fact!=null){

                response.writeHead(200, {'Content-type':'application/json;charset=utf-8'});
                response.end(JSON.stringify({
                k: k,
                fact: fact
                 }))
            }
            else{
                response.writeHead(400,{'content-type':'application/json;charset=utf-8'});
                response.end(JSON.stringify({
                error:"Factoriated number was less then 0 or not a number"
                }));
            }
        });

        }
        else if (request.method=='GET' && parsedUrl.pathname == '/fact'){
            var html = fs.readFileSync('factorial.html');
            response.writeHead(200, {'content-type': 'text/html;charset=utf-8'});
            response.end(html);
        }


    }


}).listen(5000);

console.log('server running at http://localhost:5000/fact')

function factorial(n, callback){

    if(isNaN(n) || n < 0){
        return callback(null);
    }

    if(n==0)
        return callback(1);

    let result = 1;

    function calculate(num){
        result*=num;
        if(num>1)
            process.nextTick(()=>calculate(num-1));
        else
            callback(result);
    }

    calculate(n);

}

// 1 вкладка - 230мс
// 2 вкладки - 207мс и 230мс
// 3 вклдаки - 234мс, 334мс и 218мс


