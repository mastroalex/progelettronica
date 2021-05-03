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