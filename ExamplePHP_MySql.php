Example (MySQLi Object-oriented)
<?php
// Catch variables from Arduino
$var1 = $_GET['stateValve'];
$var2 = $_GET['contDetect'];
$var3 = $_GET['emerPush'];
$var4 = $_GET['zone'];
$var5 = $_GET['valveId'];
$var6 = $_GET['site'];


$servername = "localhost";
$username = "username";
$password = "password";
$dbname = "myDB";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "UPDATE Valves SET valveId='" + $var5 + " '";

if ($conn->query($sql) === TRUE) {
    echo "Record updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}

$conn->close();
?> 