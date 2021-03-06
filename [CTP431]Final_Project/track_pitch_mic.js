
  var context;
  var myAudioBuffer = null;
  var analyser;
  
  var spec_view;
  var WIDTH = 640;
  var HEIGHT = 320;
  
  
  // initial setting for pitch detection
  var PITCH_MIN = 36;
  var PITCH_MAX = 96;
  var PITCH_STEP = 0.25;
  var pitch_range = [];
  var pitch_range_hz = [];
  var NUM_HARMONICS = 15; 


  // variable declared ///////////////////
  var comb_filter;
  var sum_filter;
  var num_harmonics = 10;
  var binfrqs;
  var row_comb;
  var col_comb;
  var pitch_gram;
  var energy;
  var audioArray_power;
  var max_pitch_gram;
  var max_pitch_index;
  var harmonicity;
  var dataArray;
  ////////////////////////////////////////




  window.onload=function(){   
    // canvas 
    spec_view = document.getElementById("spec_view");
    spec_view.width =  WIDTH;
    spec_view.height = HEIGHT;  
    
    // create audio context
    context = new AudioContext();

    // analyzer
    analyser = context.createAnalyser();
    analyser.fftSize = 2048;
    analyser.smoothingTimeConstant = 0;   
    // pitch range of interest
    for (var pitch = PITCH_MIN; pitch <= PITCH_MAX; pitch = pitch + PITCH_STEP) 
    {
      pitch_range.push(pitch);
      pitch_range_hz.push(midi2hertz(pitch))
    }
    dataArray = new Float32Array(analyser.frequencyBinCount);
//////////////////////////////////////////////////////////
    // filter design

    row_comb = analyser.frequencyBinCount;
    col_comb = pitch_range.length;
    
    fft_size = analyser.fftSize;
    binfrqs =  new Float32Array(fft_size);

    for (var i =0; i<row_comb;i++){
      binfrqs[i] =  (i/(fft_size))*context.sampleRate; 
    }        
    
    comb_filter = new Array(col_comb);
    sum_filter = new Array(col_comb);
    for (var i = 0; i< col_comb ; i++){
      comb_filter[i] = new Float32Array(row_comb);
      sum_filter[i]  = new Float32Array(row_comb);

      for (var j =0 ; j< row_comb; j++){

        comb_filter[i][j] = 0.5*Math.cos(2*Math.PI*binfrqs[j]/(pitch_range_hz[i]))+0.5;
        sum_filter[i][j] = 1;

        if (binfrqs[j] > num_harmonics*pitch_range_hz[i]){
        comb_filter[i][j] = 0;
        sum_filter[i][j] = 0;
        }

        if (binfrqs[j] < pitch_range_hz[i]/2){
          comb_filter[i][j] = 0;
          sum_filter[i][j] = 0; 
        }

      }
    }
//////////////////////////////////////////////////////////

  }
  
  function midi2hertz(midi) {
    var hertz;
    ///// YOUR CODE IS HERE /////
    hertz = (Math.pow(2,(midi-69)/12)) * 440; 
    /////////////////////////////
    return hertz;
  }
  
  function draw_spec() {
    // 2d canvas context
    var drawContext = spec_view.getContext('2d');
    
    // fill rectangular
    drawContext.fillStyle = 'rgb(15, 71, 225)';
    drawContext.fillRect(0, 0, WIDTH, HEIGHT);

    // drawing line setting
    drawContext.lineWidth = 2;
    drawContext.strokeStyle = 'rgb(255, 255, 255)';
    drawContext.beginPath();
        
    // get samples 
    analyser.getFloatFrequencyData(dataArray);
    
    var freq_scale = 10;
    var sliceWidth = WIDTH * 1.0 / (dataArray.length/freq_scale);
    var x = 0;

    // display spectrum up to Nyquist_Frequency/10
    for (var i = 0; i < dataArray.length/freq_scale; i++) {
          var v = (dataArray[i] + 100)/50;
          var y = HEIGHT - v * HEIGHT/2;

        if(i === 0) {
            drawContext.moveTo(x, y);
          } else {
            drawContext.lineTo(x, y);
          }

          x += sliceWidth;
    }

    // last touch
    drawContext.lineTo(draw_spec.width, draw_spec.height/2);
    drawContext.stroke();

    //
    // pitch detection
    //
    // Refer to the stft_pitch.m file (MATLAB) to implement the pitch detection algorithm
    
    ///// YOUR CODE IS HERE /////
    
    /////////////////////////////////////////////////////////////////////////////////////
    pitch_gram = new Float32Array(col_comb);
    energy     = new Float32Array(col_comb);
    for (var i=0; i < col_comb ; i++){
      for (var j=0 ; j < row_comb; j++){
        // dataArray[j]: in decible
        // change to power scale
        audioArray_power = Math.pow(10,(dataArray[j]/10));
        //audioArray_power = Math.pow(audioArray_power,2) 
        if (j == 0 ){
          pitch_gram[i] = comb_filter[i][j]*audioArray_power;
          energy[i]     = sum_filter[i][j]*audioArray_power;     
        }else{
          pitch_gram[i] = pitch_gram[i]+comb_filter[i][j]*audioArray_power;
          energy[i]     = energy[i]+sum_filter[i][j]*audioArray_power;         
        }
      }

      if (i == 0){
        max_pitch_gram = pitch_gram[i];
        max_pitch_index = i;
      }else if (pitch_gram[i] > max_pitch_gram){
        max_pitch_gram = pitch_gram[i];
        max_pitch_index = i;        
      }
    }
    harmonicity = max_pitch_gram /energy [max_pitch_index];
    scale_one_index = freq_scale*(WIDTH / analyser.frequencyBinCount);
    /////////////////////////////////////////////////////////////////////////////////////    
    /////////////////////////////   

    drawContext.font = "20px Arial";
    if ( harmonicity )  // THIS SHOULD BE REPLACED WITH THE CONDITIONS FOR HARMONICITY AND ENERGY VALUES 
    {
      var detected_pitch_position = 2*scale_one_index * Math.round(pitch_range_hz[max_pitch_index]) * row_comb/context.sampleRate ; 
      drawContext.strokeText( Math.round(pitch_range_hz[max_pitch_index]) + "Hz",100,50);
      drawContext.strokeText( "harmonicity:"+ (Math.round(harmonicity*100)/100) ,100,100);
      
            
      drawContext.fillStyle = 'rgb(100,0,0)';
      drawContext.fillRect(detected_pitch_position, 0, 2, HEIGHT);
    }

    // queue for next callback
    window.requestAnimationFrame(draw_spec);
  }
  
  
 <!-------------------------------------- AUDIO INPUT MIC -------------------------------------->
  
  if (!navigator.getUserMedia)
    navigator.getUserMedia = (navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia);
                
  if (!navigator.getUserMedia)
    alert("Error: getUserMedia not supported!");
            
  // get audio input streaming         
  navigator.getUserMedia({audio: true}, onStream, onStreamError)

  // successCallback
  function onStream(stream) {
      var input = context.createMediaStreamSource(stream);
    
    // Connect graph
    input.connect(analyser);
                
    // visualize audio
    draw_spec();  
  }
  
  // errorCallback       
  function onStreamError(error) {
    console.error('Error getting microphone', error);
  }

