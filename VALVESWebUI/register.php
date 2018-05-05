<?php
	Require("connect.php");
	
	$first = $_POST['first'];
	$sur = $_POST['sur'];
	$user = $_POST['user'];
	$pass = $_POST['pass'];
	
	$sqlStatement = "INSERT INTO `OnlineUser` (`firstname`, `surname`, `username`, `passwrd`)
						VALUES ('" . $first . "', '" . $sur . "', '" . $user . "', '" . $pass . "');";
	
	if ($conn->query($sqlStatement) === TRUE) {
		echo "";
	} else {
		echo "Error: " . $sqlStatement . "<br>" . $conn->error;
	}
	$conn->close();
?>
