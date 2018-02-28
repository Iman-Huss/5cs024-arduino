<?php
$servername = "mi-linux.wlv.ac.uk";
$username = "1526056";
$password = "mysql123";

$conn = new mysqli($servername, $username, $password);

$sql = "SELECT * FROM `db1526056`.`LOG`";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    echo "<table><tr><th>Valve ID</th><th>Button Press Time</th><th>Status</th><th>Final Time</th></tr>";
    while($row = $result->fetch_assoc()) {
        echo "<tr><td>".$row["vid"]."</td><td>".$row["buttonpresstime"]."</td><td>".$row["vstatus"]."</td><td>".$row["finaltime"]."</td></tr>";
    }
    echo "</table>";
} else {
    echo "0 results.";
}

$conn->close();
?>

