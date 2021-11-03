// ml5.js: Train Your Own Neural Network
// The Coding Train / Daniel Shiffman
// https://thecodingtrain.com/learning/ml5/6.1-ml5-train-your-own.html
// https://youtu.be/8HEgeAbYphA
// https://editor.p5js.org/codingtrain/sketches/zwGahux8a

let table;
let spectralData = [];
let model;
let targetLabel = 'f1';
let trainingData = [];
let state = 'collection';

const tableHeader = ['violet','blue','green','yellow','orange','red','label'];

function preload() {
  table = loadTable('DataSet2.csv', 'csv', 'header');
  spectralData = table.getRows();
  console.log(spectralData);
}

//const tableLength = table.getRowCount();

function setup() {
  print(table.getRowCount() + ' total rows in table');
  
  //console.log(tableLength);
 // print(table.getColumnCount() + ' total columns in table');

  let options = {
    inputs: ['violet', 'blue', 'green', 'yellow', 'orange', 'red'],
    outputs: ['label'],
    task: 'classification',
    debug: 'true'
  };
  model = ml5.neuralNetwork(options);
}

function keyPressed() {
  if (key == 't') {
    state = 'training';
    console.log('starting training');
    model.normalizeData();
    let options = {
      epochs: 300
    };
    model.train(options, whileTraining, finishedTraining);
  } else if (key == 'i'){
    console.log('starting data ingestion')
    //ingestData(); // start data ingestion//
    inputDataPoints(spectralData);
    console.log('done');
  }
  else {
    console.log('start data ingestion (i) or model training (t)');
  }
}


function whileTraining(epoch, loss) {
  console.log(epoch);
}

function finishedTraining() {
  console.log('finished training.');
  state = 'prediction';
}

function inputDataPoints(dataPoints) {
  const tableLength = table.getRowCount();
  console.log('im here');
  console.log(tableLength);
  for (let i = 0; i < tableLength; i++) {  
    console.log(dataPoints[i].getNum('violet'));
    let inputs = {
        violet: dataPoints[i].getNum('violet'),
        blue: dataPoints[i].getNum('blue'),
        green: dataPoints[i].getNum('green'),
        yellow: dataPoints[i].getNum('yellow'),
        orange: dataPoints[i].getNum('orange'),
        red: dataPoints[i].getNum('red')
      };

      let target = {
        label: dataPoints[i].getString('label'), //set target label
      };
      model.addData(inputs, target);
      console.log(inputs);
      console.log(target);
      console.log('added datapoints')
  }  
}

function classifyNewReading(){
  model.classify(inputs, gotResults); //predict
}

function gotResults(error, results) {
  if (error) {
    console.error(error);
    return;
  }
  console.log(results);
  let label = results[0].label;
}
