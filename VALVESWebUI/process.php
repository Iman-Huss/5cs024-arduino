
<?php
// Catch variables from Arduino
$var1 = $_GET['stateValve'];
$var2 = $_GET['contDetect'];
$var3 = $_GET['emerPush'];
$var4 = $_GET['zone'];
$var5 = $_GET['valveId'];
$var6 = $_GET['site'];



$servername = "mi-linux.wlv.ac.uk";
$username = "1526056";
$password = "mysql123";
$dbname = "db1526056";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// example of updating a valve table
$sql = INSERT INTO 'Log' (valveid, status, time, site, zone, fault, engineer)
	   VALUES ($var5, $var1, date(), $var6, $var4, "Steve", "Adam");

if ($conn->query($sql) === TRUE) {
    echo "Record updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}

$conn->close();
?> 