var http = require('http');
var { XMLParser } = require('fast-xml-parser');

const parser = new XMLParser(
    {
        ignoreAttributes: false,
        attributeNamePrefix: '',
    }
);


const PORT = 5000;


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
    });

});


req.end(xml);
