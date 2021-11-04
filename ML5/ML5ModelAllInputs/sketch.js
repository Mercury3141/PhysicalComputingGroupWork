
let model;
let xs, ys;
let labelP;
let lossP;

let tableSpectral;
let tablePrediction;
let spectralData = [];
let predictionData = [];

let tableHeader= ['violet','blue','green','yellow','orange','red','label']
let labelList = [
  'atelier',
  'draussen'
]

let next = 0;


function preload() {
  tableSpectral = loadTable('DataSet102.csv', 'csv', 'header');
  spectralData = tableSpectral.getRows();
  //console.log(spectralData);

  tablePrediction = loadTable('DataSet103.csv', 'csv', 'header');
  predictionData = tablePrediction.getRows();
  //console.log(predictionData);
}


function setup() {
  // Crude interface
  labelP = createP('label');
  lossP = createP('loss');

  let readings = [];
  let labels = []; 
 
 
  for (var i = 0; i < tableSpectral.getRowCount(); i++) {
     readings = [tableSpectral.getNum(i, "violet"),tableSpectral.getNum(i, "blue"),tableSpectral.getNum(i, "green"),tableSpectral.getNum(i, "yellow"),tableSpectral.getNum(i, "orange"),tableSpectral.getNum(i, "red")]
     labels = [tableSpectral.getString(i, "label")]
    }

  xs = tf.tensor2d([readings]);
  let labelsTensor = tf.tensor1d(labels, 'int32');

  ys = tf.oneHot(labelsTensor, 2).cast('float32');
  labelsTensor.dispose();

  model = tf.sequential();
  const hidden = tf.layers.dense({
    units: 16,
    inputShape: [6],
    activation: 'sigmoid'
  });
  const output = tf.layers.dense({
    units: 2,
    activation: 'softmax'
  });
  model.add(hidden);
  model.add(output);

  const LEARNING_RATE = 0.25;
  const optimizer = tf.train.sgd(LEARNING_RATE);

  model.compile({
    optimizer: optimizer,
    loss: 'categoricalCrossentropy',
    metrics: ['accuracy'],
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
        lossP.html('loss: ' + logs.loss);
      },
      onBatchEnd: async (batch, logs) => {
        await tf.nextFrame();
      },
      onTrainEnd: () => {
        console.log('finished')
      },
    },
  });
}



function keyPressed() {

 if (key == 'p'){
    console.log('predict data:');

    readings = [tablePrediction.getNum(next, "violet"),tablePrediction.getNum(next, "blue"),tablePrediction.getNum(next, "green"),tablePrediction.getNum(next, "yellow"),tablePrediction.getNum(next, "orange"),tablePrediction.getNum(next, "red")];
    
    tf.tidy(() => {
      const input = tf.tensor2d([readings]);
      let results = model.predict(input);
      let index = results.argMax(1).dataSync()[0];
      let label = labelList[index];
      console.log("label" + " " + label);
    });
    if (next < tablePrediction.getRowCount() - 1) {
      next += 1;
    } else {
      next = 0;
    }
  } 
} 