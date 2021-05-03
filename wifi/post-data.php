<?php

$servername = "localhost";

// REPLACE with your Database name
$dbname = "dbname";
// REPLACE with Database user
$username = "username";
// REPLACE with Database user password
$password = "user_pw";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. If you change this value, the ESP32 sketch needs to match
$api_key_value = "APIKEY";

$api_key = $tempmpu = $angle = $average = $bpm = $soglia = $temp = $hum = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $tempmpu = test_input($_POST["tempmpu"]);
        $angle = test_input($_POST["angle"]);
        $average = test_input($_POST["average"]);
        $bpm = test_input($_POST["bpm"]);
        $soglia = test_input($_POST["soglia"]);
        $temp = test_input($_POST["temp"]);
        $hum = test_input($_POST["hum"]);
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO Sensor (tempmpu, angle, average, bpm, soglia, temp, hum)
        VALUES ('" . $tempmpu . "', '" . $angle . "', '" . $average . "','" . $bpm . "','" . $soglia . "','" . $temp . "','" . $hum . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}