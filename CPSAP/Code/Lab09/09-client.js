var http = require('http');
var query = require('querystring');
var { XMLParser } = require('fast-xml-parser');
var fs = require('fs');

const parser = new XMLParser(
    {
        ignoreAttributes: false,
        attributeNamePrefix: '',
    }
);


const PORT = 5000;

http.get(`http://localhost:${PORT}/09-01`, (res) => {
    console.log('09-01');
    console.log('code: ', res.statusCode);
    console.log('message: ', res.statusMessage);

    let socket = res.socket;

    console.log('IP: ', socket.remoteAddress);
    console.log('port: ', socket.remotePort);

    let body = '';
    res.setEncoding('utf-8');
    res.on('data', (chunk) => {
        body += chunk;
    });


    res.on('end', () => {
        console.log('body: ', body);
        console.log('------------------------------------');
    });

});



let parms = query.stringify({ x: 1, y: 2 });
http.get(`http://localhost:${PORT}/09-02?${parms}`, (res) => {

    console.log('09-02');
    console.log('code: ', res.statusCode);

    let body = '';
    res.setEncoding('utf-8');
    res.on('data', (chunk) => {
        body += chunk;
    });

    res.on('end', () => {
        console.log('body: ', body);
        console.log('------------------------------------');
    })

});



parms = query.stringify({ x: 1, y: 2, s: 'xxx' });

let options = {
    host: 'localhost',
    path: `/09-03?${parms}`,
    port: PORT,
    method: 'POST'
}

let req = http.request(options, (res) => {

    console.log('09-03');
    console.log('code: ', res.statusCode);

    let body = '';
    res.setEncoding('utf-8');
    res.on('data', (chunk) => {
        body += chunk;
    });

    res.on('end', () => {
        console.log('body: ', body);
        console.log('------------------------------------');
    });

});

req.on('error', (e) => { console.log('request error: ', e.message) });

req.end();



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

        console.log('------------------------------------');
    })

})


req.end(json);



let xml =
    `<request id="28">
    <x value = "1" />
    <x value = "2" />
    <m value = "a" />
    <m value = "b" />
    <m value = "c" />
 </request>
 `;


options = {
    host: 'localhost',
    port: PORT,
    path: '/09-05',
    method: 'POST',
    headers: {
        'content-type': 'application/xml',
        'content-length': Buffer.byteLength(xml)
    }
};

req = http.request(options, (res) => {
    console.log('09-05');
    let xmlResponse = '';
    res.on('data', (chunk) => {
        xmlResponse += chunk;
    });

    res.on('end', () => {
        const parsedXML = parser.parse(xmlResponse);
        console.log('Response body: ', parsedXML);

        console.log('----------------------------');
    });

});


req.end(xml);





options = {
    host: 'localhost',
    port: 5000,
    path: '/09-06',
    method: 'POST',
    headers: {
        'Content-Type': 'text/plain'
    }
};

req = http.request(options, (response) => {
    response.on('data', chunk => console.log(chunk.toString()));
});

fs.createReadStream('MyFile.txt').pipe(req);





options = {
    host: 'localhost',
    port: 5000,
    path: '/09-07',
    method: 'POST',
    headers: {
        'Content-Type': 'image/png'
    }
};

req = http.request(options, (response) => {
    response.on('data', chunk => console.log(chunk.toString()));
});

fs.createReadStream('MyFile.png').pipe(req);



file = fs.createWriteStream('Downloaded-ServerFile.txt');

options = {
    host: 'localhost',
    port: 5000,
    path: '/09-08',
    method: 'GET'
};

const request = http.request(options, (response) => {
    response.pipe(file);
});

request.on('error', err => {
    console.log('Error:', err);
});

request.end();


