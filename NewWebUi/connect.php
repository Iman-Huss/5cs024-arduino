<?php
	$servername = "mi-linux.wlv.ac.uk";
	$username = "1526056";
	$password = "mysql123";
	$databasename = "db1526056";

	$conn = new mysqli($servername, $username, $password, $databasename);

	if ($conn->connect_error) {
	    die('Connection failed: ' . $conn->connect_error);
	}
?>