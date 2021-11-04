
// MQTT client details:
let broker = {
    hostname: 'arduinogang.cloud.shiftr.io/',
    port: 443
};


//testvariables
let b22;
let violetValue;


// MQTT client:
let client;

// client credentials:
// For shiftr.io type in both username and password

let creds = {
    clientID: 'ML',
    userName: 'arduinogang',
    password: 'GUhW31vL7eAbrIr6'
};

// topic to subscribe to when you connect
// For shiftr.io, use whatever word you want 
let topicViolet = 'violet';
let topicBlue = 'blue';
let topicGreen = 'green';
let topicYellow = 'yellow';
let topicOrange = 'orange';
let topicRed = 'red';
let topicBulb = 'bulbType';


//Sensor data buffer
let data = {
  violet: 0,
  blue: 0,
  green: 0,
  yellow: 0,
  orange: 0,
  red: 0
};

//button click
let clicked = false;

let lastTimeSent = 0;
const sendInterval = 500;

function setup() {
    createCanvas(400, 400);
    // Create an MQTT client:
    client = new Paho.MQTT.Client(broker.hostname, broker.port, creds.clientID);
    // set callback handlers for the client:
    client.onConnectionLost = onConnectionLost;
    client.onMessageArrived = onMessageArrived;

    // connect to the MQTT broker:
    client.connect(
        {
            onSuccess: onConnect,       // callback function for when you connect
            userName: creds.userName,   // username
            password: creds.password,   // password
            useSSL: true   // use SSL
        }
    );
    // create a div for local messages:
    localMsg = createP("Local message");
    localMsg.position(20, 50);

    // create a div for the response:
    remoteMsg =  createP("Waiting for message"); 
    remoteMsg.position(20, 80);
}

function draw() {
    background(255);
    noStroke();

    if (millis() - lastTimeSent > sendInterval) {
        sendBulb();
        lastTimeSent = millis();
    }
}

// called when the client connects
function onConnect() {
    localMsg.html('client is connected');
    client.subscribe(topicViolet);
    client.subscribe(topicBlue);
    client.subscribe(topicGreen);
    client.subscribe(topicYellow);
    client.subscribe(topicOrange);
    client.subscribe(topicRed);
}

// called when the client loses its connection
function onConnectionLost(response) {
    if (response.errorCode !== 0) {
        console.log(response.errorMessage);
        localMsg.html('onConnectionLost:' + response.errorMessage);
    }
}

// called when a message arrives
function onMessageArrived(message) {

    //display received message
    remoteMsg.html(message.payloadString);
    
    // assume the message payload is a JSON object  {"x":xPos, "y":yPos}  {"violet":15, "blue":330}  --> key value pairs
    // parse it and use the X and Y:
    let incomData  = JSON.parse(message.payloadString); 
    data.violet = incomData.violet;
    data.blue = incomData.blue;
    data.green = incomData.green;
    data.yellow = incomData.yellow;
    data.orange = incomData.orange;
    data.red = incomData.red;
    console.log("blue: " + data.blue);
    console.log("red: " + data.red);

    //data = {...incomData};
    //data = JSON.parse(message.payloadString);
}


// called when you want to send a message:
function sendMqttMessage(msg, tpc) {
    // if the client is connected to the MQTT broker:
    if (client.isConnected()) {
        // start an MQTT message:
        message = new Paho.MQTT.Message(JSON.stringify(msg));
        // choose the destination topic:
        message.destinationName = tpc;
        // send it:
        client.send(message);
        // print what you sent:
        localMsg.html('I sent: ' + message.payloadString);
    }
}

function sendBulb() {
  //switch case for bulbs
    sendMqttMessage('f1', topicBulb);
}

function addDatapoint(){
  let violet, blue, green, yellow, orange, red;

  console.log("did some data");
  b22 = document.getElementById("bulbType").value;

  //save current sensor readings to variable
  //violet = data.violet;


  //send to neuronal network
}