$.ajaxSetup({timeout:1000});


navigator.getUserMedia = (navigator.getUserMedia ||
                          navigator.webkitGetUserMedia ||
                          navigator.mozGetUserMedia ||
                          navigator.msGetUserMedia);

var audioCtx = new (window.AudioContext || window.webkitAudioContext)();
var analyser = audioCtx.createAnalyser();
analyser.minDecibels = -90;
analyser.maxDecibels = -10;

analyser.smoothingTimeConstant = 0.05;
//var distortion = audioCtx.createWaveShaper();
//var gainNode = audioCtx.createGain();
//var biquadFilter = audioCtx.createBiquadFilter();
//var convolver = audioCtx.createConvolver();

var latch = false;						  
						  
var rotation = 0;
var rotationl = 0;


document.onkeydown = checkKeyDown;
function checkKeyDown(e) {
    e = e || window.event;
    if (e.keyCode == '38') {
        // up arrow
	if (latch == false) {
		TextVar = myform2.inputbox.value;
		ArduinoVar = "http://" + TextVar + ":80";
		$.get( ArduinoVar, { "mot": 40 })	;
		{Connection: close};
		latch = true;
	}
    }
    else if (e.keyCode == '40') {
        // down arrow
	if (latch == false) {
		TextVar = myform2.inputbox.value;
		ArduinoVar = "http://" + TextVar + ":80";
		$.get( ArduinoVar, { "mot": 10 })	;
		{Connection: close};
		latch = true;
	}
    }
    else if (e.keyCode == '37') {
	// left arrow
	if (latch == false) {
		TextVar = myform2.inputbox.value;
		ArduinoVar = "http://" + TextVar + ":80";
		$.get( ArduinoVar, { "mot": 20 })	;
		{Connection: close};
		latch = true;
	}
    }
    else if (e.keyCode == '39') {
        // right arrow
	if (latch == false) {
		TextVar = myform2.inputbox.value;
		ArduinoVar = "http://" + TextVar + ":80";
		$.get( ArduinoVar, { "mot": 30 })	;
		{Connection: close};
		latch = true;
	}
    }
}

document.onkeyup = checkKeyUp;
function checkKeyUp(e) {
    e = e || window.event;

    if ((e.keyCode == '38')||(e.keyCode == '40')||(e.keyCode == '37')||(e.keyCode == '39')) {
	setTimeout(doNothing, 200);
    }
}

function doNothing(){
	latch = false;
}

    $( document ).ready(function() {
	
	
					if (navigator.getUserMedia) {
				   console.log('getUserMedia supported.');
				   navigator.getUserMedia (
					  // constraints - only audio needed for this app
					  {
						 audio: true
					  },

					  // Success callback
					  function(stream) {
						 source = audioCtx.createMediaStreamSource(stream);
						 source.connect(analyser);
						 //analyser.connect(distortion);
						 //distortion.connect(biquadFilter);
						 //biquadFilter.connect(convolver);
						 //convolver.connect(gainNode);
						 //gainNode.connect(audioCtx.destination);

						 //visualize();
						 //voiceChange();

					  },

					  // Error callback
					  function(err) {
						 console.log('The following gUM error occured: ' + err);
					  }
				   );
				} else {
				   console.log('getUserMedia not supported on your browser!');
				}	
				

				
$(function(){
setInterval(soundCheck, 300);
});
		
		
					$('.movbutton').click(function() {
						var elems = document.querySelectorAll(".movbutton_click");
							[].forEach.call(elems, function(el) {
							el.classList.remove("movbutton_click");
						});
					});
					$('.mov1').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 10 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 2*18000/document.getElementById("movVel").value);
						}
					});
					$('.mov2').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 20 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 2*18000/document.getElementById("movVel").value);
						}
					});
					$('.mov3').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 30 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 2*18000/document.getElementById("movVel").value);
						}
					});
					$('.mov4').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 40 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 2*18000/document.getElementById("movVel").value);
						}
					});
					$('.mov5').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 50 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 4*18000/document.getElementById("movVel").value);
						}
					});
					$('.mov6').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 60 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 4*18000/document.getElementById("movVel").value);
						}
					});
					$('.mov7').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 70 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 1000+2*18000/document.getElementById("movVel").value);
						}
					});
					$('.mov8').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 80 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 6*18000/document.getElementById("movVel").value);
						}
					});
					$('.mov9').click(function() {
						if (latch == false) {
							$(this).addClass('movbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "mov": 90 })	;
							{Connection: close};
							latch = true;
							setTimeout(unlatch, 3*18000/document.getElementById("movVel").value);
						}
					});
					$('.facbutton').click(function() {
						if (latch == false) {
							var elems = document.querySelectorAll(".facbutton_click");
								[].forEach.call(elems, function(el) {
								el.classList.remove("facbutton_click");
							});
						}
					});
					$('.fac1').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 10 })	;
							{Connection: close};
						}
					});
					$('.fac2').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 20 })	;
							{Connection: close};
						}
					});
					$('.fac3').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 30 })	;
							{Connection: close};
						}
					});
					$('.fac4').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 40 })	;
							{Connection: close};
						}
					});
					$('.fac5').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 50 })	;
							{Connection: close};
						}
					});
					$('.fac6').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 60 })	;
							{Connection: close};
						}
					});
					$('.fac7').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 70 })	;
							{Connection: close};
						}
					});
					$('.fac8').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 80 })	;
							{Connection: close};
						}
					});
					$('.fac9').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 90 })	;
							{Connection: close};
						}
					});
					$('.fac10').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 100 })	;
							{Connection: close};
						}
					});					
					$('.fac11').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 110 })	;
							{Connection: close};
						}
					});
					$('.fac12').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 120 })	;
							{Connection: close};
						}
					});
					$('.fac13').click(function() {
						if (latch == false) {
							$(this).addClass('facbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "fac": 130 })	;
							{Connection: close};
						}
					});					
					$('.oldbutton').click(function() {
						var elems = document.querySelectorAll(".oldbutton_click");
							[].forEach.call(elems, function(el) {
							el.classList.remove("oldbutton_click");
						});
					});
					$('.old1').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 10 })	;
							{Connection: close};
						}
					});
					$('.old2').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 20 })	;
							{Connection: close};
						}
					});
					$('.old3').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 30 })	;
							{Connection: close};
						}
					});
					$('.old4').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 40 })	;
							{Connection: close};
						}
					});
					$('.old5').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 50 })	;
							{Connection: close};
						}
					});
					$('.old6').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 60 })	;
							{Connection: close};
						}
					});
					$('.old7').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 70 })	;
							{Connection: close};
						}
					});
					$('.old8').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 80 })	;
							{Connection: close};
						}
					});
					$('.old9').click(function() {
						if (latch == false) {
							$(this).addClass('oldbutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "old": 90 })	;
							{Connection: close};
						}
					});
					
					$('.olebutton').click(function() {
						var elems = document.querySelectorAll(".olebutton_click");
							[].forEach.call(elems, function(el) {
							el.classList.remove("olebutton_click");
						});
					});
					$('.ole1').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 10 })	;
							{Connection: close};
						}
					});
					$('.ole2').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 20 })	;
							{Connection: close};
						}
					});
					$('.ole3').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 30 })	;
							{Connection: close};
						}
					});
					$('.ole4').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 40 })	;
							{Connection: close};
						}
					});
					$('.ole5').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 50 })	;
							{Connection: close};
						}
					});
					$('.ole6').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 60 })	;
							{Connection: close};
						}
					});
					$('.ole7').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 70 })	;
							{Connection: close};
						}
					});
					$('.ole8').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 80 })	;
							{Connection: close};
						}
					});
					$('.ole9').click(function() {
						if (latch == false) {
							$(this).addClass('olebutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "ole": 90 })	;
							{Connection: close};
						}
					});					
					$('.bocabutton').click(function() {
						var elems = document.querySelectorAll(".bocabutton_click");
							[].forEach.call(elems, function(el) {
							el.classList.remove("bocabutton_click");
						});
					});					
					$('.boc1').click(function() {
						if (latch == false) {
							$(this).addClass('bocabutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "boc": 10 })	;
							{Connection: close};
						}
					});
					$('.boc2').click(function() {
						if (latch == false) {
							$(this).addClass('bocabutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "boc": 20 })	;
							{Connection: close};
						}
					});
					$('.boc3').click(function() {
						if (latch == false) {
							$(this).addClass('bocabutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "boc": 30 })	;
							{Connection: close};
						}
					});
					$('.boc4').click(function() {
						if (latch == false) {
							$(this).addClass('bocabutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "boc": 40 })	;
							{Connection: close};
						}
					});
					$('.boc5').click(function() {
						if (latch == false) {
							$(this).addClass('bocabutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "boc": 50 })	;
							{Connection: close};
						}
					});
					$('.boc6').click(function() {
						if (latch == false) {
							$(this).addClass('bocabutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "boc": 60 })	;
							{Connection: close};
						}
					});
					$('.boc7').click(function() {
						if (latch == false) {
							$(this).addClass('bocabutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "boc": 70 })	;
							{Connection: close};
						}
					});
					$('.boc8').click(function() {
						if (latch == false) {
							$(this).addClass('bocabutton_click');
							TextVar = myform2.inputbox.value;
							ArduinoVar = "http://" + TextVar + ":80";
							$.get( ArduinoVar, { "boc": 90 })	;
							{Connection: close};
						}
					});
					
									
									
					jQuery('.tabs .tab-links a').on('click', function(e)  {
					var currentAttrValue = jQuery(this).attr('href');
			 
					// Show/Hide Tabs
					jQuery('.tabs ' + currentAttrValue).fadeIn(400).siblings().hide();
			 
					// Change/remove current tab to active
					jQuery(this).parent('li').addClass('active').siblings().removeClass('active');
			 
					e.preventDefault();
				});
});

function unlatch() {
    //alert('Hello');
	latch = false;
	var elems = document.querySelectorAll(".movbutton_click");
	[].forEach.call(elems, function(el) {
	el.classList.remove("movbutton_click");
	});
}

function soundCheck(){
				analyser.fftSize = 256;
				var bufferLength = analyser.frequencyBinCount;
				//console.log(bufferLength);
				var dataArray = new Uint8Array(bufferLength);
				analyser.getByteFrequencyData(dataArray);
				if (dataArray[0] > document.getElementById("soundSens").value) {
					if (latch == false) {
						TextVar = myform2.inputbox.value;
						ArduinoVar = "http://" + TextVar + ":80";
						$.get( ArduinoVar, { "fac": 140 })	;
						{Connection: close};
						latch = true;
						setTimeout(unlatch, 500);
					}
				}
				//console.log(dataArray[0]);
}


function hide (elements) {
  elements = elements.length ? elements : [elements];
  for (var index = 0; index < elements.length; index++) {
    elements[index].style.display = 'none';
  }
}

function readUrlAV (form) {
    TextVar = form.inputbox.value;
	VideoVar = "http://"+TextVar+":8080/video";
	AudioVar = "http://"+TextVar+":8080/audio.opus";
	document.getElementById("video").setAttribute('data', VideoVar);
	document.getElementById("audio").setAttribute('data', AudioVar);
}
function readUrlMirror (form) {
    TextVar = form.inputbox.value;
	MirrorVar = "http://"+TextVar+":8081";
	document.getElementById("mirror").setAttribute('data', MirrorVar);
}
function testarArduino (form) {
    TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "mov": 90 })	;
	{Connection: close};
}

function saveTextAsFile()
{
    var textToSave = document.getElementById("inputTextToSave").value;
    var textToSaveAsBlob = new Blob([textToSave], {type:"text/plain"});
    var textToSaveAsURL = window.URL.createObjectURL(textToSaveAsBlob);
    var fileNameToSaveAs = document.getElementById("inputFileNameToSaveAs").value;
 
    var downloadLink = document.createElement("a");
    downloadLink.download = fileNameToSaveAs;
    downloadLink.innerHTML = "Download File";
    downloadLink.href = textToSaveAsURL;
    downloadLink.onclick = destroyClickedElement;
    downloadLink.style.display = "none";
    document.body.appendChild(downloadLink);
 
    downloadLink.click();
}
 
function destroyClickedElement(event)
{
    document.body.removeChild(event.target);
}
 
function loadFileAsText()
{
    var fileToLoad = document.getElementById("fileToLoad").files[0];
 
    var fileReader = new FileReader();
    fileReader.onload = function(fileLoadedEvent) 
    {
        var textFromFileLoaded = fileLoadedEvent.target.result;
        document.getElementById("inputTextToSave").value = textFromFileLoaded;
    };
    fileReader.readAsText(fileToLoad, "UTF-8");
}

function mouseUpSr1(angle)
{
	TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "sr1": angle })	;
	{Connection: close};
}
function mouseUpSr2(angle)
{
	TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "sr2": angle })	;
	{Connection: close};
}
function mouseUpSr3(angle)
{
	TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "sr3": angle })	;
}
function mouseUpSr4(angle)
{
	TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "sr4": angle })	;
	{Connection: close};
}
function mouseUpSr5(angle)
{
	TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "sr5": angle })	;
	{Connection: close};
}
function mouseUpSr6(angle)
{
	TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "sr6": angle })	;
	{Connection: close};
}




function mouseUpVel(speed)
{
	TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "vel": speed })	;
	{Connection: close};
}

function updateTextInput1(val) {
    document.getElementById('s1textInput').value=val;
}
function updateTextInput2(val) {
    document.getElementById('s2textInput').value=val;
}
function updateTextInput3(val) {
    document.getElementById('s3textInput').value=val;
}
function updateTextInput4(val) {
    document.getElementById('s4textInput').value=val;
}
function updateTextInput5(val) {
    document.getElementById('s5textInput').value=val;
}
function updateTextInput6(val) {
    document.getElementById('s6textInput').value=val;
}

