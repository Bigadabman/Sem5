const rpcWSS = require('rpc-websockets').Server;

let server = new rpcWSS({port:4000, host: 'localhost'});

function fibonacci(num){

    if(num<2)
        return 1;

    return fibonacci(num-1) + fibonacci(num-2);
}

function factorial(num){

    if(num < 2)
        return 1;

    return num * factorial(num-1);
}


server.setAuth((l) => { return l.login == 'keo' && l.password == '1111'});

server.register('square', (params) => {
    if(params.length == 1){
        return Math.pow(params[0], 2) * Math.PI;
    }
    else if (params.length == 2){
        return  params[0] * params[1];
    }
}).public();

server.register('sum', (params) => {
    let sum = 0;

    params.forEach( (a) => {
        sum+=a;    
    });

    return sum;
   } ).public();
   
server.register('mul', (params) => { 
    let res = 1;

    params.forEach( (a) => {
        res*=a; 
    });

    return res;
}).public();

server.register('fib', (params) => {
    if(params.length == 1){
        let result = [];

        for(let i = 0; i < params[0]; i++){
            result[i] = fibonacci(i);
        }

        return result;
    }
}).protected();

server.register('fact', (params) => {
    if(params.length == 1){
        return factorial(params[0]);
    }
}).protected();