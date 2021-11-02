// ml5.js: Train Your Own Neural Network
// The Coding Train / Daniel Shiffman
// https://thecodingtrain.com/learning/ml5/6.1-ml5-train-your-own.html
// https://youtu.be/8HEgeAbYphA
// https://editor.p5js.org/codingtrain/sketches/zwGahux8a

let model;
let targetLabel = 'f1';
// let trainingData = [];

let state = 'collection';

//let env, wave;

function setup() {
  //createCanvas(400, 400);

  let options = {
    inputs: ['violet', 'blue', 'green', 'yellow', 'orange', 'red'],
    outputs: ['label'],
    task: 'classification',
    debug: 'true'
  };
  model = ml5.neuralNetwork(options);
  background(255);
}

function keyPressed() {
  if (key == 't') {
    state = 'training';
    console.log('starting training');
    model.normalizeData();
    let options = {
      epochs: 200
    };
    model.train(options, whileTraining, finishedTraining);
  } else {
    targetLabel = key.toUpperCase();
  }
}

function whileTraining(epoch, loss) {
  console.log(epoch);
}

function finishedTraining() {
  console.log('finished training.');
  state = 'prediction';
}

function keyPressed() {
  if (key == ' '){
    let inputs = {
      x: mouseX,
      y: mouseY
    };
  }


  if (state == 'collection') {
    let target = {
      label: targetLabel
    };
    model.addData(inputs, target);
  } else if (state == 'prediction') {
    model.classify(inputs, gotResults);
  }
}

function gotResults(error, results) {
  if (error) {
    console.error(error);
    return;
  }
  console.log(results);
  let label = results[0].label;
}
