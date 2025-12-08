var http = require('http');
const staticHandler = require('./m07-01')('static');

const PORT = 5000;


const server = http.createServer(staticHandler);

server.listen(PORT, () => {
    console.log("Server running on http://localhost:5000");
});

