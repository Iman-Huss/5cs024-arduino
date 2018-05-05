<?php
	include "connect.php";

	$sql = "INSERT INTO `Valve` (`valveid`, `vstatus`, `cstatus`, `site`, `zone`, `fdesc`, `eno`, `emerpush`)
				VALUES ('V1', 'Closed', 'Full', 'Birmingham', 'A1', 'None', 'E001', 'No');";

	if ($conn->query($sql) === TRUE) {
		echo "";
	} else echo "Error updating record: " . $conn->error;

	$conn->close();
?>