var http = require('http');


const PORT = 5000;



let json = JSON.stringify({
    comment: "Запрос.Лабораторная работа 09-04",
    x: 1,
    y: 2,
    s: "Сообщение",
    m: [
        "a",
        "b",
        "c",
        "d"
    ],
    o: {
        surname: "Иванов",
        name: "Иван"
    }
});


options = {
    host: 'localhost',
    port: PORT,
    path: '/09-04',
    method: 'POST',
    headers: { 'content-type': 'application/json', 'accept': 'application/json' }
};

req = http.request(options, (res) => {
    console.log('09-04');
    console.log('code: ', res.statusCode);


    let body = '';

    res.on('data', (chunk) => { body += chunk.toString('utf-8') });
    res.on('end', () => {
        console.log('body: ', body);
        console.log('parse(body): ', JSON.parse(body));
    })

})


req.end(json);