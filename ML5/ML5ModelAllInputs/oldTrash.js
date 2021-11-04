// ml5.js: Train Your Own Neural Network
// The Coding Train / Daniel Shiffman
// https://thecodingtrain.com/learning/ml5/6.1-ml5-train-your-own.html
// https://youtu.be/8HEgeAbYphA
// https://editor.p5js.org/codingtrain/sketches/zwGahux8a

let tableSpectral;
let tablePrediction;
let spectralData = [];
let predictionData = [];
let model;
let targetLabel = 'f1';
let trainingData = [];
let state = 'collection';
var options;
const tableHeader = ['violet','blue','green','yellow','orange','red','label'];

function preload() {
  tableSpectral = loadTable('DataSet102.csv', 'csv', 'header');
  spectralData = tableSpectral.getRows();
  //console.log(spectralData);

  tablePrediction = loadTable('DataSet103.csv', 'csv', 'header');
  predictionData = tablePrediction.getRows();
  //console.log(predictionData);
}

function setup() {
  print(tableSpectral.getRowCount() + ' total rows in table');
  

  options = {
    //inputs: ['violet', 'blue', 'green', 'yellow', 'orange', 'red'],
    inputs: 2,
    outputs: ['label'],
    task: 'regression',
    debug: 'true',
    learningRate: 0.2,
    epochs: 50,
  };
  model = ml5.neuralNetwork(options);

}

function keyPressed() {
  if (key == 't') {
    state = 'training';
    console.log('starting training');
 
    model.train(options, whileTraining, finishedTraining);
  } else if (key == 'i'){
    console.log('starting data ingestion');
    inputDataPoints(spectralData);
    console.log('done');
  }
  else if (key == 'p'){
    console.log('predict data:');
    inputPredictionPoints(predictionData);
    console.log('done prediction');
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
  const tableLength = tableSpectral.getRowCount();
  //console.log('im here');
  //console.log(tableLength);
  for (let i = 0; i < tableLength; i++) {  
    //console.log(dataPoints[i].getNum('violet'));
    let inputs = {
        //violet: dataPoints[i].getNum('violet'),
        //blue: dataPoints[i].getNum('blue'),
        green: dataPoints[i].getNum('green'),
        //yellow: dataPoints[i].getNum('yellow'),
        //orange: dataPoints[i].getNum('orange'),
        red: dataPoints[i].getNum('red')
      };

      let outputs = {
        label: dataPoints[i].getNum('label'), //set target label
      };
    
      model.addData(inputs, outputs);
      model.normalizeData();
      console.log("normalize" + ":" + neuralNetworkData.meta.isNormalized);
     
      //console.log(inputs);
      console.log(inputs);
      console.log('added datapoints')
  }  
}


function inputPredictionPoints(predictionPoints){
  const tableLength = tablePrediction.getRowCount();
  for (let i = 0; i < tableLength; i++) {  
    let inputs = {
        //violet: predictionPoints[i].getNum('violet'),
        //blue: predictionPoints[i].getNum('blue'),
        green: predictionPoints[i].getNum('green'),
        //yellow: predictionPoints[i].getNum('yellow'),
        //orange: predictionPoints[i].getNum('orange'),
        red: predictionPoints[i].getNum('red')
      };
    
      console.log('added predictionPoints');
     console.log(inputs[i])
      model.predict(inputs, gotResults);
  }  
}

function gotResults(error, results) {
  if (error) {
    console.error(error);
    return;
  }
  //console.log(results);
  let label = results[0].value;
  console.log(results);
  //console.log(label);
}
