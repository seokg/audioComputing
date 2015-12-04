var canvas = document.getElementById('canvas');
var body = canvas.getContext('2d');
var eye = canvas.getContext('2d');
var eyeball = canvas.getContext('2d');
var iris = canvas.getContext('2d');
var goggle = canvas.getContext('2d');
var pants = canvas.getContext('2d');

var hair = canvas.getContext('2d');

var raf;
var running = false;

var minion = {
  x: 500,
  y: 200,
  vx: 500,
  vy: 200,

  radius: 200,
  eyeradius: 30,
  eyeballradius:65,
  irisradius:20,
  goggleradius:65,

  colorbody: 'gold',
  coloreye:'brown',
  coloreyeball: 'white',
  coloriris: 'black',
  colorgoggle: 'grey',
  colorpants:'blue',

  draw: function() {

// body part
    body.beginPath();
    body.arc(this.x, this.y, this.radius, 0, Math.PI, true);
    body.rect(this.x- this.radius,this.y, this.radius *2, this.radius*2);
    body.closePath();
    body.fillStyle = this.colorbody;
    body.fill();
// pants

    pants.beginPath();
    pants.rect(this.x- this.radius,this.y +this.radius, this.radius *2, this.radius);
    pants.closePath();
    pants.fillStyle = this.colorpants;
    pants.fill();  
// eye balls  
    eyeball.beginPath();
    eyeball.arc(this.x - this.radius/3, this.y-10, this.eyeballradius, 0, Math.PI*2, true);
    eyeball.arc(this.x + this.radius/3, this.y-10, this.eyeballradius, 0, Math.PI*2, true);
    eyeball.closePath();
    eyeball.fillStyle = this.coloreyeball;
    eyeball.fill();
// eye color
    eye.beginPath();
    eye.arc(this.x - this.radius/3, this.y-10, this.eyeradius, 0, Math.PI*2, true);
    eye.arc(this.x + this.radius/3, this.y-10, this.eyeradius, 0, Math.PI*2, true);
    eye.closePath();
    eye.fillStyle = this.coloreye;
    eye.fill();    
// iris
    iris.beginPath();
    iris.arc(this.x - this.radius/3, this.y-10, this.irisradius, 0, Math.PI*2, true);
    iris.arc(this.x + this.radius/3, this.y-10, this.irisradius, 0, Math.PI*2, true);
    iris.closePath();
    iris.fillStyle = this.coloriris;
    iris.fill();
// goggle
    goggle.beginPath();
    goggle.arc(this.x - this.radius/3, this.y-10, this.goggleradius, 0, Math.PI*2, true);

    goggle.closePath();
    goggle.lineWidth = 15;
    goggle.strokeStyle = this.colorgoggle;
    goggle.stroke();
    
    goggle.beginPath();
    goggle.arc(this.x + this.radius/3, this.y-10, this.goggleradius, 0, Math.PI*2, true);
    goggle.closePath();
    goggle.lineWidth = 15;
    goggle.strokeStyle = this.colorgoggle;
    goggle.stroke();
    
// hair    
    
    
  }
};
body
pants
eyeball
eye
iris
goggle

function animate() {
  body.clearRect(0,0, canvas.width, canvas.height);
  pants.clearRect(0,0, canvas.width, canvas.height);
  eyeball.clearRect(0,0, canvas.width, canvas.height);
  eye.clearRect(0,0, canvas.width, canvas.height);
  iris.clearRect(0,0, canvas.width, canvas.height);
  goggle.clearRect(0,0, canvas.width, canvas.height);
  
  minion.draw();
  minion.x += minion.vx;
  minion.y += minion.vy;

  if (minion.y + minion.vy > canvas.height || minion.y + minion.vy < 0) {
  minion.vy = -minion.vy;
  play();
} else {
  stop();
}
if (minion.x + minion.vx > canvas.width || minion.x + minion.vx < 0) {
  minion.vx = -minion.vx;
  play();
}
  raf = window.requestAnimationFrame(animate);
};

//canvas.addEventListener('mousemove', function(e){
  //if (!running) {
    //clear();
    //ball.x = e.clientX;
    //ball.y = e.clientY;
    //ball.draw();
  //}
//};//);

canvas.addEventListener("mouseover",function(){
  if (!running) {
    window.requestAnimationFrame(animate);
    running = true;
    
  }
 
});

canvas.addEventListener("mouseout",function(){
  window.cancelAnimationFrame(raf);
  running = false;
  
});

//WEB AUDIO PART

var context = new AudioContext();

var oscillator = context.createOscillator();
oscillator.type = 'sine';
oscillator.start(0);

var gain = context.createGain();
var mixGain = context.createGain();
gain.gain.value = 0;


function getSample(url, cb) {
  var request = new XMLHttpRequest()
  request.open('GET', url)
  request.responseType = 'arraybuffer'
  request.onload = function() {
    context.decodeAudioData(request.response, cb)
  }
  request.send()
}

getSample('https://dl.dropboxusercontent.com/u/30075450/Greek%207%20Echo%20Hall.wav', function(impulse){
    
var convolver = context.createConvolver()
var buffer = context.createBufferSource()
convolver.buffer = impulse

// Connections 
oscillator.connect(gain);
gain.connect(convolver);
convolver.connect(mixGain);
gain.connect(mixGain);
mixGain.connect(context.destination);

});


function play() {
  oscillator.frequency.value = Math.random() * (1000 - 100) + 100;
  gain.gain.value = 0.8;
}

function stop() {
  gain.gain.value = 0;
}

minion.draw();