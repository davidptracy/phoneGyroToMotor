//===========================================================
//======================= WS Server =========================
//===========================================================

var WebSocketServer = require('ws').Server
  , wss = new WebSocketServer({port: 3000});

var readline = require('readline'); // include the readline module

// create an interface to read lines from the Arduino:
var lineReader = readline.createInterface({
  input: process.stdin, 
  output: process.stdout,
  terminal: false
});

var wsMessage;

console.log("Listening on 3000");

wss.on('connection', function(ws) {

	console.log("New Connection!");

    ws.on('message', function(message) {
        console.log(message);

        // when you get a newline in the stdin (ends with \n),
        // send a reply out the stdout:
        lineReader.on('line', function (data) {
            console.log(data);
        });
    });

    ws.on('close', function() {
        console.log('Client disconnected.');
    });

    ws.on('error', function() {
        console.log('ERROR occured!');
    });

});

