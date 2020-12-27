const words = document.querySelector('.words');
let p = document.createElement('p');
words.appendChild(p);
	  var xhttp = new XMLHttpRequest();

window.SpeechRecognition =
  window.SpeechRecognition || window.webkitSpeechRecognition;

const recognition = new SpeechRecognition();
recognition.interimResults = true;
recognition.lang = 'en-EN';

recognition.addEventListener('result', e => {
  const transcript = Array.from(e.results)
    .map(result => result[0].transcript)
    .join('');

  p.textContent = transcript;
  if (e.results[0].isFinal) {
    p = document.createElement('p');
    words.appendChild(p);

    if (transcript.includes('еркебулан')) {
      console.log('+unicorn');
    }
	
	    if (transcript.includes('on')) {
      console.log('+on');
	      xhttp.open("GET", "http://192.168.4.1/on", true);
  xhttp.send();
    }
	
	    if (transcript.includes('off')) {
      console.log('+off');
	      xhttp.open("GET", "http://192.168.4.1/off", true);
  xhttp.send();
    }
	/*
	  var xhttp = new XMLHttpRequest();
  function on(){
    xhttp.open("GET", "http://192.168.4.1/on", true);
  xhttp.send();
   }
     function off(){
    xhttp.open("GET", "http://192.168.4.1/off", true);
  xhttp.send();
   }
	
	*/
  }
});

recognition.addEventListener('end', recognition.start);
recognition.start();


