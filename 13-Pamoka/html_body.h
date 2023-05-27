const char index_html[] PROGMEM = R"rawliteral(
<html lang="lt">
<head>
<title>%ModuleName%</title>
  <meta name="viewport" content="width=device-width, initial-scale=1" charset="UTF-8">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous" rel="stylesheet" >

<link rel="icon" href="data:,">
<style type="text/css">
    h2 { font-size: 3.0rem; }
    html {font-family: Arial; display: inline-block; text-align: center;}
    .topnav { overflow: hidden; color:#1282fa; font-size: 1.5rem; font-weight:bold; margin-block-start:0.5em; margin-block-end:0.5em;}
    .content { padding: 0px; }
    .cards { max-width: 400px; margin: 0 auto; display: grid; grid-gap: 1.5rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .card.humidity { color: #0066ff; }
    .card.watering { color: #0066ff; }
    .card.parameters { color:  #003380; }
    .reading { font-size: 2.8rem; } 
    p {font-size: 1rem;line-height: 0.8;margin-bottom:0px}
	.params {font-weight:800}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .slider2 {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 10px}
    .slider2:before {position: absolute; content: ""; height: 30px; width: 30px; left: 5px; bottom: 5px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 6px}
  .myButton {
      background:linear-gradient(to bottom, #1282fa 5%, #00398f 100%);
      background-color:#1282fa;
      border-radius:6px;
      border:1px solid #337fed;
      display:inline-block;
      cursor:pointer;
      color:#ffffff;
      font-family:Arial;
      font-size:15px;
      font-weight:bold;
      padding:6px 24px;
      text-decoration:none;
  }
  .myButton:hover {
      background:linear-gradient(to bottom, #00398f 5%, #1282fa 100%);
      background-color:#00398f;
  }
  .myButton:active {
      position:relative;
      top:1px;
  }
</style>
<script>
function HumiditySlider(element) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humthres").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/hum_slider?value="+element.value, true);
  xhttp.send();
}
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 5000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 5000 ) ;
</script>
</head>
<body>
  <h2>ESP32 DHT Serveris</h2>
  <p>&nbsp</p>
  <div class="content">
	<div class="cards">
	  <div class="card humidity">
		<h2><i class="fas fa-thermometer-half" ></i>Temperatūra</h2>
		<span id="temperature">%TEMPERATURE%</span>
		<sup class="units">&deg;C</sup>
		<p>&nbsp</p>
	  </div>
    </div>
  </div> 
  <div class="content">
	<div class="cards">
	  <div class="card humidity">
		<h2><i class="fas fa-tint" ></i>Drėgnumas</h2>
		<span id="humidity">%HUMIDITY%</span>
        <sup class="units">&percnt;</sup>
		<p>Drėgnumo lygis: <span class="params"  id="humthres">%HumidityThreshold%</span> &percnt;</p>
		<input type="range" min="0" max="100" value="%HumidityThreshold%" class="slider" id="humSlider" onchange="HumiditySlider(this)"/>		
		<p>&nbsp</p>
	  </div>
    </div>
  </div> 
  <p style="position: fixed; bottom: 0; width:100%; text-align: center; font-size:0.5em;"> atsinaujina kas 5 sek.
  </p>
</body>
</html>
)rawliteral";