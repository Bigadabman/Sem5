const rpcWSS = require('rpc-websockets').Client;
const async = require('async');

let ws = new rpcWSS('ws://localhost:4000');

ws.on('open', () => {

    ws.login({ login: 'keo', password: '1111' })
        .then((logged) => {
            if (!logged) {
                throw new Error('login failed');
            }

            async.parallel(
                {
                    square3: (cb) => {ws.call('square', [3]).then(r => cb(null, r)).catch(e => cb(e));},
                    square54: (cb) => {ws.call('square', [5, 4]).then(r => cb(null, r)).catch(e => cb(e));},
                    mulBig: (cb) => {ws.call('mul', [3, 5, 7, 9, 11, 13]).then(r => cb(null, r)).catch(e => cb(e));},
                    fib7: (cb) => {ws.call('fib', [7]).then(r => cb(null, r)).catch(e => cb(e));},
                    mul246: (cb) => {ws.call('mul', [2, 4, 6]).then(r => cb(null, r)).catch(e => cb(e));}
                },
                (error, result) => {
                    if (error) {
                        console.log('RPC error:', error);
                        return;
                    }

                    const left = result.square3 + result.square54 + result.mulBig;

                    const right = result.fib7.length * result.mul246;

                    const finalResult = left + right;


                    console.log('result =', finalResult);
                }
            );
        })
        .catch((e) => {
            console.log('error:', e.message);
        });
});

ws.on('error', (e) => {
    console.log('ws error:', e.message);
});
