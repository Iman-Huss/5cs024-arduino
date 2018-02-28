<?php
$servername = "mi-linux.wlv.ac.uk";
$username = "";
$password = "abdumaphia123";

// Create connection
$conn = new mysqli($servername, $username, $password);

// Check connection
//if ($conn->connect_error) {
    //die("Connection failed: " . $conn->connect_error);
//} 
//echo "Connected successfully! ";

$sql = "SELECT * FROM `db1526056`.`LOG`";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    echo "<table><tr><th>Valve ID</th><th>Button Press Time</th><th>Status</th><th>Final Time</th></tr>";
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>".$row["vid"]."</td><td>".$row["buttonpresstime"]."</td><td>".$row["vstatus"]."</td><td>".$row["finaltime"]."</td></tr>";
        // Without table:
        //echo " VALVE: " . $row["vid"]. " - DETAILS: " . " Button Press Time: " . $row["buttonpresstime"]. ", Status: " . $row["vstatus"]. ", Final Time: " . $row["finaltime"]. "<br>";
    }
    echo "</table>";
} else {
    echo "0 results.";
}

$conn->close();
?>
