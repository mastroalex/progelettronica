<?php

$servername = "localhost";

$dbname = "db_name";
$username = "username";
$password = "password";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
$sql = "SELECT id, tempmpu, angle, average, bpm, soglia, temp, hum, reading_time FROM Sensor order by reading_time desc limit 20000";
$result = $conn->query($sql);
while ($data = $result->fetch_assoc()){
    $sensor_data[] = $data;
}
$readings_time = array_column($sensor_data, 'reading_time');

$tempmpu = json_encode(array_reverse(array_column($sensor_data, 'tempmpu')), JSON_NUMERIC_CHECK);
$angle = json_encode(array_reverse(array_column($sensor_data, 'angle')), JSON_NUMERIC_CHECK);
$average = json_encode(array_reverse(array_column($sensor_data, 'average')), JSON_NUMERIC_CHECK);
$bpm = json_encode(array_reverse(array_column($sensor_data, 'bpm')), JSON_NUMERIC_CHECK);
$soglia = json_encode(array_reverse(array_column($sensor_data, 'soglia')), JSON_NUMERIC_CHECK);
$temp = json_encode(array_reverse(array_column($sensor_data, 'temp')), JSON_NUMERIC_CHECK);
$hum = json_encode(array_reverse(array_column($sensor_data, 'hum')), JSON_NUMERIC_CHECK);
$reading_time = json_encode(array_reverse($readings_time), JSON_NUMERIC_CHECK);
$result->free();
$conn->close();
?>

<!DOCTYPE html>
<html>
<meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <script src="https://code.highcharts.com/highcharts.js"></script>
  <script src="https://code.highcharts.com/modules/data.js"></script>
  <script src="https://code.highcharts.com/modules/exporting.js"></script>
  <script src="https://code.highcharts.com/modules/export-data.js"></script>
  <script src="https://code.highcharts.com/modules/accessibility.js"></script>
  <style>
    body {
      min-width: 310px;
    	max-width: 90%;
    	height: 500px;
      margin: 0 auto;
    }
    h2 {
      font-family: Arial;
      font-size: 2.5rem;
      text-align: center;
    }
  
     .containerinfo { 
 
    position: center;
    column-count: 2;
    column-width: 50%;
    padding-top: 50px;
    }
    .container2 { 
    align: center;
    position: center;
    width: 50%;
    position: relative;
      margin: auto;

    }
    
  </style>
  <body>
    <h2>Data</h2>
        <?php
$password = 'elettronica';

$pwd = isset($_GET['pwd']) ? $_GET['pwd'] : false;
if (!$pwd || $pwd != $password) {
  ?>
<form method="get" action="<?php echo $_SERVER['PHPSELF']; ?>">
<table border="0" cellspacing="0" cellpadding="10">
<?php if ($pwd !== false): ?><tr class="errore"><td colspan="3">La password inserita non è corretta!</td></tr><?php endif; ?>
<tr>
  <td>Password</td>
  <td><input type="password" name="pwd" style="width: 180px;"/></td>
  <td><input type="submit" value="Entra"/></td>
</tr>
</table>
</form>  
  <?php  
}else{
  ?>
    <div class="container2">
    <div id="chart-tempmpu" class="container"></div>
    </div>

    <div class="containerinfo">
        <div id="chart-average" class="container"></div>
        <div id="chart-soglia" class="container"></div>
    </div>

    <div class="containerinfo">
        <div id="chart-angle" class="container"></div>
        <div id="chart-bpm" class="container"></div>
    </div>

    <div class="containerinfo">
        <div id="chart-temp" class="container"></div>
        <div id="chart-hum" class="container"></div>
    </div>
   <?php  
}
?>
    
</div>

<script>

var tempmpu = <?php echo $tempmpu; ?>;
var angle = <?php echo $angle; ?>;
var average = <?php echo $average; ?>;
var bpm = <?php echo $bpm; ?>;
var soglia = <?php echo $soglia; ?>;
var temp = <?php echo $temp; ?>;
var hum = <?php echo $hum; ?>;
var reading_time = <?php echo $reading_time; ?>;


var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-tempmpu',
        zoomType: 'x',
        panning: true,
        panKey: 'shift' },
  title: { text: 'Temperature' },
  series: [{
    showInLegend: false,
    data: tempmpu
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: false }
    },
    series: { color: '#C80303' }
  },
  xAxis: { 
    type: 'datetime',
    labels: { enabled: false },
    categories: reading_time
    
  },
  yAxis: {
    title: { text: 'Temperature (Celsius)' }
    
  },
  credits: { enabled: false }
});

var chartT = new Highcharts.Chart({
  chart:{ renderTo : 'chart-temp',
        zoomType: 'x',
        panning: true,
        panKey: 'shift' },
  title: { text: 'Room Temperature' },
  series: [{
    showInLegend: false,
    data: temp
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: false }
    },
    series: { color: '#C80303' }
  },
  xAxis: { 
    type: 'datetime',
        labels: { enabled: false },
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Temperature (Celsius)' }
  },
  credits: { enabled: false }
});

var chartA = new Highcharts.Chart({
  chart:{ renderTo:'chart-angle',
           zoomType: 'x',
           panning: true,
           panKey: 'shift'},
  title: { text: 'Rotation' },
  series: [{
    showInLegend: false,
    data: angle
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: false }
    },
    series: { color: '#00CDE5' }
  },
  xAxis: {
    type: 'datetime',
        labels: { enabled: false },
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Angle (°)' }
  },
  credits: { enabled: false }
});

var chartE = new Highcharts.Chart({
  chart:{ renderTo:'chart-average',
           zoomType: 'x',
           panning: true,
           panKey: 'shift'},
  title: { text: 'EMG' },
  series: [{
    showInLegend: false,
    data: average
  }],
    plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: false }
    },
    series: { color: '#DEE500' }
  },
  xAxis: {
    type: 'datetime',
        labels: { enabled: false },
    categories: reading_time
  },
  yAxis: {
    title: { text: '' }
  },
  credits: { enabled: false }
});

var chartS = new Highcharts.Chart({
  chart:{ renderTo:'chart-soglia',
           zoomType: 'x',
           panning: true,
           panKey: 'shift'},
  title: { text: 'Threeshold' },
  series: [{
    showInLegend: false,
    data: soglia
  }],
   plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: false }
    },
    series: { color: '#E5B500' }
  },
  xAxis: {
    type: 'datetime',
        labels: { enabled: false },
    categories: reading_time
  },
  yAxis: {
    title: { text: '' }
  },
  credits: { enabled: false }
});



var chartB = new Highcharts.Chart({
  chart:{ renderTo:'chart-bpm',
           zoomType: 'x',
           panning: true,
           panKey: 'shift'},
  title: { text: 'BPM' },
  series: [{
    showInLegend: false,
    data: bpm
  }],
 plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: false }
    },
    series: { color: '#A90000' }
  },
  xAxis: {
    type: 'datetime',
        labels: { enabled: false },
    categories: reading_time
  },
  yAxis: {
    title: { text: 'BPM (bpm)' }
  },
  credits: { enabled: false }
});



var chartH = new Highcharts.Chart({
  chart:{ renderTo:'chart-hum',
           zoomType: 'x',
           panning: true,
           panKey: 'shift'},
  title: { text: 'Room Humidity' },
  series: [{
    showInLegend: false,
    data: hum
  }],
  plotOptions: {
    line: { animation: false,
      dataLabels: { enabled: false }
    }
  },
  xAxis: {
    type: 'datetime',
        labels: { enabled: false },
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Humidity (%)' }
  },
  credits: { enabled: false }
});



</script>
</body>
</html>


