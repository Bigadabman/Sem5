var http = require('http');
var fs = require('fs')
const {parse} = require('querystring');
var nodemailer = require('nodemailer');

const PORT = 5000;

let server = http.createServer(function(request, response){
    
    if(request.url=="/" && request.method=="GET"){
        response.writeHead(200, {'content-type':'text/html;charset=utf-8'});
        let html = fs.readFileSync('index.html');
        response.end(html);
    }
    else if(request.url=="/" && request.method=="POST"){
        let body='';
        request.on('data', chunk => {body+=chunk.toString();});
        request.on('end', ()=>{
            const {from, password, to, message} = parse(body);

            const transporter = nodemailer.createTransport({
                service: 'gmail',
                auth: {
                    user:from,
                    pass: password
                },
                secure: true
            });


            const mailOptions = {
                from: from,
                to: to,
                subject: 'Lab 06-02 nodemailer',
                text: message
            }


            transporter.sendMail(mailOptions, (err, info) => {
                if (err) {
                    console.log("Error occured: ", err);
                    response.writeHead(500, { 'content-type': 'text/html;charset=utf-8' });
                    response.end(
                        "<h1>500 Failed to send an email</h1>" +
                        `${err}`
                    );
                }
                if (info) {
                    console.log("Mail successfully sent");
                    response.writeHead(200, { 'content-type': 'text/html;charset=utf-8' });
                    response.end(
                        "<h1>200 Mail successfully sent</h1>" +
                        `<p>Accepted: ${info.accepted}></p>` +
                        `<p>Envelope from: ${info.envelope.from}</p>` +
                        `<p>Envelope to: ${info.envelope.to}</p>` +
                        `<p>Message ID: ${info.messageId}</p>` +
                        `<p>Pending: ${info.pending}</p>` +
                        `<p>Rejected: ${info.rejected}</p>` +
                        `<p>Response: ${info.response}</p>`
                    );
                }

            })


        })
    }
    else{
        response.writeHead(404, {'content-type':'text/html;charset=utf-8'});
        response.end('<h1>404, Not found</h1>')
    }


});

server.listen(PORT);

console.log(`Server running at http://localhost:${PORT}/`)