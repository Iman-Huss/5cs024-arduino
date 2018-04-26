<?php
	Require("connect.php"); 
	
	$valve = $_POST['vid'];

	$sql = "INSERT INTO `Valve` (`valveid`, `vstatus`, `cstatus`, `site`, `zone`, `fdesc`, `eno`, `emerpush`) 
						VALUES ('" . $valve . "', 'N/A', 'N/A', 'Birmingham', 'B1', 'N/A', 'E004', 'N/A');";
	
	if ($conn->query($sql) === TRUE) {
		echo "";
	} else echo "Error: " . $sql . "<br>" . $conn->error;
	
	$conn->close();
?>