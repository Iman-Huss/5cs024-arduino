<?php
	include "connect.php";
	
	$var1 = $_GET['stateValve'];
	$var2 = $_GET['contDetect'];
	$var3 = $_GET['emerPush'];
	$var4 = $_GET['zone'];
	$var5 = $_GET['valveId'];
	$var6 = $_GET['site'];

	// example of updating a valve
	$sql1 = "UPDATE `Valve` SET `valveid` = '" + $var5 + " '";
	
	//example of inserting a new valve
	$sql2 = "INSERT INTO `Valve` (`valveid`, `vstatus`, `site`) VALUES ('" . $var5 . "', '" . $var1 . "', " . $var6 . ");";
	
	if ($conn->query($sql2) === TRUE) {
		echo "";
	} else echo "Error: " . $sql2 . "<br>" . $conn->error;

	$conn->close();
?>