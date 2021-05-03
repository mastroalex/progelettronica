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
    //title: { text: 'Temperature (Fahrenheit)' }
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
    //dateTimeLabelFormats: { second: '%H:%M:%S' },
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
    //dateTimeLabelFormats: { second: '%H:%M:%S' },
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
    //dateTimeLabelFormats: { second: '%H:%M:%S' },
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
    //dateTimeLabelFormats: { second: '%H:%M:%S' },
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
    //dateTimeLabelFormats: { second: '%H:%M:%S' },
        labels: { enabled: false },
    categories: reading_time
  },
  yAxis: {
    title: { text: 'Humidity (%)' }
  },
  credits: { enabled: false }
});



</script>