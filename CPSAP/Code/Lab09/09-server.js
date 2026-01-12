var http = require("http");
var path = require("path");
var fs = require("fs");
var { XMLParser } = require("fast-xml-parser");
var url = require("url");

const PORT = 5000;

const parser = new XMLParser({
  ignoreAttributes: false,
  attributeNamePrefix: "",
});

const server = http.createServer(async (req, res) => {
  let data = "";
  req.on("data", (chunk) => {
    data += chunk;
  });
  const parsedUrl = url.parse(req.url, true);

  switch (true) {
    case req.url == "/09-01" && req.method == "GET":
      res.writeHead(200, { "content-type": "text/plain;charset=utf-8" });
      res.end("09-01 response");

      break;

    case parsedUrl.pathname == "/09-02" && req.method == "GET":
      res.writeHead(200, { "content-type": "text/plain" });
      res.end(
        `09-02: ${parsedUrl.query.x} + ${parsedUrl.query.y} = ${
          Number.parseInt(parsedUrl.query.x) +
          Number.parseInt(parsedUrl.query.y)
        }`
      );

      break;

    case parsedUrl.pathname == "/09-03" && req.method == "POST":

    let body = '';

    req.on('data', chunk => {
        body += chunk;
    });

    req.on('end', () => {

        let params = query.parse(body);

        res.writeHead(200, { 'Content-Type': 'text/plain;charset=utf-8' });
        res.end(
            `09-03: x = ${params.x}, y = ${params.y}, s = ${params.s}`
        );
    });

      break;

    case parsedUrl.pathname == "/09-04" && req.method == "POST":
      req.on("end", () => {
        let json_parsed = JSON.parse(data);

        let JSON_response = {
          _comment: "Ответ: 09-04",
          x_plus_y: Number(json_parsed.x) + Number(json_parsed.y),
          concatination_s_0: String(json_parsed.s)
            .concat(": ")
            .concat(String(json_parsed.o.surname))
            .concat(" ")
            .concat(String(json_parsed.o.name)),
          length_m: json_parsed.m.length,
        };

        res.writeHead(200, {
          "content-type": "application/json;charset=utf-8",
        });
        res.end(JSON.stringify(JSON_response));
      });
      break;

    case parsedUrl.pathname == "/09-05" && req.method == "POST":
      req.on("end", () => {
        try {
          let parsedBody = parser.parse(data);
          if (!parsedBody.request) {
            res.statusCode = 400;
            res.setHeader("Content-Type", "text/plain");
            res.end("xml error: no request field");
          }
          let requestId = Number(parsedBody.request.id);

          let arrayX = parsedBody.request.x;
          let arrayY = parsedBody.request.m;
          if (!Array.isArray(arrayX)) {
            arrayX = [arrayX];
          }

          if (!Array.isArray(arrayY)) {
            arrayY = [arrayY];
          }
          let sumX = arrayX.reduce((accum, element) => {
            let value = Number(element.value);
            return accum + value;
          }, 0);

          let sumY = arrayY.map((element) => element.value).join("");

          const xmlresponse = `<response id="${
            Number(parsedBody.request.id) + 5
          }" request="${parsedBody.request.id}">
    <sum element="x" result="${sumX}"/>
    <concat element="m" result="${sumY}"/>
</response>`;

          res.statusCode = 200;
          res.setHeader("Content-Type", "application/xml");
          res.end(xmlresponse);
        } catch (exception) {
          res.statusCode = 400;
          res.setHeader("Content-Type", "text/plain");
          res.end("xml error: " + exception.message);
        }
      });

      break;

    case parsedUrl.pathname == "/09-06" && req.method == "POST": {
      let file = fs.createWriteStream("Received-MyFile.txt");
      req.pipe(file);

      req.on("end", () => {
        res.writeHead(200, { "Content-Type": "text/plain;charset=utf-8" });
        res.end("TXT file received");
      });

      break;
    }

    case parsedUrl.pathname == "/09-07" && req.method == "POST": {
      let file = fs.createWriteStream("Received-MyFile.png");
      req.pipe(file);

      req.on("end", () => {
        res.writeHead(200, { "Content-Type": "text/plain;charset=utf-8" });
        res.end("PNG file received");
      });

      break;
    }

    case parsedUrl.pathname == "/09-08" && req.method == "GET": {
      res.writeHead(200, {
        "Content-Type": "application/octet-stream",
        "Content-Disposition": 'attachment; filename="ServerFile.txt"',
      });

      fs.createReadStream("ServerFile.txt").pipe(res);

      break;
    }
  }
});

server.listen(PORT, () => {
  console.log("Server running at http://localhost:5000");
});
