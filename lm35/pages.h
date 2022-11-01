const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
<title>LM35 com ESP32</title>
<meta charset="utf-8">
<style>
.card, .card2 {
     max-width: 400px;
     min-height: 250px;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}

.card {
     background: #02b875;
}

.card2 {
     background: #6A5ACD;
}

h1, h2 {
  margin: 0;
  padding: 1rem;
}

</style>
</head>

<body>
<div class="card">
  <h4>The ESP32 Update web page without refresh</h4><br>
  <h1>Temperatura: <span id="temp_1">0</span></h1><br>
  <h2>Média de temperatura: <span id="temp_1_mean">0</span></h1><br>
</div>

<div class="card2">
  <h4>The ESP32 Update web page without refresh</h4><br>
  <h1>Temperatura: <span id="temp_2">0</span></h1><br>
  <h2>Média de temperatura: <span id="temp_2_mean">0</span></h1><br>
</div>
<script>

setInterval(function() {
  getData();
}, 2000); 

function getData() {
  fetch("/readADC").then((res) => {
    res.json().then((data) => {
      const { sensor_1, sensor_1_mean, sensor_2, sensor_2_mean } = data;
      document.getElementById("temp_1").innerHTML = (sensor_1).toFixed(2) ?? "Nao recebido.";
      document.getElementById("temp_1_mean").innerHTML = (sensor_1_mean).toFixed(2) ?? "Nao recebido.";
      document.getElementById("temp_2").innerHTML = (sensor_2).toFixed(2) ?? "Nao recebido.";
      document.getElementById("temp_2_mean").innerHTML = (sensor_2_mean).toFixed(2) ?? "Nao recebido.";
    })
  });
}
</script>
</body>
</html>
)=====";