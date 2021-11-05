//////// MQTT

// MQTT client details:
let broker = {
  hostname: "arduinogang.cloud.shiftr.io/",
  port: 443,
};

//colors
let violet;
let blue;
let green;
let yellow;
let orange;
let red;

// MQTT client:
let client;

// client credentials:
// For shiftr.io type in both username and password

let creds = {
  clientID: "ML5",
  userName: "arduinogang",
  password: "GUhW31vL7eAbrIr6",
};

// topic to subscribe to when you connect
// For shiftr.io, use whatever word you want
let topicViolet = "filteredSpectrums";
let topicBulb = "bulb";

//Sensor data buffer
let data = {
  violet: 0,
  blue: 0,
  green: 0,
  yellow: 0,
  orange: 0,
  red: 0,
};

//button click
let clicked = false;

let lastTimeSent = 0;
const sendInterval = 500;

//////// TENSOR
let model;
let xs, ys;
let labelP;
let lossP;

let tableSpectral;
let tablePrediction;
let spectralData = [];
let predictionData = [];

let tableHeader = [
  "violet",
  "blue",
  "green",
  "yellow",
  "orange",
  "red",
  "label",
];
let labelList = ["atelier", "draussen"];

let next = 0;

let predictionMqtt = "noPrediction";

function preload() {
  tableSpectral = loadTable("DataSet102.csv", "csv", "header");
  spectralData = tableSpectral.getRows();
  //console.log(spectralData);

  tablePrediction = loadTable("DataSet103.csv", "csv", "header");
  predictionData = tablePrediction.getRows();
  //console.log(predictionData);
}

function setup() {
  /////MQTT
  createCanvas(400, 400);
  // Create an MQTT client:
  client = new Paho.MQTT.Client(broker.hostname, broker.port, creds.clientID);
  // set callback handlers for the client:
  client.onConnectionLost = onConnectionLost;
  client.onMessageArrived = onMessageArrived;

  // connect to the MQTT broker:
  client.connect({
    onSuccess: onConnect, // callback function for when you connect
    userName: creds.userName, // username
    password: creds.password, // password
    useSSL: true, // use SSL
  });
  // create a div for local messages:
  localMsg = createP("Local message");
  localMsg.position(20, 50);

  // create a div for the response:
  remoteMsg = createP("Waiting for message");
  remoteMsg.position(20, 80);

  /////// TENSOR
  // Crude interface
  labelP = createP("label");
  lossP = createP("loss");

  let readings = [];
  let labels = [];

  for (var i = 0; i < tableSpectral.getRowCount(); i++) {
    readings = [
      tableSpectral.getNum(i, "violet"),
      tableSpectral.getNum(i, "blue"),
      tableSpectral.getNum(i, "green"),
      tableSpectral.getNum(i, "yellow"),
      tableSpectral.getNum(i, "orange"),
      tableSpectral.getNum(i, "red"),
    ];
    labels = [tableSpectral.getString(i, "label")];
  }

  xs = tf.tensor2d([readings]);
  let labelsTensor = tf.tensor1d(labels, "int32");

  ys = tf.oneHot(labelsTensor, 2).cast("float32");
  labelsTensor.dispose();

  model = tf.sequential();
  const hidden = tf.layers.dense({
    units: 16,
    inputShape: [6],
    activation: "sigmoid",
  });
  const output = tf.layers.dense({
    units: 2,
    activation: "softmax",
  });
  model.add(hidden);
  model.add(output);

  const LEARNING_RATE = 0.25;
  const optimizer = tf.train.sgd(LEARNING_RATE);

  model.compile({
    optimizer: optimizer,
    loss: "categoricalCrossentropy",
    metrics: ["accuracy"],
  });

  train();
}

async function train() {
  console.log(model);
  console.log(xs);
  console.log(ys);

  await model.fit(xs, ys, {
    shuffle: true,
    validationSplit: 0.1,
    epochs: 100,
    callbacks: {
      onEpochEnd: (epoch, logs) => {
        console.log(epoch);
        lossP.html("loss: " + logs.loss);
      },
      onBatchEnd: async (batch, logs) => {
        await tf.nextFrame();
      },
      onTrainEnd: () => {
        console.log("finished");
      },
    },
  });
}
/*
function keyPressed() {
  if (key == "p") {
    console.log("predict data:");
    
    //readings = [tablePrediction.getNum(next, "violet"),tablePrediction.getNum(next, "blue"),tablePrediction.getNum(next, "green"),tablePrediction.getNum(next, "yellow"),tablePrediction.getNum(next, "orange"),tablePrediction.getNum(next, "red")];
    
    readings = [violet, blue, green, yellow, orange, red];

    tf.tidy(() => {
      const input = tf.tensor2d([readings]);
      let results = model.predict(input);
      let index = results.argMax(1).dataSync()[0];
      let label = labelList[index];
      predictionMqtt = label;
      console.log("label" + " " + label);
    });
    if (next < tablePrediction.getRowCount() - 1) {
      next += 1;
    } else {
      next = 0;
    }
  }
}
*/

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
  localMsg.html("client is connected");
  client.subscribe(topicViolet);
}

// called when the client loses its connection
function onConnectionLost(response) {
  if (response.errorCode !== 0) {
    console.log(response.errorMessage);
    localMsg.html("onConnectionLost:" + response.errorMessage);
  }
}

// called when a message arrives
function onMessageArrived(message) {
  //display received message
  remoteMsg.html(message.payloadString);

  // assume the message payload is a JSON object  {"x":xPos, "y":yPos}  {"violet":15, "blue":330}  --> key value pairs
  // parse it and use the X and Y:
  let incomData = JSON.parse(message.payloadString);
  data.violet = incomData.violet;
  data.blue = incomData.blue;
  data.green = incomData.green;
  data.yellow = incomData.yellow;
  data.orange = incomData.orange;
  data.red = incomData.red;

  violet = data.violet;
  blue = data.blue;
  green = data.green;
  yellow = data.yellow;
  orange = data.orange;
  red = data.red;

  console.log("violet: " + violet);
  console.log("blue: " + blue);
  console.log("green: " + green);
  console.log("yellow: " + yellow);
  console.log("orange: " + orange);
  console.log("red: " + red);

//Tensor Predict
  console.log("predict data:");
  
  readings = [violet, blue, green, yellow, orange, red];

  tf.tidy(() => {
    const input = tf.tensor2d([readings]);
    let results = model.predict(input);
    let index = results.argMax(1).dataSync()[0];
    let label = labelList[index];
    predictionMqtt = label;
    console.log("label" + " " + label);
  });
  if (next < tablePrediction.getRowCount() - 1) {
    next += 1;
  } else {
    next = 0;
  }
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
    localMsg.html("I sent: " + message.payloadString);
  }
}

function sendBulb() {
  //switch case for bulbs
  //sendMqttMessage(predictionMqtt, topicBulb);
  sendMqttMessage('1', topicBulb);

}
