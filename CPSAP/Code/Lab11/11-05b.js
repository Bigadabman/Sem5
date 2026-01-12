const rpcWSS = require('rpc-websockets').Client;
const async = require('async');
let ws = new rpcWSS('ws://localhost:4000');


ws.on('open', () => {
    ws.login({login: 'keo', password: '1111'})
        .then((logged)=>{
            if(!logged){
                throw new Error('login failed');
            }

            async.parallel({
                square: (cb) => { ws.call('square', [3]).then((r) => cb(null, r)).catch(e => cb(e, null));;},
                square1: (cb) => {ws.call('square', [5, 4]).then((r) => cb(null, r)).catch(e => cb(e, null));;},
                sum: (cb) => {ws.call('sum', [2]).then((r) => cb(null, r)).catch(e => cb(e, null));},
                sum1: (cb) => {ws.call('sum', [2, 4, 6 ,8 ,10]).then((r) => cb(null, r)).catch(e => cb(e, null));},
                mull: (cb) => {ws.call('mul', [3]).then((r) => cb(null, r)).catch(e => cb(e, null));},
                mull1: (cb) => {ws.call('mul', [3,5,7,9,11,13]).then((r) => cb(null, r)).catch(e => cb(e, null));},
                fib:(cb) => {ws.call('fib', [1]).then((r) => cb(null, r)).catch(e => cb(e, null));},
                fib1:(cb) => {ws.call('fib', [2]).then((r) => cb(null, r)).catch(e => cb(e, null));},
                fib2:(cb) => {ws.call('fib', [7]).then((r) =>cb(null, r)).catch(e => cb(e, null));},
                fact: (cb) => {ws.call('fact', [0]).then((r) => cb(null, r)).catch(e => cb(e, null));},
                fact1: (cb) => {ws.call('fact', [5]).then((r) => cb(null, r)).catch(e => cb(e, null));},
                fact2: (cb) => {ws.call('fact', [10]).then((r) => cb(null, r)).catch(e => cb(e, null));},
            },
            (error, result) => {
                if(error){
                    console.log('error: ', error)
                }
                else{
                    console.log('result = ', result);
                }
            } 
        )


        })
        .catch((e) => {
            console.log('error: ', e);
        })
})

ws.on('error', (e) => {
    console.log('ws error: ', e);
})